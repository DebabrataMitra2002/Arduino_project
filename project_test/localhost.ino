/*************************************************************************************************
 *  Created By: Debabrata Mitra
 *  Created On: 10 march, 2024

**/
 
#include <WiFi.h> 
#include <HTTPClient.h> 

String URL = "http://192.168.43.27/pir_project/data_log.php";

const char* ssid = "HONOR Pad 5";
const char* password = "debodola1234";

int temperature = 0; 
int humidity = 0;
void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  //This line hides the viewing of ESP as wifi hotspot
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    
  Serial.print("connected to : "); Serial.println(ssid);
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}
void setup() {
  Serial.begin(115200); 
  connectWiFi();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) { 
    connectWiFi();
  }

   String postData = "SensorId=" + String(temperature) + "&SensorStatus=" + String(humidity);  

  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpCode = http.POST(postData);
  String payload = http.getString();

  Serial.print("URL : "); Serial.println(URL); 
  Serial.print("Data: "); Serial.println(postData);
  Serial.print("httpCode: "); Serial.println(httpCode);
  Serial.print("payload : "); Serial.println(payload);
  Serial.println("--------------------------------------------------");
  delay(5000);
}

