# Boiler controller (POSIX threads implementation)



### Usage:

For development: `make && ./build/runner`

For deployment: `(java -jar boiler_emulator/boiler_emulator.jar 8000 &) && make && (./build/runner)`


### Description:
[Description](http://www.romulosilvadeoliveira.eng.br/livrotemporeal/Trabalhos/controle-caldeira-2.pdf)

[VÍDEO: Descrição do Trabalho 2: Controlador da caldeira com várias threads](https://www.youtube.com/watch?v=cLVTDSLXTCY)

[VÍDEO: 13.5. Mecanismos de Sincronização Variáveis Compartilhadas (parte 5 de 5) - Exemplo Buffer Duplo](https://www.youtube.com/watch?v=y5aa-NQ7TQ4)


### Requirements:

Simulador é usado para simular uma unidade de caldeira e é chamado com:
java -jar aquecedor2008_1.jar <número-porta-escutada>

A caldeira possui instrumentação embutida e aceita os seguintes comandos:
- "sta0" lê valor de Ta
- "st-0" lê valor de T
- "sti0" lê valor de Ti
- "sno0" lê valor de No
- "sh-0" lê valor de H
- "ani123.4" define valor de Ni como 123.4
- "aq-567.8" define valor de Q como 567.8
- "ana123.4" define valor de Na como 123.4
- "anf123.4" define valor de Nf como 123.4

Cuidado com a formatação dos valores em ponto flutuante.

Implementar em C no Linux o programa CONTROLADOR, o qual deve incluir as seguintes funcionalidades de controle:

- Laço de controle como tarefa periódica para a temperatura;
- Laço de controle como tarefa periódica para o nível (pode considerar estratégias separadas e não multivariável);
- Uso do tanque auxiliar e da saída de água;
- Informações na tela sobre a situação corrente;
- Verificação da temperatura a cada 10ms para disparo de tarefa de alarme caso esteja acima de 30 graus.
- Entrada através do teclado dos valores de referência para nível e temperatura;
- Armazenagem periódica dos valores lidos de temperatura e armazenagem desses dados em arquivo, através de buffer duplo (produtor/consumidor).

Outros requisitos:
- Usar mutex para proteger as variáveis compartilhadas;
- Tarefas periódicas implementadas com precisão e não com sleep fixo;
- Período do controlador de temperatura deve ser 50ms;
- Período do controlador de nível deve ser 70ms;
- Atualização da tela pode ser com sleep simples de 1 segundo.

### Grade composition:

Alguns aspectos para a composição da nota do trabalho do controlador:
- Fez no Linux, em C, usando a biblioteca das pthreads ?
- Foi usado um mutex para cada estrutura compartilhada ?
- A aplicação apresenta valores dos sensores na tela ?
- A aplicação possui laços de controle para temperatura e nível ?
- A aplicação acessa teclado durante a execução do controlador, afeta valor de referência ?
- A aplicação grava leituras em arquivo ?
- As tarefas de controle são realmente periódicas ?
- Existe uma tarefa para o alarme ?