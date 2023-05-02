#include <WebServer.h>
#include <WiFi.h>
#include <esp32cam.h>

#include "credentials.h"


WebServer server(80);

static auto loRes = esp32cam::Resolution::find(320,240);
static auto miRes = esp32cam::Resolution::find(530,350);
static auto hiRes = esp32cam::Resolution::find(800,600);

void serveJpg() {
  auto image = esp32cam::capture();
  if (image == nullptr) {
    Serial.println("CAMERA CAPTURE FAIL");
    server.send(503, "", "");
    return;
  }

  Serial.printf("CAPTURE OK %dx%d %db\n", image->getWidth(), image->getHeight(), static_cast<int>(image->size()));
  
  server.setContentLength(image->size());
  server.send(200, "image/jpeg");

  WiFiClient client = server.client();
  image->writeTo(client);
}

void handleJpgLo() {
  if (!esp32cam::Camera.changeResolution(loRes)) {
    Serial.println("CAMERA SET TO LOW FAIL");
  }

  serveJpg();
}

void handleJpgMi() {
  if (!esp32cam::Camera.changeResolution(miRes)) {
    Serial.println("CAMERA SET TO MID FAIL");
  }

  serveJpg();
}

void handleJpgHi() {
  if (!esp32cam::Camera.changeResolution(hiRes)) {
    Serial.println("CAMERA SET TO HIGH FAIL");
  }

  serveJpg();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  {
    using namespace esp32cam;

    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(hiRes);
    cfg.setBufferCount(2);
    cfg.setJpeg(80);

    bool ok = Camera.begin(cfg);
    Serial.println(ok ? "CAMERA OK" : "CAMERA FAIL");
  }

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/cam-lo.jpg", handleJpgLo);
  server.on("/cam-mi.jpg", handleJpgMi);
  server.on("/cam-hi.jpg", handleJpgHi);

  // URL low quality
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/cam-lo.jpg");

  // URL medium quality
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/cam-mi.jpg");

  // URL high quality
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/cam-hi.jpg");

  server.begin();
}

void loop() {
  server.handleClient();
}
