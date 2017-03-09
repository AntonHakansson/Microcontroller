void init();
void displayNum(int num);
char getDigit(char digit);

void main()
{
   int  potValue = 0;

   init();         // Initialize our micro-controller

   while(1)
   {
      potValue = (Adc_Read(1)>>2);      // Convert analog value of potentiometer
      PWM1_Set_Duty(potValue);          // Set the duty relative to potentiometer
      displayNum(8888);
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

int _pow(char exp) {
  static const char powSize = 4;
  static char powValues[powSize] = {
    1, 10, 100, 1000
  };
  return powValues[exp%powSize];
}
void displayNum(int num) { // 8888 / 10^3 => 8
                           // (8888 /  10^2)%10 => 8
  static char digit = 0;

  PORTB = getDigit((num/(int)_pow(3-digit))%10);
  PORTC = (0b10000000 >> digit);

  digit = ++digit%4;
}

char getDigit(char digit) {
  static char digitConfiguration[10] = {
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111100,
    0b00000111,
    0b01111111,
    0b01100111
  };
  return digitConfiguration[digit%10];
}