#include <Mouse.h>
#include <stdio.h>

int horzPin = 28; // Can use any pin, but it needs to be capable of analog
int vertPin = 29;
int selPin = 27;

int vertZero, horzZero;
int sensitivity = 50;    // denominator for mouse movement
int deadZone = 10;       // jitter floor
bool stickyMouse = false;
bool lowPin = false;

unsigned long clickBack1 = 0; // Previous click time
unsigned long clickBack2 = 0; // Previous previous click time
unsigned long clickThreshold = 500;

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
    lowPin = true;
  } 
  if (lowPin & digitalRead(selPin) == HIGH) {
    unsigned long click = millis();

    if (click - clickBack2 < clickThreshold) {
      Mouse.press(MOUSE_LEFT);
      stickyMouse = true;
    } else if (click - clickBack1 < clickThreshold & !stickyMouse) {
      Mouse.click(MOUSE_RIGHT);
    } else {
      if (!stickyMouse) {
        Mouse.click(MOUSE_LEFT);
      } else {
        Mouse.release(MOUSE_LEFT);
        stickyMouse = false;
      }
    }
    // Serial.printf("click=%lu clickBack1=%lu clickBack2=%lu\n", click, clickBack1, clickBack2);
    clickBack2 = clickBack1;
    clickBack1 = click;
    lowPin = false;
    } 
  delay(10);
}
