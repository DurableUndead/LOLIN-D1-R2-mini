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