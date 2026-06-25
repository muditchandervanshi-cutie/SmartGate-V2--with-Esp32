# SmartGate-V2--with-Esp32
Smart Gate V2 🚪

An ESP32-based Smart Access Control System that combines presence detection, proximity sensing, RFID authentication, and automated gate control to create a secure and interactive entry experience.

Smart Gate V2 was developed as a practical embedded systems project to explore automation, sensor integration, user authentication, and access-control workflows. The project utilizes multiple sensors and a state-based architecture to simulate the operation of a modern intelligent entry system.

---

📹 Demo Video

Watch the complete project demonstration here:

Google Drive Link:

PASTE_YOUR_GOOGLE_DRIVE_LINK_HERE

---

✨ Features

- ESP32-based control system
- HC-SR04 visitor detection
- Flying Fish IR proximity sensing
- RFID authentication
- Servo-controlled automated gate
- Smooth opening and closing animations
- 1602A LCD with I2C interface
- Multi-user authorization system
- RGB LED status indicators
- Automatic state reset after authentication
- Expandable architecture for future IoT integration

---

🛠 Hardware Used

Component| Quantity
ESP32 Development Board| 1
1602A LCD with I2C Module| 1
HC-SR04 Ultrasonic Sensor| 1
Flying Fish IR Sensor| 1
RFID Reader Module| 1
Servo Motor| 1
Red LED| 1
Green LED| 1
Blue LED| 1
Breadboard| 1
Jumper Wires| Several

---

🎨 Status Indicator System

The system uses dedicated LEDs to indicate its current operating state.

LED| Status
🔴 Red| System startup and gate movement
🟢 Green| System ready and monitoring
🔵 Blue| Awaiting RFID authentication

Safety Indication

During gate opening and closing operations, the Red LED is activated to indicate that the gate is moving and users should maintain a safe distance from the mechanism.

---

⚙️ System Workflow

1. System Startup

- ESP32 powers on
- LCD initializes
- Red LED illuminates during startup
- System performs initialization sequence

LCD Display

Waking Up...

---

2. Ready State

- Gate remains closed
- Green LED turns ON
- HC-SR04 begins monitoring surroundings

LCD Display

Ready

---

3. Visitor Detection

- HC-SR04 detects an approaching object
- Visitor presence is confirmed

LCD Display

Visitor Detected

---

4. Access Request

- Flying Fish IR Sensor detects presence near the gate
- RFID Reader becomes active
- Blue LED turns ON

LCD Display

Scan Your Card

---

5. Authentication

The scanned RFID card is compared against the authorized user database.

Supported Access Levels

Role| Description
Owner| Full system access
Admin| Administrative access
Member| Standard access
Denied| Unauthorized card

---

6A. Access Granted

If authentication is successful:

- LCD displays access confirmation
- Red LED activates
- Servo opens the gate using a smooth animation

LCD Display

Access Granted

---

7A. Passage Monitoring

- HC-SR04 monitors the gate area
- System waits for the user to pass through

---

8A. Gate Closing

- Servo closes the gate
- Red LED remains active during movement

LCD Display

Closing Gate...

---

9A. System Reset

- Red LED turns OFF
- Green LED turns ON
- System returns to monitoring mode

LCD Display

Ready

---

6B. Access Denied

If authentication fails:

- Gate remains locked
- Access request is rejected

LCD Display

Access Denied

---

7B. Immediate Reset

- Blue LED turns OFF
- Green LED turns ON
- System immediately resumes monitoring for visitors

LCD Display

Ready

---

👥 Demonstration Access Cards

The demonstration includes multiple RFID credentials.

Credential Type| Quantity
Owner Card| 1
Owner Key Fob| 1
Admin Cards| 2
Member Cards| 2
Access Denied Test Card| 1

The project demonstration showcases successful authentication using Owner, Admin, and Member credentials, along with an unauthorized card test.

---

🧠 State Machine Architecture

┌─────────────┐
│   Startup     │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│    Ready      │
└──────┬──────┘
       │
       ▼
┌──────────────────┐
│ Visitor Detected    │
└────────┬─────────┘
         │
         ▼
┌──────────────────┐
│ Scan Your Card      │
└────────┬─────────┘
         │
    ┌────┴────┐
    │           │
    ▼           ▼

Granted      Denied
    │           │
    ▼          │

Open Gate       │
    │           │
    ▼          │

Pass Through    │
    │           │
    ▼          │

Close Gate      │
    │           │
    └────┬────┘
         ▼

       Ready

---

📺 LCD Messages

Examples of messages displayed during operation:

Hello Cutie!
Welcome Home

Ready

Visitor Detected

Scan Your Card

Access Granted

Access Denied

Opening Gate...

Closing Gate...

---

📷 Project Images

Prototype

![Prototype](images/prototype.jpg)

Wiring Diagram

![Wiring Diagram](images/wiring.jpg)

System Overview

![System Overview](images/system.jpg)

Demonstration

![Demo](images/demo.jpg)

---

🚀 Future Improvements

Authentication

- User-specific permissions
- Card registration interface
- Temporary guest credentials

Monitoring

- Access logs
- Timestamp recording
- User activity history

Connectivity

- Wi-Fi dashboard
- Mobile notifications
- Remote monitoring
- Cloud synchronization

Hardware Enhancements

- OLED display upgrade
- RGB status module
- Fingerprint authentication
- Camera integration
- Electronic locking mechanism

---

🎯 Project Goal

The goal of Smart Gate V2 is to explore the practical implementation of embedded systems, sensor fusion, automation, and authentication technologies within a single integrated platform.

The project serves as a foundation for future IoT-enabled access-control systems and demonstrates how multiple sensors and devices can work together through a structured state-machine architecture.

---

📄 License

This project is licensed under the MIT License.

Feel free to use, modify, and build upon this project for educational and personal learning purposes.
