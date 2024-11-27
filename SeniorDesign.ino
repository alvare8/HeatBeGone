// Include Libraries
#include <DHT.h>;

// Define the pin connected to the transistor's gate
const int transistorGatePin = 4;
const int windowGatePin = 5;
const int windowGatePinUp = 6;
const int tempSensor = A0;
const int thresholdTemperature = 30;
bool actionTriggered = false;

// Constants
#define DHTPIN A0
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Set the transistor gate pin as an output
  pinMode(transistorGatePin, OUTPUT);
  pinMode(windowGatePin, OUTPUT);
  pinMode(windowGatePinUp, OUTPUT);
  
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  
  // int analogTemp = analogRead(tempSensor);
  
  // // Convert the analog value to voltage (0 - 5V)
  // float voltage = analogTemp * (5.0 / 1023.0);
  
  // Convert the voltage to temperature in Celsius
  // TMP36 output is 500mV at 0°C and has a scale factor of 10mV/°C
  float temperatureC = dht.readTemperature();
  
  // Print temperature for debugging
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" C");
  
  if(temperatureC > thresholdTemperature && !actionTriggered){
    // Move motor forward
    digitalWrite(windowGatePin, HIGH);
    digitalWrite(windowGatePinUp, LOW);
    delay(2000); // Run for 2 seconds

    // Stop the motor
    digitalWrite(windowGatePin, LOW);
    digitalWrite(windowGatePinUp, LOW);
    delay(2000); // Run for 2 seconds
    
    // Turn on the transistor
    digitalWrite(transistorGatePin, HIGH);
    delay(2000);
    
    actionTriggered = true;

  }else if(temperatureC < thresholdTemperature && actionTriggered){
      // Turn off the transistor
      digitalWrite(transistorGatePin, LOW);
      delay(2000); // Run for 2 seconds
    
      // Move motor backward
      digitalWrite(windowGatePin, LOW);
      digitalWrite(windowGatePinUp, HIGH);
      delay(2000); // Run for 2 seconds

      // Stop the motor
      digitalWrite(windowGatePin, LOW);
      digitalWrite(windowGatePinUp, LOW);
      delay(2000); // Pause for 2 seconds

      actionTriggered = false;
    }  
  
}
