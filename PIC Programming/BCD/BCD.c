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
  char seed;

  OSCCON = 0b01110111;
  ANSEL = ANSELH = 0;
  TRISB = 0x0F;

  // Hardware setup
  Lcd_Init();
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);

  Lcd_Rs = 0;
  Lcd_Cmd(64);
  Lcd_Rs = 1;

  LCD_Chr_Cp(0b00000000);
  LCD_Chr_Cp(0b00001110);
  LCD_Chr_Cp(0b00011111);
  LCD_Chr_Cp(0b00011111);
  LCD_Chr_Cp(0b00011111);
  LCD_Chr_Cp(0b00001110);
  LCD_Chr_Cp(0b00000000);
  LCD_Chr_Cp(0b00000000);

  Lcd_Rs = 1;
}

// =======================================================================================================================
int clamp(int val, int min, int max) {
  return (val > min) ? min : ((val > max) ? max : val);
}

// =======================================================================================================================
void update() {
  char  i,
        pos[2]; // Index 0 => row, index 1 => col

  for (i=0; i<2; i++) {
    PORTB = (0b00010000 << i) | PORTB&0x0F;
    delay_us(500);

    pos[i] = (PORTB&0x0F)+1, 1, 9;
    LCD_Chr(4, 18+i, (PORTB&0x0F)+'0');
  }

  LCD_Chr(pos[0], pos[1], 0);
}

// =======================================================================================================================
void main() {
  init();

  while (1) {
    update();
  }
}
