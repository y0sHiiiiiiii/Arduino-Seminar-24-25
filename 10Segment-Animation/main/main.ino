// Define the pins for the segments
const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

void setup() {
  // Initialize all segment pins as outputs
  for (int i = 0; i < 10; ++i) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop() {
  // Bouncing animation: Pattern moves back and forth across the segments
  for (int i = 0; i < 10; ++i) {
    // Turn on the current segment
    digitalWrite(segmentPins[i], HIGH);
    // Delay to display the segment (adjust as needed)
    delay(50); // 50 milliseconds
    // Turn off the current segment
    digitalWrite(segmentPins[i], LOW);
  }
  
  for (int i = 8; i >= 1; --i) {
    // Turn on the current segment
    digitalWrite(segmentPins[i], HIGH);
    // Delay to display the segment (adjust as needed)
    delay(50); // 50 milliseconds
    // Turn off the current segment
    digitalWrite(segmentPins[i], LOW);
  }
  
  delay(500); // 500 milliseconds delay between animations
}
