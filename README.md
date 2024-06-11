![LoginWemos](https://github.com/DurableUndead/wemos-d1-mini/assets/92308206/b5958a5b-e61a-466c-a88c-8abbd487705f)

# WiFi Project using ESP8266 with WEMOS D1 Mini Variant

## Features:
- Web Server Capability.
- Provides Access Point (without internet).
- Connects to Wi-Fi Router and Acts as a Repeater.

## Website:
- Access Point Management
  - {Input} to change SSID & Password
- Network Management
  - Access Point
    - {Input} to change Access Point IP
  - Station
    - {Input} to change Local IP
    - {Input} to change Gateway
    - {Input} to change Subnet Mask
    - {Input} to change DNS 1
    - {Input} to change DNS 2
- Device Management
  - Refresh Button
  - List of Devices Connected to ESP 8266
    - Mac Address
    - IP Address
- Wi-Fi Management
  - Wi-Fi Status & Reset SSID & Password
  - Button to Disconnect Wi-Fi
    - Switching Mode from STA AP to AP
  - List of Wi-Fi Networks Nearby
    - SSID (Wi-Fi Name)
    - RSSI (Signal Strength)
    - Encryption (Security)
    - BSSID (Mac Address)
    - Channel (Frequency Channel)
  - {Input} to connect to Wi-Fi
    - Switching Mode from AP to STA AP
  - {Input} to change SSID & Password for Wi-Fi
- Profile
  - {Input} to change Admin Login Username and Password
- Menu
  - Logout Button
  - Reset ESP 8266 Device Button

## Network:
- AP IP Address: 192.168.4.1

## Usage:
- Login to AP:
  - SSID: Wemos
  - Password: 1234567890

- Login to Web:
  - Username: admin
  - Password: admin


---

# Complete Installation Guide for Arduino with ESP8266

## Installation Steps

## Ensure Arduino is Installed

1. **Open Preferences**  
   Add the following URL to the "Additional Boards Manager URLs" section and click OK:
   ```
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```

2. **Install ESP8266 in Boards Manager**  
   Wait for the download to complete.

3. **Select Board and Port**  
   - Open "Select Other Board and Port..."
   - Choose the board "NodeMCU 1.0 ESP-12E Module"
   - Select the port "COM Serial Port (USB)"  
     Note: If the port does not appear, try changing the data cable.

4. **Verify Code**  
   - Click the Verify button (checkmark icon) and wait for the verification process to complete.

5. **Open Serial Monitor**  
   - Open Serial Monitor from the Tools tab.

6. **Download CH340 Driver**  
   - Download and install the CH340 driver if needed.

7. **Select Other Board (Optional)**  
   - Choose the board "Lolin (Wemos) D1 R2 & Mini" or "NodeMCU 1.0 ESP-12E Module" in "Select Other Board and Port..."
   - Wait for the indexing process to complete (around 0/85).

Additional reference:  
[Arduino LittleFS Upload](https://github.com/earlephilhower/arduino-littlefs-upload)

---
