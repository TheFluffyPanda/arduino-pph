/******************************************
 *Website: www.elegoo.com
 * 
 *Time:2017.12.12
 *
 ******************************************/
int Led=13;//define LED port
int redLed=12;//define Red LED port
int buttonpin=7; //define switch port
;int  val;//define digital variable val
void  setup()
{
pinMode(Led,OUTPUT);//define LED as a output port
pinMode(redLed,OUTPUT);//define LED as a output port
pinMode(buttonpin,INPUT);//define switch as a output port
}
void  loop()

{ val=digitalRead(buttonpin);//read the value of the digital interface 3 assigned to val 
if(val==HIGH)//when the switch sensor have signal, LED blink
{
digitalWrite(Led,LOW);
digitalWrite(redLed,HIGH);
}
else
{
digitalWrite(Led,HIGH);
digitalWrite(redLed,LOW);
}
}
