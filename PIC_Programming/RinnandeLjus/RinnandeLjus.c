void init();
void blink();
void MoveSnake();
int headx,heady;
int kroppx[10];
int kroppy[10];

void main()

{
 init();

 for(;;)
 {
  blink();


  for(;;)
  {
  //upp
  if(porta.f0==1)
  { heady++};
  //ner
  if(porta.f1==1)heady--;
  //h�ger
  if(porta.f2==1)headx++;
  //v�nster
  if(porta.f3==1)headx--;
  MoveSnake(1, 0);


  }
  }
}

void MoveSnake(char x, char y)
{
int i;
for(i=9; i<=0; i--)
{
 if(kroppx[i] == -1 || kroppy[i] == -1)
              continue;

  kroppx[i] = (i==0)? headX : kroppx[i-1];
  kroppy[i] = (i==0)? headY : kroppy[i-1];
}
}

void blink()
{
int s;
          for(s=0; s<5;s++)
  {
      portb=0xff;
      portc=0xff;
      delay_ms(1000);
      portb=0;
      portc=0;
  }
}
void init()
{
     TrisA=0b11110000; //port a ing�ng
     trisB=0x00; //port b utg�ng
     trisc=0x00;       //port c utg�ng
     osccon=0b01110111; //oscillator 8 mhz
     //PORTA= 0b11111111; // PORTA ING�NG
     PORTB=0b00000000;  //PORTB utg�ng
     ANSEL=0b00000000;  //0=digitarl ing�ng, 1=analog ing�ng
     ANSELH=0b00000000;  //0=digital ing�ng, 1=analog ing�ng
     //ansel=analog select
}