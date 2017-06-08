/*
  Example for different sending methods
  
  https://github.com/sui77/rc-switch/
  
*/

#include <RCSwitch.h>

#define MAX_LEN 255

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);
  Serial.println("Waiting for input");
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);

  // Optional set pulse length.
  mySwitch.setPulseLength(180);  
}

void loop() {
  int i = 0;
  char recvChars[MAX_LEN] = {};
  while(true){
    if(Serial.available())
    {
      char input = Serial.read();
      recvChars[i] = input;
      i++;
      if( input == '\n' || input == '\r')
      {
        Serial.println("Recieved Input\n");
        delay(100);
        break;
      }
      if(i == 254){
        i = 0;
      }
    }
  }
 unsigned long code = getCodes(recvChars, i);

  /* Same switch as above, but using binary code */
  mySwitch.send(code, 24);
  Serial.println("sent code: " + String(code)+ "\n");
  //delay(1000);
}

unsigned long getCodes(char crypted[], int len){
 unsigned long code = 0;
 int pos = 0;
 String preFix = "Send:";
 char preFixChar[MAX_LEN] = {};
 int preFixLength = preFix.length();
 preFix.toCharArray(preFixChar, 255);

 for(int i = 0; i < preFixLength; i++){
  if (crypted[i] != preFixChar[i])
    return 0;
 }
 
 for(int i = len-2; i >= preFixLength; i--){
   int val = crypted[i] - '0';

   if(val < 10 || val >= 0){
      unsigned long part = val * powerto(10,pos);
      code += part;
      pos++; 
   }
   else {
    Serial.println("FUCKING WRONG CONVERSATION BULLSHIT\n");
    return -1;
   }
 }
 //Serial.println("recieved code" + String(code));
  
 return code;
}
unsigned long powerto(int x, int y){
  unsigned long res = 1;
  for (int i = 0; i < y; i++)
  {
     res *= x;
  }
  return res;
}




