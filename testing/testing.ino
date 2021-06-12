//hey amber!! heres the basic setups:

#include <U8g2lib.h>
#include <AsyncDelay.h>
#include <Wire.h>
#include "LIS3DHTR.h"
LIS3DHTR<TwoWire> LIS;
#define WIRE Wire
#include "Adafruit_NeoPixel.h"
#include <Keyboard.h>

#define DHTPIN 3
#define DHTTYPE DHT11

#include "grove_two_rgb_led_matrix.h"
 
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
#define SERIAL SerialUSB
#else
#define SERIAL Serial
#endif

GroveTwoRGBLedMatrixClass matrix;

AsyncDelay tick;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, SCL, SDA, U8X8_PIN_NONE);

//pop the image files here:

//define frame1:

uint64_t led1[] = {

  0x5c5cfefefe5c5c5c,
  0x5cff5c5c5c5cff5c,
  0xe6e65cf4f45ce6e6,
  0xe6e65c5c5c5ce6e6,
  0x5c5c5c5c5c5c5c5c,
  0x5c5c5c3a3a5c5c5c,
  0xfe5c3a3a3a3a5cfe,
  0xfefe3a3a3a3afefe
};

//define frame2:

//defining variables:

#define screen_width 128
#define screen_height 64
const int fps = 0; //fast as possible b/c sensors make it slow
int currentFrame = 0;

/*const int display_width = 164;
int current_pos = -display_width;
int move_int = 50; //movement interval
int animate_frame = 0;
float movement = 0.00;*/ //this is like the movement stuff? dont think we need it rn

char button = 6;
char led = 4;
char rotary = A0;
char sound = A2;

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  Keyboard.begin();

  tick.start(fps, AsyncDelay::MILLIS);
}

void duckAnimate() {
  u8g2.firstPage();
  do {
    switch (currentFrame) {
      case 0:
        //u8g2.drawXBMP(screen_width / 2,0, screen_width, screen_height, frame1);
        break;
      case 1: 
        //u8g2.drawXBMP(screen_width / 2,0, screen_width, screen_height, frame2);
        break;
    }
  }
  while(u8g2.nextPage());
}

void changeSong()
{
  Keyboard.press(KEY_LEFT_GUI);
  delay(100);
  Keyboard.release(KEY_LEFT_GUI);
}

void pulse()
{
  //insert
}

void loop() { 
  // put your main code here, to run repeatedly:
    if (digitalRead(button) == HIGH)
    {
      changeSong();
    }
    if (analogRead(sound) >  300)
    {
      pulse();
    }
    
    duckAnimate();
   
      if (currentFrame == 0)
      {
         currentFrame++;
      }
      else if (currentFrame == 1)
      {
        currentFrame--;
      }
      
    tick.repeat();

    for (int x=0;x<3;x++) {
        matrix.displayFrames(led1+x*8, 200, false, 1);
        delay(700);
    }
}
