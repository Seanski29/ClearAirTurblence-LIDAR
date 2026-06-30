# DEVELOPMENT OF AN INSTRUCTIONAL LIDAR-BASED TURBULENCE DETECTION SYSTEM PROTOTYPE

## Overview
The **NAAP (Non-intrusive Atmospheric Analysis Prototype)** is an embedded system designed to simulate and detect Clear Air Turbulence (CAT) using optical backscatter analysis. By measuring the intensity of a laser beam as it interacts with aerosol particles, the system provides real-time turbulence classification (Normal, Moderate, or Severe) for aviation safety research.

## Features
- **Classification:** Uses a lightweight K-Nearest Neighbors (KNN) algorithm running locally on an Arduino Mega.
- **Analysis:** Measures light attenuation through turbulent media.
- **Dashboard:** A 20x4 LCD interface providing live atmospheric readings and a visual turbulence "volume slider."
- **Operation:** Fully embedded C++ implementation; no internet or external processing required.

## Hardware Stack
- **Microcontroller:** Arduino Mega 2560
- **Emitter:** 5V Laser Module
- **Receiver:** Photodiode Sensor Module
- **Display:** 20x4 LCD with I2C Backpack
- **Environment:** Custom acrylic simulation chamber with aerosol/fan integration

## Project Architecture


## KNN Logic
The system implements a 1D K-Nearest Neighbors algorithm. By mapping sensor intensity to a localized dataset, the system performs a distance-based classification to categorize turbulence levels without the overhead of heavy machine learning libraries.

## Setup & Deployment
1. **Wiring:** Connect the sensor to A0 and the Laser to D7. Ensure the I2C LCD is connected to the Mega’s specific SDA(20)/SCL(21) pins.
2. **Library:** Install the `LiquidCrystal_I2C` library by Frank de Brabander via the Arduino Library Manager.
3. **Calibration:** Use the provided Data Logger code to establish baseline atmospheric readings for your specific sensor.
4. **Threshold Adjustment:** Update the `normalLimit` and `moderateLimit` constants in the main sketch to match your calibrated environment.

## Authors
- ANGELES, RAVEN P.
- CANONIGO, MARIA ALEXANDREA P.
- CHAVEZ, RICH CHELLE M.
- DE CASTRO, MA. CHESKA ANNE G.
- RODELAS, LYANN JOYCE M.

## Assitant Prototype builders & programmers
- OCLIMA, JASON
- DEL ROSARIO, SEAN


- *Capstone Project:  In partial fulfillment of the Requirements for the degree of BACHELOR OF SCIENCE IN AVIATION ELECTRONICS TECHNOLOGY*

## License
This project is for academic use under the National Aviation Academy of the Philippines Fernando Air Base Campus.
