// UI + games

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

#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF
#define SKY      0x6DFE

// From the PDQ_GFX config file found in the library's repo
#define    ILI9341_CS_PIN               6            
#define    ILI9341_DC_PIN              11        
#define    ILI9341_RST_PIN             10            
#define    ILI9341_SAVE_SPI_SETTINGS    0

// Initialize display object
#include <PDQ_GFX.h>
#include <PDQ_ILI9341.h>
#include <Adafruit_FT6206.h>

PDQ_ILI9341 tft;
Adafruit_FT6206 ts = Adafruit_FT6206();


int gameSelect;

// Floppy derp variables
// Sprite bit map
const PROGMEM uint8_t ballBitMap[21 * 21] = {
    0x01, 0xfc, 0x00, 0x07, 0xff, 0x00, 0x0f, 0xff, 0x80, 0x1f, 0xff, 0xc0, 0x3f, 0xff, 0xe0, 0x7f, 
	0xff, 0xf0, 0x7f, 0xff, 0xf0, 0xf9, 0xfc, 0xf8, 0xf9, 0xfc, 0xf8, 0xff, 0xff, 0xf8, 0xff, 0xff, 
	0xf8, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf8, 0xf9, 0xfc, 0xf8, 0x78, 0xf8, 0xf0, 0x7c, 0x01, 0xf0, 
	0x3e, 0x03, 0xe0, 0x1f, 0xff, 0xc0, 0x0f, 0xff, 0x80, 0x07, 0xff, 0x00, 0x01, 0xfc, 0x00};

// Initialize global vars
int Screen=0;
int screenWidth=320;
int screenHeight=240;
int borderHeight = 25;
int score = 0;
byte scoreUpdated = 0;

// Ball vars
int ballX=screenWidth/5;
int ballY=screenHeight/4;
int ballSize = 21;
int ballColors[6] = {RED, YELLOW, GREEN, BLUE, MAGENTA, CYAN};
int ballSelect = 0;
int ballColor = ballColors[ballSelect+1];
int oldY=ballY;

// Pipe vars
int pipeX = screenWidth;
int pipeY = 100;
int oldPipeY;
int pipeWidth = 40;
int pipeSpacing = 80;
float pipeSpeed = 5;
float pipeIncrement = 0.1;

// Gravity vars
float gravity = 2;
float ballSpeedVert = 0;
int jumpHeight = 10;
float terminalSpeed = 30;

// Storing button states for debouncing
byte upPress = LOW;
byte rightPress = LOW;
byte downPress = LOW;
byte leftPress = LOW;
byte aPress = LOW;
byte bPress = LOW;
byte touchPress = LOW;

// Storing time when buttons pressed for debouncing
unsigned long upTime = 0;
unsigned long rightTime = 0;
unsigned long downTime = 0;
unsigned long leftTime = 0;
unsigned long aTime = 0;
unsigned long bTime = 0;
unsigned long touchTime = 0;

unsigned long timeSince = 0;

byte quitSelect = 0;
byte quitGame = 0;

// End floppy derp variables

void setup() {
  Serial.begin(9600);
  delay(300);
  tft.begin();
  ts.begin();
  tft.setRotation(3);

  // Initialize user button inputs
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
}

void loop() {
  mainMenu();
}

void mainMenu() {
  gameSelect=1; // Reset gameSelect var
  // Print text to display for UI
  tft.setRotation(3);
  tft.fillScreen(BLACK);
  tft.setCursor(20, 20); // Cursor near top left corner
  tft.setTextColor(BLUE, YELLOW); // Blue w/ black background to show game selection
  tft.println("1. Floppy Derp                                  ");
  tft.setTextColor(RED, BLACK); // Red w/ black background
  tft.setCursor(20, 35); // Cursor on line below
  tft.println("2. {Your Game Here!}                            ");
  
  while (true) { // Button states
    if (digitalRead(BUTTON_UP) == LOW && gameSelect != 1) // User selects the game they want to play on startup. Increase the max depending on # of user-added games
    {
    gameSelect = gameSelect - 1;
    tft.setCursor(20, 20); // Cursor to Floppy Derp line on Menu
    tft.setTextColor(BLUE, YELLOW); // Highlight Floppy Derp in yellow
    tft.println("1. Floppy Derp                                  ");
    tft.setCursor(20, 35); // Cursor near top left corner
    tft.setTextColor(RED, BLACK); // Remove highlight from other menu options
    tft.println("2. {Your Game Here!}                            ");
    }
    else if (digitalRead(BUTTON_DOWN) == LOW && gameSelect != 2)
    {
    gameSelect = gameSelect + 1; // Also change the display to highlight, point to, or underline the lower number game
    tft.setCursor(20, 20); // Cursor to Floppy Derp line on Menu
    tft.setTextColor(RED, BLACK); // Highlight Floppy Derp in yellow
    tft.println("1. Floppy Derp                                  ");
    tft.setCursor(20, 35); // Cursor on line below
    tft.setTextColor(BLUE, YELLOW); // Highlight Floppy Derp in yellow
    tft.println("2. {Your Game Here!}                            ");
    }
    else if (digitalRead(BUTTON_A) == LOW) // User confirms the game they want to play
    {
      break;
    }
    }
  runGame();
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
  initializeGame();
  Screen = 0;
  /********* SETUP BLOCK *********/
  randomSeed(millis());
  drawBackground();
  initScreen();
  while (true) {
    if (quitGame) {
      quitGame = 0;
      quitSelect = 0;
      break;
    }
    // Display the contents of the current screen
    if(millis() - timeSince > 75){
      timeSince = millis();
      if (Screen == 0) {
        initScreen(); // Initial Screen
      }
      else if (Screen == 1) {
        gameScreen(); // Game Play Screen
      }
      else if (Screen == 2) {
        gameOverScreen(); // Game Over Screen
      }
      else if (Screen == 3) {
        pauseScreen(); // Pause Screen
      }
    }
      
    if (checkButton(digitalRead(BUTTON_A), &aPress, &aTime) || checkButton(ts.touched(), &touchPress, &touchTime)) { // Press A, play game
      if (Screen == 0) { // Initial screen
        drawBackground();
        Screen=1; // Game screen
      }
      else if (Screen == 1) { // Game screen
        jump();
      }
      else if (Screen == 2) {// Game over screen
        if (quitSelect) {
          // Return to main menu
          quitGame = 1;
        }
        else {
          drawBackground();
          initializeGame();
          Screen = 0; // Restart the game
        }
      }
      else if (Screen == 3) { // Pause screen
        if (quitSelect) {
          // Return to main menu
          quitGame = 1;
        }
        else {
          drawBackground();
          Screen = 1; // Unpause game
        }
      }
    }

    if (checkButton(digitalRead(BUTTON_B), &bPress, &bTime)) { // Press B to pause
      if (Screen == 1) { // If in game screen
        drawPauseScreen();
        quitSelect = 0;
        Screen = 3; // Pause the game
      }
      else if (Screen == 3) { // If on pause screen
        drawBackground();
        Screen = 1; // Unpause the game
      }
    }

    if (checkButton(digitalRead(BUTTON_LEFT), &leftPress, &leftTime)) {
      if (Screen == 0) {
        // Change ball color selection
        int arraySize = sizeof(ballColors) / sizeof(ballColors[0]);
        ballSelect--;
        ballSelect = (ballSelect + arraySize) % arraySize;
      }
      else if (Screen == 2 || Screen == 3) { // If on game over or pause screen
        quitSelect = 0; // Select "Don't return to main menu"
      }
    }

    if (checkButton(digitalRead(BUTTON_RIGHT), &rightPress, &rightTime)) {
      if (Screen == 0) {
        // Change ball color selection
        int arraySize = sizeof(ballColors) / sizeof(ballColors[0]);
        ballSelect++;
        ballSelect = (ballSelect + arraySize) % arraySize;
      }
      else if (Screen == 2 || Screen == 3) { // If on game over or pause screen
        quitSelect = 1; // Select "Return to main menu"
      }
    }
  }
}

void YourGame1() {
  // Code your own game here! If you make more than one game, make sure to add the extra slot and change the GameSelect variable max in mainMenu. Also account for LCD display, etc
  tft.fillScreen(BLACK); // Clear the screen
  tft.setCursor(20, 20); // Cursor near top left corner
  tft.setTextColor(RED, BLACK); // Red
  tft.println("Code your own game! See code file                 ");
  tft.setCursor(20, 35); // Cursor near top left corner
  tft.println("(Press B to return to Main Menu)                ");
  while (true){
    if (digitalRead(BUTTON_B) == LOW) {
    return;
  }
  }
}





/* -------------------------------------------------------
    FLOPPY DERP STUFF
   -------------------------------------------------------
   
*/

void drawBackground() {
  // Draw game background when starting or exiting menus
  tft.fillScreen(SKY);
  tft.fillRect(0, 0, screenWidth, borderHeight, BLACK);
}

void initScreen() {
  // Draw game title
  tft.setCursor(62, 75);
  tft.setTextSize(3);
  tft.setTextColor(ballColor, SKY);
  tft.print("Floppy Derp");
  
  tft.setCursor(65, 130);
  tft.setTextSize(2);
  tft.print("Select your derp");

  // Display ball collor selection
  int arraySize = sizeof(ballColors) / sizeof(ballColors[0]);
  for(int i = 0; i < arraySize; i++) {
    tft.drawBitmap(screenWidth*(i+1)/(arraySize+1)-ballSize/2, screenHeight*2/3, ballBitMap, ballSize, ballSize, ballColors[(i+ballSelect)%arraySize], SKY);
  }

  // Select the second ball that is displayed
  int selectionX = screenWidth * 2/(arraySize+1) - ballSize/2 - 5;
  tft.drawRect(selectionX,screenHeight*2/3 - 5, ballSize + 10, ballSize + 10, BLACK); // Draw box around selection
  ballColor = ballColors[(ballSelect + 1) % arraySize];
}

void gameScreen() {
  // Draw objects and update values each loop
  drawBall();
  drawPipe();
  updateScore();
  applyGravity();
  keepInScreen();
}
void gameOverScreen() {
  // Game over screen
  // Prompt retry. If no, return to main menu
  tft.setCursor(98, 75);
  tft.setTextSize(2);
  tft.setTextColor(WHITE, BLACK);
  tft.print("GAME OVER");

  tft.setTextSize(1);
  tft.setCursor(135, 105);
  tft.print("Retry?");

  if (!quitSelect) {
    tft.setTextColor(BLUE, YELLOW);
    tft.setCursor(120, 135);
    tft.print("Yes");
    tft.setTextColor(WHITE, BLACK);
    tft.setCursor(180, 135);
    tft.print("No");
  }
  else {
    tft.setTextColor(WHITE, BLACK);
    tft.setCursor(120, 135);
    tft.print("Yes");
    tft.setTextColor(BLUE, YELLOW);
    tft.setCursor(180, 135);
    tft.print("No");
  }

}

void pauseScreen() {
  // Pause menu to let user return to game selection menu
  tft.setCursor(94, 75);
  tft.setTextSize(2);
  tft.setTextColor(WHITE, BLACK);
  tft.print("GAME PAUSED");

  tft.setTextSize(1);
  tft.setCursor(99, 105);
  tft.print("Return to main menu?");

  if (!quitSelect) {
    tft.setTextColor(BLUE, YELLOW);
    tft.setCursor(120, 135);
    tft.print("No");
    tft.setTextColor(WHITE, BLACK);
    tft.setCursor(180, 135);
    tft.print("Yes");
  }
  else {
    tft.setTextColor(WHITE, BLACK);
    tft.setCursor(120, 135);
    tft.print("No");
    tft.setTextColor(BLUE, YELLOW);
    tft.setCursor(180, 135);
    tft.print("Yes");
  }

}

void drawPauseScreen() {
  tft.fillRect(screenWidth/4, screenHeight/4, screenWidth/2, screenHeight/2, BLACK); // Draw pause menu background
}

void drawBall() {
  // Draw ball after updating position
  tft.drawBitmap(ballX, ballY, ballBitMap, ballSize, ballSize, ballColor, SKY);
  clearBall();
}

void clearBall() {
  // Erase old ball pixels after updating position
  int edge = oldY;
  if ((ballY - oldY) < 0) {
    edge = ballY + ballSize;
  }

  tft.fillRect(ballX, edge, ballSize, abs(ballY - oldY), SKY);
}

void applyGravity() {
  // Gravity calculations for ball
  // Updates ball position and checks for collisions
  ballSpeedVert += gravity;
  if (ballSpeedVert > terminalSpeed) {
    ballSpeedVert = terminalSpeed;
  }
  oldY = ballY;
  ballY += ballSpeedVert;
  checkCollision();
}




// keep ball in the screen

void keepInScreen() {
  // ball hits floor
  if (ballY+ballSize > screenHeight) { 
    ballY = screenHeight - ballSize;
  }
  // ball hits ceiling
  if (ballY < borderHeight) {
    ballY = borderHeight;
  }
}

void jump() {
  // Makes the ball jump on button press
  ballSpeedVert = -jumpHeight;
  ballY += ballSpeedVert;
  keepInScreen();
}

void drawPipe() {
  // Draws pipe and erases previous pipe position
  if(pipeX < -pipeSpeed) {
    // Makes new pipe once old pipe reaches left side of screen
    pipeX = screenWidth;
    oldPipeY = pipeY; // Previous pipe position for clearing last bits
    pipeY = random(30, 150);

  }

  // Draw pipe
  tft.fillRect(pipeX, borderHeight, pipeWidth, pipeY-borderHeight, BLACK);
  tft.fillRect(pipeX, pipeY+pipeSpacing, pipeWidth, screenHeight-pipeY-pipeSpacing, BLACK);

  // Erase previous pipe position
  tft.fillRect(pipeX+pipeWidth, borderHeight, ceil(pipeSpeed), pipeY-borderHeight, SKY);
  tft.fillRect(pipeX+pipeWidth, pipeY+pipeSpacing, ceil(pipeSpeed), screenHeight-pipeY-pipeSpacing, SKY);

  if(pipeX + pipeSpeed > screenWidth - pipeWidth) {
    // Erase remnants of the last pipe after new one is created
    tft.fillRect((pipeX+pipeWidth-screenWidth-pipeSpeed), borderHeight, ceil(pipeSpeed), oldPipeY-borderHeight, SKY);
    tft.fillRect((pipeX+pipeWidth-screenWidth-pipeSpeed), oldPipeY+pipeSpacing, ceil(pipeSpeed), screenHeight-oldPipeY-pipeSpacing, SKY);
  }


  pipeX -= pipeSpeed; // Move pipe to the left
}

void checkCollision() {
  if ((pipeX < ballX+ballSize) && (pipeX+pipeWidth > ballX)) {
    // If pipe has reached the ball
    if (ballY < pipeY) {
      // If ball is above the pipe
      ballY = pipeY; // Ball stops at pipe
      drawBall();
      tft.fillRect(screenWidth/4, screenHeight/4, screenWidth/2, screenHeight/2, BLACK); // Draw pause menu background
      aTime = millis() + 1200; // Pause inputs for short time on game over
      touchTime = millis() + 1200;
      quitSelect = 0;
      Screen = 2; // Game over screen
    }
    if (ballY+ballSize > pipeY+pipeSpacing) {
      // If ball is below the pipe
      ballY = pipeY + pipeSpacing - ballSize; // Ball stops at pipe
      drawBall();
      tft.fillRect(screenWidth/4, screenHeight/4, screenWidth/2, screenHeight/2, BLACK); // Draw pause menu background
      aTime = millis() + 1200; // Pause inputs for short time on game over
      touchTime = millis() + 1200;
      quitSelect = 0;
      Screen = 2; // Game over screen
    }
  }
}

void updateScore() {
  if (!scoreUpdated && pipeX < ballX) {
    // When ball reaches pipe increment score
    score++;
    pipeSpeed += pipeIncrement; // Make pipes faster as game progresses
    scoreUpdated = 1; // Stops from incrementing again until after pipe is passed
  }
  if (pipeX > ballX) {
    scoreUpdated = 0; // Once pipe is passed, allow score increase
  }

  tft.setTextSize(2); // Update score text
  tft.setTextColor(WHITE, BLACK);
  tft.setCursor(155, 5);
  if (score > 9) tft.setCursor(145, 5);
  if (score > 99) tft.setCursor(135, 5);
  tft.print(score);
}

void initializeGame() {
  // Initialize the game variables when restarting
  score = 0;

  // Ball vars
  ballY=screenHeight/4;
  oldY=ballY;

  // Pipe vars
  pipeX = screenWidth;
  pipeY = 100;
  pipeSpeed = 5;
}

byte checkButton(byte buttonInput, byte *buttonPress, unsigned long *buttonTime) {
  // Reads button press with debounce timer, based on debounce routine from arduino docs
  // buttonPress is the current state of the input, buttonTime is the time when the button state last changed from millis()
  // Pass pointers to variables containing button state and time

  if ((millis() - *buttonTime) > 50) {
    if (*buttonPress != buttonInput) {
      *buttonTime = millis(); // Record last time button pressed/released
      *buttonPress = buttonInput; // Change button state

      if (*buttonPress == LOW) {
        return 1; // Return true if button state was changed to low
      }   
    }
      
    return 0;
  }

  // Returns false if button state was not changed to LOW
  return 0;
}
