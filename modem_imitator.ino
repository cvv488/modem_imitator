/*
  Имитатор модема
  Arduino Nano 328P old BootLoader - 
  
  vscode, github
  прошивается в Arduino IDE, platformio не работает?

    v2  добавлена отправка no carrier при молчании
    v3  at+cbst
    v5  +connect try
*/

#include "cvv_include.h";
#include "ek270.h";

int countBuf = 0;
byte buf[1024];
bool bufDone = false;

String cmd;
bool atEcho = true;
int error = 0;

bool Connected = false;
int ConnectionLimitCount, ConnectionLimit = 200; //nc при молчании 20c
int ConnectTry; //коннект с попытьки
int count = 0;

void setup()
{
    //Serial.begin(115200);
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    delay(100);
    // sp("Run serial 9600 echo"); spn
    sp("Run serial 9600 modem imitator v5 \r\nSYSSTART^");
    spn
        digitalWrite(LED_BUILTIN, HIGH);
    delay(50); // wait for a second
    digitalWrite(LED_BUILTIN, LOW);
}

int countplus = 0;
void loop() // as while()
{
    delay(100); count++;

    if (Connected)
    {
        if (--ConnectionLimitCount < 0)
        {
            Connected = false;
            sp("\r\nNO CARRIER\r\n");
        }

        if (bufDone)
        {
            // sp(" if (bufDone)");
            bufDone = false;
            io270(buf, countBuf);
            countBuf = 0;
        }
    }

    while (Serial.available() > 0)
    {
        byte b = Serial.read(); 
        count = 0;

        if (Connected)
        {
            ConnectionLimitCount = ConnectionLimit; // отсрочить
            if (b == '+') countplus++;
            else countplus = 0;
            if (countplus >= 3)
            {
                Connected = false; sp("\r\nOK\r\n");
                continue;
            }
//          sp("->"); sp((char)(b)); sp_ // echo
        } else
        {
            if (atEcho) sp((char)(b)); // echo

            if (b == '\n')
            {
                buf[countBuf] = 0;
                buf[countBuf - 1] = 0;
                cmd = String((char*)buf);
                countBuf = 0;
                continue;
            }
        }

        buf[countBuf++] = b;
        delay(5);
    }

    if(count == 10)
    {
        bufDone = true; //sp(" bufDone = true;");
    }

    if (cmd.length() > 0)
    {
        // sp(cmd.length()); sp_
        // if(atEcho){ sp(cmd); spn } //echo

        cmd.toLowerCase();

        if (cmd == "at" || cmd == "atz" || cmd == "ath") // if (cmd == "AT" || cmd == "at")
        {
            sp("\r\nOK\r\n"); // +++ без \n
        }
        else if (cmd.indexOf("atd") >= 0)
        {
            if(++ConnectTry < 2)
            {
                sp("\r\nNO CARRIER\r\n");
            }
            else
            {
                //delay(3333);
                sp("\r\nCONNECT 9600 RLP\r\n");
                Connected = true; ConnectTry = 0;
            }
            
            
            ConnectionLimitCount = ConnectionLimit;
        }
        else if (cmd == "ate0" || cmd == "atze0")
        {
            atEcho = false;
            sp("\r\nOK\r\n");
        }
        else if (cmd == "ate1")
        {
            atEcho = true;
            sp("\r\nOK\r\n");
        }
        else if (cmd == "at+creg?")
        {
            sp("\r\nCREG: 0,1r\r\nOK\r\n");
        }
        else if (cmd.indexOf("at+") >= 0) //for AT+CBST=71 etc
        {
            sp("\r\nOK\r\n");
        }
        else if (cmd.indexOf("at&") >= 0) //for AT&F etc
        {
            sp("\r\nOK\r\n");
        }
        else if (cmd.indexOf("ats") >= 0) //for AT&S etc
        {
            sp("\r\nOK\r\n");
        }
        else
            sp("\r\nERROR\r\n");

        // sp("\r\nOK\r\n");
        cmd = "";
    }

}
