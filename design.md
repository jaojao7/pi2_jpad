## Design do Projeto
Para a continuidade do projeto da inserção de tecnologias com a finalidade de realizar o processo de automatização residencial, entraremos agora na etapa do design, 
onde a estrutura e configuração de materiais necessários e como os mesmos poderão futuramente ser implementados começa a surgir.
Abaixo segue uma tabela com os componentes utilizados e suas respectivas descrições,  na sequência o esquemático da montagem:

Imagem |Componente   | Quantidade | Descrição/Utilização
:-------:|:---------: | :--------------:| :------ 
<img src="./Imagens/led.png" width="100"> |Led Branco 5mm | 10| Iluminação do projeto
<img src="./Imagens/330.png" width="100">|Resistor 330Ω | 11| Utilizado na parte do alarme e na iluminação do projeto
<img src="./Imagens/10k.png" width="100">|Resistor 10kΩ | 1 | Utilizado com o sensor DHT11
<img src="./Imagens/mega.png" width="100">|Placa Arduino Mega 2560 R3 |1|Utilizada para o desenvolvimento e funcionamento do projeto
 <img src="./Imagens/mq2.png" width="100">|MQ-2|1|Sensor de Gás inflamável e de fumaça
<img src="./Imagens/dht11.png" width="100">|DHT11|1|Sensor de umidade e temperatura 
<img src="./Imagens/pir.png" width="100">|PIR|1|Sensor de presença
<img src="./Imagens/bluetooth.png" width="100">|Módulo HC-05|1|Módulo Bluetooth
<img src="./Imagens/conversor.png" width="100">|Conversor de Nível Lógico RC|1|Conversor de Nível Lógico RC Bidirecional
<img src="./Imagens/df.png" width="100">|Modulo DFPlayer|1|Utilizado na parte do alarme
<img src="./Imagens/mb102.png" width="100">|Módulo MB102|1| Fonte de tensão ajustável
<img src="./Imagens/auto.png" width="100">|Auto falante 0.5W 8Ω|1|Utilizado na parte do alarme
<img src="./Imagens/servo.png" width="100">|Servomotor|1|Utilizado no mecanismo de entrada da garagem

###### Figura 1 - Esquemático do Projeto  

<img src="./Imagens/projetofinal.jpg" width="1000">

### Algumas Observações:

* Para utilização do módulo Bluetooth é necessário o conversor de nível lógico nas entradas RX e TX pois o mesmo trabalha com a tensão de 3.3V e as entradas do Arduino fornecem 5V.
* O amplificador PAM8403 é utilizado para melhoria do som, porém o sistema funcionaria sem o mesmo. Bastando conectar o autofalante diretamente nas entradas correspondentes no wtv020 SD.
* Atenção a tensão de alimentação do módulo wtv020 SD como sendo 3.3V.
* No sensor DHT11 é necessário um resistor de 10kΩ conectado as entradas VCC e de dados do componente.

### Aplicativo
Abaixo algumas imagens do aplicativo que será posteriormente utilizado para realizar o controle da casa:
###### Figura 2 - Tela de Login Incial  
<img src="./Imagens/iniciofinal.png" width="300">

###### Figura 3 - Tela Principal  
<img src="./Imagens/telaprincipalfinal.png" width="300">

###### Figura 4 - Tela de controle casa 
<img src="./Imagens/telacontrolefinal.png" width="300">

###### Figura 5 - Tela Tempo 
<img src="./Imagens/telatemperatura.png" width="300">

Formam realizados alguns testes inicias referentes aos sensores e as lógicas de funcionamento antes de iniciar a implementação do sistema final
*  #### [Para acessar a página referente aos testes clique aqui](https://github.com/jaojao7/pi2_jpad/blob/main/testes.md)

[Para voltar a página inicial clique aqui.](https://github.com/jaojao7/pi2_jpad)
