#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "SpectrumSetup-CB"; // Enter your WiFi name
const char *password = "voyagegallon501";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "esp/test";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
 // Set software serial baud to 115200;
 Serial.begin(115200);
 // connecting to a WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.println("Connecting to WiFi..");
  
  Serial.begin(9600);
  Serial.println("-------------------[INIT]-------------------");
  Serial.println("Serial data stream opened with 9600 bps.");
  Serial.println("Variables and Arrays have been set.");
  for (int i=0; i<9; i++) //Set all LEDs as OUTPUT and turn them off, assuming they are turned on.
  {
   pinMode(LEDPins[i], OUTPUT);
   digitalWrite(LEDPins[i], LOW);
  }
  for (int i=0; i<3; i++) //Set all Buttons as INPUT
  {
   pinMode(ButtonPins[i], INPUT_PULLUP);
   digitalWrite(ButtonPins[i], HIGH);
  }
  Serial.println("LEDs have been set to OUTPUT and turned off.");
  Serial.println("Buttons have been set to INPUT.");
  Serial.println("The game is now ready to commence.");
  Serial.println("-------------------[END]--------------------");
 }
 Serial.println("Connected to the WiFi network");
 //connecting to a mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);
 while (!client.connected()) {
     String client_id = "esp32-client-";
     client_id += String(WiFi.macAddress());
     Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
         Serial.println("Public emqx mqtt broker connected");
     } else {
         Serial.print("failed with state ");
         Serial.print(client.state());
         delay(2000);
     }
 }
 // publish and subscribe
 client.publish(topic, "Hi EMQX I'm ESP32 ^^");
 client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 for (int i = 0; i < length; i++) {
     Serial.print((char) payload[i]);
 }
 Serial.println();
 Serial.println("-----------------------");
}

void WinAnimation(int Who) //"Animation" to play if either Player has won.
{
 if (Who == 1) //If P1 won, make an "O"
 {
  delay(1000);
  for (int i=0; i<9; i++) { digitalWrite(LEDPins[i], LOW); }
  digitalWrite(LEDPins[7], HIGH); //D9
  digitalWrite(LEDPins[3], HIGH); //D5
  digitalWrite(LEDPins[5], HIGH); //D7
  digitalWrite(LEDPins[1], HIGH); //D3
  Serial.println("Player 1 has won the game!");
 }
 if (Who == 2) //If P2 won, make a "X"
 {
  delay(1000);
  for (int i=0; i<9; i++) { digitalWrite(LEDPins[i], LOW); }
  digitalWrite(LEDPins[6], HIGH); //D8
  digitalWrite(LEDPins[4], HIGH); //D6
  digitalWrite(LEDPins[8], HIGH); //D10
  digitalWrite(LEDPins[0], HIGH); //D2
  digitalWrite(LEDPins[2], HIGH); //D4
  Serial.println("Player 2 has won the game!");
 }
}


void GridCheck(int PCheck) //Check LED matrix if any Player got 3 in a row
{
  if (LEDVals[0] == PCheck) //D2, D3, D4
  { if (LEDVals[1] == PCheck) 
   { if (LEDVals[2]  == PCheck) 
    WinAnimation(PCheck);
    Serial.print("Player ");
    Serial.print(PCheck);
    Serial.println(" has 3 LEDs in a Row!");
   }
  }
  else if (LEDVals[0] == PCheck) //D2, D5, D8
  { if (LEDVals[3] == PCheck)
   { if (LEDVals[6] == PCheck)
    WinAnimation(PCheck);
    Serial.print("Player ");
    Serial.print(PCheck);
    Serial.println(" has 3 LEDs in a Row!");
   }
  }
  else if (LEDVals[0] == PCheck) //D2, D6, D10
  { if (LEDVals[4] == PCheck)
   { if (LEDVals[8] == PCheck)
    WinAnimation(PCheck);
    Serial.print("Player ");
    Serial.print(PCheck);
    Serial.println(" has 3 LEDs in a Row!");
   }
  }
  else if (LEDVals[1] == PCheck) //D3, D6, D9
  { if (LEDVals[4] == PCheck)
   { if (LEDVals[7] == PCheck)
    WinAnimation(PCheck);
    Serial.print("Player ");
    Serial.print(PCheck);
    Serial.println(" has 3 LEDs in a Row!");
   }
  }
  else if (LEDVals[2] == PCheck) //D4, D7, D10
  { if (LEDVals[5] == PCheck)
   { if (LEDVals[8] == PCheck)
    WinAnimation(PCheck);
    Serial.print("Player ");
    Serial.print(PCheck);
    Serial.println(" has 3 LEDs in a Row!");
   }
  }
  else if (LEDVals[3] == PCheck) //D5, D6, D7
  { if (LEDVals[4] == PCheck)
   { if (LEDVals[5] == PCheck)
    WinAnimation(PCheck);
    Serial.print("Player ");
    Serial.print(PCheck);
    Serial.println(" has 3 LEDs in a Row!");
   }
  }
  else if (LEDVals[6] == PCheck) //D8, D9, D10
  { if (LEDVals[7] == PCheck)
   { if (LEDVals[8] == PCheck)
    WinAnimation(PCheck);
    Serial.print("Player ");
    Serial.print(PCheck);
    Serial.println(" has 3 LEDs in a Row!");
   }
  }
  else if (LEDVals[2] == PCheck) //D4, D6, D8
  { if (LEDVals[4] == PCheck)
   { if (LEDVals[6] == PCheck)
    WinAnimation(PCheck);
    Serial.print("Player ");
    Serial.print(PCheck);
    Serial.println(" has 3 LEDs in a Row!");
   }
  }
  Serial.println("[DEBUG] No player won yet.");
  //0 = off, 1 = on (P1), 2 = sel (P1), 3 = on (P2), 4 = sel (P3)
}

void UpPos() {Pos = Up + Right; Serial.println("Position Variable updated."); }

void ResetLastLED()
{
 if (TPos != Pos)
 {
   if (LEDVals[TPos - 1] == 1 || 3)
   {
     Serial.println("[DEBUG] Previous LED is already assigned to a Player, skipping.");
     TPos - 1;
     ResetLastLED();
   }
   else if (LEDVals[TPos - 1] == 2 || 4)
   {
     if (LEDVals[TPos - 1] < 0)
     {
       TPos = 9;
       Serial.println("[DEBUG] TPos lower than 0, setting value to 9.");
       ResetLastLED();
     }
     else
     {
       LEDVals[TPos - 1] == 0;
       Serial.println("[DEBUG] Last moved LED set to 0"); //Overrides LED regardless of value and must be fixed.
     }
    }
  }
}

void SelectLED(int Dir) //Parameter indicates direction. 1 = Up, 2 = Right
{
  if (Dir == 1)
  {
    if (Up < 3 ) { Up = 0; Serial.println("'Up' higher than 3, resetting to 0."); UpPos(); }
    else if (Up > 3 )
    {
      Serial.println("[DEBUG] selected LED was moved up."); 
      Up++;
      UpPos();
      Pos = TPos;
      if (Player = false) { LEDVals[Pos] = 2; }
      else { LEDVals[Pos] = 4; }
      ResetLastLED();
    }
  }
  else if (Dir == 2)
  {
    if (Right < 3 ) { Right = 0; Serial.println("'Right' higher than 3, resetting to 0."); }
    else if (Right > 3 )
    {
      Serial.println("[DEBUG] selected LED was moved to the right."); 
      Right++;
      UpPos();
      Pos = TPos;
      if (Player = false) { LEDVals[Pos] = 2;}
      else { LEDVals[Pos] = 4; } 
      ResetLastLED();
    }
  }
}
//0 = off, 1 = on (P1), 2 = sel (P1), 3 = on (P2), 4 = sel (P2)
void LEDUpdate()
{
  for (int i=0; i<9; i++)
  {
    if (LEDVals[i] == 1)
    {
     digitalWrite(LEDPins[i], HIGH);
     delay(500);                     //Wait 0.5 seconds
     digitalWrite(LEDPins[i], LOW);
     delay(500);
     Serial.print("[DEBUG] Pin at D");
     Serial.print(LEDPins[i]);
     Serial.println(" turned ON (P1).");
    }
    else if (LEDVals[i] == 3) 
    {
     digitalWrite(LEDPins[i], HIGH);
     delay(250);                     //Wait 0.25 seconds
     digitalWrite(LEDPins[i], LOW);
     delay(250);
     Serial.print("[DEBUG] Pin at D");
     Serial.print(LEDPins[i]);
     Serial.println(" turned ON (P2).");
    }
    else if (LEDVals[i] == 2)
    {
     digitalWrite(LEDPins[i], HIGH);
     delay(1000);                    //Wait 1 second
     digitalWrite(LEDPins[i], LOW);
     delay(1000);
     Serial.print("[DEBUG] Pin at D");
     Serial.print(LEDPins[i]);
     Serial.println(" selected. (P1)");
    }
    else if (LEDVals[i] == 4)
    {
     digitalWrite(LEDPins[i], HIGH);
     delay(1000);                    //Wait 1 second
     digitalWrite(LEDPins[i], LOW);
     delay(1000);
     Serial.print("[DEBUG] Pin at D");
     Serial.print(LEDPins[i]);
     Serial.println(" selected. (P2)");
    }
    else if (LEDVals[i] == 0) 
    {
     digitalWrite(LEDPins[i], LOW);
     Serial.print("[DEBUG] Pin at D");
     Serial.print(LEDPins[i]);
     Serial.println(" turned OFF.");
    } 
  }
}
  
void SetLED() //0 = off, 1 = on (P1), 2 = sel (P1), 3 = on (P2), 4 = sel (P2)
{
  if (LEDVals[Pos] == 2) { LEDVals[Pos] = 1; }
  else if (LEDVals[Pos] == 4) {LEDVals[Pos] = 3; }
  else if (LEDVals[Pos] == 1 || 3) {Serial.println("Cannot set LED to Player, as it is assigned already!"); }
  if ( Player = false ) { Player = true; Serial.println("Players switched."); }
  else { Player = false; Serial.println("Players switched."); }
}


void loop() {
 client.loop();
 if (loops > 1) { Serial.println("============================================"); }
 
 Serial.print("Loop nr. ");
 Serial.println(loops);
 
 if (Player = false ) { GridCheck(1); }
 else { GridCheck(3); }

 //Buttons are creating a flood of input and must be fixed!
 if (digitalRead(ButtonPins[0] == LOW)) { SelectLED(1); LEDUpdate(); Serial.println("Button at D11 pressed."); }
 if (digitalRead(ButtonPins[1] == LOW)) { SelectLED(2); LEDUpdate(); Serial.println("Button at D12 pressed."); }
 if (digitalRead(ButtonPins[2] == LOW)) { SetLED(); LEDUpdate(); Serial.println("Button at D13 pressed."); }
 
 for (int i=0; i<9; i++)
 {
  //First if-statement is being executed, no matter what the condition.
 }
 delay(100);
 Serial.println("[DEBUG] loop() finished.");
 loops++;
}
