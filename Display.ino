#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// ------------------------------------------- DEFINE & VARIABLE ---------------------------------------------- //



// ------------------------------------------- FUNCTION UTILS ------------------------------------------------- //

void initDisplay()
{
  tft.begin();

  // Portrait mode (240x320)
  tft.setRotation(0);
  tft.fillScreen(ILI9341_BLACK);

  // tft.setTextColor(ILI9341_GREEN);
  // tft.setTextSize(3);
  // tft.setCursor(35, 20);
  // tft.print("Pet Plant");

  // Display sensor labels
  // Display the soil moisture label
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(15, 260);
  tft.print("Humidity:");
}

void displayHumidity()
{
  // Clear the previous humidity value
  tft.fillRect(120, 255, 105, 25, ILI9341_BLACK);

  // Configure the text appearance
  tft.setTextColor(ILI9341_CYAN);
  tft.setTextSize(2);

  // Set the text position
  tft.setCursor(120, 260);

  // Display the soil moisture percentage
  tft.print(humidityPercent);
  tft.print("%");
}


void drawScaledSprite(const uint16_t* sprite, int x, int y, int scale)
{
  // Original sprite dimensions
  const int spriteWidth = 42;
  const int spriteHeight = 42;

  // Read each pixel of the original sprite
  for (int row = 0; row < spriteHeight; row++)
  {
    for (int col = 0; col < spriteWidth; col++)
    {
      // Get the pixel color (RGB565)
      uint16_t color = pgm_read_word(
        &sprite[row * spriteWidth + col]
      );

      // Draw an enlarged pixel as a filled rectangle
      tft.fillRect(
        x + col * scale,
        y + row * scale,
        scale,
        scale,
        color
      );
    }
  }
}

void displaySprite(uint8_t frameIndex, const uint16_t sprite[][42 * 42])
{
  // Original sprite dimensions
  const int spriteSize = 42;

  // Enlarge each pixel 3 times
  const int scale = 5;

  // Calculate the final sprite size
  const int scaledSize = spriteSize * scale;

  // Center the sprite horizontally
  int x = (tft.width() - scaledSize) / 2;

  // Vertical position
  int y = 20;

  // Draw the first enlarged sprite
  drawScaledSprite(
    sprite[frameIndex],
    x,
    y,
    scale
  );
}

// ------------------------------------------- NOTE ----------------------------------------------------------- //

/*
Screen utils :
1 - Initialize the TFT display
    tft.begin();

2 - Set display orientation
    tft.setRotation(NB);
  -> 0 = Portrait
  -> 1 = Landscape
  -> 2 = Upside-down portrait
  -> 3 = Upside-down landscape
  
3 - Clear the entire screen with a color* background
    tft.fillScreen(COLOR);

4 - Set the text color
    tft.setTextColor(COLOR);

5 - Set the text size (3x the default font size)
  tft.setTextSize(3);

6 - Set the text starting position
    tft.setCursor(x, y);
  -> X = x pixels from the left
  -> Y = y pixels from the top
  
7 - Display on the TFT screen
  tft.print("MSG");

8 - Clear only the previous sensor value
    tft.fillRect(110, 115, 200, 25, ILI9341_BLACK);
  -> x = 110 pxiel from the left
  -> y = 115 pixel from the top
  -> width = 200 -> width in pixel
  -> height = 25 -> height in pixel 
  -> color -> filling color

9 - 
  tft.drawRGBBitmap(x, y, bitmap, width, height);

# ESP32 Pin Documentation — Pet Plant

## 1. GPIO 14 — TFT_CS (Chip Select)

**Role:** Selects the TFT display for SPI communication.

The ESP32 uses this pin to tell the TFT screen when it should listen to SPI communication.

- `LOW` → The TFT is selected and can receive SPI commands and data.
- `HIGH` → The TFT is deselected.

**Why do we need it?**

Several SPI devices can share the same communication bus. Each device uses its own CS pin to know when it is being addressed.

---

## 2. GPIO 27 — TFT_DC (Data / Command)

**Role:** Tells the TFT whether the information sent is a command or graphical data.

- `LOW` → Command mode (configure or control the display).
- `HIGH` → Data mode (send pixels, colors, or other display data).

**Example:**

When we call `tft.fillScreen(ILI9341_BLACK)`, the library uses DC to distinguish commands from the pixel data needed to fill the screen.

---

## 3. GPIO 26 — TFT_RST (Reset)

**Role:** Resets the TFT display.

The ESP32 can use this pin to restart the display controller and return it to its initial state.

- `LOW` → Reset is activated.
- `HIGH` → Normal operation.

**Why do we need it?**

It ensures the TFT controller starts correctly when the ESP32 initializes the display.

---

## 4. GPIO 18 — SPI SCK (Serial Clock)

**Role:** Provides the clock signal for SPI communication.

The ESP32 generates clock pulses that synchronize data transfers between the microcontroller and the TFT.

**Why do we need it?**

Without a clock signal, the TFT would not know when to read each bit of incoming data.

**Important:** GPIO 18 is the default SCK pin for the ESP32's commonly used VSPI bus.

---

## 5. GPIO 23 — SPI MOSI (Master Out, Slave In)

**Role:** Sends data from the ESP32 to the TFT display.

MOSI carries information such as:

- Pixel colors
- Graphics data
- Display commands
- Text rendering data

**Important:** GPIO 23 is the default MOSI pin on the ESP32's commonly used VSPI bus.

---

## 6. GPIO 19 — SPI MISO (Master In, Slave Out)

**Role:** Transfers data from an SPI device back to the ESP32.

MISO is the opposite direction of MOSI.

- MOSI → ESP32 sends data to the screen.
- MISO → ESP32 receives data from the screen.

**In our project:**

We do not need MISO for basic TFT drawing operations, so we can leave the TFT's SDO pin disconnected for now.
*/