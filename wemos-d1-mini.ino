#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html_content.h"

String ssid = "Wemos";
String password = "1234567890";
String adminUsername = "admin";
String adminPassword = "admin";
bool isAuthenticated = false;

String ssidTarget = "Null";
String passwordTarget;

String ssidRenamed = "Wemos_AP_STA";
String passwordRenamed = "1234567890";

int totalWifi = 0;
int totalDevices = 0;

ESP8266WebServer server(80);

void handleRoot()
{
  if (isAuthenticated)
  {
    String homePage = HOME_PAGE;

    homePage.replace("{{ssid}}", ssid);
    homePage.replace("{{password}}", password);

    homePage.replace("{{totalDevices}}", String(totalDevices));
    homePage.replace("{{deviceList}}", deviceListOfConnectedDevices());

    homePage.replace("{{ssidTarget}}", ssidTarget);
    homePage.replace("{{totalWifi}}", String(totalWifi));
    homePage.replace("{{wifiList}}", generateWifiList());

    homePage.replace("{{ssidRenamed}}", ssidRenamed);
    homePage.replace("{{passwordRenamed}}", passwordRenamed);

    homePage.replace("{{adminUsername}}", adminUsername);
    homePage.replace("{{adminPassword}}", adminPassword);
    
    
    IPAddress IPAddressAP = WiFi.softAPIP();
    IPAddress IPAddressLocal = WiFi.localIP();
    IPAddress gatewayIP = WiFi.gatewayIP();
    IPAddress subnetMask = WiFi.subnetMask();
    IPAddress dnsIP1 = WiFi.dnsIP(0);
    IPAddress dnsIP2 = WiFi.dnsIP(1);

    if (IPAddressAP.isSet()) {
      homePage.replace("{{ipAP}}", IPAddressAP.toString());
    } else {
      homePage.replace("{{ipAP}}", "0.0.0.0");
    }
    if (IPAddressLocal.isSet()) {
      homePage.replace("{{ipLocal}}", IPAddressLocal.toString());
    } else {
      homePage.replace("{{ipLocal}}", "0.0.0.0");
    }
    if (gatewayIP.isSet()) {
      homePage.replace("{{gatewayIP}}", gatewayIP.toString());
    } else {
      homePage.replace("{{gatewayIP}}", "0.0.0.0");
    }
    if (subnetMask.isSet()) {
      homePage.replace("{{subnetmaskIP}}", subnetMask.toString());
    } else {
      homePage.replace("{{subnetmaskIP}}", "0.0.0.0");
    }
    if (dnsIP1.isSet()) {
      homePage.replace("{{dns1}}", dnsIP1.toString());
    } else {
      homePage.replace("{{dns1}}", "0.0.0.0");
    }
    if (dnsIP2.isSet()) {
      homePage.replace("{{dns2}}", dnsIP2.toString());
    } else {
      homePage.replace("{{dns2}}", "0.0.0.0");
    }
    server.send(200, "text/html", homePage);
  }
  else
  {
    server.send(200, "text/html", LOGIN_PAGE);
  }
}

String generateWifiList() {
  String wifiList;
  int numNetworks = WiFi.scanNetworks();
  totalWifi = numNetworks;

  if (numNetworks > 0) {
    wifiList += "<table border='1'>";
    wifiList += "<tr>";
    wifiList += "<th>No.</th>";
    wifiList += "<th>SSID</th>";
    wifiList += "<th>RSSI</th>";
    wifiList += "<th>Encryption</th>";
    wifiList += "<th>BSSID</th>";
    wifiList += "<th>Channel</th>";
    wifiList += "</tr>";
    for (int i = 0; i < numNetworks; i++) {
      wifiList += "<tr>";
      wifiList += "<td>" + String(i + 1) + "</td>";
      wifiList += "<td>" + WiFi.SSID(i) + "</td>";
      wifiList += "<td>" + String(WiFi.RSSI(i)) + "</td>";
      wifiList += "<td>";
      switch (WiFi.encryptionType(i)) {
        case 2:
          wifiList += "WPA";
          break;
        case 5:
          wifiList += "WPA2";
          break;
        case 4:
          wifiList += "WPA/WPA2";
          break;
        case 7:
          wifiList += "Open";
          break;
        default:
          wifiList += "Unknown";
          break;
      }
      wifiList += "</td>";
      wifiList += "<td>" + WiFi.BSSIDstr(i) + "</td>";
      wifiList += "<td>" + String(WiFi.channel(i)) + "</td>";
      wifiList += "</tr>";
    }
    wifiList += "</table>";
  } else {
    wifiList = "No WiFi networks found.";
  }
  return wifiList;
}

String deviceListOfConnectedDevices() {
  String deviceList;
  unsigned char number_client;
  struct station_info *stat_info;
  struct ip4_addr *IPaddress;
  IPAddress address;
  int i = 1;

  number_client = wifi_softap_get_station_num();
  stat_info = wifi_softap_get_station_info();
  totalDevices = number_client;

  deviceList += "<table border='1'>";
  deviceList += "<tr>";
  deviceList += "<th>No.</th>";
  deviceList += "<th>MAC Address</th>";
  deviceList += "<th>IP Address</th>";
  deviceList += "</tr>";

  while (stat_info != NULL) {
    IPaddress = &stat_info->ip;
    address = IPaddress->addr;

    deviceList += "<tr>";
    deviceList += "<td>" + String(i) + "</td>";
    deviceList += "<td>";
    deviceList += String(stat_info->bssid[0], HEX) + ":" +
                  String(stat_info->bssid[1], HEX) + ":" +
                  String(stat_info->bssid[2], HEX) + ":" +
                  String(stat_info->bssid[3], HEX) + ":" +
                  String(stat_info->bssid[4], HEX) + ":" +
                  String(stat_info->bssid[5], HEX);
    deviceList += "</td>";
    deviceList += "<td>" + IPAddress(address).toString() + "</td>";
    deviceList += "</tr>";

    stat_info = STAILQ_NEXT(stat_info, next);
    i++;
  }

  deviceList += "</table>";
  return deviceList;
}

void handleLogin()
{
  if (server.hasArg("username") && server.hasArg("password"))
  {
    Serial.println("Someone is trying to login!");
    if (server.arg("username") == adminUsername && server.arg("password") == adminPassword)
    {
      Serial.println("Authentication success!");
      isAuthenticated = true;
      server.sendHeader("Location", "/", true);
      server.send(302, "text/plain", "");
    }
    else
    {
      server.send(401, "text/plain", "Authentication failed");
    }
    Serial.println("Username: " + server.arg("username"));
    Serial.println("Password: " + server.arg("password"));
  }
  else
  {
    server.send(400, "text/plain", "Bad Request");
  }
}

void handleLogout()
{
  isAuthenticated = false;
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void handleConnectToWiFi() {
  if (server.hasArg("ssidTarget") && server.hasArg("passwordTarget")) {
    String ssid = server.arg("ssidTarget");
    String password = server.arg("passwordTarget");
    ssidRenamed = server.arg("ssidToConnected");
    passwordRenamed = server.arg("passwordToConnected");
    ssidTarget = ssid;
    passwordTarget = password;

    Serial.println("Connecting to " + ssid);

    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    WiFi.waitForConnectResult();

    if (WiFi.status() == WL_CONNECTED) {
      WiFi.softAP(ssidRenamed, passwordRenamed);

      Serial.println("Connected to(1) " + ssid);
      Serial.println("IP address (Accsess Point)  : " + WiFi.softAPIP().toString());
      Serial.println("IP address (Lokal)          : " + WiFi.localIP().toString());
      Serial.println("IP gatewayIP                : " + WiFi.gatewayIP().toString());
      Serial.println("SubnetMask                  : " + WiFi.subnetMask().toString());
      Serial.println("DNS Server 1                : " + WiFi.dnsIP(0).toString());
      Serial.println("DNS Server 2                : " + WiFi.dnsIP(1).toString());
      
      Serial.println("Status: " + String(WiFi.status()) + " (" + String(WL_CONNECTED) + ")");
      Serial.println("SSID: " + WiFi.SSID());
    } else {
      server.send(500, "text/plain", "Failed to connect to " + ssid);
      Serial.println("Failed to connect to " + ssid);
    }
  } else if (server.hasArg("ssid")) {
    ssid = server.arg("ssid");
    Serial.println("Connecting to(2) " + ssid);

    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid, "");
    WiFi.waitForConnectResult();

    if (WiFi.status() == WL_CONNECTED) {
      WiFi.softAP(ssidRenamed, passwordRenamed);

      Serial.println("Connected to(2) " + ssid);
      Serial.println("IP address (Accsess Point)  : " + WiFi.softAPIP().toString());
      Serial.println("IP address (Lokal)          : " + WiFi.localIP().toString());
      Serial.println("IP gatewayIP                : " + WiFi.gatewayIP().toString());
      Serial.println("SubnetMask                  : " + WiFi.subnetMask().toString());
      Serial.println("DNS Server 1                : " + WiFi.dnsIP(0).toString());
      Serial.println("DNS Server 2                : " + WiFi.dnsIP(1).toString());

      // print wifi status
      Serial.println("---------------STATUS---------------");
      Serial.println("Status: " + String(WiFi.status()) + " (" + String(WL_CONNECTED) + ")");
      Serial.println("SSID: " + WiFi.SSID());
    } else {
      server.send(500, "text/plain", "Failed to connect to " + ssid);
      Serial.println("Failed to connect to " + ssid);
    }
  } else {
    server.send(400, "text/plain", "Bad Request");
    Serial.println("Bad Request");
  }
}

void handleUpdateProfile()
{
  if (!isAuthenticated)
  {
    server.send(401, "text/plain", "Authentication required");
    return;
  }
  String messagesPage = MESSAGES_PAGE;
  if (server.hasArg("username") && server.hasArg("password"))
  {
    adminUsername = server.arg("username");
    adminPassword = server.arg("password");

    Serial.println("-----------------");
    Serial.println("Someone is trying to update profile!");
    Serial.println("Username : " + adminUsername);
    Serial.println("Password : " + adminPassword);
    Serial.println("-----------------");

    messagesPage.replace("{{messages}}", "Profile has been updated!");
    server.send(200, "text/html", messagesPage);
  }
  else
  {
    messagesPage.replace("{{messages}}", "Profile has not been updated!!!");
    server.send(400, "text/html", messagesPage);
  }
}

void handleUpdateNetworkStation()
{
  if (!isAuthenticated)
  {
    server.send(401, "text/plain", "Authentication required");
    return;
  }

  String messagesPage = MESSAGES_PAGE;
  if (server.hasArg("ipLocal") && server.hasArg("gateway") && server.hasArg("subnetmaskIP") && server.hasArg("dns1") && server.hasArg("dns2"))
  {
  
    IPAddress local_IP1, gateway, subnet, dns1, dns2;
    local_IP1.fromString(server.arg("ipLocal"));
    gateway.fromString(server.arg("gateway"));
    subnet.fromString(server.arg("subnetmaskIP"));
    dns1.fromString(server.arg("dns1"));
    dns2.fromString(server.arg("dns2"));

    WiFi.config(local_IP1, gateway, subnet, dns1, dns2);

    Serial.println("-----------------");
    Serial.println("Someone is trying to update network!");
    Serial.println("IP Address Local  : " + WiFi.localIP().toString());
    Serial.println("gateway           : " + gateway.toString());
    Serial.println("Subnet Mask       : " + subnet.toString());
    Serial.println("DNS 1             : " + dns1.toString());
    Serial.println("DNS 2             : " + dns2.toString());
    Serial.println("-----------------");

    messagesPage.replace("{{messages}}", "Network Station has been updated!");
    server.send(200, "text/html", messagesPage);
  }
  else
  {
    messagesPage.replace("{{messages}}", "Network Station has not been updated!!!");
    server.send(400, "text/html", messagesPage);
  }
}

void handleUpdateNetworkAccessPoint()
{
  if (!isAuthenticated)
  {
    server.send(401, "text/plain", "Authentication required");
    return;
  }
  String messagesPage = MESSAGES_PAGE;
  if (server.hasArg("ipAP"))
  {
    IPAddress IP_AP;
    IP_AP.fromString(server.arg("ipAP"));

    WiFi.softAPConfig(IP_AP, WiFi.gatewayIP(), WiFi.subnetMask());

    Serial.println("-----------------");
    Serial.println("Someone is trying to update network Access Point!");
    Serial.println("IP Address Access Point : " + IP_AP.toString());
    Serial.println("-----------------");

    messagesPage.replace("{{messages}}", "Network Access Point has been updated!");
    server.send(200, "text/html", messagesPage);
  }
  else
  {
      messagesPage.replace("{{messages}}", "Network Access Point has not been updated!!!");
    server.send(400, "text/html", messagesPage);
  }
}

void handleUpdateWifi()
{
  if (!isAuthenticated)
  {
    server.send(401, "text/plain", "Authentication required");
    return;
  }
  String messagesPage = MESSAGES_PAGE;
  if (server.hasArg("ssid") && server.hasArg("password"))
  {
    ssid = server.arg("ssid");
    password = server.arg("password");
    WiFi.softAP(ssid, password);

    Serial.println("-----------------");
    Serial.println("Someone is trying to update wifi!");
    Serial.println("SSID     : " + ssid);
    Serial.println("Password : " + password);
    Serial.println("-----------------");

    messagesPage.replace("{{messages}}", "Wifi has been updated!");
    server.send(200, "text/html", messagesPage);
  }
  else
  {
    messagesPage.replace("{{messages}}", "Wifi has not been updated!!!");
    server.send(400, "text/html", messagesPage);
  }
}

void handleDisconnectFromWiFi()
{
  if (!isAuthenticated)
  {
    server.send(401, "text/plain", "Authentication required");
    return;
  }
  WiFi.disconnect();
  ssidTarget = "Null";
  
  if (server.hasArg("checkboxResetSSID")) {
    ssid = "Wemos";
    password = "1234567890";
    WiFi.softAP(ssid, password);
    ESP.restart();
  }

  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void handleResetToDefault()
{
  if (!isAuthenticated)
  {
    server.send(401, "text/plain", "Authentication required");
    return;
  }
  Serial.println("Reset to default");
  ESP.restart();
}

void setup()
{
  Serial.begin(115200);
  // WiFi.softAPConfig(IPAddressAP, gatewayIP, subnetMask);
  // WiFi.config(IPAddressLocal, gatewayIP, subnetMask, dnsIP1, dnsIP2);
  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.on("/login", handleLogin);
  server.on("/logout", handleLogout);
  server.on("/updateProfile", handleUpdateProfile);
  server.on("/updateNetworkAccessPoint", handleUpdateNetworkAccessPoint);
  server.on("/updateNetworkStation", handleUpdateNetworkStation);
  server.on("/updateWifi", handleUpdateWifi);
  server.on("/connect", handleConnectToWiFi);
  server.on("/disconnect", handleDisconnectFromWiFi);
  server.on("/resetToDefault", handleResetToDefault);

  server.begin();
}

void loop()
{
  server.handleClient();
}
