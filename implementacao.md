# IMPLEMENTAÇÃO

## MAQUETE
Para a fabricação da maquete, foi utilizado uma maquete modelo sobrado já cortada em MDF, devidamente montada e pintada para posteriormente receber toda a parte eletroeletrônica do projeto, a seguir as medidas da maquete e fotos ilustrativas da montagem:
#### Figura 1 Medidas Maquete 1
<img src="./Imagens/Medidas maquete.png" width="300">

#### Figura 2 Medidas Maquete 2
<img src="./Imagens/Medidas maquete1.png" width="300">

#### Figura 3 Montagem 1
<img src="./Imagens/montagem.jpg" width="300">

#### Figura 4 Montagem 2
<img src="./Imagens/montagem1.jpg" width="300">

#### Figura 5 Montagem 3
<img src="./Imagens/montagem2.jpg" width="300">

#### Figura 6 Montagem Concluída 
<img src="./Imagens/Maquete.png" width="300">

#### Figura 7 Pintura
<img src="./Imagens/pintada1.jpg" width="300">

#### Figura 8 Pintura Finalizada
<img src="./Imagens/pintada2.jpg" width="300">

## IMPLEMENTAÇÃO DOS CIRCUITOS A MAQUETE
Primeiro os LED's foram soldados aos resistores e colados nos devidos locais destinados, na laje da maquete:
#### Figura 9 Colocação dos LED's 
<img src="./Imagens/soldalampada.jpg" width="300">

#### Figura 10 Colagem dos LED's
<img src="./Imagens/furolampada.jpg" width="300">

Após isso foi realizada a conexão dos LED's nos fios:

#### Figura 11 Conexão LED's
<img src="./Imagens/conexaolampadas.jpg" width="300">

#### Figura 12 Passagem dos fios para o andar de cima 
<img src="./Imagens/conexaolampadas2.jpg" width="300">

Em seguida, foram instalados o servomotor e o sensor de gases :

#### Figura 13 Servo motor 
<img src="./Imagens/IMG_20210826_110613.jpg" width="300">

#### Figura 14 Sensor de gases e fumaça
<img src="./Imagens/gas1.jpg" width="300">

E por fim foi feita todas as conexões dos sensores e LED's:

#### Figura 15 Conexões Gerais
<img src="./Imagens/fios2.jpg" width="300">

E realizado testes da montagem para verificação dos resultados
#### Figura 16 Teste geral - Iluminação
<img src="./Imagens/casaluz.jpg" width="300">

#### Figura 17 Teste geral - Garagem e entrada
<img src="./Imagens/casa.jpg" width="300">

## CÓDIGO PRINCIPAL
### [PARA ACESSAR O CÓDIGO CLIQUE AQUI](https://github.com/jaojao7/pi2_jpad/blob/main/Arquivos/Projeto_Final.ino)

## FUNCIONAMENTO DO CÓDIGO

Abaixo foi montado um fluxograma para melhor compreensão e explicação do fluxo principal de funcionamento:

<img src="./Imagens/FLUXOGRAMA DE FUNCIONAMENTO DO CÓDIGO.pdf_page_1.jpg" width="1000">

Podemos dividir o fluxograma de funcionamento acima em duas partes principais, a formada pelos tarefas dentro dos retângulos na primeira linha, onde representa a função setup que é a primeira a ser executada pelo Arduino, e outra região repesentada pelas tarefas dentro das elipses que corresponde a execução da função loop do Arduino.

### Função Setup
A função setup conforme visto na representação executa uma série de comandos para inicializr a comunicação com os módulos e sensores, além disso já realiza a tarefa de verificação do módulo de som e a execução da dimuição do volume.

### Função Loop
A função loop chama diversas outras funções que são as responsáveis para a execução do conjunto de tarefas do sistema. Para melhor explicação essa parte da execução do código foi divida em quatro etapas que são executadas de forma conjunta:
* 

## APLICATIVO PARA CONTROLE 
#### [PARA BAIXAR O APK DO APLICATIVO CLIQUE AQUI](https://github.com/jaojao7/pi2_jpad/raw/main/Arquivos/JPAD_automacao.apk)
(Após baixado, basta clicar no arquivo e instalar o mesmo normalmente em seu dispositivo Android)

[PARA VOLTAR AO INÍCIO CLIQUE AQUI](https://github.com/jaojao7/pi2_jpad)
