//Código para o Arduino Due da Casa Inteligente

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

//Constantes para a Shield Ethernet
//Endereço MAC
byte mac[]    = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };
//IP estático
IPAddress ip(192,168,0,238);

//Inicialização do MQTT
//IP do Broker MQTT
byte BrokerMQTT[] = { 192, 168, 0, 20 };
//Inicialização do "Serviço" EthernetClient
EthernetClient ethClient;
//Callback do Broker
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
  // Set specific virtual switches on basis of specific incoming messages 

  //Verifica se o conteudo do Tópico é: ReleLuzEntrada01
  if (content == "ReleLuzEntrada01ON") {
    LigarReleLuzEntrada01();
  }
  
  if (content == "ReleLuzEntrada01OFF") {
    DesligarReleLuzEntrada01();
  }
  
  //Verifica se o conteudo do Tópico é: ReleLuzSala01
  if (content == "ReleLuzSala01ON") {
    LigarReleLuzSala01();
  }
  
  if (content == "ReleLuzSala01OFF") {
    DesligarReleLuzSala01();
  }  
}
//Inicialização do "Serviço" PubSubClient
PubSubClient client(BrokerMQTT, 1883, callback, ethClient);


void setup(){
  //Iniciar os relés em HIGH ou seja DESLIGADOS
  digitalWrite(ReleLuzEntrada01, HIGH);
  digitalWrite(ReleLuzSala01, HIGH);
  digitalWrite(ReleLuzSala02, HIGH);
  digitalWrite(ReleLuzCozinha01, HIGH);
  digitalWrite(ReleLuzCozinha02, HIGH);
  digitalWrite(ReleLuzCorredor01, HIGH);
  digitalWrite(ReleLuzWC01, HIGH);
  digitalWrite(ReleLuzWC02, HIGH);
  digitalWrite(ReleVentWC01, HIGH);
  digitalWrite(ReleLuzQuarto01, HIGH);
  digitalWrite(ReleLuzQuarto02, HIGH);
  digitalWrite(ReleLuzSuite01, HIGH);
  digitalWrite(ReleLuzWCSuite01, HIGH);
  digitalWrite(ReleLuzWCSuite02, HIGH);
  digitalWrite(ReleVentWCSuite01, HIGH);
  digitalWrite(ReleLuzExterior01, HIGH);

  // Setup serial connection
  Serial.begin(9600);
  // Setup ethernet connection to MQTT broker
  Ethernet.begin(mac);
}

//----------------------------------------------

void loop(){
  if (!client.connected()) {
  reconnect();
  }
  client.loop();
}


//Start of functions   --------------------------------------------------------------------------------------------------------

//Conexão ao Broker MQTT
void reconnect(){
 // Loop until we're reconnected
 while (!client.connected()) {
 Serial.print("Attempting MQTT connection...");
 // Attempt to connect
 if (client.connect("Arduino-Due")) {
  //Se conseguir ligar
  Serial.println("connected");
  client.subscribe("/casa/entrada/luz01");
  client.subscribe("/casa/sala/luz01");
  client.subscribe("/casa/sala/luz02");  
 } else {
  //Se falhar a ligar
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" try again in 5 seconds");
  // Wait 5 seconds before retrying
  delay(5000);
  }
 }
}


//--------------------------------------------------------  CONTROLO RELÉS  --------------------------------------------------------
//Controlo Relé Luz de Entrada 01
void LigarReleLuzEntrada01(){
  digitalWrite(ReleLuzEntrada01, LOW);
  client.publish("/Casa/ReleLuzEntrada01","ON");
  }
void DesligarReleLuzEntrada01(){
  digitalWrite(ReleLuzEntrada01, HIGH);
  client.publish("/Casa/ReleLuzEntrada01","OFF");
  }

//Controlo Relé Luz da Sala 01
void LigarReleLuzSala01(){
  digitalWrite(ReleLuzSala01, LOW);
  client.publish("/Casa/ReleLuzSala01","ON");
  }
void DesligarReleLuzSala01(){
  digitalWrite(ReleLuzSala01, HIGH);
  client.publish("/Casa/ReleLuzSala01","OFF");
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
