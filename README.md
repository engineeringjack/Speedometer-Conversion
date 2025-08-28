# Arduino Speedometer & Odometer Interface

This project is an **Arduino-based speedometer/odometer system** that uses a **stepper motor**, **servo motor**, and **hall effect sensor** to measure rotational speed (RPM), calculate MPH, and simulate a gauge needle movement.

---

## 📌 Features
- Reads RPM from a **hall effect sensor** on pin `2`.
- Converts RPM → MPH using a configurable ratio.
- Drives a **servo** to simulate a speedometer needle.
- Drives a **stepper motor** to simulate odometer/trip counter rotation.
- Includes startup calibration sweep for the speedometer needle.

---

## ⚙️ Hardware Requirements
- Arduino (tested with Uno/Nano)
- Hall Effect Sensor (connected to pin `2`)
- Servo motor (connected to pin `3`)
- Stepper motor + driver (connected to pins `6, 8, 5, 7` in sequence)
- External power supply for motors (recommended)
- Breadboard & wiring

---

## 📜 Code Overview
- `Stepper myStepper` → Controls odometer movement.
- `Servo myServo` → Controls speedometer needle.
- `rpmToSpeed` → Conversion factor from RPM to MPH.
- `calc(mph)` → Maps MPH to servo angle (180° scale).
- Main loop:
  - Calculates MPH from measured RPM.
  - Updates servo needle angle.
  - Steps odometer proportionally to MPH.
  - Uses hall sensor pulses to recalculate RPM.

---

## 🧮 Key Formulas
- **MPH Conversion**:  
  `mph = rpm * rpmToSpeed`
- **Servo Mapping**:  
  `angle = 180 - (mph * 1.352 - 8.5)`
- **Odometer Step Calculation**:  
  `steps = mph * odmMult * 0.5`

---

## 🚀 Setup
1. Clone this repo / copy the script into the Arduino IDE.
2. Install required libraries:
   - `Stepper.h`
   - `Servo.h`
3. Wire components as described above.
4. Upload to Arduino.
5. Open Serial Monitor (9600 baud) for debug output (optional).

---

## 🛠️ Customization
- `rpmToSpeed` → Adjust for different wheel diameters.
- `odmMult` → Adjust odometer scaling factor.
- Modify `calc()` to fine-tune servo calibration.

---

## ⚠️ Notes
- Ensure motors have **separate power** from Arduino’s 5V regulator to prevent resets.
- If servo needle alignment is off, adjust the math in `calc()`.
- Current code has **debug Serial prints commented out** — you can uncomment for troubleshooting.

---

## 📄 License
MIT License – feel free to use and modify for your own projects.
