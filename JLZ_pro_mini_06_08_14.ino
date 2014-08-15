#include <irremote.h>
// arduino pro mini
// !!!scatch need IRrecv lib!!!

#define CenterPinValue 50
#define UpPinValue 10
#define DownPinValue 1000
#define ButtonOpenCode 0xDAEA83EC
#define ButtonCloseCode 0x2BAFCEEC
#define ButtonUpCode 0xFF9867
#define ButtonDownCode 0xFF6897

int motorpin1 = 8;
int motorpin2 = 9;
int potPin = A0;
int led = 13;
int IR = 6;

IRrecv irrecv(IR);
decode_results results;

void setup()
{
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
  pinMode(IR, INPUT);

  digitalWrite(motorpin2, LOW);
  digitalWrite(motorpin1, LOW);
  Serial.begin(9600); 
  irrecv.enableIRIn();
}

void open()
{
  while((analogRead(potPin)<=DownPinValue)and(analogRead(potPin)>=UpPinValue))
  {
    digitalWrite(motorpin1, LOW);
    digitalWrite(motorpin2, HIGH);
  }
  digitalWrite(motorpin2, LOW);
  digitalWrite(motorpin1, LOW); 
}

void close()
{
  while((analogRead(potPin)>=0)and(analogRead(potPin)<=CenterPinValue))
  {
    digitalWrite(motorpin1, HIGH);
    digitalWrite(motorpin2, LOW);
  }
  digitalWrite(motorpin2, LOW);
  digitalWrite(motorpin1, LOW); 
}  

void up()
{
  if((analogRead(potPin)>0)and(analogRead(potPin)<DownPinValue))
  {
    digitalWrite(motorpin2, LOW);
    digitalWrite(motorpin1, HIGH);
    delay(10);
  }
  digitalWrite(motorpin2, LOW);
  digitalWrite(motorpin1, LOW); 
}

void down()
{
  if((analogRead(potPin)<DownPinValue)and(analogRead(potPin)>UpPinValue))
  {
    digitalWrite(motorpin1, LOW);
    digitalWrite(motorpin2, HIGH);
    delay(10);
  }
  digitalWrite(motorpin2, LOW);
  digitalWrite(motorpin1, LOW); 
}



void loop()
{

  if (irrecv.decode(&results)) {
    // receved IR commands
    // Serial.print("0x");
    // Serial.println(results.value, HEX);
    // delay(CenterPinValue);

    if((results.value == 0xFF30CF)or(results.value == ButtonOpenCode))
    {
      // Serial.println("Button 1");
      // Serial.println("UP");
      open();     

    }
    if((results.value == 0xFF18E7)or(results.value == ButtonCloseCode))
    {
      // Serial.println("Button 2");
      // Serial.println("UP");
      close();     
    }
    if(results.value == ButtonUpCode)
    {
      // Serial.println("Button Up");
      // Serial.println("UP");
      up();     
    }
    if(results.value == ButtonDownCode)
    {
      // Serial.println("Button down");
      // Serial.println("DOWN");
      down();     
    }
    irrecv.resume();// Receive the next value
  }
  //potentiometer value
  //Serial.println(analogRead(potPin));
}

