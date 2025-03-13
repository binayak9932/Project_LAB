
---

## 🛠️ Components Used  
1. **ESP32 Board** – Handles sensor readings, LED control, and web interface.  
2. **Water Level Sensor** – Provides an analog output to indicate water levels.  
3. **LED Indicators** – Displays the current water level:
   - **GPIO 25** → FULL Level LED (Green)  
   - **GPIO 26** → MEDIUM Level LED (Yellow)  
   - **GPIO 27** → LOW Level LED (Red)  
4. **Wi-Fi Web Server** – Allows users to monitor water levels via a webpage.  

---

## 🌐 Web Interface  
The ESP32 acts as a **Wi-Fi Access Point** and serves a webpage showing real-time water levels. The page updates automatically every **2 seconds**.  

### **🔗 Web Interface Screenshot**  
[![Web Interface Preview](https://github.com/binayak9932/Project_LAB/blob/main/Water_Level/web.png)](https://github.com/binayak9932/Project_LAB/blob/main/Water_Level/web.png)  


---

## 📌 Pin Connections  

| Component       | ESP32 Pin |
|---------------|-----------|
| Water Sensor VCC | 3.3V |
| Water Sensor GND | GND |
| Water Sensor Signal | GPIO 34 |
| FULL Level LED | GPIO 25 |
| MEDIUM Level LED | GPIO 26 |
| LOW Level LED | GPIO 27 |

---

## 📜 How It Works  

1. **Reads Water Level** – The ESP32 reads **analog values** from the sensor on **GPIO 34**.  
2. **Determines Level** – Based on the sensor value, it classifies the water level as:
   - **FULL (400-1000)**
   - **MEDIUM (1900-2200)**
   - **LOW (>2300)**
3. **Controls LEDs** – Activates the corresponding LED for each water level.  
4. **Web Server Updates** – Sends real-time water level data to a web-based dashboard.  

---

## 🌊 Working Principle of the Water Level Sensor  

A **water level sensor** typically consists of a **set of probes** and an **internal resistance circuit**.  
It works on the principle of **conductivity**:  

### 🏞️ **Water Conductivity**  

✔️ Water is a **conductive medium** (though not as much as metal).  
✔️ The presence of **water between probes** completes an **electrical circuit**, allowing **current to flow**.  

### 🔋 **Resistance-Based Measurement**  

✔️ The sensor contains a **voltage divider circuit** with resistors.  
✔️ As **water covers more probes**, the **resistance decreases**, and the sensor outputs a **lower voltage**.  
✔️ If the **water level is low**, **higher resistance** leads to a **higher voltage output**.  

### 📡 **ESP32 Reads Analog Signal**  

✔️ The **ESP32’s analog input pin (GPIO 34)** reads this **voltage output**.  
✔️ It then categorizes the reading into different **water levels**:  

| **Voltage Output** | **Water Level** |
|-------------------|---------------|
| High Voltage | LOW |
| Medium Voltage | MEDIUM |
| Low Voltage | FULL |

---

## 🛠️ Role of Resistors in the Water Level Sensor  

Resistors in the sensor help with **voltage division** and **current limiting**:  

✔️ **Voltage Divider**: Converts the varying conductivity into a measurable voltage.  
✔️ **Current Limiting**: Prevents excessive current flow when probes are submerged.  
✔️ **Pull-Down Resistors**: Ensures the sensor gives a stable reading even when probes are not touching water.  

### 🎯 **Example**  

- If the **water level is FULL** → **more probes are submerged** → **low resistance** → **low voltage output**.  
- If the **water level is LOW** → **fewer probes are submerged** → **high resistance** → **high voltage output**.  

---

