/*
  - Dimensionering av transistor-switchen

    Potentialskillnaden mellan emittorn och kollektorn är 5v där emittorn går
    till jord och på så vis är mer negativ än kollektorn 

*/

// =============================================================================
// I/O configuration
// =============================================================================
static char START_PORT at PORTB;
static char START_BIT = 5;
sbit START_OUT at PORTC.B5;

static char STOPP_PORT at PORTB;
static const char STOPP_BIT = 4;
sbit STOPP_OUT at PORTC.B4;

// =============================================================================
// Constants
// =============================================================================
// Require a button to be held down for X ms
char buttonDownThreashold = 150;

// =============================================================================
// Program
// =============================================================================
void init() {
  OSCCON = 0b01110111;  // Set clock to 8 Mhz
  ANSEL = ANSELH = 0;   // Disable Analog to digital

  // Disable comparators
  C1ON_bit = 0;
  C2ON_bit = 0;

  // Configure ports as output by default
  TRISC = PORTB = TRISA = 0;

  // Configure START and STOPP as inputs
  START_PORT |= 1 << START_BIT;
  STOPP_PORT |= 1 << STOPP_BIT;

  // Enable weak pull up for START & STOPP inputs
  OPTION_REG.NOT_RBPU = 0;
  WPUB |= 1 << START_BIT;
  WPUB |= 1 << STOPP_BIT;
}

void update() {
  // Read I/O and output result for START and STOPP
  START_OUT = Button(&START_PORT, START_BIT, buttonDownThreashold, 0);
  STOPP_OUT = Button(&STOPP_PORT, STOPP_BIT, buttonDownThreashold, 0);
}

void main() {
  init();

  for(;;) {
   update();
  }
}
