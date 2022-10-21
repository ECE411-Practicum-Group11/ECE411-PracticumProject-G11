// This program is just a test to make a bouncing ball in arduino using a 2x16 LCD
// The ball jumps and bounces when a key is pressed.
// This is a precursor to making the ball jump with motion controls

#include <LiquidCrystal.h>

#define SET_POINT 1.25 // Initial ball velocity
#define GRAVITY 0.1
#define PERIOD 50 // Time between frames in milliseconds

// ---- From Arduino learn LCD page ----
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// -------------------------------------

// Initializing variables
int lcdpos = 0;
float ballpos = 0;
float gravity = GRAVITY;
float ballspeed = SET_POINT;
char input;
unsigned long currTime = 0;


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(115200);
  currTime = millis();
  Serial.println(currTime);
}

void loop() {
  // Advance animation after the desired time has elapsed
  if((millis() - currTime) >= PERIOD){
    currTime = millis();
    animation();
  }
  // Jump when 'q' is entered into the serial port
  if(Serial.available() > 0){
    input = Serial.read();
    if(input == 'q'){
      ballspeed = SET_POINT;
    }
  }

}

void animation(){
  // Update ball position and velocity
  ballspeed -= gravity;
  ballpos += ballspeed;

  // Bounce when height reaches 0
  if(ballpos <= 0){
    ballpos = 0;
    ballspeed *= -0.8; // Ball bounces with friction
  }

  // Debug logs
  //Serial.println("");
  //Serial.print(ballspeed);
  //Serial.print(", ");
  //Serial.print(ballpos);
  
  lcdpos = floor(ballpos);
  //Serial.print(", ");
  //Serial.print(lcdpos);

  // Draw ball when within screen bounds
  lcd.clear();
  lcd.setCursor(lcdpos, 0);
  if((lcdpos >= 0) && (lcdpos < 16)){
    lcd.print("O");
  }
}