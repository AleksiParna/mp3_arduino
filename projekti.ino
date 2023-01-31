#include "SD.h"
//#define SD_ChipSelectPin 4
#include "TMRpcm.h"
#include "SPI.h"
#include "LiquidCrystal.h"
#include "LcdBarGraph.h"

TMRpcm music;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LcdBarGraph lbg(&lcd, 5,2,1);

int buttonpause = 6;
int buttonselect = 7;
int buttonright = 8;
int buttonleft = 13;

int potVol;
int oldpotVol;

int song = 0;
bool debounce1 = true;
bool debounce2 = true;

void setup() {
  pinMode(buttonpause, INPUT_PULLUP);
  pinMode(buttonselect, INPUT_PULLUP);
  pinMode(buttonright, INPUT_PULLUP);
  pinMode(buttonleft, INPUT_PULLUP);

  music.speakerPin=9;
  /*
  if(!SD.begin(SD_ChipSelectPin)){
    Serial.println("SD fail");
    return;
  }
*/
  lcd.begin(16, 2);

  music.setVolume(5);sss
}

void loop() {
  potVol = analogRead(A3);
  if (abs(potVol-oldpotVol)>5){
    volumecontrol();
  }

  songchoose();

}


void volumecontrol(){
  oldpotVol = potVol;
  if(potVol==0){
    music.setVolume(0);
  }
  else if (potVol<247){
    music.setVolume(1);
  }    
  else if (potVol<495){
    music.setVolume(2);
  }
  else if (potVol<743){
    music.setVolume(3);
  }
  else if (potVol<991){
    music.setVolume(4);
  }
  else{
    music.setVolume(5);
  }

  lcd.setCursor(0, 0);
  lcd.print("Volume");
  lcd.setCursor(0,1);
  lcd.print("0<");
  lcd.setCursor(7,1);
  lcd.print(">5");
  lbg.drawValue(potVol,1024);
  delay(500);

}


void songchoose(){
  if (digitalRead(buttonselect)==LOW)
    music.play("carol.wav");
        
}
