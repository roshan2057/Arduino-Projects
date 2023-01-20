#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

const char* ssid = "IOT";
const char* password = "11112222";

// +international_country_code + phone number
// Portugal +351, example: +351912345678
String phoneNumber = "your phone number";
String apiKey = "api code";


#define gas 4 // Input for HC-S501
int Value; // Place to store read PIR Value


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
  pinMode(gas, INPUT);
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
   Value = digitalRead(gas);
    Serial.println(Value);
    delay(400);
if (Value == 1) 
  { 
    Serial.println("check");
      // Send Message to WhatsAPP
  sendMessage("hey whats upp!!!");
     delay(4000);
  }
  else {
    Serial.println(Value);
     
   
  }
 

}