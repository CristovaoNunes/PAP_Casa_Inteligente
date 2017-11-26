//Eu deixei os comentários do código original de prepósito

/*
 Example MQTT-switch-relay-node with 4 buttons and 4 leds 
 
  - connects to an MQTT server
  - publishes "hello world" to the topic "led"
  - subscribes to the topic "led"
  - controls 4 leds on pins 2,3,5 and 6 - leds can be replaced with relays
  - reads 4 button on pins 7,8,9 and 10
  - turns on/off a specific led when it receives a specific "on"/"off" from the "led" topic
  - sends a specific "on"/"off" to the "led" topic a specific button is pressed
  - multiple arduino's with same generic sketch can run parallel to each other
  - multiple arduino's need each to have a unique ip-addres, unique mac address and unique MQTT client-ID

  - tested on arduino-uno with W5100 ethernet shield
  - Ethernet Shield W5100 uses pins 4,10,11,12,13
  - availbale digital pins: 1,2,3,5,6,7,8,9,10 
*/

//------------------------------------------------------------------------------

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Set led variables to Arduino digital pins
int ReleLuzEntrada01 = 2;
int ReleLuzSala01 = 3;
int ReleLuzSala02 = 22;
int ReleLuzCozinha01 = 5;
int ReleLuzCozinha02 = 6;
int ReleLuzCorredor01 = 7;
int ReleLuzWC01 = 8;
int ReleLuzWC02 = 9;
int ReleVentWC01 = 14;
int ReleLuzQuarto01 = 15;
int ReleLuzQuarto02 = 16;
int ReleLuzSuite01 = 17;
int ReleLuzWCSuite01 = 18;
int ReleLuzWCSuite02 = 19;
int ReleVentWCSuite01 = 20;
int ReleLuzExterior01 = 21;

//---------------------------------------------------------------------------

// Arduino MAC address is on a sticker on your Ethernet shield
// must be unique for every node in same ne02rk
// To make a new unique address change last letter

byte mac[]    = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };  

// Unique static IP address of this Arduino - change to adapt to your ne02rk
IPAddress ip(192,168,0,238);

// IP Address of your MQTT broker - change to adapt to your ne02rk
byte server[] = { 192, 168, 0, 20 };

// Handle and convert incoming MQTT messages ----------------------------------------

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
  String content="";
  char character;
  for (int num=0;num<length;num++) {
      character = payload[num];
      content.concat(character);
  }   
  Serial.println(topic);
  Serial.println(content); // message sent out by button actions is returned from broker and serial printed

//
//
//----------  Pensei em usar um só tópico de controlo e vários de estado
//
//
// Set specific virtual switches on basis of specific incoming messages ----------------------------
  
  if (content == "ReleLuzEntrada01ON") {
    LigarReleLuzEntrada01();
  }
  
  if (content == "ReleLuzEntrada01OFF") {
    DesligarReleLuzEntrada01();
  }
}

// Initiate instances -----------------------------------

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

//-------------------------------------------------------

void setup()

{
  // setup serial and ethernet communications -------------------------------

  // Setup serial connection
  Serial.begin(9600);

  // Setup ethernet connection to MQTT broker
  Ethernet.begin(mac);
  if (client.connect("Arduino-Due")) {                // change as desired - clientname must be unique for MQTT broker
    client.publish("led","hello world - here arduino ip 239");
    Serial.println("connected");
    client.subscribe("led");                    // subscribe to topic "led"
  }
}

//----------------------------------------------

void loop()
{
  client.loop();
}

//Start of functions
//Controlo Relé Luz de Entrada 01
void LigarReleLuzEntrada01(){
  digitalWrite(ReleLuzEntrada01, LOW);
  }
void DesligarReleLuzEntrada01(){
  digitalWrite(ReleLuzEntrada01, HIGH);
  }


//Controlo Relé Luz da Sala 01
void LigarReleLuzSala01(){
  digitalWrite(ReleLuzSala01, LOW);
  }
void DesligarReleLuzSala01(){
  digitalWrite(ReleLuzSala01, HIGH);
  }

//Controlo Relé Luz da sala 02
void LigarReleLuzSala02(){
  digitalWrite(ReleLuzSala02, LOW);
  }
void DesligarReleLuzSala02(){
  digitalWrite(ReleLuzSala02, HIGH);
  }

//Controlo Relé Luz da cozinha 01
void LigarReleLuzCozinha01(){
  digitalWrite(ReleLuzCozinha01, LOW);
  }
void DesligarReleLuzCozinha01(){
  digitalWrite(ReleLuzCozinha01, HIGH);
  }

//Controlo Relé Luz da cozinha 02
void LigarReleLuzCozinha02(){
  digitalWrite(ReleLuzCozinha02, LOW);
  }
void DesligarReleLuzCozinha02(){
  digitalWrite(ReleLuzCozinha02, HIGH);
  }

//Controlo Relé Luz do Corredor 01
void LigarReleLuzCorredor01(){
  digitalWrite(ReleLuzCorredor01, LOW);
  }
void DesligarReleLuzCorredor01(){
  digitalWrite(ReleLuzCorredor01, HIGH);
  }

//Controlo Relé Luz WC 01
void LigarReleLuzWC01(){
  digitalWrite(ReleLuzWC01, LOW);
  }
void DesligarReleLuzWC01(){
  digitalWrite(ReleLuzWC01, HIGH);
  }

//Controlo Relé Luz WC 02
void LigarReleLuzWC02(){
  digitalWrite(ReleLuzWC02, LOW);
  }
void DesligarReleLuzWC02(){
  digitalWrite(ReleLuzWC02, HIGH);
  }

//Controlo Relé Luz Quarto 01
void LigarReleLuzQuarto01(){
  digitalWrite(ReleLuzQuarto01, LOW);
  }
void DesligarReleLuzQuarto01(){
  digitalWrite(ReleLuzQuarto01, HIGH);
  }

//Controlo Relé Luz Quarto 02
void LigarReleLuzQuarto02(){
  digitalWrite(ReleLuzQuarto02, LOW);
  }
void DesligarReleLuzQuarto02(){
  digitalWrite(ReleLuzQuarto02, HIGH);
  }

//Controlo Relé Luz Suite 01
void LigarReleLuzSuite01(){
  digitalWrite(ReleLuzSuite01, LOW);
  }
void DesligarReleLuzSuite01(){
  digitalWrite(ReleLuzSuite01, HIGH);
  }

//Controlo Relé Luz WC Suite 01
void LigarReleLuzWCSuite01(){
  digitalWrite(ReleLuzWCSuite01, LOW);
  }
void DesligarReleLuzWCSuite01(){
  digitalWrite(ReleLuzWCSuite01, HIGH);
  }

//Controlo Relé Luz WC Suite 02
void LigarReleLuzWCSuite02(){
  digitalWrite(ReleLuzWCSuite02, LOW);
  }
void DesligarReleLuzWCSuite02(){
  digitalWrite(ReleLuzWCSuite02, HIGH);
  }

//Controlo Relé Ventoinha WC Suite 01
void LigarReleVentWCSuite01(){
  digitalWrite(ReleVentWCSuite01, LOW);
  }
void DesligarReleVentWCSuite01(){
  digitalWrite(ReleVentWCSuite01, HIGH);
  }

//Controlo Relé Exterior 01
void LigarReleLuzExterior01(){
  digitalWrite(ReleLuzExterior01, LOW);
  }
void DesligarReleLuzExterior01(){
  digitalWrite(ReleLuzExterior01, HIGH);
  }


// End of sketch ---------------------------------
