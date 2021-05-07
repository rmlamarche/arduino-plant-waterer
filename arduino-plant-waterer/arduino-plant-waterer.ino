#define SOIL_SENSOR_POWER_PIN 13
#define WATER_PUMP_POWER_PIN 4
#define SOIL_SENSOR_PIN A1
#define WATERING_TIME_MS 7000
#define SOIL_MOISTURE_THRESHOLD 300

const unsigned long SECOND = 1000;
const unsigned long HOUR = SECOND * 60 * 60;
const unsigned long DELAY_MS = HOUR * 6;  // 6 hours in MS
int soilMoisture = 0;

// read soil moisture level from sensor and return result
int getSoilMoisture() {
  digitalWrite(SOIL_SENSOR_POWER_PIN, HIGH);
  delay(200);
  int result = analogRead(SOIL_SENSOR_PIN);
  delay(200);
  digitalWrite(SOIL_SENSOR_POWER_PIN, LOW);
  return result;
}

// pump water for t ms
void pumpWater(int t) {
  digitalWrite(WATER_PUMP_POWER_PIN, HIGH);
  delay(t);
  digitalWrite(WATER_PUMP_POWER_PIN, LOW);
}

// blinks once for every 100 soilMoisture
// if soilMoisture is 750, blinks 7 times
void blink_moisture() {
    int soilMoistureHundreds = (int) soilMoisture / 100;
    for (int i = 0; i < soilMoistureHundreds; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(400);
    }
}

void setup() {
  // Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SOIL_SENSOR_POWER_PIN, OUTPUT);
  pinMode(WATER_PUMP_POWER_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  soilMoisture = getSoilMoisture();
  // Serial.println(soilMoisture);
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);
  blink_moisture();
  delay(2000);
  if (soilMoisture < SOIL_MOISTURE_THRESHOLD) {
    digitalWrite(LED_BUILTIN, HIGH);
    pumpWater(WATERING_TIME_MS);
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(DELAY_MS);
}
