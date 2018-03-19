

//ThaddeusSM
//03/16/18

//Libraries
#include <Arduboy2.h>
#include <FixedPoints.h>
#include <FixedPointsCommon.h>
#include <ArduboyTones.h>
#include <ArduboyTonesPitches.h>

#include "images.h"
#include "sounds.h"

#define MAX_GUN_ANGLE 1.05
#define MIN_GUN_ANGLE -1.05
#define NUMBER_OF_BULLETS 15
#define NUMBER_OF_SOLDIERS 2
#define NUMBER_OF_HELICOPTERS 1
#define NUMBER_OF_TACOBOSSES 3

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

//Variables

int gamestate = 0;
const int x1 = 20;
const int y1 = 27;
float gunAngle = 0.0;
const float GAinc = 0.15;
int x2;
int y2;
int x3;
int y3;
int score = 0;
struct Bullet {
  uint8_t x;
  uint8_t y;
  uint8_t xDelta;
  int8_t yDelta;
  bool active;
};
struct Soldier {
  uint16_t x;
  uint8_t y;
  float xDelta;
  int8_t yDelta;
  bool active;
};
struct Helicopter {
  uint16_t x;
  uint8_t y;
  float xDelta;
  int8_t yDelta;
  bool active;
};
struct Tacoboss {
  uint16_t x;
  uint8_t y;
  float xDelta;
  int8_t yDelta;
  bool active;
};
int health = 50;


Bullet bullets[NUMBER_OF_BULLETS];
Soldier soldiers[NUMBER_OF_SOLDIERS];
Helicopter helicopters[NUMBER_OF_HELICOPTERS];
Tacoboss tacobosses[NUMBER_OF_TACOBOSSES];





//Setup Script
void setup() {
  arduboy.begin();
  Serial.begin(9600);
  arduboy.initRandomSeed();
  arduboy.setFrameRate(60);
  arduboy.audio.begin();
  arduboy.clear();
}

//Game Code
void loop() {
  if(!arduboy.nextFrame()) {
    return;
  }
  arduboy.pollButtons();
  arduboy.clear();
  switch(gamestate){
    case 0:
    arduboy.drawBitmap(0, 0, titleScreen, 128, 64, WHITE);
    if(arduboy.justPressed(A_BUTTON)) {
      gamestate = 1;
      score = 0;
      health = 50;
      sound.tones(playGame);
    }
    if(arduboy.justPressed(B_BUTTON)) {
      gamestate = 4;
    }

      break;
    case 1:
    arduboy.drawBitmap(0, 0, Gameplay1, 128, 64, WHITE);
    x2 = x1 + cos(gunAngle) * 8;
    y2 = y1 + sin(gunAngle) * 8;
    arduboy.drawLine(x1, y1, x2, y2, WHITE);
    if(arduboy.justPressed(UP_BUTTON) or arduboy.pressed(LEFT_BUTTON)) {
      if(gunAngle > MIN_GUN_ANGLE){
        gunAngle = gunAngle - GAinc;
      }
    }
    if(arduboy.justPressed(DOWN_BUTTON) or arduboy.pressed(RIGHT_BUTTON)){
      if(gunAngle < MAX_GUN_ANGLE){
         gunAngle = gunAngle + GAinc;
      } 
    }
     
     if(arduboy.justPressed(B_BUTTON)) {
      sound.tones(gunShot);
        for (uint8_t x = 0; x < NUMBER_OF_BULLETS; x++) {

          if (!bullets[x].active) {
            bullets[x].x = x2;
            bullets[x].y = y2;
            bullets[x].xDelta = cos(gunAngle)* 5;
            bullets[x].yDelta = sin(gunAngle)* 7 ;
            bullets[x].active = true;
            break;  // We found one so we can leave the loop.
            
          }
          
        }
     }
      if(score > -1 && score < 699) {
        for (uint16_t x = 0; x < NUMBER_OF_SOLDIERS; x++) {

          if (!soldiers[x].active) {
            soldiers[x].x = random(130, 200);
            soldiers[x].y = 36;
            soldiers[x].xDelta = -1;
            soldiers[x].yDelta = 0;
            soldiers[x].active = true;
            break; 
            
          }
          
        }
     }
     if(score > 129 && score < 699) {
        for (uint16_t x = 0; x < NUMBER_OF_HELICOPTERS; x++) {

          if (!helicopters[x].active) {
            helicopters[x].x = random(180, 250);
            helicopters[x].y = random(12, 24);
            helicopters[x].xDelta = random(-2, -1);
            helicopters[x].yDelta = 0;
            helicopters[x].active = true;
            break; 
            
          }
          if (!helicopters[x].active == true && score < 129) {
            helicopters[x].active = false;
        }

        }
     }
     if(score > 699) {
        for (uint16_t x = 0; x < NUMBER_OF_TACOBOSSES; x++) {

          if (!tacobosses[x].active) {
            tacobosses[x].x = random(180, 250);
            tacobosses[x].y = random(10, 30);
            tacobosses[x].xDelta = -2;
            tacobosses[x].yDelta = 0;
            tacobosses[x].active = true;
            break; 
            
          } 
          if (!tacobosses[x].active == true && score < 699) {
            tacobosses[x].active = false;
          }
        }
     }






    // Render the bullets ..

    for (uint8_t x = 0; x < NUMBER_OF_BULLETS; x++) {
    
      if (bullets[x].active) {
      
        arduboy.drawPixel(bullets[x].x, bullets[x].y, WHITE);

      }
      
    }
    for (uint16_t x = 0; x < NUMBER_OF_SOLDIERS; x++) {
    
      if (soldiers[x].active) {
      
        arduboy.drawBitmap(soldiers[x].x, soldiers[x].y, Soldier1, 16, 16, WHITE);

      }
      
    }
     for (uint16_t x = 0; x < NUMBER_OF_HELICOPTERS; x++) {
    
      if (helicopters[x].active) {
      
        arduboy.drawBitmap(helicopters[x].x, helicopters[x].y, Helicopter1, 20, 20, WHITE);

      }
      
    }
    for (uint16_t x = 0; x < NUMBER_OF_TACOBOSSES; x++) {
    
      if (tacobosses[x].active) {
      
        arduboy.drawBitmap(tacobosses[x].x, tacobosses[x].y, TACOBOSS, 20, 20, WHITE);

      }
      
    }
    for (uint16_t x = 0; x < NUMBER_OF_SOLDIERS; x++) {
    
      if (soldiers[x].active) {
      
        soldiers[x].x += soldiers[x].xDelta; 
        soldiers[x].y += soldiers[x].yDelta;

        

        if (soldiers[x].x < 18 || soldiers[x].y < 0 || soldiers[x].y > HEIGHT ) {
          soldiers[x].active = false;
          health -= 2;
          sound.tones(playerHit);
          
        }

      }
      
    }
    for (uint16_t x = 0; x < NUMBER_OF_HELICOPTERS; x++) {
    
      if (helicopters[x].active) {
      
        helicopters[x].x += helicopters[x].xDelta; 
        helicopters[x].y += helicopters[x].yDelta;

        

        if (helicopters[x].x < 18 || helicopters[x].y < 0 || helicopters[x].y > HEIGHT ) {
          helicopters[x].active = false;
          health -= 10;
          sound.tones(playerHit);
          
        }

      }
      
    }
    for (uint16_t x = 0; x < NUMBER_OF_TACOBOSSES; x++) {
    
      if (tacobosses[x].active) {
      
        tacobosses[x].x += tacobosses[x].xDelta; 
        tacobosses[x].y += tacobosses[x].yDelta;

       

        if (tacobosses[x].x < 18 || tacobosses[x].y < 0 || tacobosses[x].y > HEIGHT ) {
          tacobosses[x].active = false;
          health -= 30;
          sound.tones(playerHit);          
        }

      }
      
    }




    // Move the bullets ..

    for (uint8_t x = 0; x < NUMBER_OF_BULLETS; x++) {
    
      if (bullets[x].active) {
      
        bullets[x].x += bullets[x].xDelta; 
        bullets[x].y += bullets[x].yDelta;

        // Out of range ?

        if (bullets[x].x > WIDTH || bullets[x].y < 0 || bullets[x].y > HEIGHT) {

          bullets[x].active = false;
          
        } else { 
          for (uint16_t x = 0; x < NUMBER_OF_SOLDIERS; x++) {
            Point bulletPoint = Point {bullets[x].x, bullets[x].y};
            if(soldiers[x].active) {
              Rect enemyRect = Rect {soldiers[x].x, soldiers[x].y, 14, 18};
                 if(arduboy.collide(bulletPoint, enemyRect)) {
                  soldiers[x].active = false;
                  bullets[x].active = false;
                  score += 2;
                  sound.tones(enemyHit);
                }
             }
          } 
        for (uint16_t x = 0; x < NUMBER_OF_HELICOPTERS; x++) {
            Point bulletPoint = Point {bullets[x].x, bullets[x].y};
            if(helicopters[x].active) {
              Rect helicopterRect = Rect {helicopters[x].x, helicopters[x].y, 20, 18};
                 if(arduboy.collide(bulletPoint, helicopterRect)) {
                  helicopters[x].active = false;
                  bullets[x].active = false;
                  score += 10;
                  sound.tones(enemyHit);
                }
             }
          } 
           for (uint16_t x = 0; x < NUMBER_OF_TACOBOSSES; x++) {
            Point bulletPoint = Point {bullets[x].x, bullets[x].y};
            if(tacobosses[x].active) {
              Rect tacobossRect = Rect {tacobosses[x].x, tacobosses[x].y, 20, 18};
                 if(arduboy.collide(bulletPoint, tacobossRect)) {
                  tacobosses[x].active = false;
                  bullets[x].active = false;
                  score += 10;
                  sound.tones(enemyHit);
                }
             }
          } 
        }
        

      }
      
      

      
    }
    if(arduboy.justPressed(A_BUTTON) && score > 49 && health < 50 && score < 699) {
      health += 10;
      score -= 50;
      sound.tones(healthRegen);
    }


    arduboy.setCursor(0, 0);
    arduboy.print(score);
    arduboy.setCursor(50, 0);
    arduboy.print("HP:");
    arduboy.drawLine(64, 3, 64 + health, 3, WHITE); 
    if (health < 1) {
      sound.tones(lose);
      gamestate = 2;
    }
    if(score > 999) {
      sound.tones(win);
      gamestate = 3;
    }

      break;
     case 2:
     arduboy.setCursor(40, 28);
     arduboy.print("GAME OVER");
     arduboy.setCursor(40, 38);
     arduboy.print("Score:");
     arduboy.print(score);
     arduboy.setCursor(40,48);
     arduboy.print("PRESS 'A' ");
     if(arduboy.justPressed(A_BUTTON)){
     gamestate = 0;
    }
      break;
     case 3:
     arduboy.setCursor(40, 28);
     arduboy.print("YOU WIN!!!");
     arduboy.setCursor(40, 40);
     arduboy.print("PRESS 'A' ");
     if(arduboy.justPressed(A_BUTTON)){
      gamestate = 0;
      } break;
      case 4: 
      arduboy.setCursor(40, 20);
      arduboy.print("CREDITS:");
      arduboy.setCursor(40, 28);
      arduboy.print("ThaddeusSM");
      arduboy.setCursor(40, 36);
      arduboy.print("Filmote");
      arduboy.setCursor(40, 44);
      arduboy.print("Pharap");
      arduboy.setCursor(0, 52);
      arduboy.print("The Arduboy Community");
      if(arduboy.justPressed(A_BUTTON)) {
        gamestate = 0;
      }
      
  }

   Serial.write(arduboy.getBuffer(), 128 * 64 / 8);
   arduboy.display();
}
