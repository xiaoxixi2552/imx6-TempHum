#include "temphum.h"

TempHum::TempHum()
{
    temperature = 40;
    humidity = 40;
}
void TempHum::setValue(QByteArray& byte)
{ 

    if (byte.size() >= 12 &&(char)byte[0] ==(char)0xBB && (char)byte[1] == (char)0xFF && (char)byte[6] == (char)0xFF)
    {
           int highByte = byte[2];
           int lowByte = byte[3];
           int decimalFlag = byte[4];
           if (decimalFlag == 0x00)
           {
               temperature = highByte * 10 + lowByte;
           }
           else if (decimalFlag == 0x01)
           {
               temperature = highByte + lowByte / 10.0f;
           }
     }
    if (byte.size() >= 12 &&(char)byte[7] ==(char)0xBB && (char)byte[8] == (char)0xFF && (char)byte[13] == (char)0xFF)
    {
           int highByte = byte[9];
           int lowByte = byte[10];
           int decimalFlag = byte[11];
           if (decimalFlag == 0x00)
           {
               humidity = highByte * 10 + lowByte;
           }
           else if (decimalFlag == 0x01)
           {
               humidity = highByte + lowByte / 10.0f;
           }
     }
}
int TempHum::getTemperature()
{
    return temperature;
}

int TempHum::getHumidity()
{
    return humidity;
}


