# MEDICADOR - Relógio Despertador para Medicação

![Projeto Medicador+ TE:CN](assets\Medicador.jpg)

## Descrição
Este projeto foi desenvolvido como parte da disciplina de Introdução à Engenharia de Computação na Universidade Federal da Paraíba (UFPB). O objetivo do projeto é criar um relógio despertador que auxilia usuários a lembrar de tomar seus medicamentos em horários específicos. O sistema utiliza um RTC (Real Time Clock) DS3231, um display LCD com interface I2C, um teclado matricial e um Arduino para controlar o sistema.

## Autores
- [Camila Alves](https://github.com/CamilaAlves01)
- [Maria Eduarda](https://github.com/EduardaBezerra)
- [Néfi Leite](https://github.com/neficl)
- [Taylor Cantalice](https://github.com/taylorkcantalice)

## Professor
- Anand Subramanian

## Instituição
- Universidade Federal da Paraíba (UFPB)

## Componentes Utilizados
- Arduino Uno
- RTC DS3231
- Display LCD com módulo I2C
- Teclado Matricial 4x4
- LED
- Buzzer
- Jumpers e protoboard

## Bibliotecas Utilizadas
- **DS3231**: Biblioteca para comunicação com o módulo RTC DS3231.
- **Wire**: Biblioteca para comunicação I2C.
- **LCD, LiquidCrystal, LiquidCrystal_I2C**: Bibliotecas para controle do display LCD.
- **Keypad**: Biblioteca para controle do teclado matricial.

## Funcionalidades
- Ajuste de Data e Hora do sistema.
- Configuração de alarmes para até quatro medicamentos diferentes (A, B, C, D).
- Display do relógio, data e temperatura no LCD.
- Alerta sonoro e visual (buzzer e LED) quando chega a hora de tomar um medicamento.
- Menu de configuração e edição de alarmes.

## Como Usar
1. **Montagem do Circuito**:
   - Conecte o módulo RTC DS3231 ao Arduino utilizando os pinos SDA e SCL.
   - Conecte o display LCD com módulo I2C ao Arduino utilizando os pinos SDA e SCL.
   - Conecte o teclado matricial ao Arduino conforme os pinos definidos no código.
   - Conecte o LED e o Buzzer aos pinos definidos no código.

2. **Carregar o Código**:
   - Faça o upload do código presente no arquivo `MEDICADOR.cpp` para o Arduino utilizando a IDE do Arduino.

3. **Configuração Inicial**:
   - Após o upload, o sistema irá iniciar e apresentar uma mensagem de boas-vindas.
   - Utilize o teclado matricial para navegar pelo menu e configurar a data, hora e horários dos alarmes para os medicamentos.

4. **Operação**:
   - O relógio será exibido no display LCD junto com a data e a temperatura ambiente.
   - Quando chegar a hora configurada para um medicamento, o sistema irá emitir um alerta sonoro e visual até que a tecla `#` seja pressionada no teclado matricial.

## Vídeo de Apresentação
Assista ao vídeo de apresentação do projeto no YouTube:

[![Vídeo de Apresentação](https://img.youtube.com/vi/aKH-eVeIoDw/0.jpg)](https://www.youtube.com/watch?v=aKH-eVeIoDw&t=183s)

## Estrutura do Código
- **setup()**: Inicializa os componentes do sistema (RTC, LCD, teclado, LED e Buzzer).
- **loop()**: Função principal que atualiza o display e verifica os alarmes.
- **Funções de Ajuste**: Funções para ajustar data, hora e horários dos alarmes.
- **Funções de Alerta**: Funções que são chamadas quando um alarme é acionado.
- **Menu e Navegação**: Funções para apresentar e navegar pelo menu de configuração e edição.

## Licença
Este projeto é de uso livre para fins acadêmicos e pessoais. Sinta-se à vontade para modificar e adaptar conforme suas necessidades.

---