//#define INPUT 0
//#define OUTPUT 1

#define DELTAH	5
#define MAXCHAR 127


//Util ==============================================

#define sp    Serial.print
#define sp_   Serial.print(" ");
#define spok  Serial.print(" ok ");
#define sp1   Serial.print("<====1====>");
#define spn  Serial.print("\r\n");
void sph(char *h, int i){  Serial.print(h), Serial.print("="), Serial.print(i); Serial.print(" ");}
void sph(int i){Serial.print(i); Serial.print(" ");}


/*float roundd(float v) {
  return round(v * 10) / 10;
  }*/

//void IncChar(char &cc) {  if (cc < MAXCHAR) cc++;}

//  Y[i] = Y[i-1] + (X[i] – Y[i-1]) * Alpha Экспоненциальное скользящее среднее (EMA) http://www.may.nnov.ru/mak/DSP/chEMA.shtml
float EMA_Filter(float PY, float X, int kf)
{
  if (!kf)return X; //без
  if (kf > 99)kf = 99;
  kf = 100 - kf;
  float alfa = (float)kf / 100;
  float Y = (PY + (X - PY) * alfa);
  return Y;
}
