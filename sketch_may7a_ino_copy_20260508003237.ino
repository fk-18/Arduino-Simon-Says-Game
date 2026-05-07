#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int leds[] = {2, 3, 4, 5};
const int buttons[] = {6, 7, 8, 9};
const int buzzer = 10;

int patterns[3][3] = {
  {0},
  {1, 2},
  {3, 2, 1}
};

int lengthOfPattern[3] = {1, 2, 3};

void showMessage(String line1, String line2 = "", String line3 = "") {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(10, 15);
  display.println(line1);

  display.setCursor(10, 30);
  display.println(line2);

  display.setCursor(10, 45);
  display.println(line3);

  display.display();
}

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT_PULLUP);
  }

  pinMode(buzzer, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  showMessage("HELLO!");
  delay(1500);

  showMessage("LET'S PLAY!");
  delay(1500);
}

void loop() {

  for (int level = 0; level < 3; level++) {

    showMessage("ROUND " + String(level + 1));
    delay(1000);

    showPattern(level);

    if (!check(level)) {
      gameOver();
      showMessage("TRY AGAIN", "Restarting...");
      delay(1500);
      return;
    }

    tone(buzzer, 1200, 200);
    delay(500);
  }

  victory();
  showMessage("YOU WIN!", "Restarting...");
  delay(1500);

  return;
}

void showPattern(int level) {
  for (int i = 0; i < lengthOfPattern[level]; i++) {

    int led = patterns[level][i];

    digitalWrite(leds[led], HIGH);
    tone(buzzer, 1000, 200);
    delay(500);
    digitalWrite(leds[led], LOW);
    delay(300);
  }
}

bool check(int level) {
  for (int i = 0; i < lengthOfPattern[level]; i++) {

    int input = waitButton();

    if (input != patterns[level][i]) {
      return false;
    }
  }

  return true;
}

int waitButton() {
  while (true) {
    for (int i = 0; i < 4; i++) {

      if (digitalRead(buttons[i]) == LOW) {

        digitalWrite(leds[i], HIGH);
        delay(150);
        digitalWrite(leds[i], LOW);

        while (digitalRead(buttons[i]) == LOW);
        return i;
      }
    }
  }
}

void gameOver() {
  for (int i = 0; i < 3; i++) {

    showMessage("GAME OVER");

    tone(buzzer, 200, 400);

    for (int j = 0; j < 4; j++) {
      digitalWrite(leds[j], HIGH);
    }

    delay(400);

    for (int j = 0; j < 4; j++) {
      digitalWrite(leds[j], LOW);
    }

    delay(400);
  }
}

void victory() {
  for (int i = 0; i < 5; i++) {
    tone(buzzer, 1500, 200);
    delay(300);
  }
} this is the code