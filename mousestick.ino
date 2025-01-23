#include <Mouse.h>

int horzPin = 28; // Can use any pin, but it needs to be capable of analog
int vertPin = 29;
int selPin = 27;

int vertZero, horzZero;
int sensitivity = 50;    // denominator for mouse movement
int deadZone = 10;       // jitter floor
bool mouseClickFlag = false;
bool stickyMouse = false;

unsigned long lastClickTime = 0;
unsigned long doubleClickThreshold = 250;
unsigned long tripleClickThreshold = 300;
int clickCount = 0;

void setup() {
  pinMode(selPin, INPUT_PULLUP);
  vertZero = analogRead(vertPin);
  horzZero = analogRead(horzPin);
  Serial.begin(9600);
  Mouse.begin();
}

void loop() {
  int vertValue = analogRead(vertPin) - vertZero;
  int horzValue = analogRead(horzPin) - horzZero;

    /*
  Serial.print("Vert: ");
  Serial.print(vertValue);
  Serial.print(" Horz: ");
  Serial.println(horzValue);
  */

  if (abs(vertValue) > deadZone) {
    Mouse.move(0, -vertValue / sensitivity, 0);
  }
  if (abs(horzValue) > deadZone) {
    Mouse.move(horzValue / sensitivity, 0, 0);
  }

  if (digitalRead(selPin) == LOW) {
    if (!mouseClickFlag) {
      mouseClickFlag = true;
      
      unsigned long currentTime = millis();
      if (currentTime - lastClickTime < doubleClickThreshold) {
        clickCount++;
      } else {
        clickCount = 1; // Reset if the time between clicks is too long
      }

      lastClickTime = currentTime;

      if (clickCount == 2) {
        Mouse.click(MOUSE_RIGHT);
        //Serial.println("Right Click");
      } else if (clickCount == 3) {
        stickyMouse = !stickyMouse;
        if (stickyMouse) {
          Mouse.press(MOUSE_LEFT);
          //Serial.println("Sticky Click On");
        } else {
          Mouse.release(MOUSE_LEFT);
          //Serial.println("Sticky Click Off");
        }
        clickCount = 0; // Reset click count after a triple click
      } else {
        if (!stickyMouse) {
          Mouse.press(MOUSE_LEFT);
          //Serial.println("Left Click");
        }
      }
    }
  } else {
    if (mouseClickFlag) {
      mouseClickFlag = false;
      if (!stickyMouse) {
        Mouse.release(MOUSE_LEFT);
      }
    }
  }

  delay(10);
}
