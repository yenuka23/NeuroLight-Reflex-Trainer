# NeuroLight Reflex Trainer

## Project Overview
The NeuroLight Reflex Trainer is a wireless cognitive and physical reaction training system engineered using ESP32 microcontrollers[cite: 4]. Designed as a low-cost, accessible therapeutic tool, the system aims to support cognitive health, hand-eye coordination, and physical responsiveness for athletes, individuals in physical therapy, or aging populations experiencing cognitive decline[cite: 4].

## System Architecture & Hardware
- **Core Microcontrollers:** ESP32-C3 Development Boards[cite: 4]
- **Wireless Communication Protocol:** ESP-NOW (Low-power, low-latency, peer-to-peer wireless linkage)[cite: 4]
- **Sensors:** HC-SR04 Mini Ultrasonic Distance Sensors[cite: 4]
- **Visual Indicators:** High-visibility synchronized LED arrays[cite: 4]
- **Power Configuration:** 3.7V LiPo Batteries paired with 5V step-up Boost Converters for standalone portability[cite: 4]

## Logic & Software Workflow
The system relies on a Master-Client (Host-Dummy) structural pattern:
1. **Master Node:** Executes a random delay, selects a target Client node via mapped hardware MAC addresses, transmits an activation token over ESP-NOW, and spins up a precision millisecond timer[cite: 4].
2. **Client Node:** Listens for the activation token, instantly turns on its local LED array to alert the user, and monitors the HC-SR04 sensor[cite: 4].
3. **User Interaction:** When the user breaks the sensor beam (hand proximity under 10cm), the client kills the LEDs and instantly transmits a completion signal back to the master controller[cite: 4].
4. **Data Evaluation:** The master records the final timestamp to compute overall reaction latency in milliseconds[cite: 4]. If a node isn't hit within a maximum threshold (700ms), it automatically times out and cycles to a new random target node[cite: 4].

## Web Presentation Platform
This repository includes a custom documentation website built from scratch using structural HTML5 and responsive CSS3[cite: 4]. The web layout includes dedicated navigation paths exploring the technical proposal, system flowcharts, wiring blueprints, and comprehensive evaluation summaries[cite: 4].

## Testing & Debugging Iterations
- Resolved early compile conflicts and timing variations by optimizing variable scopes and master-to-client synchronization delays[cite: 4].
- Implemented software filtering adjustments on the ultrasonic sensor reading functions to wipe out noise variables and reduce missed detections or false positives[cite: 4].