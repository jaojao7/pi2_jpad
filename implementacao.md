# Implementação

# Maquete
Para a fabricação da maquete, foi utilizado uma maquete modelo sobrado já cortada em MDF, devidamente montada e pintada para posteriormente receber toda a parte eletroeletrônica do projeto, a seguir as medidas da maquete e fotos ilustrativas da montagem:
#### Figura 1 Medidas Maquete 1
<img src="./Imagens/Medidas maquete.png" width="600">

#### Figura 2 Medidas Maquete 2
<img src="./Imagens/Medidas maquete1.png" width="600">

#### Figura 3 Montagem 1
<img src="./Imagens/montagem.jpg" width="500">

#### Figura 4 Montagem 2
<img src="./Imagens/montagem1.jpg" width="500">

#### Figura 5 Montagem 3
<img src="./Imagens/montagem2.jpg" width="500">

#### Figura 6 Montagem Concluída 
<img src="./Imagens/Maquete.png" width="500">

#### Figura 7 Pintura
<img src="./Imagens/pintada1.jpg" width="500">

#### Figura 8 Pintura Finalizada
<img src="./Imagens/pintada2.jpg" width="500">

### Cógigo Principal

~~~C++

/**********************************************************************************************************
  Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina-Campus Florianópolis
  Unidade Curricular: Projeto Integrador II
  Aluno: João Pedro de Araújo Duarte
  Semestre 2021.1
  _____    _____    ___           _____    ____   __  __   ____   _______  _____   _____
  |  __ \  |_   _|  |__ \         |  __ \  / __ \ |  \/  | / __ \ |__   __||_   _| / ____|    /\
  | |__) |   | |       ) | ______ | |  | || |  | || \  / || |  | |   | |     | |  | |        /  \
  |  ___/    | |      / / |______|| |  | || |  | || |\/| || |  | |   | |     | |  | |       / /\ \
  | |       _| |_    / /_         | |__| || |__| || |  | || |__| |   | |    _| |_ | |____  / ____ \
  |_|      |_____|  |____|        |_____/  \____/ |_|  |_| \____/    |_|   |_____| \_____|/_/    \_\
**********************************************************************************************************/
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"
#include "DHT.h"
#include <VarSpeedServo.h>
#define dados_servo 5
#define DHTPIN 53
#define pinPIR 50
#define DHTTYPE DHT11
#define sala 30
#define segsala 31
#define banheiro 32
#define cozinha 33
#define garagem 34
#define entrada 35
#define quarto 36
#define suite 37
#define sala2 38
#define banheiro2 39
#define entradaDigital 52
#define entradaAnalogica A0
VarSpeedServo servo_motor;
DHT dht(DHTPIN, DHTTYPE);
int incomingByte, leitura, i;
float t, h, f;
bool gas;

SoftwareSerial bluetooth(10, 11);
SoftwareSerial mySoftwareSerial(12, 13);
DFRobotDFPlayerMini myDFPlayer;
void setup() {
  pinMode(entradaDigital, INPUT);
  pinMode(pinPIR, INPUT);
  pinMode(sala, OUTPUT);
  pinMode(segsala, OUTPUT);
  pinMode(banheiro, OUTPUT);
  pinMode(cozinha, OUTPUT);
  pinMode(garagem, OUTPUT);
  pinMode(entrada, OUTPUT);
  pinMode(quarto, OUTPUT);
  pinMode(suite, OUTPUT);
  pinMode(sala2, OUTPUT);
  pinMode(banheiro2, OUTPUT);
  pinMode(dados_servo, OUTPUT);
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  bluetooth.begin(9600);
  dht.begin();
  servo_motor.attach(dados_servo);
  myDFPlayer.setTimeOut(500);
  som();
  for (i = 1; i <= 10; i++) {
    myDFPlayer.volumeDown();
  }
}
void tarefas() {
  bluetooth.listen();
  if (bluetooth.available() > 0) {
    incomingByte = bluetooth.read();
    switch (incomingByte) {
      case 'A':
        digitalWrite(sala, !digitalRead(sala));
        digitalWrite(segsala, !digitalRead(segsala));
        break;
      case 'B':
        digitalWrite(banheiro, !digitalRead(banheiro));
        break;
      case 'C':
        digitalWrite(cozinha, !digitalRead(cozinha));
        break;
      case 'D':
        digitalWrite(garagem, !digitalRead(garagem));
        break;
      case 'F':
        servo_motor.slowmove(88, 40);
        break;
      case 'G':
        servo_motor.slowmove(200, 40);
        break;
      case 'H':
        digitalWrite(quarto, !digitalRead(quarto));
        break;
      case 'I':
        digitalWrite(suite, !digitalRead(suite));
        break;
      case 'J':
        digitalWrite(sala2, !digitalRead(sala2));
        break;
      case 'K':
        digitalWrite(banheiro2, !digitalRead(banheiro2));
        break;
    }
  }
}

void som() {
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    while (true);
  }
}

long tempoAnterior1 = 0, tempoAnterior2 = 0, tempoAnterior3 = 0;

void verificacao() {
  if (millis() >= tempoAnterior1 + 500) {
    tempoAnterior1 = millis();
    gas = digitalRead(entradaDigital);
    leitura = analogRead(entradaAnalogica);
  }
}
void alarme() {

  if (gas == 0) {
    myDFPlayer.start();
  }
  else {
    myDFPlayer.stop();
  }
}

void presenca() {
  bool valorPIR = digitalRead(pinPIR);

  if (valorPIR == HIGH) {
    digitalWrite(entrada, HIGH);
  }
  else if (valorPIR == LOW) {
    digitalWrite(entrada, LOW);
  }
}

void funcionamento() {
  if (millis() >= tempoAnterior2 + 1000) {
    tempoAnterior2 = millis();
    h = dht.readHumidity();
    t = dht.readTemperature();
    f = dht.readTemperature(true);
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Falha na leitura do sensor DHT!");
    }
  }
}


void temperatura () {
  if (millis() >= tempoAnterior3 + 2000) {
    tempoAnterior3 = millis();
    bluetooth.print("TEMP|");
    bluetooth.print(t);
    bluetooth.print("|UMID|");
    bluetooth.print(h);
  }
}
void loop() {
  tarefas();
  funcionamento();
  temperatura();
  presenca();
  alarme();
  verificacao();

}

~~~
*  ### [PARA BAIXAR O APK DO APLICATIVO CLIQUE AQUI](https://github.com/jaojao7/pi2_jpad/raw/main/Arquivos/JPAD_automacao.apk)
