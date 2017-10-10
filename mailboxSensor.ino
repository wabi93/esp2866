#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// set WiFi parameter
const char* ssid     = "SSID";
const char* password = "***********";

//set pushing paramenter
Sring apiKey = "XXXXXXXX"; //DevID code
const char* server = "api.pushingbox.com";

/* 
 * create a client WiFi-connection
 */
void WiFiStart(const char* ssid,const char* password) {
  
  // check for the presence of the shield
  //if no shield wait
  while (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    delay(10000);
  }

  Serial.print("Connecting to ");
  Serial.println(ssid);
  //connecting to a WiFi network
  WiFi.begin(ssid, password);

  // wait until WiFi is connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());            
}

void setup() {
  
  // start serial
  Serial.begin(115200);
  delay(100);

  // inital connect
  WiFi.mode(WIFI_STA);
  WiFiStart(ssid, password);

}

void loop() {
   // check if WLAN is connected
  if (WiFi.status() != WL_CONNECTED){
    WiFiStart(ssid, password);
  }

  if (client.connect(server,80)) { 
    Serial.println("Connecting");
      client.print("GET /pushingbox?devid=");
      client.print(apiKey);
      client.println(" HTTP/1.1");
      client.print("Host: ");
      client.println(server);
      client.println("User-Agent: Arduino");
      client.println();


   //set ESP8266 to deepsleep
   ESP.deepSleep(0);
}
