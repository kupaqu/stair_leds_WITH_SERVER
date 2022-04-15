#include "Config.h"
#include "WIFI.h"
#include "Server.h"
#include "MQTT.h"

double val;
bool go_backwards = false;
int led = -1;
int prev_led = -1;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  range_init();
  WIFI_init(MODE_AP);
  MQTT_init();

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  mqtt_client.loop();
  val = get_range();
  if (go_backwards)
    mqtt_client.publish(String("buda/leds/backwards").c_str(), String(val).c_str());
  mqtt_client.publish(String("buda/leds/forwards").c_str(), String(val).c_str());
  delay(1000);
}
