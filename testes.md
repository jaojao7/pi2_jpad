# Testes

Para a etapa de testes, o conjunto de funcionalidades foi dividido nos seguintes blocos:
* Iluminação
* Alarme 
* Garagem
* Tempo

Esta página trata dos testes realizados individualmente para cada bloco.

### Garagem (Servomotor)

Para o funcionamento do sistema de garagem o seguinte esquemático foi seguido para verificação do correto funcionamento do componente e se seu desempenho atende ao objetivo esperado.


##### Código da Garagem

~~~C++
/**************************************************************************************************************
Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina-Campus Florianópolis
Unidade Curricular: Projeto Integrador II
Aluno: João Pedro de Araújo Duarte
Semestre 2021.1

Objetivo: Verificar o funcionamento do sistema de abertura e fechamento da garagem utilizando o servomotor
***************************************************************************************************************/   
#include "SoftwareSerial.h"
#include <Servo.h> 
int incomingByte;
SoftwareSerial bluetooth(10, 11);
Servo servo_motor; 
void setup() {

 servo_motor.attach(50);  
 pinMode(50, OUTPUT); 
 bluetooth.begin(9600);
  
  }
void estado(){
if (bluetooth.available() > 0) {
    incomingByte = bluetooth.read();
}
}
  
void fechar(){
  
  if (incomingByte == 'G'){
    servo_motor.write(200); 
  }
}
void abrir (){
 if (incomingByte == 'F'){
    servo_motor.write(88); 
   }
}
void loop(){
  estado();
  fechar();
  abrir();

}
~~~
##### Código Temperatura
~~~C++
/*
Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina-Campus Florianópolis
Unidade Curricular: Projeto Integrador II
Aluno: João Pedro de Araújo Duarte
Semestre 2021.1

Objetivo: Verificar a temperatura e umidade no aplicativo do celular via Bluetooth
*/ 
#include "SoftwareSerial.h"
#include "DHT.h"
#define DHTPIN 53  
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial bluetooth(10, 11);
float t,h,f;
void setup() {
  Serial.begin(9600); 
  dht.begin(); 
  bluetooth.begin(9600);
  delay(1000);

}
void funcionamento(){
 h = dht.readHumidity();
 t = dht.readTemperature();
 f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Falha na leitura do sensor DHT!");
   delay (1000);
   return;

  }
 }
void mostra (){
 bluetooth.print("TEMP|");
 bluetooth.print(t);
 bluetooth.print("|UMID|");
 bluetooth.print(h);
 delay(1000);
  }
void loop() {
funcionamento();
mostra();
 
}
~~~

### Código Alarme

~~~C++
/****************************************************************************************
Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina-Campus Florianópolis
Unidade Curricular: Projeto Integrador II
Aluno: João Pedro de Araújo Duarte
Semestre 2021.1

Objetivo: Verificar o sensor de gás e acionar o som, caso o sensor de gás ative
****************************************************************************************/ 

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#define entradaDigital 52
#define entradaAnalogica 0

SoftwareSerial mySoftwareSerial(12, 13); // RX, TX
SoftwareSerial bluetooth(10, 11);
DFRobotDFPlayerMini myDFPlayer;
bool gas;
int leitura,incomingByte,i,a=2,c=0;
void setup()
{
  pinMode(entradaDigital, INPUT);

  Serial.begin(9600);
  bluetooth.begin(9600);
   mySoftwareSerial.begin(9600);
   //Verifica se o modulo esta respondendo e se o cartao SD foi encontrado
   som();
  //Definicoes iniciais
  myDFPlayer.setTimeOut(500); //Timeout serial 500ms
  myDFPlayer.EQ(5); 
   // Ajusta Volume  
  for(i=1;i<=10;i++){
   myDFPlayer.volumeDown();
   }
}
void som(){
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini"));
  Serial.println(F("Inicializando modulo DFPlayer... (3~5 segundos)"));
  if (!myDFPlayer.begin(mySoftwareSerial))
  {
    Serial.println(F("Nao inicializado:"));
    Serial.println(F("1.Cheque as conexoes do DFPlayer Mini"));
    Serial.println(F("2.Insira um cartao SD"));
    while (true);
  }
  Serial.println();
  Serial.println(F("Modulo DFPlayer Mini inicializado!"));

  }



void tarefas(){
if (bluetooth.available() > 0) {
    incomingByte = bluetooth.read();
  if (incomingByte =='S'){
        myDFPlayer.stop(); 
      }
}
}
void verificacao(){
gas = digitalRead(entradaDigital);
leitura = analogRead(entradaAnalogica);

}
void alarme(){
  if(gas==0){
  myDFPlayer.start(); 
      }
   else {
        myDFPlayer.stop(); 
        }
  }

void loop()
{
tarefas();
verificacao();
alarme();   
delay (1000);
}
~~~
