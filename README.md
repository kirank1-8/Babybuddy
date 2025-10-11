# 🌊 Smart Microplastic Detection System (Arduino-Based)

## 💡 Overview
The **Smart Microplastic Detection System** is a **chemical-free, low-cost device** that detects **microplastics in water** using a combination of **optical, vibration, and TDS sensors**.  
It provides instant detection results through LEDs, buzzer alerts, and an LCD display.

This project is designed for **hackathons**, **environmental innovation**, and **IoT competitions**.

---

## ⚙️ Components Required

| Component | Quantity | Approx. Cost (₹) | Purpose |
|------------|-----------|------------------|----------|
| Arduino UNO  | 1 | 500 | Main controller |
| LDR (Light Dependent Resistor) | 2 | 40 | Detects light intensity and scattering |
| LED (White / Laser) | 1 | 20 | Light source |
| SW-420 Vibration Sensor | 1 | 80 | Detects micro-movement in water |
| TDS Sensor Module | 1 | 350 | Measures dissolved solids (water quality) |
| Ultrasonic Sensor (HC-SR04) *(optional)* | 1 | 100 | Detects reflection differences in water |
| 16x2 LCD Display | 1 | 120 | Displays readings |
| Buzzer | 1 | 25 | Alerts when microplastics are detected |
| RGB LEDs | 3 | 30 | Status indication (Clean, Moderate, Polluted) |
| Jumper Wires + Breadboard | - | 100 | Connections |
| Power Source (5V Battery / USB) | 1 | - | Power supply |

**Total Estimated Cost:** ₹1200 – ₹1500 (approx.)

---

## 🧠 Working Principle

The system detects microplastics using **multi-sensor fusion** — combining data from optical, vibration, and TDS sensors for more accurate results.

### 1. **Optical Detection**
- A **white or laser LED** shines light through a transparent water container.  
- Two LDR sensors are placed:
  - **Front LDR**: Detects how much light passes through.
  - **Side LDR**: Detects scattered light from microplastic particles.  
- Microplastics scatter and block light, reducing the signal to the LDRs.

### 2. **Vibration Detection**
- The **SW-420 sensor** is placed below or on the side of the container.  
- It senses tiny vibrations caused by floating microplastics in the water.

### 3. **TDS Detection**
- The **TDS sensor** is placed inside the water.  
- Measures **total dissolved solids** (salts, minerals, and pollutants).  
- Sudden changes in TDS levels indicate contamination.

### 4. **Data Fusion & Decision**
- Arduino reads values from all sensors.
- A logic algorithm compares readings to set thresholds.
- Based on sensor values:
  - 🟢 **Green LED** → Clean water  
  - 🟡 **Yellow LED** → Slight pollution (few microplastics)  
  - 🔴 **Red LED + Buzzer** → High microplastic content  

---

## 📟 Output Display
- LCD shows:
