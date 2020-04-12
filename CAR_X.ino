#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>
#include <stdio.h>
#include <Wire.h>
#include <math.h>
#include <stdlib.h>
//#define infrared D6
#define accel_module (0x53)
byte values[6];
char output[512];
int count=1;
int val;
long currentMillis=0;
long continueMillis=0;
long Millitime=0;
int currentorder=0;
int prevorder=0;
int *times,*orders;
int sizeoftimes=1;
int sizeoforders=1;
//--------------------------------
const char *ssid = "Sujeewifi";
const char *password = "12345678";
const char *mqtt_server = "34.87.103.108";
int data=0;
/*#define MQTT_PUB_TOPIC "glove/output"*/
#define MQTT_SUB_TOPIC "robot/input"
#define MQTT_PUB_TOPIC_Ax "robot/Ax"
#define MQTT_PUB_TOPIC_Ay "robot/Ay"
#define MQTT_PUB_TOPIC_Vx "robot/Vx"
#define MQTT_PUB_TOPIC_Vy "robot/Vy"
#define MQTT_PUB_TOPIC_Sx "robot/Sx"
#define MQTT_PUB_TOPIC_Sy "robot/Sy"
#define MQTT_PUB_TOPIC_Heading "robot/Heading"
#define MQTT_PUB_TOPIC_SxSy "robot/SxSy"
#define MQTT_ID "Robot"
#define BACK D5
#define FORW D6
#define LEFT D3
#define RIGHT D4
ESP8266WiFiMulti WiFiMulti;
WiFiClient esp8266Client;
PubSubClient client(esp8266Client);
//-------------------
int *Ax,*Ay,*Vx,*Vy,*Sx,*Sy,*S,a,b;
int sizeofAx=1;
int sizeofAy=1;
int sizeofVx=1;
int sizeofVy=1;
int sizeofSx=1;
int sizeofSy=1;
int sizeofS=1;
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
//------------------------------------------------------
void forward()
{
   digitalWrite(BACK, LOW);
   digitalWrite(FORW, HIGH);
   digitalWrite(LEFT, LOW);
   digitalWrite(RIGHT, LOW);
   Serial.println("UP");
   if(val!=-20)
   {
     currentMillis=continueMillis;
     currentorder=1;
     Millitime=continueMillis-currentMillis;
     times[sizeoftimes-1]=Millitime;
     orders[sizeoforders-1]=currentorder;
   }
}
void backward()
{
   digitalWrite(BACK, HIGH);
   digitalWrite(FORW, LOW);
   digitalWrite(LEFT, LOW);
   digitalWrite(RIGHT, LOW);
   Serial.println("DOWN");
    if(val!=-20)
   {
     currentMillis=continueMillis;
     currentorder=2;
     Millitime=continueMillis-currentMillis;
     times[sizeoftimes-1]=Millitime;
     orders[sizeoforders-1]=currentorder;  
   }
}
void turnleft()
{
   digitalWrite(BACK, LOW);
   digitalWrite(FORW, HIGH);
   digitalWrite(LEFT, HIGH);
   digitalWrite(RIGHT, LOW);
   Serial.println("LEFT");
    if(val!=-20)
   {
     currentMillis=continueMillis;
     currentorder=3;
     Millitime=continueMillis-currentMillis;
     times[sizeoftimes-1]=Millitime;
     orders[sizeoforders-1]=currentorder;  
   }
}
void turnright()
{
   digitalWrite(BACK, LOW);
   digitalWrite(FORW, HIGH);
   digitalWrite(LEFT, LOW);
   digitalWrite(RIGHT, HIGH);
   Serial.println("RIGHT");
    if(val!=-20)
   {
     currentMillis=continueMillis;
     currentorder=4;
     Millitime=continueMillis-currentMillis;
     times[sizeoftimes-1]=Millitime;
     orders[sizeoforders-1]=currentorder;
   }
}
void turnleftback()
{
   digitalWrite(BACK, HIGH);
   digitalWrite(FORW, LOW);
   digitalWrite(LEFT, HIGH);
   digitalWrite(RIGHT, LOW);
   Serial.println("LEFTBACK");

}
void turnrightback()
{
   digitalWrite(BACK, HIGH);
   digitalWrite(FORW, LOW);
   digitalWrite(LEFT, LOW);
   digitalWrite(RIGHT, HIGH);
   Serial.println("RIGHTBACK");

}
void leftdegree(int degree)
{
    int delays;
    digitalWrite(BACK, LOW);
    digitalWrite(FORW, HIGH);
    digitalWrite(LEFT, HIGH);
    digitalWrite(RIGHT, LOW);
    if(degree==30)
    {
      currentorder=5;
      Millitime=4500;
      delays=Millitime;
    }
    else if(degree==60)
    {
      currentorder=6;
      Millitime=9000;
      delays=Millitime;
    }
    else if(degree==90)
    {
      currentorder=7;
      Millitime=13000;
      delays=Millitime;
    }
     else if(degree==120)
    {
      currentorder=8;
      Millitime=17000;
      delays=Millitime;
    }
     else if(degree==150)
    {
      currentorder=9;
      Millitime=22000;
      delays=Millitime;
    }
     else if(degree==180)
    {
      currentorder=10;
      Millitime=26000;
      delays=Millitime;
    }
    times[sizeoftimes-1]=Millitime;
    orders[sizeoforders-1]=currentorder;
    delay(delays);
    forward();
}
void rightdegree(int degree)
{
    int delays;
    digitalWrite(BACK, LOW);
    digitalWrite(FORW, HIGH);
    digitalWrite(LEFT, LOW);
    digitalWrite(RIGHT, HIGH);
    if(degree==30)
    {
      currentorder=11;
      Millitime=4500;
      delays=Millitime;
    }
    else if(degree==60)
    {
      currentorder=12;
      Millitime=9000;
      delays=Millitime;
    }
    else if(degree==90)
    {
      currentorder=13;
      Millitime=13000;
      delays=Millitime;
    }
     else if(degree==120)
    {
      currentorder=14;
      Millitime=17000;
      delays=Millitime;
    }
     else if(degree==150)
    {
      currentorder=15;
      Millitime=22000;
      delays=Millitime;
    }
    times[sizeoftimes-1]=Millitime;
    orders[sizeoforders-1]=currentorder;
    delay(delays);
    forward();
}
void stops()
{
  digitalWrite(BACK, LOW);
  digitalWrite(FORW, LOW);
  digitalWrite(LEFT, LOW);
  digitalWrite(RIGHT, LOW);
}
void callbacks(int order,int delays)
{
  if(order==1){
    backward();
    delay(delays);
  }
  else if(order==2)
  {
    forward();
    delay(delays);
  }
  else if(order==3||order==5||order==6||order==7||order==8||order==9||order==10)
  {
    turnleftback();
    delay(delays);
  }
  else if(order==4||order==11||order==12||order==13||order==14||order==15)
  {
    turnrightback();
    delay(delays);
  }
}
//------------------------------------------------------
/*void callback(char *topic, byte *payload, unsigned int length)*/
void callback(char *topic,byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  payload[length] = '\0'; // Make payload a string by NULL terminating it.
  val = atoi((char *)payload);
  continueMillis=millis();
  /*---------------------Move Forward ----------------*/
  if((val>= 700) && (val <=900))
  {
    forward();
  }
  /*--------------------Move Backward------------------*/
  else if( (val >= 2000) && (val <=3000) )
  {
    backward();
  }
  /*----------------------Move Left------------------*/
  else if(val>=-3 && val<=50)
  {
    turnleft();
  }
  /*-----------------------Move Right------------------*/
  else if( (val >= 3500) && (val <=5500) )
  {
    turnright();
  }
  //--------------Turn left 30 then forw---------------------
  else if(val==-5)
  {
    leftdegree(30);
  }
  //--------------Turn left 60 then forw---------------------
  else if(val==-6)
  {
    leftdegree(60);
  }
  //--------------Turn left 90 then forw---------------------
  else if(val==-7)
  {
    leftdegree(90);
  }
  //--------------Turn left 120 then forw---------------------
  else if(val==-8)
  {
    leftdegree(120);
  }
  //--------------Turn left 150 then forw---------------------
  else if(val==-9)
  {
    leftdegree(150);
  }
  //--------------Turn left 180 then forw---------------------
  else if(val==-10)
  {
    leftdegree(180);
  }
  //--------------Turn Right 30 then forw---------------------
  else if(val==-11)
  {
    rightdegree(30);
  }
  //--------------Turn Right 60 then forw---------------------
  else if(val==-12)
  {
    rightdegree(60);
  }
  //--------------Turn Right 90 then forw---------------------
  else if(val==-13)
  {
    rightdegree(90);
  }
  //--------------Turn Right 120 then forw---------------------
  else if(val==-14)
  {
    rightdegree(120);
  }
  //--------------Turn Right 150 then forw---------------------
  else if(val==-15)
  {
    rightdegree(150);
  }
  else if(val==-16)
  {
    stops();
  }
  orders=(int*)realloc(orders,sizeoforders*sizeof(int));//add to array
  sizeoftimes++;
  sizeoforders++;
  times=(int*)realloc(times,sizeoftimes*sizeof(int));//add to array
  Serial.print("TIMES: ");
  for(int i=0;i<sizeoftimes-1;i++)
  {
    Serial.print("TIMES: ");
    Serial.print(" '");
    Serial.print(times[i]);
    Serial.print("' ");
  }
  Serial.println("");
  Serial.print("ORDERS: ");
  for(int i=0;i<sizeoforders-1;i++)
  {
    Serial.print(" '");
    Serial.print(orders[i]);
    Serial.print("' ");
  }
  //---------------CALL BACK FUNCTION----------------------
  if(val==-20)
  {
    for(int i=sizeof(orders-1);i=0;i--)
    {
      callbacks(orders[i],times[i]);
    }
    orders=(int*)realloc(orders,1*sizeof(int));//clear array
    times=(int*)realloc(times,1*sizeof(int));//clear array
  }
  //------------------------------------
  else{
    digitalWrite(BACK, LOW);
    digitalWrite(FORW, LOW);
    digitalWrite(LEFT, LOW);
    digitalWrite(RIGHT, LOW);
  }
}
//------------END CALLBACK----------------------
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
int integrate(int x_new,int x_old,int f_0)
{
  int f_new= (int)(f_0 + 0.5 * 0.5 *(x_old+x_new));//sample rate 200ms
  Serial.println(f_0);
  return f_new;
}
int headingangle(int Sy,int Sx)
{
  int heading=atan2(Sy,Sx)*57.296;//1rad = 57.296 degree
  return heading;
}
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  
  client.setCallback(callback);
  pinMode(BACK, OUTPUT);
  pinMode(FORW, OUTPUT);
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
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
  Ax=(int*)calloc(sizeofAx,sizeof(int));
  Ay=(int*)calloc(sizeofAy,sizeof(int));
  Vx=(int*)calloc(sizeofVx,sizeof(int));
  Vy=(int*)calloc(sizeofVy,sizeof(int));
  Sx=(int*)calloc(sizeofSx,sizeof(int));
  Sy=(int*)calloc(sizeofSy,sizeof(int));
  times=(int*)calloc(sizeoftimes,sizeof(int));
  orders=(int*)calloc(sizeoforders,sizeof(int));
}
//-----------------------------
int counts = 0;
char msgAx[220];
char msgAy[220];
char msgVx[220];
char msgVy[220];
char msgSx[220];
char msgSy[220];
char msgheading[220];
char msgSxSy[220];
//-----------------------------
void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  //---------------ADXL----------------------------
  int xyzregister = 0x32;
  int x, y;
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
  //--------------------------------
  if(count<4)
  {
      //Serial.println("count<4");
      count++;
      delay(500);
  }
  if(count==4){
  //----------Array A in X axis---------------------------------
    Serial.println("sizeofAx="+(String)sizeofAx);
    if(sizeofAx==1 && x>=40000)
    {
      Ax[sizeofAx-1]=0;
      // Serial.println("X>40000");
    }
    else if(sizeofAx==1 && x<40000)
    {
      Ax[sizeofAx-1]=x;
      // Serial.println("Ax=x1");
    }
    else if(sizeofAx>1 && x>40000)
    {
      Ax[sizeofAx-1]=Ax[sizeofAx-2];
      //Serial.println("Ax=Ax-2");
    }
    else
    {
      Ax[sizeofAx-1]=x;
      //Serial.println("Ax=x");
    }
    Serial.print(Ax[sizeofAx-1]);
    sizeofAx++;
    Ax=(int*)realloc(Ax,sizeofAx*sizeof(int));
     Serial.print("Array Ax");
     Serial.print("|||");
     Serial.print("Size= ");
     Serial.print(sizeofAx);
    for(int i=0;i<sizeofAx-1;i++)
    {
       Serial.print(" '");
       Serial.print(Ax[i]);
       Serial.print("' ");
      snprintf(msgAx, 75, "%d",Ax[i]);
    }
    if(sizeofAx==4)
    
    {
      Ax[sizeofAx-4]=Ax[sizeofAx-3];
      Ax[sizeofAx-3]=Ax[sizeofAx-2];
      sizeofAx=3;
    }
    Ax=(int*)realloc(Ax,sizeofAx*sizeof(int));
     Serial.println("");
    //--------------Array A in Y axis----------------------------------------
    // Serial.println("sizeofAy="+(String)sizeofAy);
    if(sizeofAy==1 && y>=40000)
    {
      Ay[sizeofAy-1]=0;
      // Serial.println("y>40000");
    }
    else if(sizeofAy==1 && y<40000)
    {
      Ay[sizeofAy-1]=y;
      // Serial.println("Ay=y1");
    }
    else if(sizeofAy>1 && y>40000)
    {
      Ay[sizeofAy-1]=Ay[sizeofAy-2];
      //Serial.println("Ay=Ay-2");
    }
    else
    {
    Ay[sizeofAy-1]=y;
    //Serial.println("Ay=y");
    }
     Serial.print(Ay[sizeofAy-1]);
    sizeofAy++;
    Ay=(int*)realloc(Ay,sizeofAy*sizeof(int));
     Serial.print("Array Ay");
     Serial.print("|||");
     Serial.print("Size= ");
     Serial.print(sizeofAy);
    for(int i=0;i<sizeofAy-1;i++)
    {
       Serial.print(" '");
       Serial.print(Ay[i]);
       Serial.print("' ");
      snprintf(msgAy, 75, "%d",Ay[i]);
    }
    if(sizeofAy==4)
    {
      Ay[sizeofAy-4]=Ay[sizeofAy-3];
      Ay[sizeofAy-3]=Ay[sizeofAy-2];
      sizeofAy=3;
    }
    Ay=(int*)realloc(Ay,sizeofAy*sizeof(int));
    Serial.println("");
    //-------------------------------
    Serial.println("----------");
    //-------------------Vx----------------------
    //Serial.println("SizeofVx="+(String)sizeof
    if(sizeofVx<3)
    {
      Vx[sizeofVx-1]=0;
      //Serial.println("Vy<3"+(String)Vy[1]);
      //printV(Vy);
    }
    if(sizeofVx==3)
    {
      Vx[sizeofVx-1]=integrate(Ax[sizeofAx-2],Ax[sizeofAx-3],Vx[1]);
      //Serial.println("Vx"+(String)Vx[1]);
      //printV(Vx);
    }
    sizeofVx++;
    Vx=(int*)realloc(Vx,sizeofVx*sizeof(int));
     Serial.print("Array Vx");
     Serial.print("|||");
     Serial.print("Size= ");
     Serial.print(sizeofVx);
    for(int i=0;i<sizeofVx-1;i++)
    {
       Serial.print(" '");
       Serial.print(Vx[i]);
       Serial.print("' ");
      snprintf(msgVx, 75, "%d",Vx[i]);
    }
    if(sizeofVx==4)
    {
      Vx[0]=Vx[1];
      Vx[1]=Vx[2];
      sizeofVx=3;
    }
    Vx=(int*)realloc(Vx,sizeofVx*sizeof(int));
    Serial.println("");
    //-------------------Vy----------------------
    if(sizeofVy<3)
    {
      Vy[sizeofVy-1]=0;
      //Serial.println("Vy<3"+(String)Vy[1]);
      //printV(Vy);
    }
    if(sizeofVy==3)
    {
      Vy[sizeofVy-1]=integrate(Ay[sizeofAy-2],Ay[sizeofAy-3],Vy[1]);
      //Serial.println("Vy"+(String)Vy[1]);
      //printV(Vy);
    }
    sizeofVy++;
    Vy=(int*)realloc(Vy,sizeofVy*sizeof(int));
     Serial.print("Array Vy");
     Serial.print("|||");
     Serial.print("Size= ");
     Serial.print(sizeofVy);
    for(int i=0;i<sizeofVy-1;i++)
    {
       Serial.print(" '");
       Serial.print(Vy[i]);
       Serial.print("' ");
      snprintf(msgVy, 75, "%d",Vy[i]);
    }
    if(sizeofVy==4)
    {
      Vy[0]=Vy[1];
      Vy[1]=Vy[2];
      sizeofVy=3;
    }
    Vy=(int*)realloc(Vy,sizeofVy*sizeof(int));
    Serial.println("");
    //-------------------------------
     Serial.println("----------");
    //--------------------Sx----------------------------
    if(sizeofSx<3)
    {
      Sx[sizeofSx-1]=0;
      //Serial.println("Sx<3"+(String)Sx[1]);
      //printV(Sx);
    }
    if(sizeofSx==3)
    {
      Sx[sizeofSx-1]=integrate(Vx[sizeofVx-2],Vx[sizeofVx-3],Vx[1]);
      //Serial.println("Sx"+(String)Sx[1]);
      //printV(Sx);
    }
    sizeofSx++;
    Sx=(int*)realloc(Sx,sizeofSx*sizeof(int));
     Serial.print("Array Sx");
     Serial.print("|||");
     Serial.print("Size= ");
     Serial.print(sizeofSx);
    for(int i=0;i<sizeofSx-1;i++)
    {
       Serial.print(" '");
       Serial.print(Sx[i]);
       Serial.print("' ");
      snprintf(msgSx, 75, "%d",Sx[i]);
    }
    if(sizeofSx==4)
    {
      Sx[0]=Sx[1];
      Sx[1]=Sx[2];
      sizeofSx=3;
    }
    Sx=(int*)realloc(Sx,sizeofSx*sizeof(int));
     Serial.println("");
    //--------------------Sy----------------------------
    if(sizeofSy<3)
    {
      Sy[sizeofSy-1]=0;
      //Serial.println("Sy<3"+(String)Sy[1]);
      //printV(Sy);
    }
    if(sizeofSy==3)
    
    {
      Sy[sizeofSy-1]=integrate(Vy[sizeofVy-2],Vy[sizeofVy-3],Vy[1]);
      //Serial.println("Sy"+(String)Sy[1]);
      //printV(Sy);
    }
    sizeofSy++;
    Sy=(int*)realloc(Sy,sizeofSy*sizeof(int));
     Serial.print("Array Sy");
     Serial.print("|||");
     Serial.print("Size= ");
     Serial.print(sizeofSy);
    for(int i=0;i<sizeofSy-1;i++)
    {
       Serial.print(" '");
       Serial.print(Sy[i]);
       Serial.print("' ");
      snprintf(msgSy, 75, "%d",Sy[i]);
    }
    if(sizeofSy==4)
    {
      Sy[0]=Sy[1];
      Sy[1]=Sy[2];
      sizeofSy=3;
    }
    Sy=(int*)realloc(Sy,sizeofSy*sizeof(int));
    Serial.println("");
    //--------------------------------------------------
    //Serial.println("----------");
    int headingangles=headingangle(Sy[sizeofSy-1],Sx[sizeofSx-1]);
     Serial.println("Heading Angle = ");
     Serial.print(headingangles);
     Serial.println("");
    snprintf(msgheading, 75, "%d",headingangles);
    //-------------------------------------------------
    client.publish(MQTT_PUB_TOPIC_Ax, msgAx);
    client.publish(MQTT_PUB_TOPIC_Ay, msgAy);
    client.publish(MQTT_PUB_TOPIC_Vx, msgVx);
    client.publish(MQTT_PUB_TOPIC_Vy, msgVy);
    client.publish(MQTT_PUB_TOPIC_Sx, msgSx);
    client.publish(MQTT_PUB_TOPIC_Sy, msgSy);
    client.publish(MQTT_PUB_TOPIC_Heading,msgheading);
    counts++;
    count=4;
    delay(500);//**When RUN to actual program use delay=200***
  }
}
