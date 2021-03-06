#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <SoftwareSerial.h>
#define TCAADDR 0x70 // 멀티플렉서가 0x70의 주소를 가집니다. 

byte gammatable[256];
char str[3];
int count = 0;
 uint16_t clear, red, green, blue;

 float r, g, b;

 uint32_t sum;
/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC - 5V도 무방합니다.
   Connect GROUND to common ground */
   

Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_1X);

Adafruit_TCS34725 tcs2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_1X);

Adafruit_TCS34725 tcs3 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_1X);
/*  multiplexer는 0부터 7까지의 8개의 센서를 연결할 수 있습니다.
 *  tcaselect 함수는 입력한 숫자에 연결된 센서로 연결을 변경해줍니다.
 *  tcs37425는 헤더에 센서 주소가 내장되어 있어 건드리기가 귀찮아 본 함수로 대체합니다.
 *  i2c주소가 함수로 지정 가능한 liquidCrystal 같은 경우는 본 함수 없이 0x70~0x77 로 주소를 지정하는 것으로 사용이 가능합니다.
 *  자전거의 기어 변속을 생각하시면 편합니다.
 */

 SoftwareSerial bt(2, 3);
 
void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}
/* 기본적으로 tcs34725에서 전송하는 데이터는 일반 rgb값과는 조금 다릅니다.
 *  조금 더 직관적으로 값을 보기 위해 평소 보는 (255, 255, 255)의 형식으로 바꿔줍니다.
 *  이 값은 임의의 비이기 때문에 실제 rgb값과는 차이가 있습니다. 
 *  clear는 원래 객체에 write 혹은 print된 내용을 지우기 위해 쓰이는 함수이지만 
 *  여기서는 변수명으로 지정하였습니다.
 */
/*
void color(){
  if ( red ) bt.print("R");
  if ( pink ) bt.print("P");
  if ( orange ) bt.print("O");
  if ( yellow ) bt.print("Y");
  if ( green ) bt.print("G");
  if ( blue ) bt.print("B");
  if ( magenta ) bt.print("M");
  if ( violet ) bt.print("V");
  
}
*/
void color()
{
  if (150 < r &&  r < 170 && 40 < g && g < 70 && 40 < b && b < 50)
  {
    Serial.println("R");
    str[count] = 'R';
  }
 if(r > 250 && 140 < g && g < 180 && 80 < b && b < 110) 
  {
    Serial.println("O");
    str[count] = 'O';
  }
if (80 < r && r < 95 && 80 < g  && g < 90 && 90 < b && b < 110 )
  {
    Serial.println("V");
    str[count] = 'V';
  }
if (140 < r && r <160 && 230 < g && 100 < b && b < 120)
{
     Serial.println("P");
     str[count]='P';
}
// 실제로는 연두색입니다. 핑크색 우드락이 없었어요....
if (r >250 && g>250 && 140 < b && b < 165)
{
    Serial.println("Y");
    str[count]='Y';
}
if (70 < r && r < 90 && 170 < g && g < 210 && 95 < b && b < 130)
{
     Serial.println("G");
     str[count]='G';
}
if (50 < r && r < 70 && 80 < g && g < 100 && 95 < b && b < 115 )
{
     Serial.println("B");
     str[count]='B';
}
  count += 1;
  if (count == 3 )
  {
    for (int i = 0; i < 3; i++)
    {
      bt.write(str[i]);
      str[i] = 0;
    }
    count = 0;
  }
}
/* 문자열 str의 count 위치에 색 판별의 결과값을 대입합니다.
 *  색 판별이 한번 이루어진 이후 count 값이 1 증가합니다.
 * count가 3이되었을 때, 즉 색이 3번 읽혔을 때 문자열 str을 블루투스에 출력합니다.
 * 출력 후 문자열 str을 초기화합니다.
 */
void datatorgb() 
{
   sum = red;
  sum += green;
  sum += blue;
  sum = clear;
  
  r = red; 
  r /= sum;
  g = green; 
  g /= sum;
  b = blue; 
  b /= sum;
  r *= 256; 
  g *= 256; 
  b *= 256;
  if (r > 255) r = 255;
  if (g > 255) g = 255;
  if (b > 255) b = 255;
  Serial.print(r);
  Serial.print("\t");
  Serial.print(g);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print(clear);
  Serial.println();
  color();

  
}

void setup(void) {
  Serial.begin(9600); 
  Wire.begin();
  bt.begin(9600);
  /* 멀티플렉서와의 통신이 필요합니다. 
   * 멀티플렉서는 wire.h를 통해 작동합니다. 
   * 통신 주소는 tcaselect를 통해 지정됩니다.
   */
  delay(1000);
  tcaselect(2);
  if(tcs1.begin()) Serial.println("TCS1 connected");
  else { Serial.println("TCS1 connect failed"); while(1);}
  delay(1000);
  tcaselect(3);
  if(tcs2.begin()) Serial.println("TCS2 connected");
  else { Serial.println("TCS2 connect failed"); while(1);}
  delay(1000);
  tcaselect(4);
  if(tcs3.begin()) Serial.println("TCS3 connected");
  else { Serial.println("TCS3 connect failed"); while(1);}
  /* tcs 1,2,3의 주소는 모두 헤더에서 0x27로 지정되어있습니다.
  tcaselect 함수를 통해 0x27의 주소가 가르키는 센서를 계속 변경해줍니다. 
  1번센서는 2번에, 2번 센서는 3번에, 3번 센서는 4번에 연결되어있습니다.*/
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
    gammatable[i] = x; 
  }
  //gammatable 배열에 값을 지정해줍니다. 그런데 사용되는 것처럼 보이지는 않습니다.

}

void loop(void) {

  tcaselect(2);
  Serial.println("1번 센서");
  tcs1.getRawData(&red, &green, &blue, &clear);
  datatorgb();
   tcaselect(3);
     Serial.println("2번 센서");
  tcs2.getRawData(&red, &green, &blue, &clear);
  datatorgb();
  tcaselect(4);
    Serial.println("3번 센서");
  tcs3.getRawData(&red, &green, &blue, &clear);
  datatorgb();

}


