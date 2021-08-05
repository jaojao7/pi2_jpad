# Implementação
*  ### [Para acessar a página referente aos testes realizados clique aqui](https://github.com/jaojao7/pi2_jpad/blob/main/testes.md)

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
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "DHT.h"
#include <Servo.h> 
#define entradaDigital 52
#define entradaAnalogica 0
#define DHTPIN 53  
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);
Servo servo_motor; 
SoftwareSerial mySoftwareSerial(12, 13);
SoftwareSerial bluetooth(10, 11);
int incomingByte,leitura,i,a=2,c=0; 
bool gas;
DFRobotDFPlayerMini myDFPlayer;
float t,h,f;



void setup() {
Serial.begin(9600);  
bluetooth.begin(9600); 
mySoftwareSerial.begin(9600);
pinMode(entradaDigital, INPUT);
servo_motor.attach(50);  
pinMode(50, OUTPUT); 
dht.begin(); 
 // Ajusta Volume  
  for(i=1;i<=10;i++){
   myDFPlayer.volumeDown();
   }


}

void estado(){
if (bluetooth.available() > 0) {
    incomingByte = bluetooth.read();
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
void funcionamento(){
 h = dht.readHumidity();
 t = dht.readTemperature();
 f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Falha na leitura do sensor DHT!");
   return;}
   else {};
 bluetooth.print("TEMP|");
 bluetooth.print(t);
 bluetooth.print("|UMID|");
 bluetooth.print(h);
 delay(5000);
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



void loop() {
estado();
alarme(); 
verificacao();
abrir();
fechar();
funcionamento();
delay (1000);
}
~~~
