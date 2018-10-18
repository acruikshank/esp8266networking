#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

#define STRANDS 15

const char WIFI_NET[20] = "anthazoa";
const char WIFI_PSK[20] = "chaartdev";

uint16_t INFOPort = 50050;

char packetBuffer[255]; //buffer to hold incoming packet
char  replyBuffer[] = "acknowledged";       // a string to send back
// IPAddress packetServer(255,255,255,255);
IPAddress packetServer(192,168,4,18);

WiFiUDP Udp;

typedef struct Location {
  float x;
  float y;
} Location;

typedef struct Strand {
  uint64_t macAddress;
  Location location;
} Strand;

Strand distanceTable[STRANDS];
Location myLocation;

float distance(Location loc1, Location loc2) {
  float dx = loc1.x - myLocation.x;
  float dy = loc1.y - myLocation.y;
  return sqrt(dx*dx + dy*dy);
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(WIFI_NET, WIFI_PSK);
    // WiFi.begin("Floor5GIG", "innovation");
    Serial.println();
    Serial.print("Wait for WiFi");

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: " + WiFi.localIP().toString());

    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, HIGH);

    // Serial.println(Udp.beginPacket(packetServer, 60741)); /
    // char ipBuffer[255];
    // WiFi.localIP().toString().toCharArray(ipBuffer, 255);
    // Udp.write(ipBuffer);
    // Serial.println(Udp.endPacket());
    // Serial.println("Sent ip adress to server");

    Udp.begin(INFOPort);


    for (int packetSize = Udp.parsePacket(); packetSize == 0; packetSize = Udp.parsePacket()) {
      delay(10);
    }

    // Udp.read((char *) &distanceTable, sizeof(distanceTable));
    Udp.read((char *) &distanceTable, sizeof(distanceTable));
    uint8_t macAddress[6] = {0};
    WiFi.macAddress(&macAddress[0]);
    uint64_t longMac = 0;
    for(int i=5; i > -1; i--){
      longMac = longMac & macAddress[i];
      longMac = longMac << (i*8);
    }

    for (int i=0; i<STRANDS; i++) {
      if (longMac == distanceTable[i].macAddress) {
        myLocation = distanceTable[i].location;
      }
      Serial.printf("%d: %f, %f\n", distanceTable[i].macAddress, distanceTable[i].location.x, distanceTable[i].location.y);
    }
    Serial.println();
}

void loop() {

  // Udp.beginPacket("10.0.1.255", 54608);
  // delay(5);
  // Udp.print("esp8266");
  // Udp.endPacket();
  // Udp.flush();
  // digitalWrite(BUILTIN_LED, LOW);
  // delay(50);
  // digitalWrite(BUILTIN_LED, HIGH);
  // delay(2950);

  // if there's data available, read a packet
  // int packetSize = Udp.parsePacket();
  // if (packetSize) {
    // Serial.print("Received packet of size ");
    // Serial.println(packetSize);
    // Serial.print("From ");
    // IPAddress remoteIp = Udp.remoteIP();
    // Serial.print(remoteIp);
    // Serial.print(", port ");
    // Serial.println(Udp.remotePort());
    //
    // // read the packet into packetBufffer
    // int len = Udp.read(packetBuffer, 255);
    // if (len > 0) {
    //   packetBuffer[len] = 0;
    // }
    // Serial.println("Contents:");
    // Serial.println(packetBuffer);

    // digitalWrite(BUILTIN_LED, LOW);
    // delay(50);
    // digitalWrite(BUILTIN_LED, HIGH);

    // send a reply, to the IP address and port that sent us the packet we received
    // Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    // delay(5);
    // // Udp.write(replyBuffer);
    // Serial.println(Udp.endPacket());
  // }

}
