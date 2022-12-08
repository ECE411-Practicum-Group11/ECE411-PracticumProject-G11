// Script for testing hardware functionality of the Nerd Box console
// Writes text to the display and serial monitor corresponding to each hardware button when pressed
// Uses the PDQ_GFX PDQ_ILI9341 libraries which optimize the default adafruit TFT display libraries for better speed and program size

// Display libraries
#include <SPI.h>

// Pin number macro definitions
#define DISPLAY_LITE 9

#define BUTTON_LEFT A5
#define BUTTON_UP A4
#define BUTTON_RIGHT A3
#define BUTTON_DOWN A2
#define BUTTON_A A1
#define BUTTON_B A0

// From the PDQ_GFX config file found in the library's repo
#define	ILI9341_CS_PIN		6			
#define	ILI9341_DC_PIN		11		
#define	ILI9341_RST_PIN   10			
#define	ILI9341_SAVE_SPI_SETTINGS	0

// Initialize display object
#include "PDQ_GFX.h"
#include "PDQ_ILI9341.h"

PDQ_ILI9341 tft;

void setup() {
  delay(100);
  Serial.begin(19200);
  pinMode(DISPLAY_LITE, OUTPUT);
  analogWrite(DISPLAY_LITE, 255);
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

  if ((millis() - *buttonTime) > 50) {
    if (*buttonPress != buttonInput) {
      *buttonTime = millis(); // Record last time button pressed/released
      *buttonPress = buttonInput; // Change button state

      if (*buttonPress == LOW) {
        return 1;
      }   
    }

  return 0;
  }

  // Returns false if button state was not changed to HIGH
  return 0;
}