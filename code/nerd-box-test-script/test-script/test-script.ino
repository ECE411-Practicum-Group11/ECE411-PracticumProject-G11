// Script for testing hardware functionality of the Nerd Box console
// Writes text to the display and serial monitor corresponding to each hardware button when pressed

// Display libraries
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Pin number macro definitions
#define DISPLAY_CS 6
#define DISPLAY_DC 11
#define DISPLAY_RST 10

#define DISPLAY_LITE 9

#define BUTTON_LEFT A5
#define BUTTON_UP A4
#define BUTTON_RIGHT A3
#define BUTTON_DOWN A2
#define BUTTON_A A1
#define BUTTON_B A0

// Initialize display object
Adafruit_ILI9341 tft = Adafruit_ILI9341(DISPLAY_CS, DISPLAY_DC, MOSI, SCK, DISPLAY_RST, MISO);

void setup() {
  delay(100);
  Serial.begin(19200);
  pinMode(DISPLAY_LITE, OUTPUT);
  analogWrite(DISPLAY_LITE, 30);
  tft.begin();
  
  // Print debug text to serial monitor and dispaly
  Serial.println("Nerd Box test script v1.0");  
  tft.setRotation(3);
  tft.fillScreen(0x0000);
  tft.setCursor(20, 20); // Cursor near top left corner
  tft.setTextColor(0xF800, 0x0000); // Red with black fill
  tft.println("Nerd Box test script v1.0");
  tft.println();

  // Initialize user button inputs
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
}


// Storing button states for debouncing
byte upPress = LOW;
byte rightPress = LOW;
byte downPress = LOW;
byte leftPress = LOW;
byte aPress = LOW;
byte bPress = LOW;

// Storing time when buttons pressed for debouncing
unsigned long upTime = 0;
unsigned long rightTime = 0;
unsigned long downTime = 0;
unsigned long leftTime = 0;
unsigned long aTime = 0;
unsigned long bTime = 0;

void loop() {
  // Check button inputs
  // Print button name to serial monitor and display when pressed

  if (checkButton(BUTTON_UP, &upPress, &upTime)) {
    Serial.println("Up");
    tft.println("Up      ");
  }

  if (checkButton(BUTTON_RIGHT, &rightPress, &rightTime)) {
    Serial.println("Right");
    tft.println("Right  ");
  }

  if (checkButton(BUTTON_DOWN, &downPress, &downTime)) {
    Serial.println("Down");
    tft.println("Down   ");
  }

  if (checkButton(BUTTON_LEFT, &leftPress, &leftTime)) {
    Serial.println("Left");
    tft.println("Left    ");
  }

  if (checkButton(BUTTON_A, &aPress, &aTime)) {
    Serial.println("A");
    tft.println("A       ");
  }

  if (checkButton(BUTTON_B, &bPress, &bTime)) {
    Serial.println("B");
    tft.println("B      ");
  }

}

byte checkButton(int pinNumber, byte *buttonPress, unsigned long *buttonTime) {
  // Reads button press with debounce timer, based on debounce routine from arduino docs
  // buttonPress is the current state of the input, buttonTime is the time when the button state last changed from millis()
  // Pass pointers to variables containing button state and time

  byte buttonInput = digitalRead(pinNumber);
  if (*buttonPress != buttonInput) {
    // Record last time button pressed/released
    *buttonTime = millis();
  }

  if ((millis() - *buttonTime) > 50) {
    // Change button state after debounce period
    *buttonPress = buttonInput;

      if(*buttonPress == LOW) {
        // Return true if button is pressed after debounce period
        tft.setCursor(20, 40);
        return 1;
      }
  }

  // Returns false if button state was not changed to HIGH
  return 0;
}