# 🌱 Pet Plant

<p align="center">
    <img src="assets/banner.png" alt="Pet Plant Banner" width="900">
</p>

<p align="center">
    <strong>An interactive virtual plant powered by an ESP32.</strong><br>
    Monitor a real plant's environment using sensors and bring a digital companion to life on a TFT display.

---

# 📖 About

Pet Plant is an embedded systems project built around an **ESP32**.

The goal is to create an interactive digital pet that reflects the health of a real plant. Using environmental sensors, the ESP32 continuously monitors the plant's conditions and updates a virtual companion displayed on a TFT screen.

The project combines **electronics**, **embedded programming**, **hardware communication**, and **graphical interface development** into a fun and practical application.

---

# 🎥 Demonstration

## Video

-> a venir

<p align="center">
    <img src="assets/demo.gif" width="700">
</p>

---

# 📸 Gallery

## Final Result

<p align="center">
    <img src="assets/final_setup.jpg" width="700">
</p>

---

## TFT Interface

<p align="center">
    <img src="assets/display.jpg" width="500">
</p>

---

## Electronics

<p align="center">
    <img src="assets/electronics.jpg" width="700">
</p>

---

## Breadboard

<p align="center">
    <img src="assets/breadboard.jpg" width="700">
</p>

---

# ✨ Features

- 🌱 Real-time soil moisture monitoring
- ☀️ Ambient light monitoring
- 😊 Animated virtual plant
- 📺 TFT graphical interface
- ⚡ ESP32 microcontroller
- 📈 Live sensor readings
- 🎮 Interactive embedded application
- 🔌 Modular hardware design

---

# 🛠 Hardware

| Component | Description |
|-----------|-------------|
| ESP32 | Main microcontroller |
| ILI9341 TFT Display | 2.4" SPI Display |
| Soil Moisture Sensor | Detects soil humidity |
| Photoresistor (LDR) | Measures ambient light |
| Breadboard | Circuit assembly |
| Jumper Wires | Connections |

---

# 💻 Software

- C++
- Arduino Framework
- ESP32 SDK
- SPI Communication
- Adafruit GFX
- Adafruit ILI9341

---

# ⚙️ How it Works

The ESP32 continuously reads data from its sensors.

### 🌱 Soil Moisture

The soil sensor determines whether the plant is:

- Dry
- Healthy
- Overwatered

The virtual plant reacts accordingly.

---

### ☀️ Light Sensor

The photoresistor measures the surrounding brightness.

Depending on the light level, the virtual plant can react to indicate if it receives enough light.

---

### 📺 TFT Display

The display updates in real time by showing:

- Plant status
- Sensor values
- Visual feedback
- Interactive graphics

---

# 📂 Project Structure

```
PetPlant/
│
├── assets/
│   ├── banner.png
│   ├── demo.gif
│   ├── display.jpg
│   ├── electronics.jpg
│   └── final_setup.jpg
│
├── include/
│
├── src/
│
├── README.md
│
└── PetPlant.ino
```

---

# 🚀 Getting Started

## Clone the repository

```bash
git clone https://github.com/Lyseron/PetPlant.git
```

---

## Open

Open the project with the Arduino IDE.

---

## Install Libraries

Install:

- Adafruit GFX
- Adafruit ILI9341

---

## Upload

1. Connect the ESP32
2. Select the correct COM port
3. Upload the program

---

# 🧠 What I Learned

Through this project I practiced:

- Embedded C++
- ESP32 programming
- Reading analog sensors
- SPI communication
- Hardware debugging
- TFT graphics
- Real-time data processing
- Electronics prototyping

---

# 🔮 Future Improvements

- 💧 Automatic watering system
- 🔊 Sound effects
- 📱 Mobile application
- ☁️ Wi-Fi connectivity
- 📊 Historical sensor graphs
- 🌡 Temperature and humidity sensor
- 🔋 Battery-powered version
- 🌐 Remote monitoring

---

# 📷 Development Photos

<p align="center">
    <img src="assets/dev1.jpg" width="250">
    <img src="assets/dev2.jpg" width="250">
    <img src="assets/dev3.jpg" width="250">
</p>

---

# ❤️ Why this project?

I wanted to explore embedded programming through a fun and interactive project that combines software and hardware.

Pet Plant helped me better understand how sensors, microcontrollers and graphical interfaces work together to create responsive embedded systems.

---

# 📜 License

This project is released under the MIT License.
````
