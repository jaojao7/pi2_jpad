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
#include "Arduino.h" //Biblioteca padrão 
#include "DFRobotDFPlayerMini.h" //Biblioteca do módulo Dfplayer mini
#include "SoftwareSerial.h" //Biblioteca para utilizar comunicação serial
#include "DHT.h" //Biblioteca do sensor DHT11
#include <VarSpeedServo.h> //Biblioteca do servo motor
#define DADOS_SERVO 5 
#define DHTPIN 53
#define PINPIR 50
#define DHTTYPE DHT11
#define SALA 22
#define SEG_SALA 26
#define BANHEIRO 24
#define COZINHA 25
#define GARAGEM 23
#define ENTRADA 35
#define QUARTO 36
#define SUITE 37
#define SALA_2 38
#define BANHEIRO_2 39
#define ENTRADA_DIGITAL 52
#define ENTRADA_ANALOGICA A0
VarSpeedServo servo_motor; 
DHT dht(DHTPIN, DHTTYPE);
int incomingByte, leitura, i;
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
  //A utilização do for comentado abaixo é controlar o volume do alarme, descomente o bloco para utilizar. O volume varia de 0 a 30 níveis, substitua o valor '10' pela quantidade que deseja diminuir do volume total
  /*for (i = 1; i <= 10; i++) {
    myDFPlayer.volumeDown();
    }*/
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
        break;
      case 'F':
        servo_motor.slowmove(95, 40);
        break;
      case 'G':
        servo_motor.slowmove(170, 40);
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
  if (millis() >= tempoAnterior1 + 500) {
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


void temperatura () { //Função responsável por enviar ao aplicativo os valores armazenados referentes a temperatura e umidade
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
