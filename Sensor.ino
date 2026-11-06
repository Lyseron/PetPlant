
 // ------------------------------------------- DEFINE & VARIABLE ---------------------------------------------- //

// Soil moisture calibration values
#define SOIL_DRY 3300
#define SOIL_WET 1300

// ------------------------------------------- FUNCTION UTILS ------------------------------------------------- //

void initSensors()
{
  // Set ADC resolution to 12 bits (0-4095)
  analogReadResolution(12);

  // Configure sensors as analog inputs
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  pinMode(HUMIDITY_SENSOR_PIN, INPUT);
}

void readSensors()
{
  // Read the raw light sensor value
  lightValue = analogRead(LIGHT_SENSOR_PIN);

  // Read the raw soil moisture value
  humidityValue = analogRead(HUMIDITY_SENSOR_PIN);

  // Convert raw soil moisture to percentage
  humidityPercent = map(
    humidityValue,
    SOIL_DRY,
    SOIL_WET,
    0,
    100
  );

  // Keep humidity between 0% and 100%
  humidityPercent = constrain(humidityPercent, 0, 100);
}