/*
  Имитатор модема
  Arduino Nano 328P old BootLoader - в vscode прошивается
  to github
*/

#include "cvv_include.h";
int count = 0;
byte buf[1024];
String cmd;
bool ate0 = true;
int error = 0;
bool Connected = false; //todo

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(100);
  //sp("Run serial 9600 echo"); spn
  sp("Run serial 9600 modem imitator v1\r\nSYSSTART^");
  spn
    digitalWrite(LED_BUILTIN, HIGH);
  delay(50);  // wait for a second
  digitalWrite(LED_BUILTIN, LOW);
}

int countplus = 0;
void loop() { //as while()
  delay(10);

  //echo
  // if (Serial.available() > 0) {
  //   digitalWrite(LED_BUILTIN, HIGH);
  //   byte incomingByte = Serial.read();
  //   Serial.print((char)incomingByte); sp("_"); //echo
  // }
  // count++; //  sp(count); sp_
  // digitalWrite(LED_BUILTIN, LOW);

  
  //modem

  while (Serial.available() > 0) {
    byte b = Serial.read();
    ///if(ate0){ sp((char)(b)); } //echo

    if (Connected)
    {
      sp(b); //echo
      if (b == '+')countplus++; else countplus = 0;
      if (countplus >= 3){
        Connected = false;
        sp("\r\nOK\r\n"); 
      }
      continue;
    }

    if (b == '\n') {
      buf[count] = 0;
      buf[count - 1] = 0;
      cmd = buf;
      count = 0;
      continue;
    }
    
    //old rx +++
    // if (b == '+'){
    //   if (count >= 2 && (buf[count - 1] == '+') && (buf[count - 2] == '+'))
    //   {
    //     Connected = false;
    //     sp("\r\nOK\r\n"); 
    //     count = 0;
    //     continue;
    //   }
    // }

    buf[count++] = b;
    delay(5);
  }

  if (cmd.length() > 0) {
    // sp(cmd.length()); sp_
    // if(ate0){ sp(cmd); spn } //echo

    cmd.toLowerCase();

    if(cmd == "at" || cmd == "atz" || cmd == "ath") // if (cmd == "AT" || cmd == "at")
    {
      sp("\r\nOK\r\n"); // +++ без \n
    }
    else if(cmd.indexOf("atd") >= 0)
    {
      delay(5555);
      sp("\r\nCONNECT 9600 RLP\r\n");
      Connected = true;
    }
    else if(cmd == "ate0" || cmd == "atze0")
    {
      ate0 = false; 
      if(error > 0){error--; sp("\r\nQQate0\r\n");} else sp("\r\nOK\r\n");
    }
    else if(cmd == "ate1")
    {
      ate0 = true; sp("\r\nOK\r\n");
    }
    else if(cmd == "at+creg?")
    {
      sp("\r\nCREG: 0,1r\r\nOK\r\n");
    }
    else sp("\r\nERROR\r\n");
    
    // sp("\r\nOK\r\n");
    cmd = "";
  }

  /*
  char bb = 'a';
  for(int n = 0; n < 10; n++)
  {
    sp(bb++);
    // delay(10);
  }
   sp("\r\n");
  // sp("-!");
  delay(2000);
  */

}
