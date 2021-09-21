# Boiler controller (FreeRTOS implementation)

### Usage:

For development: `make && ./build/runner`

For deployment: `(java -jar boiler_emulator/boiler_emulator.jar 8000 &) && make && (./build/runner)`


### Description:
[Description](http://www.romulosilvadeoliveira.eng.br/livrotemporeal/Trabalhos/controle-caldeira-2.pdf)

[Repositório tutorial - cŕedito @alankc](https://github.com/alankc/FreeRTOS_Posix_Socket)


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

Implementar em C usando FreeRTOS Posix o programa CONTROLADOR, o qual deve incluir as seguintes funcionalidades de controle:
- Laço de controle como tarefa periódica para a temperatura;
- Laço de controle como tarefa periódica para o nível (pode considerar estratégias separadas e não multivariável);
- Uso do tanque auxiliar e da saída de água;
- Informações na tela sobre a situação corrente;
- Verificação da temperatura a cada 10ms para disparo de tarefa de alarme caso esteja acima de 30 graus.
Essa funcionalidade deve ser implementada utilizando notificações do freeRTOS (Documentação: https://www.freertos.org/RTOS-task-notifications.html)
- Valores de referência para nível e temperatura devem ser configurados no próprio código;
- Armazenagem periódica dos dez últimos valores lidos de temperatura. Apresentar a média destes valores na tela e conjunto com os demais dados.
- Medir o tempo em segundos para o sistema sair do estágio inicial e chegar a 5% do valor de referência para temperatura. Começar a apresentar este dado na tela apenas quando a caldeira alcançar 5% do valor de referência pela primeira vez. (Pode utilizar: xTaskGetTickCount())

Outros requisitos:
- Usar mutex para proteger as variáveis compartilhadas;
- Tarefas periódicas devem ser implementadas utilizando a função vTaskDelayUntil;
- Período do controlador de temperatura deve ser 50ms;
- Período do controlador de nível deve ser 70ms;
- Atualização da tela com período de 1 segundo.


### Grade composition:

Alguns aspectos para a composição da nota do trabalho do controlador:
- Fez no Linux, em C, usando o freeRTOS Posix ?
- Foi usado um mutex para cada estrutura compartilhada ?
- A aplicação apresenta valores dos sensores na tela ?
- A aplicação possui laços de controle para temperatura e nível ?
- A aplicação apresenta média dos últimos dez valores de temperatura lidos?
- A aplicação mede o tempo para chegar a 5% do valor de referência e mostra na tela apenas no momento adequado?
- Existe uma tarefa para o alarme ?
- Implementou o alarme utilizando notificação no freeRTOS?