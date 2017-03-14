sbit LCD_RS at RC4_bit; // RS på LCD: n ansluts till B4 på PIC:en
sbit LCD_EN at RC5_bit; // E(Enable på LCD: n ansluts till B5 på PIC:en

sbit LCD_D4 at RC0_bit; // D4 på LCD: n ansluts till B0 på PIC:en
sbit LCD_D5 at RC1_bit; // D5 på LCD: n ansluts till B1 på PIC:en
sbit LCD_D6 at RC2_bit; // D6 på LCD: n ansluts till B2 på PIC:en
sbit LCD_D7 at RC3_bit; // D7 på LCD: n ansluts till B3 på PIC:en

// Tell mirco processor how it is connected to the LCD display
sbit LCD_RS_Direction at TRISC4_bit;
sbit LCD_EN_Direction at TRISC5_bit;
sbit LCD_D4_Direction at TRISC0_bit;
sbit LCD_D5_Direction at TRISC1_bit;
sbit LCD_D6_Direction at TRISC2_bit;
sbit LCD_D7_Direction at TRISC3_bit;

// =======================================================================================================================
void init() {
  OSCCON = 0b01110111;
  TRISA = 0xFF;
  TRISB = 0x0F;

  ANSEL = 0b00000010;   // Enable ADC converter on PA0
  ANSELH = 0;           // Disable ADC converter for pins.
  ADCON1.VCFG0 = 1;     // Use Vref+ as ref for ADC

  // Hardware setup
  Lcd_Init();
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);
}

// =======================================================================================================================
unsigned int getTemp() {
  unsigned long int tempVal;
  tempVal = ((ADC_READ(1) >> 2)*4706);
  return tempVal/1000;
}

void update() {
  char tempStr[11];
  IntToStr(getTemp(), tempStr);
  LCD_OUT(1, 1, tempStr);
  LCD_OUT_CP("\xDFC");

  IntToStr((ADC_READ(1)>>2), tempStr);
  LCD_OUT(2, 1, tempStr);
  delay_ms(100);
}

// =======================================================================================================================
void main() {
int t;
  init();

  t= 5;
  t = 10/(5-t);
  while (1) {
    update();
  }
}