# Testes

Para a etapa de testes, o conjunto de funcionalidades foi dividido nos seguintes blocos:
* Iluminação
* Alarme
* Garagem
* Tempo

Esta página trata da simulação e testes realizados individualmente para cada bloco.

### Garagem (Servomotor)

Para o funcionamento do sistema de garagem o seguinte esquemático foi seguido para verificação do correto funcionamento do componente e se seu desempenho atende ao objetivo esperado.

#### Figura 1 Esquemático
<img src="./Arquivos/esquematico.jpg" width="1000">

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
#include <Servo.h> // Inclui a biblioteca para servos motores
int incomingByte;
SoftwareSerial bluetooth(10, 11);
Servo servo_motor;  // Cria um objeto para o controle do servo
void setup() {

 servo_motor.attach(50);  // Informa qual pino será usado para o servo declarado anteriormente
 pinMode(50, OUTPUT); // configura o pino como saída
 bluetooth.begin(9600);
  
  }
void estado(){
if (bluetooth.available() > 0) {
    incomingByte = bluetooth.read();
}
}
  
void fechar(){
  
  if (incomingByte == 'G'){// se botão estiver pressionado (HIGH)
    servo_motor.write(200);  // Fecha o portão
  }
}
void abrir (){
 if (incomingByte == 'F'){// se botão estiver pressionado (HIGH)
    servo_motor.write(88); //Abre o portão
   }
}
void loop(){
  estado();
  fechar();
  abrir();

}
~~~
