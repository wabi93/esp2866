#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// set WiFi parameter
const char* ssid     = "SSID";
const char* password = "***********";

//set pushing paramenter
char devIdMail[] = "XXXXXXXX"; //DevID code for incomming mail
char devIdBattery[] = "XXXXXXXX"; //DevID code for emty battery 
char serverName[] = "api.pushingbox.com";

WiFiClient client;
const float batteryVoltage = 3,75; //voltage of used battery

/* 
 * Function for create a client WiFi-connection
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

/*
 *Function for sending the request to PushingBox
 */
void sendToPushingBox(char devid[]){
  if(client.connect(serverName, 80)) { 
    client.print("GET /pushingbox?devid=");
    client.print(devidMail);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(serverName);
    client.println("User-Agent: Arduino");
    client.println();
  }  
}

/*
 * Function for check battery charge condition
 */
void checkBatteryChargeCondition {
  int battlevel = analogRead(A0);
  float voltage = battlevel * (batteryVoltage / 1024.0); 
  
  if (voltage < (3,33*1024.0)){
    sendToPushingBox(devIdBattery);
  }
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

   //Sending request to PushingBox
   sendToPushingBox(devId);

   //set ESP8266 to deepsleep
   ESP.deepSleep(0);
}
