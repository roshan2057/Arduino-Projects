#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

const char* ssid = "WI-FI";
const char* password = "11112222";

String phoneNumber = "your phone number";
String apiKey = "api code";



int pir = 16; //pir sensor
int motionvalue; //pir value
int gas = A0;
int gasvalue;
int led = 5;
int buzzer = 4;

void sendMessage(String message){

  // Data to send with HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}



void setup() {
   Serial.begin(115200); // start serial communication at 9600bps
 pinMode(led, OUTPUT);
 pinMode(buzzer, OUTPUT);
 digitalWrite(led, LOW);
 digitalWrite(buzzer, HIGH);
 
Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
}

void loop() {
  //motion
  motionvalue = digitalRead(pir);
Serial.println(motionvalue);


if(motionvalue == 1){
   sendMessage("Someone is there in your room");
Serial.println("motion detected message send sucessfully");

Serial.println(" Motion detected ");

 

for(int i=1; i<=5; i++)
{
digitalWrite(led, HIGH);
delay(500);
digitalWrite(led, LOW);
delay(300);
digitalWrite(led, HIGH);
delay(500);
digitalWrite(led, LOW);
delay(300);
}
}
digitalWrite(led, LOW);



//gas
gasvalue = analogRead(gas);
Serial.println(gasvalue);
delay(600);

if(gasvalue > 150){
  sendMessage("Gas leaked and exjust fan is started");
Serial.println("gas massage sent");

 
delay(100);
}


while(gasvalue >150){
digitalWrite(buzzer, LOW);
Serial.println(" gas leaked ");
gasvalue = analogRead(gas);
delay(600);
}
digitalWrite(buzzer, HIGH);


 digitalWrite(13, LOW);
delay(300);
 digitalWrite(13, HIGH);
}






