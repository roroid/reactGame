//***********************************************************
//********************reactGAME******************************
//See who is the fastes button presser. Be the first to reach to 10 and you win the game.
//Circuit is made with 1 arduino pro mini,40 leds (10 for each player), 4pcs MCP23017 and 5 push buttons

#include <TrueRandom.h>//import library for real random numbers
#include <Bounce2.h>//debounce library for push buttons

#include <Wire.h>//i2c comunication with the MCP23017
#include <Bounce2mcp.h>//debounce library for push buttons connected to MCP23017
#include <Adafruit_MCP23017.h>//Adafruit MCP library
//button connections for each player
#define BUTTON_J1 15
#define BUTTON_J2 15
#define BUTTON_J3 15
#define BUTTON_J4 15
//various variables
boolean game_on, game = true;//variable to know when game is on or we need to generate a aditional random number
boolean led_on = false;//keep track of main led status
long intervalu;//random interval for lighting led
//main LED settings
#define LED_PIN 9//led is connected on pin 9
long previousMillis = 0;
int ledState = LOW;
//player 1
int player_1[10] = {12, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int scor_p1 = 0;
BounceMcp debouncer_1 = BounceMcp();
Adafruit_MCP23017 mcp1;

//player 2
int player_2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int scor_p2 = 0;
BounceMcp debouncer_2 = BounceMcp();
Adafruit_MCP23017 mcp2;

//player 3
int player_3[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int scor_p3 = 0;
BounceMcp debouncer_3 = BounceMcp();
Adafruit_MCP23017 mcp3;

//player 4
int player_4[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int scor_p4 = 0;
BounceMcp debouncer_4 = BounceMcp();
Adafruit_MCP23017 mcp4;

int j = 12;

Bounce reset = Bounce();


void setup() {
  // settings player 2
  mcp2.begin(0);
  mcp2.pinMode(BUTTON_J2, INPUT);
  mcp2.pullUp(BUTTON_J2, HIGH);
  debouncer_2.attach(mcp2, BUTTON_J2, 5);
  for (int i = 0; i <= 14; i++)
  { mcp2.pinMode(i, OUTPUT);
    mcp2.digitalWrite(i, LOW);
  }

  // settings player 1
  mcp1.begin(1);
  mcp1.pinMode(BUTTON_J1, INPUT);
  mcp1.pullUp(BUTTON_J1, HIGH);
  debouncer_1.attach(mcp1, BUTTON_J1, 5);
  for (int i = 0; i <= 14; i++)
  { mcp1.pinMode(i, OUTPUT);
    mcp1.digitalWrite(i, LOW);
  }

  // settings player 3
  mcp3.begin(2);
  mcp3.pinMode(BUTTON_J3, INPUT);
  mcp3.pullUp(BUTTON_J3, HIGH);
  debouncer_3.attach(mcp3, BUTTON_J3, 5);
  for (int i = 0; i <= 14; i++)
  { mcp3.pinMode(i, OUTPUT);
    mcp3.digitalWrite(i, LOW);
  }

  // settings player 4
  mcp4.begin(4);
  mcp4.pinMode(BUTTON_J4, INPUT);
  mcp4.pullUp(BUTTON_J4, HIGH);
  debouncer_4.attach(mcp4, BUTTON_J4, 5);
  for (int i = 0; i <= 14; i++)
  { mcp4.pinMode(i, OUTPUT);
    mcp4.digitalWrite(i, LOW);
  }

  Serial.begin(9600);
  // Setup the LED :
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  pinMode(2, INPUT_PULLUP);

  reset.attach(2);
  reset.interval(5);;
}

void loop() {
  //player 1
  debouncer_1.update();
  if ( debouncer_1.fell() && (led_on == true)) {
    mcp1.digitalWrite(player_1[scor_p1], HIGH);
    scor_p1++;
    Serial.println(1);
    digitalWrite(LED_PIN, LOW);
    game_on = true;
    led_on = false;
    if (scor_p1 == 10) {
      delay(500);
      scor_p1 = 0;
      game = false;
      castigator(1);
    }
  }

  //player 2
  debouncer_2.update();
  if ( debouncer_2.fell() && (led_on == true)) {
    mcp2.digitalWrite(player_2[scor_p2], HIGH);
    scor_p2++;
    Serial.println(2);
    digitalWrite(LED_PIN, LOW);
    game_on = true;
    led_on = false;
    if (scor_p2 == 10) {
      delay(500);
      scor_p2 = 0;
      game = false;
      castigator(2);
    }
  }


  //player 3
  debouncer_3.update();
  if ( debouncer_3.fell() && (led_on == true)) {
    mcp3.digitalWrite(player_3[scor_p3], HIGH);
    scor_p3++;
    Serial.println(3);
    digitalWrite(LED_PIN, LOW);
    game_on = true;
    led_on = false;
    if (scor_p3 == 10) {
      delay(500);
      scor_p3 = 0;
      game = false;
      castigator(3);
    }
  }


  //player 4
  debouncer_4.update();
  if ( debouncer_4.fell() && (led_on == true)) {
    mcp4.digitalWrite(player_4[scor_p4], HIGH);
    scor_p4++;
    Serial.println(4);
    digitalWrite(LED_PIN, LOW);
    game_on = true;
    led_on = false;
    if (scor_p4 == 10) {
      delay(500);
      scor_p4 = 0;
      game = false;
      castigator(4);
    }
  }



  //light led at random intervals
  if ((game_on == true) && (led_on == false)) {
    intervalu = TrueRandom.random(5, 15);
    intervalu = intervalu * 1000;
    game_on = false;
    previousMillis = millis();
  }

  if (led_on == false) {

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > intervalu) {
      previousMillis = currentMillis;
      digitalWrite(LED_PIN, HIGH);
      led_on = true;
      Serial.println(intervalu);
    }
  }
  reset.update();
  int val = reset.read();

  if (val == LOW) {
    reset_();
  }

  Serial.println(led_on);



}

//clean score
void curatator() {
  for (int i = 0; i <= 14; i++)
  { mcp1.digitalWrite(i, LOW);
    mcp2.digitalWrite(i, LOW);
    mcp3.digitalWrite(i, LOW);
    mcp4.digitalWrite(i, LOW);
  }
}

void castigator(int nr) {
  while (game == false) {
    reset.update();
    int val = reset.read();

    if (val == LOW) {
      reset_();
    }
    if (nr == 1) {
      for (int i = 0; i <= 14; i++)
      { mcp1.digitalWrite(i, LOW);
      }
      delay(400);
      for (int i = 0; i <= 14; i++)
      { mcp1.digitalWrite(i, HIGH);
      }
      delay(400);
    }
    if (nr == 2) {
      for (int i = 0; i <= 14; i++)
      { mcp2.digitalWrite(i, LOW);
      }
      delay(400);
      for (int i = 0; i <= 14; i++)
      { mcp2.digitalWrite(i, HIGH);
      }
      delay(400);
    }
    if (nr == 3) {
      for (int i = 0; i <= 14; i++)
      { mcp3.digitalWrite(i, LOW);
      }
      delay(400);
      for (int i = 0; i <= 14; i++)
      { mcp3.digitalWrite(i, HIGH);
      }
      delay(400);
    }
    if (nr == 4) {
      for (int i = 0; i <= 14; i++)
      { mcp4.digitalWrite(i, LOW);
      }
      delay(400);
      for (int i = 0; i <= 14; i++)
      { mcp4.digitalWrite(i, HIGH);
      }
      delay(400);
    }

  }
}

//procedure to reset the board
void reset_() {
  game = true;
  digitalWrite(LED_PIN, LOW);

  curatator();
  game_on = true;
  scor_p3 = 0;
  scor_p1 = 0;
  scor_p2 = 0;
  scor_p4 = 0;
  led_on = false;
  previousMillis = millis();

  Serial.println("RES");
}
