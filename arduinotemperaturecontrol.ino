/ Include the necessary libraries
#include <Arduino.h>
#include <SimpleTimer.h>

// Define the analog pin for the LM35 temperature sensor
const int lm35Pin = A0;

// Define the onboard LED pin
const int ledPin = 13;

// Variable to store the temperature value
int temperature = 0;

// Create an instance of SimpleTimer
SimpleTimer timer;

// Function prototypes
void blinkLed();

void setup() {
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
  
  // Initialize serial communication
  Serial.begin(9600);

  // Attach the blinkLed function to the timer
  timer.setInterval(250, blinkLed);
}

void loop() {
  // Read the analog value from the LM35 temperature sensor
  int sensorValue = analogRead(lm35Pin);
  
  // Convert the analog value to temperature in degrees Celsius
  temperature = sensorValue * 0.488; // (5.0 / 1023) * 100
  
  // Print the temperature value to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  // Check if temperature is below 30°C
  if (temperature < 30) {
    // Change the blink interval to 250ms
    timer.changeInterval(250, blinkLed);
  } else {
    // Change the blink interval to 500ms
    timer.changeInterval(500, blinkLed);
  }

  // Update the timer
  timer.run();
}

// Function to blink the LED
void blinkLed() {
  // Toggle the LED state
  digitalWrite(ledPin, !digitalRead(ledPin));
}
