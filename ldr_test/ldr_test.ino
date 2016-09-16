// Sketch to test LDR DHT11, PIR sensors on UNO
// James R Barrett
// 13 Sept 2016

#include <math.h>
#include <DHT.h>
const byte interruptPin = 2;
volatile byte state = LOW;

#define DHTPIN 3     // what digital pin we're connected to

// Uncomment whatever DHT type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

void setup() {
 pinMode(interruptPin, INPUT);
 Serial.begin(9600);
 // Initialise DHT sensor
 dht.begin();
 // Setup interrupt for PIR motion detection
 attachInterrupt(digitalPinToInterrupt(interruptPin), motion, CHANGE);
}

void loop() {
 // read LDR raw
 int raw = analogRead(0);

 // Wait a few seconds between DHT measurements.
 delay(2000);
 // Reading temperature or humidity takes about 250 milliseconds!
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 
 // Read relative humidity (%)
 float h = dht.readHumidity();
 // Read temperature as Celsius
 float t = dht.readTemperature();

 // Check if any reads failed and exit early (to try again).
 if (isnan(h) || isnan(t)) {
  Serial.println("Failed to read from DHT sensor!");
  return;
 }
 
 // print temp and humidity
 Serial.print("Temperature: "); Serial.print(t); Serial.println(" deg C");
 Serial.print("Humidity: "); Serial.print(h); Serial.println(" % RH");
 // print LDR raw data
 Serial.print("LDR raw: "); Serial.println(raw);

}

void motion(){
  state = !state;
  sendMotion();
}

void sendMotion(){
  Serial.println("MOTION CHANGE");
}


