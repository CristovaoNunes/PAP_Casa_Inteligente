
//UPDATE
//Já consegui fazer a subscrição de vários tópicos falta só resolver a questão dos botões

//Código para o Arduino Due da Casa Inteligente

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <OneButton.h> //http://www.mathertel.de/Arduino/OneButtonLibrary.aspx

//Inicialização dos botões
OneButton BtnCozinha01(A6, true);
OneButton BtnCozinha02(A7, true);
OneButton BtnWC01(A1, true);
OneButton BtnQuarto01(A0, true);
OneButton BtnSala01(A8, true);
OneButton BtnSala02(A9, true);
OneButton BtnEntrada01(A2, true);
OneButton BtnGaragem01(A3, true);
OneButton BtnGaragem02(A5, true);
OneButton BtnGaragem03(A4, true);

//Marcacão dos pinos dos Relés no Arduino
int ReleLuzEntrada01 = 46;
int ReleLuzSala01 = 48;
int ReleLuzSala02 = 47;
int ReleLuzCozinha01 = 53;
int ReleLuzCozinha02 = 52;
int ReleLuzWC01 = 51;
int ReleVentWC01 = 50;
int ReleLuzQuarto01 = 49;
int ReleLuzGaragem01 = 45;
int ReleLuzGaragem02 = 44;
int ReleLuzGaragem03 = 43;
int ReleLuzExterior01 = 42;

//Inicialização das variáveis valor dos pinos
int ReleLuzEntrada01Value = LOW;
int ReleLuzSala01Value = LOW;
int ReleLuzSala02Value = LOW;
int ReleLuzCozinha01Value = LOW;
int ReleLuzCozinha02Value = LOW;
int ReleLuzWC01Value = LOW;
int ReleVentWC01Value = LOW;
int ReleLuzQuarto01Value = LOW;
int ReleLuzGaragem01Value = LOW;
int ReleLuzGaragem02Value = LOW;
int ReleLuzGaragem03Value = LOW;
int ReleLuzExterior01Value = LOW;



//Constantes para a Shield Ethernet
//Endereço MAC
byte mac[]    = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };
//IP estático
IPAddress ip(192, 168, 2, 20);

//Inicialização do MQTT
//IP do Broker MQTT
byte BrokerMQTT[] = {192, 168, 2, 106};
//Inicialização do "Serviço" EthernetClient
EthernetClient ethClient;
//Callback do Broker
void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
  String content = "";
  char character;
  for (int num = 0; num < length; num++) {
    character = payload[num];
    content.concat(character);
  }
  String topico = topic;
  String conteudo = content;

  Serial.println(topico);
  Serial.println(conteudo);


  //Verifica o tópico /Casa/ReleLuzCozinha01/set
  if (topico == "/Casa/ReleLuzCozinha01/set") {
    if (conteudo == "ON") {
      LigarReleLuzCozinha01();
    }
    if (conteudo == "OFF") {
      DesligarReleLuzCozinha01();
    }
  }

  //Verifica o tópico /Casa/ReleLuzCozinha02/set
  if (topico == "/Casa/ReleLuzCozinha02/set") {
    if (conteudo == "ON") {
      LigarReleLuzCozinha02();
    }
    if (conteudo == "OFF") {
      DesligarReleLuzCozinha02();
    }
  }

  //Verifica o tópico /Casa/ReleLuzWC01/set
  if (topico == "/Casa/ReleLuzWC01/set") {
    if (conteudo == "ON") {
      LigarReleLuzWC01();
    }
    if (conteudo == "OFF") {
      DesligarReleLuzWC01();
    }
  }

  //Verifica o tópico /Casa/ReleVentWC01/set
  if (topico == "/Casa/ReleVentWC01/set") {
    if (conteudo == "ON") {
      LigarReleVentWC01();
    }
    if (conteudo == "OFF") {
      DesligarReleVentWC01();
    }
  }

  //Verifica o tópico /Casa/ReleQuarto01/set
  if (topico == "/Casa/ReleLuzQuarto01/set") {
    if (conteudo == "ON") {
      LigarReleLuzQuarto01();
    }
    if (conteudo == "OFF") {
      DesligarReleLuzQuarto01();
    }
  }

  //Verifica o tópico /Casa/ReleLuzSala01/set
  if (topico == "/Casa/ReleLuzSala01/set") {
    if (conteudo == "ON") {
      LigarReleLuzSala01();
    }
    if (conteudo == "OFF") {
      DesligarReleLuzSala01();
    }
  }

  //Verifica o tópico /Casa/ReleLuzSala02/set
  if (topico == "/Casa/ReleLuzSala02/set") {
    if (conteudo == "ON") {
      LigarReleLuzSala02();
    }
    if (conteudo == "OFF") {
      DesligarReleLuzSala02();
    }
  }

  //Verifica o tópico /Casa/ReleLuzEntrada01/set
  if (topico == "/Casa/ReleLuzEntrada01/set") {
    if (conteudo == "ON") {
      LigarReleLuzEntrada01();
    }
    if (conteudo == "OFF") {
      DesligarReleLuzEntrada01();
    }
  }

  //Verifica o tópico /Casa/ReleLuzGaragem01/set
  if (topico == "/Casa/ReleLuzGaragem01/set") {
    if (conteudo == "ON") {
      LigarReleLuzGaragem01();
    }
    if (conteudo == "OFF") {
      DesligarReleLuzGaragem01();
    }
  }

  //Verifica o tópico /Casa/ReleLuzExterior01/set
  if (topico == "/Casa/ReleLuzExterior01/set") {
    if (conteudo == "ON") {
      LigarReleLuzExterior01();
    }
    if (conteudo == "OFF") {
      DesligarReleLuzExterior01();
    }
  }


}
//Inicialização do "Serviço" PubSubClient
PubSubClient client(BrokerMQTT, 1883, callback, ethClient);


void setup() {
  //Iniciar os pinos dos relés como OUTPUTs
  pinMode(ReleLuzEntrada01, OUTPUT);
  pinMode(ReleLuzSala01, OUTPUT);
  pinMode(ReleLuzSala02, OUTPUT);
  pinMode(ReleLuzCozinha01, OUTPUT);
  pinMode(ReleLuzCozinha02, OUTPUT);
  pinMode(ReleLuzWC01, OUTPUT);
  pinMode(ReleVentWC01, OUTPUT);
  pinMode(ReleLuzQuarto01, OUTPUT);
  pinMode(ReleLuzGaragem01, OUTPUT);
  pinMode(ReleLuzExterior01, OUTPUT);

  //Iniciar os relés em HIGH ou seja DESLIGADOS
  digitalWrite(ReleLuzEntrada01, HIGH);
  digitalWrite(ReleLuzSala01, HIGH);
  digitalWrite(ReleLuzSala02, HIGH);
  digitalWrite(ReleLuzCozinha01, HIGH);
  digitalWrite(ReleLuzCozinha02, HIGH);
  digitalWrite(ReleLuzWC01, HIGH);
  digitalWrite(ReleVentWC01, HIGH);
  digitalWrite(ReleLuzQuarto01, HIGH);
  digitalWrite(ReleLuzGaragem01, HIGH);
  digitalWrite(ReleLuzExterior01, HIGH);

  //Iniciar Botões
  BtnCozinha01.attachClick(BtnCozinha01C);
  BtnCozinha02.attachClick(BtnCozinha02C);
  BtnWC01.attachClick(BtnWC01unico);
  BtnWC01.attachDoubleClick(BtnWC01duplo);
  BtnWC01.attachLongPressStart(BtnWC01LP);
  BtnQuarto01.attachClick(BtnQuarto01C);
  BtnQuarto01.attachLongPressStart(BtnQuarto01LP);
  BtnSala01.attachClick(BtnSala01C);
  BtnSala01.attachLongPressStart(BtnSala01LP);
  BtnSala02.attachClick(BtnSala02C);
  BtnSala02.attachLongPressStart(BtnSala02LP);
  BtnEntrada01.attachClick(BtnEntrada01C);
  BtnGaragem01.attachClick(BtnGaragem01C);
  BtnGaragem02.attachClick(BtnGaragem02C);
  BtnGaragem03.attachClick(BtnGaragem03C);


  // Setup serial connection
  Serial.begin(9600);
  // Setup ethernet connection to MQTT broker
  Ethernet.begin(mac);
}

//----------------------------------------------

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  BtnCozinha01.tick();
  BtnCozinha02.tick();
  BtnWC01.tick();
  BtnQuarto01.tick();
  BtnSala01.tick();
  BtnSala02.tick();
  BtnEntrada01.tick();
  BtnGaragem01.tick();
  BtnGaragem02.tick();
  BtnGaragem03.tick();
  client.loop();
}


//Start of functions   --------------------------------------------------------------------------------------------------------

//Conexão ao Broker MQTT
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Arduino-Due")) {
      //Se conseguir ligar
      Serial.println("connected");
      client.publish("/status", "Arduino ON");
      client.publish("/Casa/ReleLuzCozinha01/status", "OFF");
      client.publish("/Casa/ReleLuzCozinha02/status", "OFF");
      client.publish("/Casa/ReleLuzWC01/status", "OFF");
      client.publish("/Casa/ReleVentWC01/status", "OFF");
      client.publish("/Casa/ReleLuzQuarto01/status", "OFF");
      client.publish("/Casa/ReleLuzSala01/status", "OFF");
      client.publish("/Casa/ReleLuzSala02/status", "OFF");
      client.publish("/Casa/ReleLuzEntrada01/status", "OFF");
      client.publish("/Casa/ReleLuzGaragem01/status", "OFF");
      client.publish("/Casa/ReleLuzExterior01/status", "OFF");

      client.subscribe("/Casa/ReleLuzCozinha01/set");
      client.subscribe("/Casa/ReleLuzCozinha02/set");
      client.subscribe("/Casa/ReleLuzWC01/set");
      client.subscribe("/Casa/ReleVentWC01/set");
      client.subscribe("/Casa/ReleLuzQuarto01/set");
      client.subscribe("/Casa/ReleLuzSala01/set");
      client.subscribe("/Casa/ReleLuzSala02/set");
      client.subscribe("/Casa/ReleLuzEntrada01/set");
      client.subscribe("/Casa/ReleLuzGaragem01/set");
      client.subscribe("/Casa/ReleLuzExterior01/set");
    } else {
      //Se falhar a ligar
      Serial.println("failed, rc=");
      Serial.println(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


//--------------------------------------------------------  ONEBUTTON - CLIQUES --------------------------------------------------------
//------------------------------------------  COZINHA
void BtnCozinha01C() {
  Serial.println("Clique BtnCozinha01");
  if (ReleLuzCozinha01Value == LOW) {
    LigarReleLuzCozinha01();
  } else {
    DesligarReleLuzCozinha01();
  }
}

void BtnCozinha02C() {
  Serial.println("Clique BtnCozinha02");
  if (ReleLuzCozinha02Value == LOW) {
    LigarReleLuzCozinha02();
  } else {
    DesligarReleLuzCozinha02();
  }
}


//------------------------------------------  CASA DE BANHO
void BtnWC01unico() {
  Serial.println("Clique BtnWC01");
  if (ReleLuzWC01Value == HIGH && ReleVentWC01Value == HIGH) {
    DesligarReleLuzWC01();
    DesligarReleVentWC01();
  } else {
    if (ReleLuzWC01Value == LOW) {
      LigarReleLuzWC01();
    } else {
      DesligarReleLuzWC01();
    }
  }
}

void BtnWC01duplo() {
  Serial.println("Duplo Clique BtnWC01");
  if (ReleLuzWC01Value == LOW && ReleVentWC01Value == LOW) {
    LigarReleLuzWC01();
    LigarReleVentWC01();
  } else {
    if (ReleLuzWC01Value == HIGH && ReleVentWC01Value == HIGH) {
      DesligarReleLuzWC01();
      DesligarReleVentWC01();
    } else {
      if (ReleLuzWC01Value == HIGH && ReleVentWC01Value == LOW) {
        LigarReleVentWC01();
      }
    }
  }
}



void BtnWC01LP() {
  Serial.println("Pressionamento Longo BtnWC01-----------");
  if (ReleLuzWC01Value == HIGH && ReleVentWC01Value == HIGH) {
    DesligarReleLuzWC01();
    client.publish("/Casa/ReleLuzWC01/delay", "ON");
    }
}


//------------------------------------------  QUARTO
void BtnQuarto01C() {
  Serial.println("Clique BtnQuarto01");
  if (ReleLuzQuarto01Value == LOW) {
    LigarReleLuzQuarto01();
  } else {
    DesligarReleLuzQuarto01();
  }
}

void BtnQuarto01LP() {
  Serial.println("Pressionamento Longo BtnQuarto01");
  if (ReleLuzQuarto01Value == LOW) {
    LigarReleLuzQuarto01();
  } else {
    DesligarReleLuzQuarto01();
  }
}


//------------------------------------------  SALA
//LUZ 01
void BtnSala01C() {
  Serial.println("Clique BtnSala01");
  if (ReleLuzSala01Value == LOW) {
    LigarReleLuzSala01();
  } else {
    DesligarReleLuzSala01();
  }
}

void BtnSala01LP() {
  Serial.println("Pressionamento Longo BtnSala01");
  if (ReleLuzSala01Value == LOW) {
    LigarReleLuzSala01();
  } else {
    DesligarReleLuzSala01();
  }
}
//LUZ 02
void BtnSala02C() {
  Serial.println("Clique BtnSala02");
  if (ReleLuzSala02Value == LOW) {
    LigarReleLuzSala02();
  } else {
    DesligarReleLuzSala02();
  }
}

void BtnSala02LP() {
  Serial.println("Pressionamento Longo BtnSala01");
  if (ReleLuzSala02Value == LOW) {
    LigarReleLuzSala02();
  } else {
    DesligarReleLuzSala02();
  }
}


//------------------------------------------  ENTRADA
void BtnEntrada01C() {
  Serial.println("Clique BtnEntrada01");
  if (ReleLuzEntrada01Value == LOW) {
    LigarReleLuzEntrada01();
  } else {
    DesligarReleLuzEntrada01();
  }
}


//------------------------------------------  GARAGEM
void BtnGaragem01C() {
  Serial.println("Clique BtnGaragem01");
  if (ReleLuzGaragem01Value == LOW) {
    LigarReleLuzGaragem01();
  } else {
    DesligarReleLuzGaragem01();
  }
}

void BtnGaragem02C() {
  Serial.println("Clique BtnGaragem02");
  if (ReleLuzGaragem02Value == LOW) {
    LigarReleLuzGaragem02();
  } else {
    DesligarReleLuzGaragem02();
  }
}

void BtnGaragem03C() {
  Serial.println("Clique BtnGaragem03");
  if (ReleLuzGaragem03Value == LOW) {
    LigarReleLuzGaragem03();
  } else {
    DesligarReleLuzGaragem03();
  }
}



//--------------------------------------------------------  CONTROLO RELÉS  --------------------------------------------------------

//Controlo Relé Luz da cozinha 01 ------------------------------------------------
void LigarReleLuzCozinha01() {
  digitalWrite(ReleLuzCozinha01, LOW);
  ReleLuzCozinha01Value = HIGH;
  client.publish("/Casa/ReleLuzCozinha01/status", "ON");
  Serial.println("Luz Cozinha 01 LIGADA");
}
void DesligarReleLuzCozinha01() {
  digitalWrite(ReleLuzCozinha01, HIGH);
  ReleLuzCozinha01Value = LOW;
  client.publish("/Casa/ReleLuzCozinha01/status", "OFF");
  Serial.println("Luz Cozinha 01 DESLIGADA");
}

//Controlo Relé Luz da cozinha 02 ------------------------------------------------
void LigarReleLuzCozinha02() {
  digitalWrite(ReleLuzCozinha02, LOW);
  ReleLuzCozinha02Value = HIGH;
  client.publish("/Casa/ReleLuzCozinha02/status", "ON");
  Serial.println("Luz Cozinha 02 LIGADA");
}
void DesligarReleLuzCozinha02() {
  digitalWrite(ReleLuzCozinha02, HIGH);
  ReleLuzCozinha02Value = LOW;
  client.publish("/Casa/ReleLuzCozinha02/status", "OFF");
  Serial.println("Luz Cozinha 02 DESLIGADA");
}

//Controlo Relé Luz WC 01 ------------------------------------------------
void LigarReleLuzWC01() {
  digitalWrite(ReleLuzWC01, LOW);
  ReleLuzWC01Value = HIGH;
  client.publish("/Casa/ReleLuzWC01/status", "ON");
  Serial.println("Luz WC 01 LIGADA");
}
void DesligarReleLuzWC01() {
  digitalWrite(ReleLuzWC01, HIGH);
  ReleLuzWC01Value = LOW;
  client.publish("/Casa/ReleLuzWC01/status", "OFF");
  Serial.println("Luz WC 01 DESLIGADA");
}

//Controlo Relé Ventoinha WC 01 ------------------------------------------------
void LigarReleVentWC01() {
  digitalWrite(ReleVentWC01, LOW);
  ReleVentWC01Value = HIGH;
  client.publish("/Casa/ReleVentWC01/status", "ON");
  Serial.println("Ventoinha WC 01 LIGADA");
}
void DesligarReleVentWC01() {
  digitalWrite(ReleVentWC01, HIGH);
  ReleVentWC01Value = LOW;
  client.publish("/Casa/ReleVentWC01/status", "OFF");
  Serial.println("Ventoinha WC 01 DESLIGADA");
}

//Controlo Relé Luz Quarto 01 ------------------------------------------------
void LigarReleLuzQuarto01() {
  digitalWrite(ReleLuzQuarto01, LOW);
  ReleLuzQuarto01Value = HIGH;
  client.publish("/Casa/ReleLuzQuarto01/status", "ON");
  Serial.println("Luz Quarto 01 LIGADA");

}
void DesligarReleLuzQuarto01() {
  digitalWrite(ReleLuzQuarto01, HIGH);
  ReleLuzQuarto01Value = LOW;
  client.publish("/Casa/ReleLuzQuarto01/status", "OFF");
  Serial.println("Luz Quarto 01 DESLIGADA");
}

//Controlo Relé Luz da Sala 01 ------------------------------------------------
void LigarReleLuzSala01() {
  digitalWrite(ReleLuzSala01, LOW);
  ReleLuzSala01Value = HIGH;
  client.publish("/Casa/ReleLuzSala01/status", "ON");
  Serial.println("Luz Sala 01 LIGADA");
}
void DesligarReleLuzSala01() {
  digitalWrite(ReleLuzSala01, HIGH);
  ReleLuzSala01Value = LOW;
  client.publish("/Casa/ReleLuzSala01/status", "OFF");
  Serial.println("Luz Sala 01 DESLIGADA");
}

//Controlo Relé Luz da Sala 02 ------------------------------------------------
void LigarReleLuzSala02() {
  digitalWrite(ReleLuzSala02, LOW);
  ReleLuzSala02Value = HIGH;
  client.publish("/Casa/ReleLuzSala02/status", "ON");
  Serial.println("Luz Sala 02 LIGADA");
}
void DesligarReleLuzSala02() {
  digitalWrite(ReleLuzSala02, HIGH);
  ReleLuzSala02Value = LOW;
  client.publish("/Casa/ReleLuzSala02/status", "OFF");
  Serial.println("Luz Sala 02 DESLIGADA");
}

//Controlo Relé Luz de Entrada 01 ------------------------------------------------
void LigarReleLuzEntrada01() {
  digitalWrite(ReleLuzEntrada01, LOW);
  ReleLuzEntrada01Value = HIGH;
  client.publish("/Casa/ReleLuzEntrada01/status", "ON");
  Serial.println("Luz Entrada 01 LIGADA");
}
void DesligarReleLuzEntrada01() {
  digitalWrite(ReleLuzEntrada01, HIGH);
  ReleLuzEntrada01Value = LOW;
  client.publish("/Casa/ReleLuzEntrada01/status", "OFF");
  Serial.println("Luz Entrada 01 DESLIGADA");
}

//Controlo Relé Garagem 01 ------------------------------------------------
void LigarReleLuzGaragem01() {
  digitalWrite(ReleLuzGaragem01, LOW);
  ReleLuzGaragem01Value = HIGH;
  client.publish("/Casa/ReleLuzGaragem01/status", "ON");
  Serial.println("Luz Garagem 01 LIGADA");
}
void DesligarReleLuzGaragem01() {
  digitalWrite(ReleLuzGaragem01, HIGH);
  ReleLuzGaragem01Value = LOW;
  client.publish("/Casa/ReleLuzGaragem01/status", "OFF");
  Serial.println("Luz Garagem 01 DESLIGADA");
}

//Controlo Relé Garagem 02 ------------------------------------------------
void LigarReleLuzGaragem02() {
  digitalWrite(ReleLuzGaragem02, LOW);
  ReleLuzGaragem02Value = HIGH;
  client.publish("/Casa/ReleLuzGaragem02/status", "ON");
  Serial.println("Luz Garagem 02 LIGADA");
}
void DesligarReleLuzGaragem02() {
  digitalWrite(ReleLuzGaragem02, HIGH);
  ReleLuzGaragem02Value = LOW;
  client.publish("/Casa/ReleLuzGaragem02/status", "OFF");
  Serial.println("Luz Garagem 02 DESLIGADA");
}

//Controlo Relé Garagem 03 ------------------------------------------------
void LigarReleLuzGaragem03() {
  digitalWrite(ReleLuzGaragem03, LOW);
  ReleLuzGaragem03Value = HIGH;
  client.publish("/Casa/ReleLuzGaragem03/status", "ON");
  Serial.println("Luz Garagem 03 LIGADA");
}
void DesligarReleLuzGaragem03() {
  digitalWrite(ReleLuzGaragem03, HIGH);
  ReleLuzGaragem03Value = LOW;
  client.publish("/Casa/ReleLuzGaragem03/status", "OFF");
  Serial.println("Luz Garagem 03 DESLIGADA");
}

//Controlo Relé Exterior 01 ------------------------------------------------
void LigarReleLuzExterior01() {
  digitalWrite(ReleLuzExterior01, LOW);
  ReleLuzExterior01Value = HIGH;
  client.publish("/Casa/ReleLuzExterior01/status", "ON");
  Serial.println("Luz Exterior 01 LIGADA");
}
void DesligarReleLuzExterior01() {
  digitalWrite(ReleLuzExterior01, HIGH);
  ReleLuzExterior01Value = LOW;
  client.publish("/Casa/ReleLuzExterior01/status", "OFF");
  Serial.println("Luz Exterior 01 DESLIGADA");
}

// End of sketch ---------------------------------
