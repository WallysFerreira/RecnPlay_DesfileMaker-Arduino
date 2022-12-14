#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/*Put your SSID & Password*/
const char* ssid = "SENAC-Mesh";  // Enter SSID here
const char* password = "09080706";  //Enter Password here
//IP do Local -> 

ESP8266WebServer server(80);

uint8_t ledColar = D7;   //pode ser o colar
bool LED1status = LOW;  //chave liga/desliga

uint8_t ledJanela = D6;   //pode ser janela
bool LED2status = LOW;  //chave liga/desliga

//---novo
uint8_t ledOlhos = D5;   //pode ser olhos
bool LED3status = LOW;  //chave liga/desliga

uint8_t ledCrab = D2;   //pode ser crab
bool LED4status = LOW;  //chave liga/desliga


//===========================================================MAIN SETUP=====================================================
void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(ledColar, OUTPUT);
  pinMode(ledJanela, OUTPUT);
  //---novo
  pinMode(ledOlhos, OUTPUT);
  pinMode(ledCrab, OUTPUT);


  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
//---novo
  server.on("/led3on", handle_led3on);
  server.on("/led3off", handle_led3off);
  server.on("/led4on", handle_led4on);
  server.on("/led4off", handle_led4off);
//--
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}


//===========================================================MAIN LOOP=====================================================
void loop() {
  server.handleClient();
  if(ledColarStatus)
  {digitalWrite(ledColar, HIGH);}
  else
  {digitalWrite(ledColar, LOW);}
  
  if(ledJanelaStatus)
  {digitalWrite(ledJanela, HIGH);}
  else
  {digitalWrite(ledJanela, LOW);}

//---novo
  if(ledOlhosStatus)
  {digitalWrite(ledOlhos, HIGH);}
  else
  {digitalWrite(ledOlhos, LOW);}

  if(ledCrabStatus)
  {digitalWrite(ledCrab, HIGH);}
  else
  {digitalWrite(ledCrab, LOW);}

}





//===========================================================FUNCOES=====================================================
void handle_OnConnect() {
  ledColar = LOW;
  ledJanela = LOW;
//---novo
  ledOlhos = LOW;
  ledCrab = LOW;
  Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF | GPIO5 Status: OFF | GPIO2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status)); 
}



//============COLAR
void handle_ligarColar() {
  ledColarStatus = HIGH;
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(true, ledJanelaStatus, ledOlhosStatus, ledCrabStatus)); 
}
//--
void handle_desligarColar() {
  ledColarStatus = LOW;
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(false, ledJanelaStatus, ledOlhosStatus, ledCrabStatus)); 
}



//=============JANELA
void handle_ligarJanela() {
  ledJanelaStatus = HIGH;
  Serial.println("GPIO6 Status: ON");
  server.send(200, "text/html", SendHTML(ledColarStatus, true, ledOlhosStatus, ledCrabStatus)); 
}
//--
void handle_desligarJanela() {
  ledJanelaStatus = LOW;
  Serial.println("GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(ledColarStatus, false, ledOlhosStatus, ledCrabStatus)); 
}



//==============OLHOS
void handle_ligarOlhos() {
  ledOlhosStatus = HIGH;
  Serial.println("GPIO5 Status: ON");
  server.send(200, "text/html", SendHTML(ledColarStatus, ledJanelaStatus, true, ledCrabStatus)); 
}
//--
void handle_desligarOlhos() {
  ledOlhosStatus = LOW;
  Serial.println("GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(ledColarStatus, ledJanelaStatus, false, ledCrabStatus)); 
}



//==============CRAB
void handle_ligarCrab() {
  ledCrabStatus = HIGH;
  Serial.println("GPIO2 Status: ON");
  server.send(200, "text/html", SendHTML(ledColarStatus, ledJanelaStatus, ledOlhosStatus, true)); 
}
//--
void handle_desligarCrab() {
  ledCrabStatus = LOW;
  Serial.println("GPIO2 Status: OFF");
  server.send(200, "text/html", SendHTML(ledColarStatus, ledJanelaStatus, ledOlhosStatus, false)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}




String SendHTML(uint8_t colarStatus, uint8_t janelaStatus, uint8_t olhosStatus, uint8_t crabStatus){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
    ptr +="<h3>Using Station(STA) Mode</h3>\n";
  
   if(colarStatus)
  {ptr +="<p>Colar Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>Colar Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(janelaStatus)
  {ptr +="<p>Janela Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>Janela Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}
 
  if(olhosStatus)
  {ptr +="<p>Olhos Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>Olhos Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}
  
  if(crabStatus)
  {ptr +="<p>Crab Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>Crab Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
