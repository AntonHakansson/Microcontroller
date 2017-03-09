void init();

void main()
{
   int  ad1_dir,   // Variable for storing the analog value from potentiometer,
                   // ranging from -127 to 128 to specify direction and speed of motor.
        ad1_abs;   // The absolute value of ad1_dir, specifying the speed of the motor.
                   // ranges from 0-254
        
   init();         // Initialize our micro-controller
   
   while(1)
   {
      ad1_dir = (Adc_Read(1)>>2)-127;      // Convert analog value of potentiometer
                                           // to a 8 bit digital value.
                                           // subtract 127 so value ranges from -127-128
                                           
      ad1_abs =  min(abs(ad1_dir), 127)*2; // Convert ad1_dir to it's absolute value, ranging from 0-254
      
      PWM1_Set_Duty(ad1_abs);              // Set the duty relative to potentiometer

      if(ad1_dir > 0)                      // If the value's positive rotate anti-clockwise
         PORTB = 0b00000100;
      else                                 // If the value equals zero, reverse direction.
         PORTB = 0b00000010;
        
      if(ad1_abs>70)                       // If speed reaches a certain value, turn on the respective LEDs.
         PORTB.f3 = 1;
      if(ad1_abs>160)
         PORTB.f4 = 1;
      if(ad1_abs>220)
         PORTB.f5 = 1;
   }
}


void init()
{
   OSCCON = 0b01110111;  // Set Clock Frequency 8Mhz

   C1ON_bit = 0;         // Disable comparators
   C2ON_bit = 0;

   TRISC = 0;            // Assign PORTC pins as output, used for PWM
   TRISB = 0;            // Assign PORTB as outputs, bits 1-2 for motor direction and 3-5 for RPM meter.
   TRISA = 0xff;         // Assign PORTA as input, used to read analog value from potentiometer.
   
   ADCON1 = 0b10000000;  //
   ANSEL = 0b00000010;   // Enable ADC converter for second pin on PORTA
   ANSELH = 0;           // Disable ADC converter for pins.

   PWM1_Init(3000);      // Initialize PWM with a frequency of 3000 Hz
   PWM1_Start();         // Start and output PWM, active the whole time.
   PWM1_Set_Duty(127);   // For now set the duty time to 50%
}