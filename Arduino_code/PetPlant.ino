// Library for SPI communication
#include <SPI.h>
// Graphics library for drawing text and shapes
#include <Adafruit_GFX.h>
// Driver library for the ILI9341 TFT display
#include <Adafruit_ILI9341.h>

// ------------------------------------------- DEFINE & VARIABLE ---------------------------------------------- //

// -------------------- TFT SCREEN -------------------- //

// Selects the TFT display for SPI communication
#define TFT_CS 14
// Tells the display whether data is a command or graphical content
#define TFT_DC 27
// Allows the ESP32 to reset the TFT display
#define TFT_RST 26
// Create the TFT display object using the configured pins
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

// -------------------- ANIMATION SPRITES -------------- //

// Sprite animations
#include "too_wet_sprites.h"
#include "healthy_sprites.h"
#include "thirsty_sprites.h"
#include "sleeping_sprites.h"

// -------------------- LIGHT SENSOR ------------------- //

// GPIO 35 - Analog input for the light sensor
#define LIGHT_SENSOR_PIN 35
// Store the sensor reading
int lightValue = 0;

// -------------------- HUMIDITY SENSOR ---------------- //

// GPIO 34 - Analog input for the humidity sensor
#define HUMIDITY_SENSOR_PIN 34
// Store the sensor reading
int humidityValue = 0;
int humidityPercent = 0;

// Sensor update interval
const unsigned long sensorInterval = 500;

// Time of the last sensor reading
unsigned long lastSensorTime = 0;

// ------------------------------------------- FUNCTION DECLARATION ------------------------------------------- //

// Display functions
void initDisplay();

// Sensor functions
void initSensors();
void readSensors();

// Animation functions
void initTooWetAnimation();
void updateTooWetAnimation();

// ------------------------------------------- SETUP ---------------------------------------------------------- //

void setup() 
{
  // Init the TFT screen
  initDisplay();

  // Init the light & humidity sensors as inputs
  initSensors();

  // Read the first sensor value
  readSensors();

  chooseSprite();

  // Display the initial humidity value
  displayHumidity();
}

// ------------------------------------------- LOOP ---------------------------------------------------------- //

void loop()
{
    // Get the current time
  unsigned long currentTime = millis();

  // Read sensors every 500 milliseconds
  if (currentTime - lastSensorTime >= sensorInterval)
  {
    lastSensorTime = currentTime;

    // Update humidity readings
    readSensors();
    // Update humidity on the TFT
    displayHumidity();
  }
  // Choose the right Anim
    chooseSprite();
}

// ------------------------------------------- FUNCTION UTILS ------------------------------------------------- //





// ------------------------------------------- NOTE ----------------------------------------------------------- //

/*

# Pet Plant — Pin Summary

| ESP32 Pin | Component | Function |
|---|---|---|
| GPIO 14 | TFT | Chip Select |
| GPIO 27 | TFT | Data / Command |
| GPIO 26 | TFT | Reset |
| GPIO 18 | TFT | SPI Clock (SCK) |
| GPIO 23 | TFT | SPI MOSI (Output data) |
| GPIO 19 | TFT | SPI MISO (Optional) |
| GPIO 35 | LDR | Analog light measurement |
| GPIO 34 | Soil sensor | Analog soil moisture measurement|
| GPIO 25 | Relay | Water pump control (planned) |
| 3V3 | Power | 3.3 V supply |
| GND | Ground | Common electrical reference |

*/
