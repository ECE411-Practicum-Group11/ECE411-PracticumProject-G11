// UI + games

// Display libraries
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Pin number macro definitions
#define DISPLAY_CS 6
#define DISPLAY_DC 11
#define DISPLAY_RST 10
#define SCK PORTB1
#define MOSI PORTB2
#define MISO PORTB3
#define BUTTON_LEFT 19
#define BUTTON_UP 18
#define BUTTON_RIGHT 17
#define BUTTON_DOWN 16
#define BUTTON_A 15
#define BUTTON_B 14

// Initialize display object
Adafruit_ILI9341 tft = Adafruit_ILI9341(DISPLAY_CS, DISPLAY_DC, MOSI, SCK, DISPLAY_RST, MISO);

void setup() {
  Serial.begin(9600);
  tft.begin();
  
  // Print text to display for UI
  tft.setCursor(20, 20); // Cursor near top left corner
  tft.setTextColor(0xF800); // Red
  Serial.println("1. Floppy Derp");
  Serial.println("2. {Your Game Here!}");
  tft.println("1. Floppy Derp");
  tft.println();
  tft.println("2. {Your Game Here!}");

  // Initialize user button inputs
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
}

int gameSelect=1;

void loop() {
  mainMenu();
}

void mainMenu() {
  if (digitalRead(BUTTON_UP) == LOW && gameSelect != 2) // User selects the game they want to play on startup. Increase the max depending on # of user-added games
  {
    gameSelect = gameSelect + 1; // Also change the display to highlight, point to, or underline the higher number game
    Serial.println(gameSelect);
  }
  else if (digitalRead(BUTTON_DOWN) == LOW && gameSelect != 1)
  {
    gameSelect = gameSelect - 1; // Also change the display to highlight, point to, or underline the lower number game
    Serial.println(gameSelect);
  }
  else if (digitalRead(BUTTON_A) == LOW) // User confirms the game they want to play
  {
    runGame();
  }
}

void runGame() {
  if (gameSelect == 1) {
    FloppyDerp();
  }
  else if (gameSelect == 2) { // Play your own game!
    YourGame1();
  }
}

void FloppyDerp() {
  tft.setCursor(20, 20); // Cursor near top left corner
  tft.setTextColor(0xF800); // Red
  Serial.println("Play Floppy Derp! (if there's enough storage...)");
  Serial.println("(Press B to return to Main Menu)");
  tft.println("Play Floppy Derp! (if there's enough storage...)");
  tft.println();
  tft.println("(Press B to return to Main Menu)");
}

void YourGame1() {
  // Code your own game here! If you make more than one game, make sure to add the extra slot and change the GameSelect variable max in mainMenu. Also account for LCD display, etc
  Serial.println("Code your own game! See code file");  
  Serial.println("(Press B to return to Main Menu)");
  tft.setCursor(20, 20); // Cursor near top left corner
  tft.setTextColor(0xF800); // Red
  tft.println("Code your own game! See code file");
  tft.println();
  tft.println("(Press B to return to Main Menu)");
}
