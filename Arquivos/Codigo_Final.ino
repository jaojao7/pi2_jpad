/**********************************************************************************************************
  Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina-Campus Florianópolis
  Unidade Curricular: Projeto Integrador II
  Aluno: João Pedro de Araújo Duarte
  Semestre 2021.1
 *               Arduino Mega 2560
 *               -----------------
 *           /|\|              A0 |- <-- Dados do MQ-2 Analógico
 *            | |              10 |- <--Rx  - Bluetooth
 *            --| RST          11 |- -->Tx  - Bluetooth
 *              |              12 |- <--Rx  - Dfplayer mini    
 *  LED1  <---  | D22          13 |- -->Tx  - Dfplayer mini
 *  LED2  <---  | D23          05 |- --> Dados Servo motor
 *  LED3  <---  | D24             |        
 *  LED4  <---  | D25         D50 |- <-- Dados do sensor PIR
 *  LED5  <---  | D26         D53 |- --> Dados DHT11
 *  LED6  <---  | D27         D52 |- --> Dados do MQ-2 Digital
 *  LED7  <---  | D28         D29 |- --> LED10
 *  LED8  <---  | D30         D31 |- --> LED11
 *  LED9  <---  | D32             |
**********************************************************************************************************/
#include "Arduino.h" //Biblioteca padrão 
#include "DFRobotDFPlayerMini.h" //Biblioteca do módulo Dfplayer mini
#include "SoftwareSerial.h" //Biblioteca para utilizar comunicação serial
#include "DHT.h" //Biblioteca do sensor DHT11
#include <VarSpeedServo.h> //Biblioteca do servo motor
#define DADOS_SERVO 5
#define DHTPIN 53
#define PINPIR 50
#define DHTTYPE DHT11
#define SALA 28
#define SEG_SALA 25
#define BANHEIRO 26
#define COZINHA 27
#define VARANDA 23
#define GARAGEM 22
#define ENTRADA 24
#define QUARTO 32
#define SUITE 31
#define SALA_2 29
#define BANHEIRO_2 30
#define ENTRADA_DIGITAL 52
#define ENTRADA_ANALOGICA A0
VarSpeedServo servo_motor;
DHT dht(DHTPIN, DHTTYPE);
int  leitura, i, incomingByte = 0;
float t, h, f;
bool gas;

SoftwareSerial bluetooth(10, 11); //Declaração dos pinos que serão utilizados para a comunicação com o módulo Bluetooth
SoftwareSerial mySoftwareSerial(12, 13); //Declaração dos pinos que serão utilizados para a comunicação com o módulo Dfplayer
DFRobotDFPlayerMini myDFPlayer;
void setup() {
  pinMode(ENTRADA_DIGITAL, INPUT);
  pinMode(PINPIR, INPUT);
  pinMode(SALA, OUTPUT);
  pinMode(SEG_SALA, OUTPUT);
  pinMode(BANHEIRO, OUTPUT);
  pinMode(COZINHA, OUTPUT);
  pinMode(GARAGEM, OUTPUT);
  pinMode(ENTRADA, OUTPUT);
  pinMode(VARANDA, OUTPUT);
  pinMode(QUARTO, OUTPUT);
  pinMode(SUITE, OUTPUT);
  pinMode(SALA_2, OUTPUT);
  pinMode(BANHEIRO_2, OUTPUT);
  pinMode(DADOS_SERVO, OUTPUT);
  mySoftwareSerial.begin(9600); //Inicializa a comunicação serial com o módulo Dfplayer
  Serial.begin(9600);
  bluetooth.begin(9600); //Inicializa a comunicação serial com o módulo Bluetooth
  dht.begin(); //Inicializa o sensor DHT11
  servo_motor.attach(DADOS_SERVO); //Declara qual pino será utilizado para controle do servo motor
  myDFPlayer.setTimeOut(500);
  som(); //Função para checar a inicialização do módulo Dfplayer
  //A utilização do for comentado abaixo é controlar o volume do alarme, descomente o bloco para utilizar
 /* for (i = 1; i <= 10; i++) {
    myDFPlayer.volumeDown();
  }*/
servo_motor.slowmove(160, 100);//Utilizado para garantir a garagem fechada inicialmente
}
void tarefas() { //Função responsável por realizar todo o controle das funções que dependem do comando do aplicativo via Bluetooth
  bluetooth.listen(); //Importante sua utilização para dizer o arduino que deseja-se comunicar com o módulo Bluetooth
  if (bluetooth.available() > 0) {

    incomingByte = bluetooth.read();
    switch (incomingByte) {
      case 'A':
        digitalWrite(SALA, !digitalRead(SALA));
        digitalWrite(SEG_SALA, !digitalRead(SEG_SALA));

        break;
      case 'B':
        digitalWrite(BANHEIRO, !digitalRead(BANHEIRO));

        break;
      case 'C':
        digitalWrite(COZINHA, !digitalRead(COZINHA));

        break;
      case 'D':
        digitalWrite(GARAGEM, !digitalRead(GARAGEM));
        digitalWrite(VARANDA, !digitalRead(VARANDA));

        break;
      case 'F':
        servo_motor.slowmove(70, 80);

        break;
      case 'G':
        servo_motor.slowmove(160, 80);

        break;
      case 'H':
        digitalWrite(QUARTO, !digitalRead(QUARTO));

        break;
      case 'I':
        digitalWrite(SUITE, !digitalRead(SUITE));

        break;
      case 'J':
        digitalWrite(SALA_2, !digitalRead(SALA_2));

        break;
      case 'K':
        digitalWrite(BANHEIRO_2, !digitalRead(BANHEIRO_2));

        break;
      default:
        incomingByte = 0;
    }
  }
}
long tempoAnterior1 = 0, tempoAnterior2 = 0, tempoAnterior3 = 0;



void som() {
  mySoftwareSerial.begin(9600);
  while (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("Aguardando som");

  }
  delay (1000);
}

void verificacao() { //Função responsável pela verificação da leitura do sensor de gás e fumaça
  if (millis() >= tempoAnterior1 + 1000) {
    tempoAnterior1 = millis();
    gas = digitalRead(ENTRADA_DIGITAL);
    leitura = analogRead(ENTRADA_ANALOGICA);
  }
}
void alarme() { //Fução responsável por acionar o alerta sonoro

  if (gas == 0) {
    myDFPlayer.start();
  }
  else {
    myDFPlayer.stop();
  }
}

void presenca() { //Função responsável por realizar o controle da luz da entrada com o sensor de presença
  bool valorPIR = digitalRead(PINPIR);

  if (valorPIR == HIGH) {
    digitalWrite(ENTRADA, HIGH);
  }
  else if (valorPIR == LOW) {
    digitalWrite(ENTRADA, LOW);
  }
}

void funcionamento() { //Função responsável por armazenar os valores de temperatura e leitura do sensor DHT11
  if (millis() >= tempoAnterior2 + 2000) {
    tempoAnterior2 = millis();
    h = dht.readHumidity();
    t = dht.readTemperature();
    f = dht.readTemperature(true);
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Falha na leitura do sensor DHT!");
    }
  }
}


void temperatura () { //Função responsável por enviar ao aplicativo os valores armazenados referentes a temperatura e umidade
  if (millis() >= tempoAnterior3 + 3000) {
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
