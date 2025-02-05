# 🚀 Temporizador One Shot com Raspberry Pi Pico W

Este projeto implementa um **sistema de temporização** para acionamento de **LEDs** a partir do clique em um **botão (pushbutton)**. O código utiliza a função **`add_alarm_in_ms()`** do **Pico SDK** para criar um temporizador **One Shot**, que controla o estado dos LEDs em intervalos de 3 segundos.

## 📌 Funcionamento
1. Ao pressionar o botão, os **três LEDs** (vermelho, verde e azul) acendem.
2. Após **3 segundos**, um dos LEDs é desligado.
3. Depois de **mais 3 segundos**, outro LED desliga.
4. Por fim, após **mais 3 segundos**, o último LED desliga.
5. O botão só pode ser pressionado novamente **após o último LED ser desligado**.

## 🛠 Componentes Utilizados
- Raspberry Pi Pico W
- 3 LEDs (Azul, Vermelho e Verde)
- 3 Resistores de 330Ω
- 1 Botão (Pushbutton)

## 🖥️ Instalação e Configuração

### 1️⃣ Configurar o Pico SDK
Antes de compilar, o **Pico SDK** deve estar instalado. Se ainda não configurou, siga os passos:

```sh
export PICO_SDK_PATH=/<caminho_para_o_pico-sdk>
2️⃣ Clonar o Repositório

git clone https://github.com/seu-usuario/seu-repositorio.git
cd seu-repositorio

3️⃣ Compilar o Código

    Criar a pasta de build:

mkdir build && cd build

Executar o CMake:

cmake ..

Rodar o Make:

    make

Após a compilação, um arquivo .uf2 será gerado.
4️⃣ Executar no Hardware

    Conecte o Raspberry Pi Pico W ao PC segurando o BOOTSEL.
    Arraste o arquivo temporizadorOneShot.uf2 para a unidade do Pico.
    O código será executado automaticamente. 🎯

5️⃣ Executar no Wokwi

Se quiser testar no simulador Wokwi, siga estes passos:

    Instale o Wokwi CLI (se ainda não tiver):

npm install -g wokwi-server

Rode o simulador com:

    wokwi-server diagram.json

📜 Código-Fonte
Arquivo: temporizadorOneShot.c

O código principal está no arquivo temporizadorOneShot.c e segue o seguinte fluxo:

    Interrupção no botão → Ativa os LEDs
    Uso do temporizador One Shot → Controla a sequência de desligamento
    Debounce no botão → Evita múltiplos cliques acidentais

Arquivo: diagram.json

Define a simulação no Wokwi, com os componentes corretamente conectados.