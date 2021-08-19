# Testes

Para a etapa de testes, o conjunto de funcionalidades foi dividido nos seguintes blocos:
* Garagem
* Tempo
* Alarme 
* Iluminação

Esta página trata dos testes realizados individualmente para cada bloco.

### Garagem (Servomotor)

Para o funcionamento do sistema de garagem o seguinte esquemático foi seguido para verificação do correto funcionamento do componente e se seu desempenho atende ao objetivo esperado.


##### Código da Garagem

~~~C++
/**********************************************************************************************************
  Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina-Campus Florianópolis
  Unidade Curricular: Projeto Integrador II
  Aluno: João Pedro de Araújo Duarte
  Semestre 2021.1

  Objetivo: Verificar o funcionamento do sistema de abertura e fechamento da garagem utilizando o servomotor
  com controle do aplicativo
************************************************************************************************************/
#define dados_servo 5
#include "SoftwareSerial.h"
#include <VarSpeedServo.h> // Inclui a biblioteca para servos motores com controle de velocidade da abertura
int incomingByte; // Variável para armazenar o comando recebido pelo aplicativo
VarSpeedServo servo_motor; // Cria um objeto para o controle do servo
SoftwareSerial bluetooth(10, 11);// Descreve as portas para comunicação serial entre o bluetooth e o arduino ordem RX, TX

void setup() {
  Serial.begin(9600);
  servo_motor.attach(dados_servo);  // Informa qual pino será usado para o servo declarado anteriormente
  pinMode(dados_servo, OUTPUT); // configura o pino como saída
  bluetooth.begin(9600); // Inicializa o módulo bluetooth

}
void estado() {
  if (bluetooth.available() > 0) {
    incomingByte = bluetooth.read();
    if (incomingByte == 'G') {
      servo_motor.slowmove(200, 30); //Quando o botão 'fechar' no aplicativo é pressionado o arduino recebe a variável 'G' e executa a tarefa
    }
    else if (incomingByte == 'F') { //Quando o botão 'abrir' no aplicativo é pressionado o arduino recebe a variável 'F' e executa a tarefa
      servo_motor.slowmove(88, 30);
    }
  }
}

void loop() {
  estado();
}
~~~
##### Código Temperatura
~~~C++
/******************************************************************************************
  Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina-Campus Florianópolis
  Unidade Curricular: Projeto Integrador II
  Aluno: João Pedro de Araújo Duarte
  Semestre 2021.1

  Objetivo: Verificar a temperatura e umidade no aplicativo do celular via Bluetooth
*******************************************************************************************/
#include "SoftwareSerial.h"
#include "DHT.h"
#define DHTPIN 53
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial bluetooth(10, 11);// Descreve as portas para comunicação serial entre o bluetooth e o arduino ordem RX, TX
float t, h, f; //Define as variáveis para armazenar os valores lidos pelo sensor
void setup() {
  Serial.begin(9600); //Inicializa a serial
  dht.begin(); //Inicializa o módulo DHT11
  bluetooth.begin(9600); //Inicializa o módulo bluetooth
}

long tempoAnterior = 0, tempoAnterior1 = 0; //  Variáveis para definir o controle do intervalo de operação de cada função

void funcionamento() {
  if (millis() >= tempoAnterior + 1000) { //Define que a leitura da variáveis acontece a cada 1000 milisegundos
    tempoAnterior = millis(); //Responsável por zerar a diferença entre o tempo millis e condição tempoAnterior+500
    h = dht.readHumidity();
    t = dht.readTemperature();
    f = dht.readTemperature(true);
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Falha na leitura do sensor DHT!");
    }
  }
}
void mostra () { //Função responsável por imprimir a leitura do sensor no monitor serial e também envia-lo ao aplicativo já previamente conectado
  if (millis() >= tempoAnterior1 + 2000) {
    tempoAnterior1 = millis();
    bluetooth.print("TEMP|");
    bluetooth.print(t);
    bluetooth.print("|UMID|");
    bluetooth.print(h);
    Serial.print("|");
    Serial.print("1|");
    Serial.print(t);
    Serial.print("|2|");
    Serial.print(h);
  }
}
void loop() {
  funcionamento();
  mostra();

}
~~~

#### Código Alarme

~~~C++
/****************************************************************************************
  Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina-Campus Florianópolis
  Unidade Curricular: Projeto Integrador II
  Aluno: João Pedro de Araújo Duarte
  Semestre 2021.1

  Objetivo: Verificar o sensor de gás e acionar o som de alerta, caso o sensor de gás ative
****************************************************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h" //Biblioteca do Dfplayer Mini
#define entradaDigital 52
#define entradaAnalogica A0

SoftwareSerial mySoftwareSerial(12, 13); // Descreve as portas para comunicação serial entre o bluetooth e o arduino ordem RX, TX
DFRobotDFPlayerMini myDFPlayer;
bool gas;
int leitura, i;
void setup()
{
  pinMode(entradaDigital, INPUT);
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  som();
  //Definicoes iniciais
  myDFPlayer.setTimeOut(500); //Timeout serial 500ms
  myDFPlayer.EQ(5);
  // Ajusta Volume
  for (i = 1; i <= 10; i++) {
    myDFPlayer.volumeDown();
  }
}
void som() {

  mySoftwareSerial.begin(9600);
  // Vai esperar o software serial iniciar, mas se não iniciar, não tem feedback porque não tem outra serial
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    while (true);
  }
}
long tempoAnterior = 0;
void verificacao() { //Função responsável por verificar os valores do sensor de gás e fumaça
  if (millis() >= tempoAnterior + 1000) {
    tempoAnterior = millis();
    gas = digitalRead(entradaDigital);
    leitura = analogRead(entradaAnalogica);
  }
}
void alarme() { //Aciona o alarme dando play no módulo caso o sensor de gás e fumaça ative
  if (gas == 0) {
    myDFPlayer.start();
  }
  else {
    myDFPlayer.stop();
  }
}

void loop()
{
  verificacao();
  alarme();
}
~~~


#### Código Iluminação
~~~C++
/******************************************************************************************
  Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina-Campus Florianópolis
  Unidade Curricular: Projeto Integrador II
  Aluno: João Pedro de Araújo Duarte
  Semestre 2021.1

  Objetivo: Verificar o sistema de iluminação, acionamento por presença e por comandos diretos no aplicativo
*******************************************************************************************/
#include "SoftwareSerial.h"
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
#define pinPIR 50
int incomingByte;
SoftwareSerial bluetooth(10, 11);

void setup() {
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
  bluetooth.begin(9600);
}
void luzes() { //Função responsável por acionar as luzes caso o arduino receba do aplicativo a variável correspondente
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

void presenca() { //Função responsável por verificar se o sensor de presença foi acionado ou não, caso positivo liga o LED da entrada
  bool valorPIR = digitalRead(pinPIR);

  if (valorPIR == HIGH) {
    digitalWrite(entrada, HIGH);
  }
  else if (valorPIR == LOW) {
    digitalWrite(entrada, LOW);
  }
}

void loop() {
  luzes();
  presenca();
}
~~~
