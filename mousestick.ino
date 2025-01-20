#include <Mouse.h>

int horzPin = 28; // Can use any pin, but it needs to be capable of analog
int vertPin = 29;
int selPin = 27;

int vertZero, horzZero;
int sensitivity = 50;    // denominator for mouse movement
int deadZone = 10;       // jitter floor
bool mouseClickFlag = false;

unsigned long lastClickTime = 0;
unsigned long doubleClickThreshold = 250;

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
        Mouse.click(MOUSE_RIGHT);
        // Serial.println("Right Click");
      } else {
        Mouse.press(MOUSE_LEFT);
        // Serial.println("Left Click");
      }
      lastClickTime = currentTime;
    }
  } else {
    if (mouseClickFlag) {
      mouseClickFlag = false;
      Mouse.release(MOUSE_LEFT);
    }
  }

  delay(10);
}
