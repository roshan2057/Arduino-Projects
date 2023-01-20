//use irrevdemo to find hexcode


#include <IRremote.h>
//Define PIN constant
const int switch_1 = 7;
const int switch_2 = 8;
int RECV_PIN = 11;

int toggleState_1 = 0; //Define integer to remember the toggle state for switch 1
int toggleState_2 = 0; //Define integer to remember the toggle state for switch 2

//Define IR receiver and Result Objects
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Enable the IR receiver
   pinMode(switch_1, OUTPUT);
   pinMode(switch_2, OUTPUT);
}


void all_SwitchOff(){
  digitalWrite(switch_1, LOW); // turn off switch 1
                  toggleState_1 = 0;
delay(100);
 digitalWrite(switch_2, LOW); // turn off switch 2
                  toggleState_2 = 0;
delay(100);
}





void loop() {
  if (irrecv.decode(&results)) {

    switch(results.value){
      case 0x10EFA956:        // 10EFA956 = Hex code for IR remote button 1 (change this)
                if(toggleState_1 == 0){
                  digitalWrite(switch_1, HIGH); // turn on switch 1
                  toggleState_1 = 1;
                  }
                else{
                  digitalWrite(switch_1, LOW); // turn off switch 1
                  toggleState_1 = 0;
                  }
                  delay(100);
      break;
      case 0x10EF9966:          // 10EF9966 = Hex code for IR remote button 2 (change this)
                if(toggleState_2 == 0){
                  digitalWrite(switch_2, HIGH); // turn on switch 2
                  toggleState_2 = 1;
                  }
                else{
                  digitalWrite(switch_2, LOW); // turn off switch 2
                  toggleState_2 = 0;
                  }
                  delay(100);
      break;
      case 0x10EFB946: //(change this)
               all_SwitchOff(); 
      break;
     
      default : break;      
      }    
    irrecv.resume(); // Receive the next value
  }  
}