#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "auth.h"

/* 'auth' file has these lines
  const char *ssid      = "????";
  const char *password  = "????";

  #define LOCATION        "????"

*/

boolean debug = 1;

ESP8266WebServer httpd(80);
WiFiServer telnetd(23); // for command line and avrdude dfu
WiFiClient client;
char buffer[255];
int bufferIndex;


#define HTMLLEN 1000
void handleRoot() {
  char temp[HTMLLEN];
  snprintf(temp, HTMLLEN, "<html>\
  <head>\
    <meta http-equiv='refresh' content='2'/>\
    <title>%s Data</title>\
    <style>\
      body { }\
    </style>\
  </head>\
  <body>\
    <pre>\
%s %d %s\
   </pre>\
  </body>\
</html>", LOCATION, LOCATION, millis(), buffer);
  httpd.send ( 200, "text/html", temp );
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += httpd.uri();
  message += "\nMethod: ";
  message += ( httpd.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += httpd.args();
  message += "\n";

  for (uint8_t i = 0; i < httpd.args(); i++) {
    message += " " + httpd.argName(i) + ": " + httpd.arg(i) + "\n";
  }

  httpd.send(404, "text/plain", message);
}

void setup(void) {
  Serial.begin(115200);
  WiFi.begin(ssid, password );
  if (debug) Serial.println("\n\n");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (debug) Serial.print(".");
  }

  if (debug) {
    Serial.println("");
    Serial.print("Connected to " );
    Serial.println(ssid );
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP() );
  }

  if (MDNS.begin(LOCATION) ) {
    if (debug) Serial.println("MDNS responder started");
  }

  httpd.on("/", handleRoot);
  httpd.onNotFound(handleNotFound);
  httpd.begin();
  if (debug) Serial.println ("HTTP server started");

  telnetd.begin();
  //  telnetd.setNoDelay(true);
}

void loopTelnetd() {
  if (client) {
    if (client.connected()) {
      while (client.available()) {
        Serial.write(client.read());
      }
    } else {
      client.stop();
    }
  } else {
    client = telnetd.available();
  }
}

void loopSerial() {
  char c;
  if (Serial.available()) {
    c = Serial.read();
    if (c == '\n') {
      buffer[bufferIndex] = 0;
      bufferIndex = 0;
    } else {
      buffer[bufferIndex++] = c;

      if (bufferIndex > 255) {
        bufferIndex = 0;
      }
    }
    if (client) {
      if (client.connected()) {
        client.write(&c,1);
      }
    }
  }
}

void loop(void) {
  httpd.handleClient();
  loopTelnetd();
  loopSerial();
}
