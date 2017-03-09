void init();
void custom_delay_ms(unsigned int milliseconds);

void main() {
   char phases[8],            // Array that stores all phases of step motor
        phaseIndex=0,         // Variable that stores the current phase
        ad0=0,                // Digital value read from potentiometer
        motorDir=0,          // Variable that signifies the directoin of the motor
        motorSpeed=0;        // Stores the speed of the motor

   init();                    // Call our init function

   // Set Portb configuration for the different phases
   phases[0] = 0b00000001;
   phases[1] = 0b00000101;
   phases[2] = 0b00000100;
   phases[3] = 0b00000110;
   phases[4] = 0b00000010;
   phases[5] = 0b00001010;
   phases[6] = 0b00001000;
   phases[7] = 0b00001001;

   while(1) {
      ad0 = (ADC_READ(0)>>2);                   // Read value from potentiometer as 8 bit value
      motorDir = (ad0 > 127) ? 1 : -1;         // Based on read value calculate direction
      motorSpeed = 128-abs(ad0-127);           // calculate speed of motor ranging from 0-128

      phaseIndex = (phaseIndex+motorDir)%8;    // Step through the different phases based on motor direction
      PORTB = phases[phaseIndex];               // Set PortB to the current phase
      my_delay_ms(20+motorSpeed);              // Give motor some delay based of motor speed
   }
}


void init() {
   OSCCON = 0b01110111;  // Set Clock Frequency 8Mhz

   TRISA = 0xFF;         // Set PortA as inputs
   TRISB = 0;            // Set PortB as outputs

   ANSEL = 0b00000001;   // Enable ADC converter on PA0
   ANSELH = 0;           // Disable ADC converter for pins.
}

// Custom delay_ms that accepts a non-constant value.
void custom_delay_ms(unsigned int milliseconds) {
  while(milliseconds > 0) {
    delay_ms(1);
    milliseconds--;
  }
}
