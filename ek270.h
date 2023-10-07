/*
<-(7)  | 00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00
<-(8) /?!rn | 2F-3F-21-0D-0A
->[12] /Els6EK270rn | 2F-45-6C-73-36-45-4B-32-37-30-0D-0A
<-(9) 061rn | 06-30-36-31-0D-0A
       P0(1234567)P | 01-50-30-02-28-31-32-33-34-35-36-37-29-03-50
->[15] P0(1234567)P | 01-50-30-02-28-31-32-33-34-35-36-37-29-03-50

<-(10) R13:170.0()B | 01-52-31-02-33-3A-31-37-30-2E-30-28-29-03-42
->[13] 3:170.0(1) | 02-33-3A-31-37-30-2E-30-28-31-29-03-12
<-(11) R14:170.0()E | 01-52-31-02-34-3A-31-37-30-2E-30-28-29-03-45
->[13] 4:170.0(0) | 02-34-3A-31-37-30-2E-30-28-30-29-03-14
<-(12) R16:36E.0(0) | 01-52-31-02-36-3A-33-36-45-2E-30-28-30-29-03-01
->[23] 6:36E.0(-2.7315E+02)r | 02-36-3A-33-36-45-2E-30-28-2D-32-2E-37-33-31-35-45-2B-30-32-29-03-0D


/ELS5TC210rn | 2F-45-4C-53-35-54-43-32-31-30-0D-0A
16.06.2023 1:05:27 DEBUG	1200^4aa2c994.tcpclient	 47623<-(2) 051rn | 06-30-35-31-0D-0A
16.06.2023 1:05:32 DEBUG	1200^4aa2c994.tcpclient	 47623->[16] P0(1234567)P | 01-50-30-02-28-31-32-33-34-35-36-37-29-03-50-00


*/

void io270(byte *buf, int len)
{
    //Serial.print(len); Serial.print("--"); Serial.print(buf[0]); Serial.write(buf, len);  Serial.println();

    if(buf[0] == 0) return;

    String istr = String((char*)buf);

    if (buf[0] == 0x2f)
    {
        Serial.print("/Els6EK270\r\n");  //2F-45-6C-73-36-45-4B-32-37-30-0D-0A
        // Serial.print("/ELS5TC210\r\n"); 
    }

    //ответ на <- .051.  |  06-30-35-31-0D-0A
    if (buf[0] == 6)
    {
        byte b[] = {0x01, 0x50, 0x30, 0x02, 0x28, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x29, 0x03, 0x50}; //->[15] P0(1234567)P 
        Serial.write(b,sizeof(b));
    }

    //ответ на <-  R1 4:170.0() | 01-52-31-02-34-3A-31-37-30-2E-30-28-29-03-45
    if (istr.indexOf("4:170") >= 0)
     {
        byte b[] = {0x02, 0x34, 0x3A, 0x31, 0x37, 0x30, 0x2E, 0x30, 0x28, 0x31, 0x29, 0x03, 0x15}; // 4:170.0(1)
        Serial.write(b,sizeof(b));
    }


    // switch(buf[0]) не работает?
    // {
    //     case 0: 
    //     case 47: Serial.print("qqq/Els6EK270qqq\r\n"); 
    // }
    return;
}