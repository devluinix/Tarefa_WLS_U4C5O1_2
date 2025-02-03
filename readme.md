# Controle de Semaforo usando Timer

## Descrição

Este projeto utiliza a placa BitDogLab com um microcontrolador RP2040 integrado na Raspberry Pi Pico W para controlar uma matriz de LEDs WS2812 e um LED RGB por meio de dois botões. O sistema exibe números na matriz e permite a sua alteração através dos botões. Os componentes utilizados são:

2. **LED RGB** - Com pinos conectados às GPIOs 11 (vermelho), 12 (amarelo) e 13 (verde).

## Funcionalidades

- Ao pressionar o botão pino 5, todas as LEDS acendem, e de 3 em 3 segundos, vao apagando.
- Tudo ligado > Led Azul Apaga, Vermelho Apaga, Verde Apaga

## Demonstração (VÍDEO)

[Vídeo Demonstração](https://youtube.com/shorts/DUGcFvfNFmk)

## Como compilar e executar

1. Configure o ambiente de desenvolvimento para o Raspberry Pi Pico W.
2. Compile o código utilizando um compilador C compatível para gerar os arquivos `.uf2` e `.elf`.
3. Execute o simulador Wokwi clicando no arquivo `diagram.json` e pressione "Play" para testar as funcionalidades.

## Requisitos

- Compilador C (gcc ou equivalente).
- Sistema operacional compatível com programas C.
- Extensão Raspberry Pi Pico.
- Wokwi configurado no VS Code.

## Desenvolvedores

Equipe 2 - Grupo 3 - EmbarcaTech

- [Luiz Marcelo](https://github.com/devluinix/Tarefa_WLS_U4C5O1_2)
