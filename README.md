# Projeto de Exibição de Dados GPS

Este projeto foi projetado para exibir dados GPS no M5Cardputer. Ele usa a biblioteca TinyGPSPlus para analisar os dados do GPS.

## Dependências

- M5Cardputer
- TinyGPSPlus

## Configuração

A função `setup()` inicializa o M5Cardputer e configura a comunicação serial para o módulo GPS. Também define o tamanho do texto e a rotação para o display LCD.

## Loop Principal

A função `loop()` lê continuamente os dados do módulo GPS e atualiza o display. Se o BtnGo no M5Cardputer for pressionado, o display é limpo.

## Funções

- `displayclear()`: Limpa o display LCD.
- `displayGPSData()`: Exibe a latitude, longitude, velocidade, número de satélites, data e hora dos dados do GPS no LCD.
- `readGPSData()`: Lê os dados do módulo GPS. Se uma sentença completa for recebida, atualiza o display com os novos dados.

## Uso

Carregue o código no seu M5Cardputer, certifique-se de que o módulo GPS está conectado corretamente e você deverá ver os dados do GPS exibidos na tela.
