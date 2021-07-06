# Boiler controller (cyclic executive implementation)

### Usage:

For development: `make && ./build/runner`
For deployment: `(java -jar boiler_emulator/boiler_emulator.jar 8000 &) && make && (./build/runner localhost 8000)`


### Description:

[Description](http://www.romulosilvadeoliveira.eng.br/livrotemporeal/Trabalhos/controle-caldeira-2.pdf)

[VÍDEO: Descrição do Trabalho 1 (1 de 3): Descrição da caldeira e sua instrumentação](https://www.youtube.com/watch?v=ZPSq4zozfTE)

[VÍDEO: Descrição do Trabalho 1 (2 de 3): Simulador da caldeira](https://www.youtube.com/watch?v=cgnx3cxVuDU)

[VÍDEO: Descrição do Trabalho 1 (3 de 3): Comunicação com o Simulador da Caldeira](https://www.youtube.com/watch?v=RQhIx62PV_0)


### Requirements:

Simulador é usado para simular uma unidade de caldeira e é chamado com:
java -jar aquecedor2008_1.jar <número-porta-escutada>

A caldeira possui instrumentação embutida e aceita os seguintes comandos:
"sta0" lê valor de Ta
"st-0" lê valor de T
"sti0" lê valor de Ti
"sno0" lê valor de No
"sh-0" lê valor de H
"ani123.4" define valor de Ni como 123.4
"aq-567.8" define valor de Q como 567.8
"ana123.4" define valor de Na como 123.4
"anf123.4" define valor de Nf como 123.4

Cuidado com a formatação dos valores em ponto flutuante.

Implementar em C no Linux o programa CONTROLADOR, o qual deve incluir as seguintes funcionalidades de controle:

- Laço de controle como tarefa periódica para a temperatura;
- Uso do tanque auxiliar e da saída de água;
- Informações na tela sobre a situação corrente.

Outros requisitos:
- Não usar threads;
- Período do controlador de temperatura deve ser 30ms exato, ver exemplo;
- Atualização da tela pode ser aproximadamente a cada 1 segundo.


### Report:

Partindo do programa controlador desenvolvido, meça o tempo de resposta do controle de temperatura.

O tempo de resposta inicia no momento t de acordar. Após concluir o controlador, antes de calcular o novo t de acordar, obtenha a hora atual t1. Com "t1 - t" temos o tempo de resposta do controlador em questão. Cuidado com a divisão de segundos e nanosegundos. Para maior precisão, NÃO converta para float ou double, mas mantenha em long+long (segundos e nanosegundos) até fazer a subtração.

Armazene esta informação em um array e depois de algum tempo grave em arquivo.

Apresente um histograma destas medições. Identifique o pior caso, isto é, o maior tempo de resposta observado (high water mark).

Até que período seria possível levar o controlador nestas condições de execução ?

Usar as funções clock_nanosleep e clock_gettime.

Adicionalmente:

- Número de amostras >= 10000.

- Usar como unidade microsegundo nos gráficos.

- Fazer a coleta dos dados em máquina real e não em máquina virtual.

- Gerar relatório em PDF com texto descrevendo as observações e os gráficos.

