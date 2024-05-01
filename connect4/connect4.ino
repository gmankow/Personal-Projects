 // FastLED - Version: Latest 
#include <FastLED.h>
#include <Keypad.h>


#define LED_PIN 7
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];

//grid used to store light positions and to display the lights
int ledGrid[7][7] = {
  {6,7,20,21,34,35,48},
  {5,8,19,22,33,36,47},
  {4,9,18,23,32,37,46},
  {3,10,17,24,31,38,45},
  {2,11,16,25,30,39,44},
  {1,12,15,26,29,40,43},
  {0,13,14,27,28,41,42}
};

//grid to store whether a light is on or off (off = 0), and its color (either 1 or 2)
int onOff[7][7] = {
  {0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0}
};

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
  Serial.begin(9600);
}

int i = 0; // up/down
int j = 0; // left/right

int ledNum = ledGrid[i][j];

int isPlayerRedTurn = 1; // 1 = true, 0 = false


void loop() {

  char command = Serial.read();
  
  // right
  if (command == 'd') {
    onOff[i][j] = 0;
    ledNum = ledGrid[i][j];
    leds[ledNum] = CRGB(0,0,0);
    FastLED.show();
    j++;
    if (j > 6) {
      j = 6;
    }
    if (isRedTurn()) {
      onOff[i][j] = 1;
      ledNum = ledGrid[i][j];
      leds[ledNum] = CRGB(128,0,0);
      FastLED.show();
    } else {
      onOff[i][j] = 2;
      ledNum = ledGrid[i][j];
      leds[ledNum] = CRGB(0,0,128);
      FastLED.show();
    }
    for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 7; j++) {
        Serial.print(onOff[i][j]);
      }
      Serial.println("");
    }
  }

  // left
  if (command == 'a') {
    onOff[i][j] = 0;
    ledNum = ledGrid[i][j];
    leds[ledNum] = CRGB(0,0,0);
    FastLED.show();
    j--;
    if (j < 0) {
      j = 0;
    }
    if (isRedTurn()) {
      onOff[i][j] = 1;
      ledNum = ledGrid[i][j];
      leds[ledNum] = CRGB(128,0,0);
      FastLED.show();
    } else {
      onOff[i][j] = 2;
      ledNum = ledGrid[i][j];
      leds[ledNum] = CRGB(0,0,128);
      FastLED.show();
    }
    for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 7; j++) {
        Serial.print(onOff[i][j]);
      }
      Serial.println("");
    }
  }

  // down 
  if (command == 's') {
    Serial.println("S pressed");
    i = 0;
    onOff[i][j] = 0;  // top row, cant put anything
    ledNum = ledGrid[i][j];
    leds[ledNum] = CRGB(0,0,0);
    FastLED.show();
  
    for (i = 7; i >= 1; i--) {
      if (onOff[i][j] == 0) {
        // put piece
        if (isRedTurn()) {
          int y = 1;
          while (y < i) {
            ledNum = ledGrid[y][j];
            leds[ledNum] = CRGB(128,0,0);
            FastLED.show();
            delay(100);
            leds[ledNum] = CRGB(0,0,0);
            FastLED.show();
            //delay(100);
            y++;
          }
          onOff[i][j] = 1;
          ledNum = ledGrid[i][j];
          leds[ledNum] = CRGB(128,0,0);
          FastLED.show();
        } else {
          int y = 1;
          while (y < i) {
            ledNum = ledGrid[y][j];
            leds[ledNum] = CRGB(0,0,128);
            FastLED.show();
            delay(100);
            leds[ledNum] = CRGB(0,0,0);
            FastLED.show();
            //delay(100);
            y++;
          }
          onOff[i][j] = 2;
          ledNum = ledGrid[i][j];
          leds[ledNum] = CRGB(0,0,128);
          FastLED.show();
        }
        // break
        break;
      }
    }

    Serial.println("Changed Turn");
    if (isRedTurn()) {
      isPlayerRedTurn = 0;
    } else {
      isPlayerRedTurn = 1;
    }

    CheckGameWin();

    CheckTie();

    i = 0;
    j = 0;
    
    if (isRedTurn()) {
      onOff[i][j] = 1;
      ledNum = ledGrid[i][j];
      leds[ledNum] = CRGB(128,0,0);
      FastLED.show();

    } else {
      onOff[i][j] = 2;
      ledNum = ledGrid[i][j];
      leds[ledNum] = CRGB(0,0,128);
      FastLED.show();
    }

    for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 7; j++) {
        Serial.print(onOff[i][j]);
      }
      Serial.println("");
    }
  }
}

int isRedTurn() {
  if (isPlayerRedTurn == 1) {
    return 1;
  } else {
    return 0;
  }
}

void CheckGameWin() {
  // check rows
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7 - 3; j++) {
      if (onOff[i][j] != 0 && 
          onOff[i][j] == onOff[i][j + 1] && 
          onOff[i][j] == onOff[i][j + 2] && 
          onOff[i][j] == onOff[i][j + 3]) {
            Serial.println("Winner");
            int playerTurn = onOff[i][j];
            int ledNum1 = ledGrid[i][j];
            int ledNum2 = ledGrid[i][j+1];
            int ledNum3 = ledGrid[i][j+2];
            int ledNum4 = ledGrid[i][j+3];
            for (int x = 0; x < 5; x++) {
              leds[ledNum1] = CRGB(0,0,0);
              leds[ledNum2] = CRGB(0,0,0);
              leds[ledNum3] = CRGB(0,0,0);
              leds[ledNum4] = CRGB(0,0,0);
              FastLED.show();
              delay(500);
              if (playerTurn == 1) {
                leds[ledNum1] = CRGB(128,0,0);
                leds[ledNum2] = CRGB(128,0,0);
                leds[ledNum3] = CRGB(128,0,0);
                leds[ledNum4] = CRGB(128,0,0);
                FastLED.show();
                delay(500);
              } else {
                leds[ledNum1] = CRGB(0,0,128);
                leds[ledNum2] = CRGB(0,0,128);
                leds[ledNum3] = CRGB(0,0,128);
                leds[ledNum4] = CRGB(0,0,128);
                FastLED.show();
                delay(500);
              }
            }
            for (int i = 0; i < 7; i++) {
              for (int j = 0; j < 7; j++) {
                ledNum = ledGrid[i][j];
                if (playerTurn == 1) {
                  leds[ledNum] = CRGB(128,0,0);
                } else  {
                  leds[ledNum] = CRGB(0,0,128);
                }
                FastLED.show();
                delay(50);
              }
            }
            delay(500);
            ResetBoard();
          
      }
    }
  }
  // check columns
  for (int i = 0; i < 7 - 3; i++) {
    for (int j = 0; j < 7; j++) {
      if (onOff[i][j] != 0 && 
          onOff[i][j] == onOff[i + 1][j] && 
          onOff[i][j] == onOff[i + 2][j] && 
          onOff[i][j] == onOff[i + 3][j]) {
            Serial.println("Winner");
            int playerTurn = onOff[i][j];
            int ledNum1 = ledGrid[i][j];
            int ledNum2 = ledGrid[i+1][j];
            int ledNum3 = ledGrid[i+2][j];
            int ledNum4 = ledGrid[i+3][j];
            for (int i = 0; i < 5; i++) {
              leds[ledNum1] = CRGB(0,0,0);
              leds[ledNum2] = CRGB(0,0,0);
              leds[ledNum3] = CRGB(0,0,0);
              leds[ledNum4] = CRGB(0,0,0);
              FastLED.show();
              delay(500);
              if (playerTurn == 1) {
                leds[ledNum1] = CRGB(128,0,0);
                leds[ledNum2] = CRGB(128,0,0);
                leds[ledNum3] = CRGB(128,0,0);
                leds[ledNum4] = CRGB(128,0,0);
                FastLED.show();
                delay(500);
              } else {
                leds[ledNum1] = CRGB(0,0,128);
                leds[ledNum2] = CRGB(0,0,128);
                leds[ledNum3] = CRGB(0,0,128);
                leds[ledNum4] = CRGB(0,0,128);
                FastLED.show();
                delay(500);
              }
            }
            for (int i = 0; i < 7; i++) {
              for (int j = 0; j < 7; j++) {
                ledNum = ledGrid[i][j];
                if (playerTurn == 1) {
                  leds[ledNum] = CRGB(128,0,0);
                } else  {
                  leds[ledNum] = CRGB(0,0,128);
                }
                FastLED.show();
                delay(50);
              }
            }
            delay(500);
            ResetBoard();
          
      }
    }
  }
  // check diagonal (back slash shape)
  for (int i = 0;  i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (onOff[i][j] != 0 && 
          onOff[i][j] == onOff[i + 1][j + 1] && 
          onOff[i][j] == onOff[i + 2][j + 2] && 
          onOff[i][j] == onOff[i + 3][j + 3]) {
            Serial.println("Winner");
            int playerTurn = onOff[i][j];
            int ledNum1 = ledGrid[i][j];
            int ledNum2 = ledGrid[i+1][j+1];
            int ledNum3 = ledGrid[i+2][j+2];
            int ledNum4 = ledGrid[i+3][j+3];
            for (int i = 0; i < 5; i++) {
              leds[ledNum1] = CRGB(0,0,0);
              leds[ledNum2] = CRGB(0,0,0);
              leds[ledNum3] = CRGB(0,0,0);
              leds[ledNum4] = CRGB(0,0,0);
              FastLED.show();
              delay(500);
              if (playerTurn == 1) {
                leds[ledNum1] = CRGB(128,0,0);
                leds[ledNum2] = CRGB(128,0,0);
                leds[ledNum3] = CRGB(128,0,0);
                leds[ledNum4] = CRGB(128,0,0);
                FastLED.show();
                delay(500);
              } else {
                leds[ledNum1] = CRGB(0,0,128);
                leds[ledNum2] = CRGB(0,0,128);
                leds[ledNum3] = CRGB(0,0,128);
                leds[ledNum4] = CRGB(0,0,128);
                FastLED.show();
                delay(500);
              }
            }
            for (int i = 0; i < 7; i++) {
              for (int j = 0; j < 7; j++) {
                ledNum = ledGrid[i][j];
                if (playerTurn == 1) {
                  leds[ledNum] = CRGB(128,0,0);
                } else  {
                  leds[ledNum] = CRGB(0,0,128);
                }
                FastLED.show();
                delay(50);
              }
            }
            delay(500);
            ResetBoard();
          
      }
    }
  }
  // check other diagonal (forward slash shape)
  for (int i = 3;  i < 7; i++) {
    for (int j = 0; j < 4; j++) {
      if (onOff[i][j] != 0 && 
          onOff[i][j] == onOff[i - 1][j + 1] && 
          onOff[i][j] == onOff[i - 2][j + 2] && 
          onOff[i][j] == onOff[i - 3][j + 3]) {
            Serial.println("Winner");
            int playerTurn = onOff[i][j];
            int ledNum1 = ledGrid[i][j];
            int ledNum2 = ledGrid[i-1][j+1];
            int ledNum3 = ledGrid[i-2][j+2];
            int ledNum4 = ledGrid[i-3][j+3];
            for (int i = 0; i < 5; i++) {
              leds[ledNum1] = CRGB(0,0,0);
              leds[ledNum2] = CRGB(0,0,0);
              leds[ledNum3] = CRGB(0,0,0);
              leds[ledNum4] = CRGB(0,0,0);
              FastLED.show();
              delay(500);
              if (playerTurn == 1) {
                leds[ledNum1] = CRGB(128,0,0);
                leds[ledNum2] = CRGB(128,0,0);
                leds[ledNum3] = CRGB(128,0,0);
                leds[ledNum4] = CRGB(128,0,0);
                FastLED.show();
                delay(500);
              } else {
                leds[ledNum1] = CRGB(0,0,128);
                leds[ledNum2] = CRGB(0,0,128);
                leds[ledNum3] = CRGB(0,0,128);
                leds[ledNum4] = CRGB(0,0,128);
                FastLED.show();
                delay(500);
              }
            }
            for (int i = 0; i < 7; i++) {
              for (int j = 0; j < 7; j++) {
                ledNum = ledGrid[i][j];
                if (playerTurn == 1) {
                  leds[ledNum] = CRGB(128,0,0);
                } else  {
                  leds[ledNum] = CRGB(0,0,128);
                }
                FastLED.show();
                delay(50);
              }
            }
            delay(500);
            ResetBoard();
          
      }
    }
  }
}
void CheckTie() {
  bool noneAvailable = true;
  for (int i = 1; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      if (onOff[i][j] == 0) {
        noneAvailable = false;
      }
    }
  }
  if (noneAvailable) {
    ResetBoard();
  }
}

void ResetBoard() {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      onOff[i][j] = 0;
      ledNum = ledGrid[i][j];
      leds[ledNum] = CRGB(0,0,0);
      FastLED.show();
      delay(50);
    }
  }
  int i = 0; // up/down
  int j = 0; // left/right

  int ledNum = ledGrid[i][j];

  int isPlayerRedTurn = 1; // 1 = true, 0 = false
}