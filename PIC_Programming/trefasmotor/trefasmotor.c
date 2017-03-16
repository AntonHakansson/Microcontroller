/*
--- Dimensionering av transistor-switchen

    För att NPN transistorn ska leda måste två villkor uppfyllas
      1. Emittorn ska vara mer positiv än kollektorn
      2. Potentialskillnaden mellan basen och kollektorn ska vara ~0.6V

    Första villkoret är uppfyllt där Emittorn

    För att uppfylla andra villkoret så vill vi mata transistorns bas med 0.6V
    och vill därför ha ett spänningfall från PIC-utgången som ligger 5V.
    Spänningsfallet vi söker blir således 5.0 - 0.6 = 4.4V.
    Vi tilldelar ett rimligt värde för strömmen och låter:
      I = 2mA
    Vi får att:
      R = U/I = 4.4/0.02 = 220 ohm

    Vi avrundar upp resistansen till 330 ohm vilket finns tillgängligt i
    laborationssalen.

--- Vad som är viktigt att kontrollera när man väljer ett relä till en viss applikation

    Den absolut viktigaste tekniska specificationen är ett reläs brytförmåga.
    Brytförmågan beskriver den maximal lasten man kan ha under brytningstillfället.
    Om man överstiger denna gräns finns risken att en ljusbåge bildas som i längden
    bränner sönder kontaktpunkterna eller under extrema fall svetsar fast
    kontaktbläcken.

--- En liten förklaring av trefasmotorns funktion

    Den grundläggande principen bygger på nätets tre faser som förskjutna 120
    grader sinns i mellan. Faserna ansluts till spolar statorn.
    I trefasmotorns rotor går rotorns ledarräls. Då dessa utsätts för statorns
    varierande magnetfält induceras en spänning som driver ström genom rotorledarna.
    Den inducerade spänningen ger upphov till ett magnetfält som fångas upp av
    rotorns roterande magnetfält.

    se http://28oa9i1t08037ue3m1l0i861.wpengine.netdna-cdn.com/wp-content/uploads/2015/05/inductionmotoranimation.gif
*/

// =============================================================================
// I/O configuration
// =============================================================================

// Inputs
static char START_PORT at PORTB;
static char START_BIT = 5;

static char STOPP_PORT at PORTB;
static const char STOPP_BIT = 4;

// Outputs
sbit START_OUT at PORTC.B5;
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
