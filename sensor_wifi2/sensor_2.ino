#include <ESP8266WiFi.h> 
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define sensor_2 A0     

void setup() {
  Serial.begin(9600);
  pinMode(sensor_2, INPUT);
  Serial.println("Sensor 2 test!");
  WiFi.begin("OPPO A33w", "12345679");
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting....");
    delay(300);
    }
  Serial.println("\r\nWiFi connected");
}
float value;
void loop() {
  delay(800);
  
   value =analogRead(sensor_2);//read pin A0 from sensor
   value=map(value,0,1023,0,3300);

  if (isnan(value) ) {
    Serial.println("Failed to read from FSR sensor!");
    return;
  }
  
  String request = "http://shm-utc.com/update.php?temp=" + String(value+10);//site target need get data
  Http_ReQuest(request);//http protocol
  
  Serial.print("Sensor Data: ");
  Serial.print(value);
  Serial.print("\t");

}


void Http_ReQuest(String request){
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    String url = request;
//    String thumbprint =   "08:3B:71:72:02:43:6E:CA:ED:42:86:93:BA:7E:DF:81:C4:BC:62:30"; //hash trim code for url
    http.begin(url);
    int httpCODE = http.GET();//get code, httpcode 200==true, httpcode <0 fail 
       Serial.println(url);
       Serial.println("http code :"+String(httpCODE));
    if(httpCODE > 0){
      String payload = http.getString();
      Serial.println(payload);
      }
    else{
      Serial.printf("HTTP GET failed, ERRORS: %s\n", http.errorToString(httpCODE).c_str());
      }
      http.end();
    }
  }
