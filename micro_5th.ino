#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "AndroidAP9790"; //Enter your WIFI ssid
const char *password = "00000000"; //Enter your WIFI password
int led = D1;
int fan = D5;
ESP8266WebServer server(80);

char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Micro Lib Azazad University of shiraz</title>
</head>
<body>
   <center>
   <div>
    <form action="/Fan_on" method="get" id="form1" style="display: inline;">
       <button type="submit" value="FanOn" style="height:120px; width:200px;font-size:40px;">Fan On</button>
    </form>
     <form action="/Fan_off" method="get" id="form2" style="display: inline;">
       <button type="submit"  value="FanOff" style="height:120px; width:200px;font-size:40px;">Fan Off</button>
     </form>
     </div> 
   <br>
    <div>
    <form action="/LED_on" method="get" id="form3" style="display: inline;">
       <button type="submi" value="LedOn"style="height:120px; width:200px;font-size:40px;">Led On</button>
    </form>
    <form action="/LED_off" method="get" id="form4" style="display: inline;">
       <button type="submi"  value="LedOff"style="height:120px; width:200px;font-size:40px;">Led Off</button>
    </form>
     </div>
    </center>
</body>
)rawliteral"; //End index_html[]

void handleRoot() {
  String mysite = String((char *)index_html);
  server.send(200,"text/html",mysite); 
  }
void Function_FanOn(){
    digitalWrite(fan,HIGH);
    Serial.println("Fan on");
    handleRoot();
  }
void Function_FanOff(){
    digitalWrite(fan,LOW);
    Serial.println("Fan off");
    handleRoot();
  }
 void  Function_LEDon(){
    digitalWrite(led,HIGH);
    Serial.println("led on");
    handleRoot();
  }
  void Function_LEDoff(){
    digitalWrite(led,LOW);
    Serial.println("led off");
    handleRoot();
  }

void setup() {
  pinMode(fan, OUTPUT);
  pinMode(led, OUTPUT);

  Serial.begin(9600);
  Serial.print("Configuring access point...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.on ( "/", handleRoot );
  
  server.begin();
  Serial.println ( "HTTP server started" );
  server.on("/Fan_on",Function_FanOn);
  server.on("/Fan_off",Function_FanOff);
  server.on("/LED_on",Function_LEDon);
  server.on("/LED_off",Function_LEDoff);
}
void loop() {
  server.handleClient();
}
