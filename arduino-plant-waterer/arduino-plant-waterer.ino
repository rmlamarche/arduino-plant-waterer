#define SOIL_SENSOR_POWER_PIN 13
#define WATER_PUMP_POWER_PIN 4
#define SOIL_SENSOR_PIN A1
#define DELAY_MS 30000
#define WATERING_TIME_MS 7000
#define SOIL_MOISTURE_THRESHOLD 100

int soilMoisture = 0;

int getSoilMoisture() {
  digitalWrite(SOIL_SENSOR_POWER_PIN, HIGH);
  delay(200);
  int result = analogRead(SOIL_SENSOR_PIN);
  delay(200);
  digitalWrite(SOIL_SENSOR_POWER_PIN, LOW);
  return result;
}

void pumpWater(int t) {
  digitalWrite(WATER_PUMP_POWER_PIN, HIGH);
  delay(t);
  digitalWrite(WATER_PUMP_POWER_PIN, LOW);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SOIL_SENSOR_POWER_PIN, OUTPUT);
  pinMode(WATER_PUMP_POWER_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  soilMoisture = getSoilMoisture();
  if (soilMoisture < SOIL_MOISTURE_THRESHOLD) {
    pumpWater(WATERING_TIME_MS);
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(DELAY_MS);
}
