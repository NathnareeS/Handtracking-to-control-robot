#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>
#include <Wire.h>
#define accel_module (0x53)
byte values[6];
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads(0x48);
float Voltage = 0.0;
const char *ssid = "Sujeewifi";
const char *password = "12345678";
const char *mqtt_server = "34.87.103.108";
int headingangle;
int buttonstate=0;
int cnt=0;
int pstate=0;
int cstate=0;
#define MQTT_PUB_TOPIC "glove/output"
#define MQTT_SUB_TOPIC "glove/input"
#define MQTT_ID "Glove"
ESP8266WiFiMulti WiFiMulti;
WiFiClient esp8266Client;
PubSubClient client(esp8266Client);
void setup_wifi() {
  // put your setup code here, to run once:
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFiMulti.addAP(ssid, password);
  delay(10);
  while (WiFiMulti.run() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  payload[length] = '\0'; // Make payload a string by NULL terminating it.
  headingangle = atoi((char *)payload);
  Serial.println("heading in callback"+(String)headingangle);
  //send seperate topic.
  Serial.println();
  /*----------------*/
}
void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
  if (client.connect(MQTT_ID))
  {
    Serial.println("connected");
    // ... and resubscribe
    client.subscribe(MQTT_SUB_TOPIC);
  }
  else
  {
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" try again in 2 seconds");
  // Wait 2 seconds before retrying
  delay(2000);
}
}
}
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(A0,INPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  ads.begin();
  //-------------------------------------
  Wire.begin();
  Wire.beginTransmission(accel_module);
  Wire.write(0x20); // CTRL_REG1 - Power Mode
  Wire.write(0); // Normal mode: 15d - 00001111b
  Wire.endTransmission();
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D); // CTRL_REG4 - Sensitivity, Scale Selection
  Wire.write(16); // 2000dps: 48d - 00110000b
  Wire.endTransmission();
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D); // CTRL_REG4 - Sensitivity, Scale Selection
  Wire.write(8); // 2000dps: 48d - 00110000b
  Wire.endTransmission();
}
char msg[220];
int count = 0;
void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  //---------------ADXL----------------------------
  int xyzregister = 0x32;
  int x, y, z;

  Wire.beginTransmission(accel_module); // transmit to device
  Wire.write(xyzregister);
  Wire.endTransmission();

  Wire.beginTransmission(accel_module);
  Wire.requestFrom(accel_module,6);

  int q = 0;
  while(Wire.available()){
    values[q] = Wire.read();
    q++;
  }
  Wire.endTransmission();

  x = (((int)values[1]) << 8) | values[0];
  y = (((int)values[3]) << 8) | values[2];
  z = (((int)values[5]) << 8) | values[4];
  //--------------------------------
  int16_t button;
  int order;
  float sensor=analogRead(A0);
  button = ads.readADC_SingleEnded(0);
  //------activate CALLBACK function----------------
  if(sensor>700 && sensor<800)
  {
    snprintf(msg, 75, "%d",-20);
  }
  //switch mode button val =8000-9000
  if(button>=8000 && button<=9000)//Switch mode
  {
    cstate=1;
    if(cstate=1 and pstate==0)
    {
      pstate=cstate;
      cnt++;
    }
   //--------when switch to hand control---------
    //-----------------Hand>Forward--------------
    if((x>60000 and y>60000 and z>=0 and z<=1000) )
    {
      if(0<=headingangle && headingangle<=29)//0 degree
      {
        snprintf(msg, 75, "%d",-7);
      }
      else if(30<=headingangle && headingangle<=59)//30 degree
      {
        snprintf(msg, 75, "%d",-6);
      }
      else if(60<=headingangle && headingangle<=89)//60 degree
      {
        snprintf(msg, 75, "%d",-5);
      }
      else if(90<=headingangle && headingangle<=119)//90 degree
      {
        snprintf(msg, 75, "%d",750);
      }
      else if(120<=headingangle && headingangle<=149)//120 degree
      {
        snprintf(msg, 75, "%d",-11);
      }
      else if(150<=headingangle && headingangle<=179)//150 degree
      {
        snprintf(msg, 75, "%d",-12);
      }
      else if(180<=headingangle && headingangle<=209)//180 degree
      {
        snprintf(msg, 75, "%d",-13);
      }
      else if(210<=headingangle && headingangle<=239)//210 degree
      {
        snprintf(msg, 75, "%d",-14);
      }
      else if(240<=headingangle && headingangle<=269)//240 degree
      {
        snprintf(msg, 75, "%d",-15);
      }
      else if(270<=headingangle && headingangle<=299)//270 degree
      {
        snprintf(msg, 75, "%d",-10);
      }
      else if(300<=headingangle && headingangle<=329)//300 degree
      {
        snprintf(msg, 75, "%d",-9);
      }
      else if(330<=headingangle && headingangle<=360)//330 degree
      {
        snprintf(msg, 75, "%d",-8);
      }
    }
    //---------------Hand>Turn Left-------------
    else if(x>60000 and y>=0 and y<=1000 and z>10000)
    {
      if(0<=headingangle && headingangle<=29)//0 degree
      {
        snprintf(msg, 75, "%d",-10);
      }
      else if(30<=headingangle && headingangle<=59)//30 degree
      {
        snprintf(msg, 75, "%d",-9);
      }
      else if(60<=headingangle && headingangle<=89)//60 degree
      {
        snprintf(msg, 75, "%d",-8);
      }
      else if(90<=headingangle && headingangle<=119)//90 degree
      {
        snprintf(msg, 75, "%d",-7);
      }
      else if(120<=headingangle && headingangle<=149)//120 degree
      {
        snprintf(msg, 75, "%d",-6);
      }
      else if(150<=headingangle && headingangle<=179)//150 degree
      {
        snprintf(msg, 75, "%d",-5);
      }
      else if(180<=headingangle && headingangle<=209)//180 degree
      {
        snprintf(msg, 75, "%d",750);
      }
      else if(210<=headingangle && headingangle<=239)//210 degree
      {
        snprintf(msg, 75, "%d",-11);
      }
      else if(240<=headingangle && headingangle<=269)//240 degree
      {
        snprintf(msg, 75, "%d",-12);
      }
      else if(270<=headingangle && headingangle<=299)//270 degree
      {
        snprintf(msg, 75, "%d",-13);
      }
      else if(300<=headingangle && headingangle<=329)//300 degree
      {
        snprintf(msg, 75, "%d",-14);
      }
      else if(330<=headingangle && headingangle<=360)//330 degree
      {
        snprintf(msg, 75, "%d",-15);
      }
    }
    //----------------Hand>Turn Right-------------
    else if(x>60000 and y>60000 and z>=2000 and z<=10000)
    {
      if(0<=headingangle && headingangle<=29)//0 degree
      {
        snprintf(msg, 75, "%d",750);
      }
      else if(30<=headingangle && headingangle<=59)//30 degree
      {
        snprintf(msg, 75, "%d",-11);
      }
      else if(60<=headingangle && headingangle<=89)//60 degree
      {
        snprintf(msg, 75, "%d",-12);
      }
      else if(90<=headingangle && headingangle<=119)//90 degree
      {
        snprintf(msg, 75, "%d",-13);
      }
      else if(120<=headingangle && headingangle<=149)//120 degree
      {
        snprintf(msg, 75, "%d",-14);
      }
      else if(150<=headingangle && headingangle<=179)//150 degree
      {
        snprintf(msg, 75, "%d",-15);
      }
      else if(180<=headingangle && headingangle<=209)//180 degree
      {
        snprintf(msg, 75, "%d",-10);
      }
      else if(210<=headingangle && headingangle<=239)//210 degree
      {
        snprintf(msg, 75, "%d",-9);
      }
      else if(240<=headingangle && headingangle<=269)//240 degree
      {
        snprintf(msg, 75, "%d",-8);
      }
      else if(270<=headingangle && headingangle<=299)//270 degree
      {
        snprintf(msg, 75, "%d",-7);
      }
      else if(300<=headingangle && headingangle<=329)//300 degree
      {
        snprintf(msg, 75, "%d",-6);
      }
      else if(330<=headingangle && headingangle<=360)//330 degree
      {
        snprintf(msg, 75, "%d",-5);
      }
    //-----------------Hand>Stop-------------------
    else if(x<=0 and x>=100 and y<=0 and y>=500 and z<=500 and z>=2000)
    {
      snprintf(msg, 75, "%d",-16);
    }
  }
  else //initial state > button function activated 
  {
    cstate=0;
    pstate=cstate;
    snprintf(msg, 75, "%d",button);
  }
 }
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish(MQTT_PUB_TOPIC, msg);
  Serial.println("Heading in loop"+(String)headingangle);
  delay(1000);
  count = count+1;
} 
