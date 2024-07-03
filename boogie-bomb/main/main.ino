// Constants for pin numbers
const int BUTTON_PIN = 3;
const int GREEN_PIN = 10;
const int RED_PIN = 11;
const int BLUE_PIN = 9;

// Variables
bool partyOn = false; // Flag to track party state

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize button pin as input with internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initialize LED pins as outputs
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // Read button state
  bool buttonState = digitalRead(BUTTON_PIN);

  // Check for button press (transition from HIGH to LOW)
  if (buttonState == LOW) {
    // Debounce delay
    delay(50);
    buttonState = digitalRead(BUTTON_PIN); // Read again after debounce delay

    if (buttonState == LOW) {
      // Button is pressed, toggle party state
      partyOn = !partyOn;
      Serial.println(partyOn ? "Party ON" : "Party OFF");

      // Perform action based on current party state
      switch (partyOn) {
        case true:
          // Party is ON, perform party action (e.g., light show)
          rgbLightShow();
          break;
        case false:
          // Party is OFF, turn off all LEDs
          analogWrite(RED_PIN, 0);
          analogWrite(GREEN_PIN, 0);
          analogWrite(BLUE_PIN, 0);
          break;
      }

      // Wait for button release
      while (digitalRead(BUTTON_PIN) == LOW) {
        delay(50); // Debounce delay
      }
    }
  }
}

// Function to perform disco light show
void rgbLightShow() {
  // Array of colors (R, G, B values)
  int colors[][3] = {
    {255, 0, 0},    // Red
    {255, 127, 0},  // Orange
    {255, 255, 0},  // Yellow
    {0, 255, 0},    // Green
    {0, 0, 255},    // Blue
    {75, 0, 130},   // Indigo
    {148, 0, 211}   // Violet
  };

  int numColors = sizeof(colors) / sizeof(colors[0]);

  // Loop through each color
  while (partyOn) {
    for (int i = 0; i < numColors; i++) {
      // Set the color
      analogWrite(RED_PIN, colors[i][0]);
      analogWrite(GREEN_PIN, colors[i][1]);
      analogWrite(BLUE_PIN, colors[i][2]);

      // Blink the LEDs
      delay(500);  // Wait for 0.5 seconds
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 0);
      delay(500);  // Wait for 0.5 seconds
    }
  }
}
