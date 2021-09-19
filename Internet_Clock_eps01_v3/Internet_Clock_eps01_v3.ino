  #include <NTPClient.h>
  #include <ESP8266WiFi.h>
  #include <WiFiUdp.h>

  const char *ssid     = "VIVOFIBRA-9501";
  const char *password = "rgw7ucm3GT";

  const long utcOffsetInSeconds =  -10800;
  char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sabado"};
  
  WiFiUDP ntpUDP;
  NTPClient timeClient(ntpUDP, "south-america.pool.ntp.org", utcOffsetInSeconds,60000);

//  byte  Minuto,
//        Hora;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("Ok");
}

void loop() {
  timeClient.update();
//  Hora = (timeClient.getHours());
//  Minuto = (timeClient.getMinutes());
  Serial.println(timeClient.getFormattedTime());
//  Serial.print(Hora);
//  Serial.print(":");
//  Serial.print(Minuto);
//  Serial.println(";");
  delay(1000);
}
