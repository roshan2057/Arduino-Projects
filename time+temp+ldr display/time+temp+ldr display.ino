#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);



#define ldr 6 // Input for ldr
int value; // Place to store read ldr value
#define relay 10



#include "LiquidCrystal.h"
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int cs=9;
const int contrast = 100;
int h=12;
int m=59;
int s=45;
int flag=1;
int button1;
int button2;
int hs=8;
int ms=9;
const int Time_light=150;
int bl_TO=Time_light;
int bl=10;
const int backlight=120;
static uint32_t last_time, now = 0;


void setup()
{
    Serial.begin(9600);
    pinMode(ldr, INPUT);  
    pinMode(relay, OUTPUT);
      lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Time:");
   lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print("Temp:");
   lcd.setCursor(9, 1);
  // Print a message to the LCD.
  lcd.print("Hum:");
  dht.begin();
  pinMode(hs,INPUT_PULLUP);
  pinMode(ms,INPUT_PULLUP);
  analogWrite(cs,contrast);
  analogWrite(bl,backlight);
  now=millis(); 

}


void loop()
{
  //HTD 11
   int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();

  //ldr
value = digitalRead(ldr);
    Serial.println(value);
    delay(200);
if (value == 1) 
  { 
    //relay on
    Serial.println("on");
        digitalWrite(relay, LOW);
 
  }
  else {
    Serial.println("off");
           digitalWrite(relay, HIGH);
   
  }  
  
  Serial.print("Humidity: ");
     lcd.setCursor(13, 1);
  // Print a message to the LCD.
  lcd.print(humidity);
  Serial.print(humidity);
    lcd.setCursor(15, 1);
 lcd.print("%");
  Serial.print("Temperature: ");
     lcd.setCursor(5, 1);
  // Print a message to the LCD.
  lcd.print(temperature);
  Serial.print(temperature);  
     lcd.setCursor(7, 1);
 lcd.print("C");

  lcd.setCursor(0,0);

 lcd.print("Time:");
 if(h<10)lcd.print("0");
 lcd.print(h);
 lcd.print(":");
 if(m<10)lcd.print("0");
 lcd.print(m);
 lcd.print(":");
 if(s<10)lcd.print("0");
 lcd.print(s);

 if(flag==0) lcd.print(" AM");
 if(flag==1) lcd.print(" PM");

for ( int i=0 ;i<5 ;i++)
{

  while ((now-last_time)<200)
  {
    now=millis();
  }
 last_time=now;
 button1=digitalRead(hs);
 button2=digitalRead(ms);
 if(  ((button1==0)|(button2==0)) & (bl_TO==1)  )
 {
  bl_TO=Time_light;
  analogWrite(bl,backlight);
  while ((button1==0)|(button2==0))
  {
   button1=digitalRead(hs);
   button2=digitalRead(ms);
  }
 }
 else
 {
  if(button1==0){
   h=h+1;
   bl_TO=Time_light;
   analogWrite(bl,backlight);
  }

 if(button2==0){
  s=0;
  m=m+1;
  bl_TO=Time_light;
  analogWrite(bl,backlight);
  }
 if(s==60){
  s=0;
  m=m+1;
 }
 if(m==60)
 {
  m=0;
  h=h+1;
 }
 if(h==13)
 {
  h=1;
  flag=flag+1;
  if(flag==2)flag=0;
 }


 if((button1==0)|(button2==0))
 {
  lcd.setCursor(0,0);
  lcd.print("Time:");
  if(h<10)lcd.print("0");
  lcd.print(h);
  lcd.print(":");
  if(m<10)lcd.print("0");
  lcd.print(m);
  lcd.print(":");
  if(s<10)lcd.print("0");
  lcd.print(s);

  if(flag==0) lcd.print(" AM");
  if(flag==1) lcd.print(" PM");
}
}
}

 s=s+1;
 if(s==60){
  s=0;
  m=m+1;
 }
 if(m==60)
 {
  m=0;
  h=h+1;
 }
 if(h==13)
 {
  h=1;
  flag=flag+1;
  if(flag==2)flag=0;
 }
}
