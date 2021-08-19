# Alarme

## Esquemático
![Alarme](./Imagens/Alarme.jpg) 

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

#IMPORTANTE
O modúlo de som Dfplayer mini necessita de um cartão microSD formatado em FAT32 para poder tocar o arquivo de áudio do alarme. 
#### [Para baixar o arquivo mp3 do alarme clique aqui](https://github.com/jaojao7/pi2_jpad/blob/main/somarquivo.md)


## [Para voltar a página referente aos testes realizados clique aqui](https://github.com/jaojao7/pi2_jpad/blob/main/testes.md)
