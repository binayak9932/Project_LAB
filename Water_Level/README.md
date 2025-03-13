
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
[![Web Interface Preview](IMAGE_LINK_HERE)](IMAGE_LINK_HERE)  
*Click the image to view full size.*

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

