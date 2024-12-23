/*
 ============================================================================
 Name        : MEDICADOR
 Authors     : Camila Alves, Eduarda Bezerra, Néfi Leite e Taylor Cantalice
 Copyright   : Your copyright notice
 Description : Projeto da Disciplina de Introdução a Engenharia de Computação
               - Relógio Despertador
 Teacher     : Anand Subramanian 
 Institution : Universidade Federal da Paraíba(UFPB)
 ============================================================================
*/

#include <DS3231.h> // Biblioteca do RTC DS3231
#include <Wire.h> // Biblioteca para fazer a comunicação com os módulos I2C (SCL e SDA)
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h> // Biblioteca do LCD com o módulo I2C
#include <Keypad.h> // Biblioteca do Teclado Matricial

#define LED 10
#define BUZZER 11

///////////////////////////////////////////////////
//
//  RTC
//
///////////////////////////////////////////////////
DS3231 rtc; // Definição do RTC DS3231
RTCDateTime dt; // Definição do DateTime

uint32_t timer = 0;
int control = 0;

///////////////////////////////////////////////////
//
//  LCD
//
///////////////////////////////////////////////////
// Inicializa o número dos pinos utilizados pelo LCD
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

///////////////////////////////////////////////////
//
//  TECLADO MATRICIAL
//
///////////////////////////////////////////////////
// Pinos de conexao com as linhas  e as colunas do teclado
byte pinos_linhas[4] = {9, 8, 7, 6};
byte pinos_colunas[4] = {5, 4, 3, 2};
// Matriz de caracteres (mapeamento do teclado)
char teclas_matriz[4][4] = {{'1','2','3', 'A'},
                            {'4','5','6', 'B'},
                            {'7','8','9', 'C'},
                            {'*','0','#', 'D'},};
// Inicializa o Teclado Matricial
Keypad teclado = Keypad(makeKeymap(teclas_matriz), pinos_linhas, pinos_colunas, 4, 4);

///////////////////////////////////////////////////
//
//  VARIÁVEIS
//
///////////////////////////////////////////////////
char tecla_pressionada = 'Z';
String entrada;
byte ano, mes, dia, horas, minutos, segundos;
byte horas_A, minutos_A, segundos_A;
byte horas_B, minutos_B, segundos_B;
byte horas_C, minutos_C, segundos_C;
byte horas_D, minutos_D, segundos_D;
int tempo = 6000;
int op = 0;
bool ajustar = true;

///////////////////////////////////////////////////
//
//  FUNÇÕES
//
///////////////////////////////////////////////////
void Apresentacao();
void AjustarData();
void AjustarHora();
void AjustarHoraAlarm_A();
void AjustarHoraAlarm_B();
void AjustarHoraAlarm_C();
void AjustarHoraAlarm_D();
void Configurar();
void Editar();
void Editar_Remedios();
void Sair();

void setup() {
    // Inicializa o Serial Monitor
    Serial.begin(9600);

    // Inicializa o LED
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

    // Inicializa o BUZZER
    pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW);

    // Inicializa o módulo RTC DS3231
    rtc.begin(); 

    // Inicializa o LCD
    lcd.begin(16, 2); 
    lcd.clear(); // Limpa o LCD
}

void loop() {

    if(ajustar){
      Apresentacao();
      Menu(); 
      lcd.clear(); // Limpa o LCD
      ajustar = false;
    }
    
    tecla_pressionada = teclado.getKey();
    if(tecla_pressionada == '#'){
      op = 0;
      Menu();
    }
    
    dt = rtc.getDateTime();
    float temperatura = rtc.readTemperature();
    rtc.forceConversion();
    
    // Relógio
       lcd.setCursor(4,0);
       if (dt.hour < 10) {
          lcd.print("0");
       }
       lcd.print(dt.hour);
       lcd.print(":");
       if (dt.minute < 10) {
          lcd.print("0");
       }
       lcd.print(dt.minute);
       lcd.print(":");
       if (dt.second < 10) {
          lcd.print("0");
       }
       lcd.print((dt.second));
  
    // Temporizador: Data, Temperatura e Identificação
       switch(control)    {
               case 0: {
                  lcd.setCursor(0,1);
                  lcd.print("Data: ");
                  lcd.print(dt.day);
                  lcd.print("/");
                  lcd.print(dt.month);
                  lcd.print("/");
                  lcd.print(dt.year); 
                  lcd.print("                ");             
                  temporizador(1);
                  break;
               }
            case 1: {
                  lcd.setCursor(0,1);             
                  lcd.print("Temp: ");
                  lcd.print(temperatura);
                  lcd.print(" C");
                  lcd.print("            ");
                  temporizador(2);
                  break; 
            }
            case 2: {
                 lcd.setCursor(0,1);     
                 lcd.print("    MEDICADOR");
                 lcd.print("                ");           
                 temporizador(0);
                 break; 
            }
       }

///////////////////////////////////////////////////
//
//  ALARMES A
//
/////////////////////////////////////////////////// 
    if ((dt.hour == horas_A) && (dt.minute == minutos_A) && (dt.second == segundos_A)){

      lcd.clear();
      
      lcd.setCursor(5, 0);  
      lcd.print("ALARME");
      lcd.setCursor(3, 1);  
      lcd.print("REMEDIO A");
      
      while(tecla_pressionada != '#'){
        tecla_pressionada = teclado.getKey();
        tone(BUZZER,262); 
        digitalWrite(LED, HIGH);
        delay(500);
        tone(BUZZER,250);
        digitalWrite(LED, LOW);
        delay(500);    
      }
      if(tecla_pressionada == '#'){
        noTone(BUZZER);
        digitalWrite(LED, LOW);
        tecla_pressionada == 'Z';
      }
      
      lcd.clear();  
    }

///////////////////////////////////////////////////
//
//  ALARMES B
//
///////////////////////////////////////////////////
    if ((dt.hour == horas_B) && (dt.minute == minutos_B) && (dt.second == segundos_B)){

      lcd.clear();
      
      lcd.setCursor(5, 0);  
      lcd.print("ALARME");
      lcd.setCursor(3, 1);  
      lcd.print("REMEDIO B");
      
      while(tecla_pressionada != '#'){
        tecla_pressionada = teclado.getKey();
        tone(BUZZER,262); 
        digitalWrite(LED, HIGH);
        delay(500);
        tone(BUZZER,250);
        digitalWrite(LED, LOW);
        delay(500); 
      }
      if(tecla_pressionada == '#'){
        noTone(BUZZER);
        digitalWrite(LED, LOW);
        tecla_pressionada == 'Z';
      }
      
      lcd.clear();  
    }

///////////////////////////////////////////////////
//
//  ALARMES C
//
///////////////////////////////////////////////////
    if ((dt.hour == horas_C) && (dt.minute == minutos_C) && (dt.second == segundos_C)){

      lcd.clear();
      
      lcd.setCursor(5, 0);  
      lcd.print("ALARME");
      lcd.setCursor(3, 1);  
      lcd.print("REMEDIO C");
      
      while(tecla_pressionada != '#'){
        tecla_pressionada = teclado.getKey();
        tone(BUZZER,262); 
        digitalWrite(LED, HIGH);
        delay(500);
        tone(BUZZER,250);
        digitalWrite(LED, LOW);
        delay(500);    
      }
      if(tecla_pressionada == '#'){
        noTone(BUZZER);
        digitalWrite(LED, LOW);
        tecla_pressionada == 'Z';
      }
      
      lcd.clear();  
    }

///////////////////////////////////////////////////
//
//  ALARMES D
//
///////////////////////////////////////////////////
    if ((dt.hour == horas_D) && (dt.minute == minutos_D) && (dt.second == segundos_D)){

      lcd.clear();
      
      lcd.setCursor(5, 0);  
      lcd.print("ALARME");
      lcd.setCursor(3, 1);  
      lcd.print("REMEDIO D");
      
      while(tecla_pressionada != '#'){
        tecla_pressionada = teclado.getKey();
        tone(BUZZER,262); 
        digitalWrite(LED, HIGH);
        delay(500);
        tone(BUZZER,250);
        digitalWrite(LED, LOW);
        delay(500);  
      }
      if(tecla_pressionada == '#'){
        noTone(BUZZER);
        digitalWrite(LED, LOW);
        tecla_pressionada == 'Z';
      }
      
      lcd.clear();  
    }
}

///////////////////////////////////////////////////
//
//  IMPLEMENTAÇÃO DAS FUNÇÕES
//
///////////////////////////////////////////////////

// Função para avaliar o que está sendo digitado é um número
int EhNumero(int pressionada){
  if(pressionada == 'A' || pressionada == 'B' ||
       pressionada == 'C' || pressionada == 'D' ||
       pressionada == '#' || pressionada == '*'){
         return 0;
    }
    return 1;
}

// Função para avaliar o que está sendo digitado é um caracter especial
int EhCaracter(int pressionada){
  if(pressionada == '#' || pressionada == '*'){
         return 0;
    }
    return 1;
}


///////////////////////////////////////////////////
//
//  TEMPORIZADOR
//
///////////////////////////////////////////////////

// Atualiza a cada 3 segundos
void temporizador(int x) {
  if (millis() - timer >=3000) {
    control = x;
    timer = millis(); // Atualiza a referência            
  }
}

///////////////////////////////////////////////////
//
//  AJUSTAR DATA
//
///////////////////////////////////////////////////

void AjustarData(){
  
    lcd.clear();
  
    lcd.setCursor(0, 0);
    lcd.print("Ajustar Data");
    lcd.setCursor(0,1);
    lcd.print("Data:   /  /    ");
  
    lcd.cursor();
    lcd.blink();

  //----- DIAS -----//  
    while(true){    
      lcd.setCursor(6,1);
      
      for(int i = 0; i < 2; i++){
        tecla_pressionada = teclado.waitForKey();
        
        // O While vai avaliar se foi digitado um número
        while(EhNumero(tecla_pressionada) == 0){
          tecla_pressionada = teclado.waitForKey();
        } // Fim While
        
        lcd.print(tecla_pressionada);
        entrada += tecla_pressionada;
      } // Fim For
      
      dia = atoi(entrada.c_str());
      // O If vai avaliar se o valor digitado para dias é compatível
      if(dia > 31){
        entrada = "";
        lcd.setCursor(6,1);
        lcd.print("  ");
        continue;
      }
      
      tecla_pressionada = teclado.waitForKey();
      
      // O While vai avaliar se foi digitado um caracter especial
      while(EhCaracter(tecla_pressionada) != 0){
        tecla_pressionada = teclado.waitForKey();
      } // Fim While

      if(tecla_pressionada == '*'){
        entrada = "";
        lcd.setCursor(6,1);
        lcd.print("  ");
        continue;
      }

      if(tecla_pressionada == '#'){
        dia = atoi(entrada.c_str());
        entrada = "";
        break;
      }
    }

  //----- MESES -----//  
  while(true){    
      lcd.setCursor(9,1);
      
      for(int i = 0; i < 2; i++){
        tecla_pressionada = teclado.waitForKey();
        
        // O While vai avaliar se foi digitado um número
        while(EhNumero(tecla_pressionada) == 0){
          tecla_pressionada = teclado.waitForKey();
        } // Fim While
        
        lcd.print(tecla_pressionada);
        entrada += tecla_pressionada;
      } // Fim For
      
      mes = atoi(entrada.c_str());
      // O If vai avaliar se o valor digitado para mes é compatível
      if(mes > 12){
        entrada = "";
        lcd.setCursor(9,1);
        lcd.print("  ");
        continue;
      }
      
      tecla_pressionada = teclado.waitForKey();
      
      // O While vai avaliar se foi digitado um caracter especial
      while(EhCaracter(tecla_pressionada) != 0){
        tecla_pressionada = teclado.waitForKey();
      } // Fim While

      if(tecla_pressionada == '*'){
        entrada = "";
        lcd.setCursor(9,1);
        lcd.print("  ");
        continue;
      }

      if(tecla_pressionada == '#'){
        mes = atoi(entrada.c_str());
        entrada = "";
        break;
      }
    }

  //----- ANOS -----//  
    while(true){    
      lcd.setCursor(12,1);
      
      for(int i = 0; i < 4; i++){
        tecla_pressionada = teclado.waitForKey();
        
        // O While vai avaliar se foi digitado um número
        while(EhNumero(tecla_pressionada) == 0){
          tecla_pressionada = teclado.waitForKey();
        } // Fim While
        
        lcd.print(tecla_pressionada);
        entrada += tecla_pressionada;
      } // Fim For
      
      tecla_pressionada = teclado.waitForKey();
      
      // O While vai avaliar se foi digitado um caracter especial
      while(EhCaracter(tecla_pressionada) != 0){
        tecla_pressionada = teclado.waitForKey();
      } // Fim While

      if(tecla_pressionada == '*'){
        entrada = "";
        lcd.setCursor(12,1);
        lcd.print("    ");
        continue;
      }

      if(tecla_pressionada == '#'){
        ano = atoi(entrada.c_str());
        entrada = "";
        break;
      }
    }
  
    lcd.noCursor();
    lcd.noBlink();

    lcd.clear();
}

///////////////////////////////////////////////////
//
//  AJUSTAR HORA
//
///////////////////////////////////////////////////

void AjustarHora(){
    
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Ajustar Horario");
    lcd.setCursor(0,1);
    lcd.print("Hora:   :  ");

    lcd.cursor();
    lcd.blink();

  //----- HORAS -----//  
    while(true){

      lcd.setCursor(6,1);

      for(int i = 0; i < 2; i++){
        tecla_pressionada = teclado.waitForKey();
        
        // O While vai avaliar se foi digitado um número
        while(EhNumero(tecla_pressionada) == 0){
          tecla_pressionada = teclado.waitForKey();
        } // Fim While
        
        lcd.print(tecla_pressionada);
        entrada += tecla_pressionada;
      } // Fim For

      horas = atoi(entrada.c_str());
      // O If vai avaliar se o valor digitado para hora é compatível
      if(horas > 23){
        entrada = "";
        lcd.setCursor(6,1);
        lcd.print("  ");
        continue;
      } // Fim If

      tecla_pressionada = teclado.waitForKey();
      
      // O While vai avaliar se foi digitado um caracter especial
      while(EhCaracter(tecla_pressionada) != 0){
        tecla_pressionada = teclado.waitForKey();
      } // Fim While

      if(tecla_pressionada == '*'){
        entrada = "";
        lcd.setCursor(6,1);
        lcd.print("  ");
        continue;
      } // Fim If
  
      if(tecla_pressionada == '#'){
        horas = atoi(entrada.c_str());
        entrada = "";
        break;
      } // Fim If
  
    } // Fim While

  //----- MINUTOS -----//  
    while(true){

      lcd.setCursor(9,1);

      for(int i = 0; i < 2; i++){
        tecla_pressionada = teclado.waitForKey();
        
        // O While vai avaliar se foi digitado um número
        while(EhNumero(tecla_pressionada) == 0){
          tecla_pressionada = teclado.waitForKey();
        } // Fim While
        
        lcd.print(tecla_pressionada);
        entrada += tecla_pressionada;
      } // While For

      minutos = atoi(entrada.c_str());
      // O If vai avaliar se o valor digitado para minuto é compatível
      if(minutos > 59){
        entrada = "";
        lcd.setCursor(9,1);
        lcd.print("  ");
        continue;
      } // Fim If

      tecla_pressionada = teclado.waitForKey();
      
      // O While vai avaliar se foi digitado um caracter especial
      while(EhCaracter(tecla_pressionada) != 0){
        tecla_pressionada = teclado.waitForKey();
      } // Fim While

      if(tecla_pressionada == '*'){
        entrada = "";
        lcd.setCursor(9,1);
        lcd.print("  ");
        continue;
      } // Fim If

      if(tecla_pressionada == '#'){
        minutos = atoi(entrada.c_str());
        entrada = "";
        break;
      } // Fim If
    } // Fim While

    segundos = 0;
    
    lcd.noCursor();
    lcd.noBlink();

    lcd.clear();
} // Fim AjustarHora()

///////////////////////////////////////////////////
//
//  AJUSTAR HORA DO ALARME A
//
///////////////////////////////////////////////////

void AjustarHoraAlarm_A(){
    
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Ajustar Horario");
    lcd.setCursor(0,1);
    lcd.print("Hora:   :  ");

    lcd.cursor();
    lcd.blink();

  //----- HORAS -----//  
    while(true){

      lcd.setCursor(6,1);

      for(int i = 0; i < 2; i++){
        tecla_pressionada = teclado.waitForKey();
        
        // O While vai avaliar se foi digitado um número
        while(EhNumero(tecla_pressionada) == 0){
          tecla_pressionada = teclado.waitForKey();
        } // Fim While
        
        lcd.print(tecla_pressionada);
        entrada += tecla_pressionada;
      } // Fim For

      horas_A = atoi(entrada.c_str());
      // O If vai avaliar se o valor digitado para hora é compatível
      if(horas_A > 23){
        entrada = "";
        lcd.setCursor(6,1);
        lcd.print("  ");
        continue;
      } // Fim If

      tecla_pressionada = teclado.waitForKey();
      
      // O While vai avaliar se foi digitado um caracter especial
      while(EhCaracter(tecla_pressionada) != 0){
        tecla_pressionada = teclado.waitForKey();
      } // Fim While

      if(tecla_pressionada == '*'){
        entrada = "";
        lcd.setCursor(6,1);
        lcd.print("  ");
        continue;
      } // Fim If
  
      if(tecla_pressionada == '#'){
        horas_A = atoi(entrada.c_str());
        entrada = "";
        break;
      } // Fim If
  
    } // Fim While

  //----- MINUTOS -----//  
    while(true){

      lcd.setCursor(9,1);

      for(int i = 0; i < 2; i++){
        tecla_pressionada = teclado.waitForKey();
        
        // O While vai avaliar se foi digitado um número
        while(EhNumero(tecla_pressionada) == 0){
          tecla_pressionada = teclado.waitForKey();
        } // Fim While
        
        lcd.print(tecla_pressionada);
        entrada += tecla_pressionada;
      } // While For

      minutos_A = atoi(entrada.c_str());
      // O If vai avaliar se o valor digitado para minuto é compatível
      if(minutos_A > 59){
        entrada = "";
        lcd.setCursor(9,1);
        lcd.print("  ");
        continue;
      } // Fim If

      tecla_pressionada = teclado.waitForKey();
      
      // O While vai avaliar se foi digitado um caracter especial
      while(EhCaracter(tecla_pressionada) != 0){
        tecla_pressionada = teclado.waitForKey();
      } // Fim While

      if(tecla_pressionada == '*'){
        entrada = "";
        lcd.setCursor(9,1);
        lcd.print("  ");
        continue;
      } // Fim If

      if(tecla_pressionada == '#'){
        minutos_A = atoi(entrada.c_str());
        entrada = "";
        break;
      } // Fim If
    } // Fim While

    segundos_A = 0;
    
    lcd.noCursor();
    lcd.noBlink();

    lcd.clear();
} // Fim AjustarHoraAlarm_A()

///////////////////////////////////////////////////
//
//  AJUSTAR HORA DO ALARME B
//
///////////////////////////////////////////////////

void AjustarHoraAlarm_B(){
    
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Ajustar Horario");
    lcd.setCursor(0,1);
    lcd.print("Hora:   :  ");

    lcd.cursor();
    lcd.blink();

  //----- HORAS -----//  
    while(true){

      lcd.setCursor(6,1);

      for(int i = 0; i < 2; i++){
        tecla_pressionada = teclado.waitForKey();
        
        // O While vai avaliar se foi digitado um número
        while(EhNumero(tecla_pressionada) == 0){
          tecla_pressionada = teclado.waitForKey();
        } // Fim While
        
        lcd.print(tecla_pressionada);
        entrada += tecla_pressionada;
      } // Fim For

      horas_B = atoi(entrada.c_str());
      // O If vai avaliar se o valor digitado para hora é compatível
      if(horas_B > 23){
        entrada = "";
        lcd.setCursor(6,1);
        lcd.print("  ");
        continue;
      } // Fim If

      tecla_pressionada = teclado.waitForKey();
      
      // O While vai avaliar se foi digitado um caracter especial
      while(EhCaracter(tecla_pressionada) != 0){
        tecla_pressionada = teclado.waitForKey();
      } // Fim While

      if(tecla_pressionada == '*'){
        entrada = "";
        lcd.setCursor(6,1);
        lcd.print("  ");
        continue;
      } // Fim If
  
      if(tecla_pressionada == '#'){
        horas_B = atoi(entrada.c_str());
        entrada = "";
        break;
      } // Fim If
  
    } // Fim While

  //----- MINUTOS -----//  
    while(true){

      lcd.setCursor(9,1);

      for(int i = 0; i < 2; i++){
        tecla_pressionada = teclado.waitForKey();
        
        // O While vai avaliar se foi digitado um número
        while(EhNumero(tecla_pressionada) == 0){
          tecla_pressionada = teclado.waitForKey();
        } // Fim While
        
        lcd.print(tecla_pressionada);
        entrada += tecla_pressionada;
      } // While For

      minutos_B = atoi(entrada.c_str());
      // O If vai avaliar se o valor digitado para minuto é compatível
      if(minutos_B > 59){
        entrada = "";
        lcd.setCursor(9,1);
        lcd.print("  ");
        continue;
      } // Fim If

      tecla_pressionada = teclado.waitForKey();
      
      // O While vai avaliar se foi digitado um caracter especial
      while(EhCaracter(tecla_pressionada) != 0){
        tecla_pressionada = teclado.waitForKey();
      } // Fim While

      if(tecla_pressionada == '*'){
        entrada = "";
        lcd.setCursor(9,1);
        lcd.print("  ");
        continue;
      } // Fim If

      if(tecla_pressionada == '#'){
        minutos_B = atoi(entrada.c_str());
        entrada = "";
        break;
      } // Fim If
    } // Fim While

    segundos_B = 0;
    
    lcd.noCursor();
    lcd.noBlink();

    lcd.clear();
} // Fim AjustarHoraAlarm_B()

///////////////////////////////////////////////////
//
//  AJUSTAR HORA DO ALARME C
//
///////////////////////////////////////////////////

void AjustarHoraAlarm_C(){
    
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Ajustar Horario");
    lcd.setCursor(0,1);
    lcd.print("Hora:   :  ");

    lcd.cursor();
    lcd.blink();

  //----- HORAS -----//  
    while(true){

      lcd.setCursor(6,1);

      for(int i = 0; i < 2; i++){
        tecla_pressionada = teclado.waitForKey();
        
        // O While vai avaliar se foi digitado um número
        while(EhNumero(tecla_pressionada) == 0){
          tecla_pressionada = teclado.waitForKey();
        } // Fim While
        
        lcd.print(tecla_pressionada);
        entrada += tecla_pressionada;
      } // Fim For

      horas_C = atoi(entrada.c_str());
      // O If vai avaliar se o valor digitado para hora é compatível
      if(horas_C > 23){
        entrada = "";
        lcd.setCursor(6,1);
        lcd.print("  ");
        continue;
      } // Fim If

      tecla_pressionada = teclado.waitForKey();
      
      // O While vai avaliar se foi digitado um caracter especial
      while(EhCaracter(tecla_pressionada) != 0){
        tecla_pressionada = teclado.waitForKey();
      } // Fim While

      if(tecla_pressionada == '*'){
        entrada = "";
        lcd.setCursor(6,1);
        lcd.print("  ");
        continue;
      } // Fim If
  
      if(tecla_pressionada == '#'){
        horas_C = atoi(entrada.c_str());
        entrada = "";
        break;
      } // Fim If
  
    } // Fim While

  //----- MINUTOS -----//  
    while(true){

      lcd.setCursor(9,1);

      for(int i = 0; i < 2; i++){
        tecla_pressionada = teclado.waitForKey();
        
        // O While vai avaliar se foi digitado um número
        while(EhNumero(tecla_pressionada) == 0){
          tecla_pressionada = teclado.waitForKey();
        } // Fim While
        
        lcd.print(tecla_pressionada);
        entrada += tecla_pressionada;
      } // While For

      minutos_C = atoi(entrada.c_str());
      // O If vai avaliar se o valor digitado para minuto é compatível
      if(minutos_C > 59){
        entrada = "";
        lcd.setCursor(9,1);
        lcd.print("  ");
        continue;
      } // Fim If

      tecla_pressionada = teclado.waitForKey();
      
      // O While vai avaliar se foi digitado um caracter especial
      while(EhCaracter(tecla_pressionada) != 0){
        tecla_pressionada = teclado.waitForKey();
      } // Fim While

      if(tecla_pressionada == '*'){
        entrada = "";
        lcd.setCursor(9,1);
        lcd.print("  ");
        continue;
      } // Fim If

      if(tecla_pressionada == '#'){
        minutos_C = atoi(entrada.c_str());
        entrada = "";
        break;
      } // Fim If
    } // Fim While

    segundos_C = 0;
    
    lcd.noCursor();
    lcd.noBlink();

    lcd.clear();
} // Fim AjustarHoraAlarm_C()

///////////////////////////////////////////////////
//
//  AJUSTAR HORA DO ALARME D
//
///////////////////////////////////////////////////

void AjustarHoraAlarm_D(){
    
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Ajustar Horario");
    lcd.setCursor(0,1);
    lcd.print("Hora:   :  ");

    lcd.cursor();
    lcd.blink();

  //----- HORAS -----//  
    while(true){

      lcd.setCursor(6,1);

      for(int i = 0; i < 2; i++){
        tecla_pressionada = teclado.waitForKey();
        
        // O While vai avaliar se foi digitado um número
        while(EhNumero(tecla_pressionada) == 0){
          tecla_pressionada = teclado.waitForKey();
        } // Fim While
        
        lcd.print(tecla_pressionada);
        entrada += tecla_pressionada;
      } // Fim For

      horas_D = atoi(entrada.c_str());
      // O If vai avaliar se o valor digitado para hora é compatível
      if(horas_D > 23){
        entrada = "";
        lcd.setCursor(6,1);
        lcd.print("  ");
        continue;
      } // Fim If

      tecla_pressionada = teclado.waitForKey();
      
      // O While vai avaliar se foi digitado um caracter especial
      while(EhCaracter(tecla_pressionada) != 0){
        tecla_pressionada = teclado.waitForKey();
      } // Fim While

      if(tecla_pressionada == '*'){
        entrada = "";
        lcd.setCursor(6,1);
        lcd.print("  ");
        continue;
      } // Fim If
  
      if(tecla_pressionada == '#'){
        horas_D = atoi(entrada.c_str());
        entrada = "";
        break;
      } // Fim If
  
    } // Fim While

  //----- MINUTOS -----//  
    while(true){

      lcd.setCursor(9,1);

      for(int i = 0; i < 2; i++){
        tecla_pressionada = teclado.waitForKey();
        
        // O While vai avaliar se foi digitado um número
        while(EhNumero(tecla_pressionada) == 0){
          tecla_pressionada = teclado.waitForKey();
        } // Fim While
        
        lcd.print(tecla_pressionada);
        entrada += tecla_pressionada;
      } // While For

      minutos_D = atoi(entrada.c_str());
      // O If vai avaliar se o valor digitado para minuto é compatível
      if(minutos_D > 59){
        entrada = "";
        lcd.setCursor(9,1);
        lcd.print("  ");
        continue;
      } // Fim If

      tecla_pressionada = teclado.waitForKey();
      
      // O While vai avaliar se foi digitado um caracter especial
      while(EhCaracter(tecla_pressionada) != 0){
        tecla_pressionada = teclado.waitForKey();
      } // Fim While

      if(tecla_pressionada == '*'){
        entrada = "";
        lcd.setCursor(9,1);
        lcd.print("  ");
        continue;
      } // Fim If

      if(tecla_pressionada == '#'){
        minutos_D = atoi(entrada.c_str());
        entrada = "";
        break;
      } // Fim If
    } // Fim While

    segundos_D = 0;
    
    lcd.noCursor();
    lcd.noBlink();

    lcd.clear();
} // Fim AjustarHoraAlarm_D()

///////////////////////////////////////////////////
//
//  APRESENTAÇÃO
//
///////////////////////////////////////////////////

void Apresentacao(){
  
    lcd.clear();
  
    lcd.setCursor(4, 0);
    lcd.print("Bem-vindo"); 
    delay(tempo);
    
    lcd.clear();
  
    lcd.setCursor(4, 0);
    lcd.print("Me  Chamo");
    lcd.setCursor(4, 1);
    lcd.print ("Medicador");        
    delay(tempo);
    
    lcd.clear();
    
    lcd.setCursor(2, 0);
    lcd.print("Vou te ajudar"); 
    lcd.setCursor(1, 1);
    lcd.print("com os remedios "); 
    delay(tempo);
    
    lcd.clear();
    
    lcd.setCursor(1, 0);
    lcd.print("Vamos comecar!"); 
    delay(tempo);
    
    lcd.clear();
}

///////////////////////////////////////////////////
//
//  MENU
//
///////////////////////////////////////////////////

void Menu(){
  
    lcd.clear();
    
    lcd.print("Escolha uma das 3 opcoes a seguir");
    delay(500);
    
    for (int i = 0; i < 24; i++){
       delay(400);
       lcd.scrollDisplayLeft();
    }
      
    lcd.clear();
    
    lcd.setCursor(2, 0);
    lcd.print("Aperte 1 para");
    lcd.setCursor(3, 1);          
    lcd.print("CONFIGURAR");
    delay(tempo);
    
    lcd.clear();
    
    lcd.setCursor(2, 0);
    lcd.print("Aperte 2 para");
    lcd.setCursor(5, 1);
    lcd.print("EDITAR");
    delay(tempo);
    
    lcd.clear();
    
    lcd.setCursor(2, 0);
    lcd.print("Aperte 3 para");
    lcd.setCursor(6, 1);
    lcd.print("SAIR");
    delay(tempo);
    
    lcd.clear();
    
    lcd.setCursor(3, 0);
    lcd.print("Aguardando");
    lcd.setCursor(2, 1); 
    lcd.print("sua  escolha");
    delay(1000);
    
    while(op == 0){
          
    tecla_pressionada = teclado.waitForKey(); 
      
        switch (tecla_pressionada){
  
          case '1': ///////////////////////////////////////////////
          
           Configurar();
           op = 1;
           break;
  
          case '2': ///////////////////////////////////////////////
          
           Editar();
           op = 1;
           break;
  
          case '3': ///////////////////////////////////////////////
          
           Sair();
           op = 1;
           break; 
  
          default: ///////////////////////////////////////////////
          
          lcd.clear();
          
          lcd.print("Comando Invalido");
          delay(tempo);
          
          lcd.clear();
          
          lcd.setCursor(2, 0);
          lcd.print("Tente de Novo");
          op = 0;
          break;
      }
    }   
}

///////////////////////////////////////////////////
//
//  CONFIGURAR
//
///////////////////////////////////////////////////

void Configurar(){ 
  
    lcd.clear();
    
  //Apresentação da função   
    lcd.setCursor(2, 0);
    lcd.print("Voce escolheu");
    lcd.setCursor(3, 1);
    lcd.print("CONFIGURAR");
    delay(tempo);
    
    lcd.clear();
      
    AjustarData();
    AjustarHora();
    rtc.setDateTime(ano, mes, dia, horas, minutos, segundos);
  
  //Configuração dos remédios
    
///////////////////////////////////////////////////
//
//  REMÉDIO A
//
///////////////////////////////////////////////////    
    lcd.clear();
    
    lcd.print("Digite a hora do");
    lcd.setCursor(3, 1);
    lcd.print("remedio A");
    delay(tempo);

    lcd.clear();

    AjustarHoraAlarm_A();

    lcd.clear();

    lcd.print("O remedio A vai");
    lcd.setCursor(2, 1);
    lcd.print("alarmar as");
    delay(tempo);

    lcd.clear();

    lcd.setCursor(4,0);
    lcd.print("REMEDIO A");
    lcd.setCursor(4,1);
    if (horas_A < 10) {
      lcd.print("0");
    }
    lcd.print(horas_A);
    lcd.print(":");
    if (minutos_A < 10) {
      lcd.print("0");
    }
    lcd.print(minutos_A);
    lcd.print(":");
    if (segundos_A < 10) {
      lcd.print("0");
    }
    lcd.print(segundos_A);
    delay(tempo);   
            
    lcd.clear();
      
///////////////////////////////////////////////////
//
//  REMÉDIO B
//
///////////////////////////////////////////////////    
    lcd.clear();
    
    lcd.print("Digite a hora do");
    lcd.setCursor(3, 1);
    lcd.print("remedio B");
    delay(tempo);
    
    lcd.clear();

    AjustarHoraAlarm_B();
    
    lcd.clear();

    lcd.print("O remedio B vai");
    lcd.setCursor(2, 1);
    lcd.print("alarmar as");
    delay(tempo);
    
    lcd.clear();

    lcd.setCursor(4,0);
    lcd.print("REMEDIO B");
    lcd.setCursor(4,1);
    if (horas_B < 10) {
      lcd.print("0");
    }
    lcd.print(horas_B);
    lcd.print(":");
    if (minutos_B < 10) {
      lcd.print("0");
    }
    lcd.print(minutos_B);
    lcd.print(":");
    if (segundos_B < 10) {
      lcd.print("0");
    }
    lcd.print(segundos_B);
    delay(tempo);   
            
    lcd.clear();
  
///////////////////////////////////////////////////
//
//  REMÉDIO C
//
///////////////////////////////////////////////////  
    lcd.clear();
    
    lcd.print("Digite a hora do");
    lcd.setCursor(3, 1);
    lcd.print("remedio C");
    delay(tempo);
    
    lcd.clear();

    AjustarHoraAlarm_C();
    
    lcd.clear();
    
    lcd.print("O remedio C vai");
    lcd.setCursor(2, 1);
    lcd.print("alarmar as");
    delay(tempo);
    
    lcd.clear();

    lcd.setCursor(4,0);
    lcd.print("REMEDIO C");
    lcd.setCursor(4,1);
    if (horas_C < 10) {
      lcd.print("0");
    }
    lcd.print(horas_C);
    lcd.print(":");
    if (minutos_C < 10) {
      lcd.print("0");
    }
    lcd.print(minutos_C);
    lcd.print(":");
    if (segundos_C < 10) {
      lcd.print("0");
    }
    lcd.print(segundos_C);
    delay(tempo);   
            
    lcd.clear();
    
///////////////////////////////////////////////////
//
//  REMÉDIO D
//
///////////////////////////////////////////////////
    
    lcd.clear();
    
    lcd.print("Digite a hora do");
    lcd.setCursor(3, 1);
    lcd.print("remedio D");
    delay(tempo);
    
    lcd.clear();

    AjustarHoraAlarm_D();
    
    lcd.clear();
    
    lcd.print("O remedio D vai");
    lcd.setCursor(2, 1);
    lcd.print("alarmar as");
    delay(tempo);
    
    lcd.clear();

    lcd.setCursor(4,0);
    lcd.print("REMEDIO D");
    lcd.setCursor(4,1);
    if (horas_D < 10) {
      lcd.print("0");
    }
    lcd.print(horas_D);
    lcd.print(":");
    if (minutos_D < 10) {
      lcd.print("0");
    }
    lcd.print(minutos_D);
    lcd.print(":");
    if (segundos_D < 10) {
      lcd.print("0");
    }
    lcd.print(segundos_D);
    delay(tempo);   
            
    lcd.clear();
}

///////////////////////////////////////////////////
//
//  EDITAR
//
///////////////////////////////////////////////////

void Editar(){ 
  
    lcd.clear();
    
  //Apresentação da função
    lcd.setCursor(2, 0);
    lcd.print("Voce escolheu");
    lcd.setCursor(5, 1);
    lcd.print("EDITAR");
    delay(tempo);
    
    lcd.clear();
    
    lcd.setCursor(3, 0);
    lcd.print("O que voce");
    lcd.setCursor(2, 1);
    lcd.print("deseja editar?");
    delay(tempo);
    
    lcd.clear();
    
    lcd.print("Escolha uma das 3 opcoes a seguir");
    delay(500);
    
    for (int i = 0; i < 24; i++){
       delay(400);
       lcd.scrollDisplayLeft();
    }
      
    lcd.clear();
    
    lcd.setCursor(2, 0);
    lcd.print("Aperte 1 para");
    lcd.setCursor(6, 1);
    lcd.print("Data");
    delay(tempo);
    
    lcd.clear();
    
    lcd.setCursor(2, 0);
    lcd.print("Aperte 2 para");
    lcd.setCursor(6, 1);
    lcd.print("Hora");
    delay(tempo);
    
    lcd.clear();
    
    lcd.setCursor(2, 0);
    lcd.print("Aperte 3 para");
    lcd.setCursor(1, 1);
    lcd.print("Hora do Remedio");
    delay(tempo);
    
    lcd.clear();
    
    lcd.setCursor(3, 0);
    lcd.print("Aguardando");
    lcd.setCursor(2, 1); 
    lcd.print("sua  escolha");
    delay(tempo);
    
    while(op == 0){
          
    tecla_pressionada = teclado.waitForKey(); 
      
        switch (tecla_pressionada){
  
          case '1': ///////////////////////////////////////////////
          
           lcd.clear();
          
           lcd.setCursor(2, 0);
           lcd.print("Voce escolheu");
           lcd.setCursor(5, 1);
           lcd.print("opcao 1");
           delay(tempo);
           
           lcd.clear();
          
           AjustarData();
           rtc.setDateTime(ano, mes, dia, dt.hour, dt.minute, dt.second);
           
           op = 1;
           break;
          
          case '2': ///////////////////////////////////////////////
          
           lcd.clear();
          
           lcd.setCursor(2, 0);
           lcd.print("Voce escolheu");
           lcd.setCursor(5, 1);
           lcd.print("opcao 2");
           delay(tempo);
    
           lcd.clear();
           
           AjustarHora();
           rtc.setDateTime(dt.year, dt.month, dt.day, horas, minutos, segundos);
          
           op = 1;
           break;
  
          case '3': ///////////////////////////////////////////////
           
           Editar_Remedios();
           op = 1;
           break;
  
          default: ///////////////////////////////////////////////
          
           lcd.clear();
          
           lcd.print("Comando Invalido");
           delay(tempo);
          
           lcd.clear();
          
           lcd.setCursor(2, 0);
           lcd.print("Tente de Novo");
           op = 0;
           break;
      }
    }   
}

///////////////////////////////////////////////////
//
//  EDITAR REMEDIOS
//
///////////////////////////////////////////////////

void Editar_Remedios(){
  
    lcd.clear();
    
    lcd.setCursor(2, 0);
    lcd.print("Voce escolheu");
    lcd.setCursor(5, 1);
    lcd.print("opcao 3");
    delay(tempo);
    
    lcd.clear();
          
    lcd.setCursor(2, 0);
    lcd.print("Qual remedio");
    lcd.setCursor(1, 1);
    lcd.print("deseja editar:");
    delay(tempo);
          
    lcd.clear();
    
    lcd.setCursor(2, 0);      
    lcd.print("A, B, C ou D?");
    delay(tempo);
    
    while(op == 0){
          
    tecla_pressionada = teclado.waitForKey();
    
      switch (tecla_pressionada){
  
        case 'A': ///////////////////////////////////////////////
  
          lcd.clear();
          
          lcd.setCursor(2, 0);
          lcd.print("Voce escolheu");
          lcd.setCursor(3, 1);
          lcd.print("Remedio A");
          delay(tempo);
          
          lcd.clear();
  
          AjustarHoraAlarm_A();
  
          lcd.clear();

          lcd.setCursor(0, 0);
          lcd.print("O remedio A vai");
          lcd.setCursor(3, 1);
          lcd.print("alarmar as");
          delay(tempo);
      
          lcd.clear();

          lcd.setCursor(4,0);
          lcd.print("REMEDIO A");
          lcd.setCursor(4,1);
          if (horas_A < 10) {
            lcd.print("0");
          }
          lcd.print(horas_A);
          lcd.print(":");
          if (minutos_A < 10) {
            lcd.print("0");
          }
          lcd.print(minutos_A);
          lcd.print(":");
          if (segundos_A < 10) {
            lcd.print("0");
          }
          lcd.print(segundos_A);
          delay(tempo);   
                  
          lcd.clear();
  
          op = 1;
          break;
  
        case 'B': ///////////////////////////////////////////////
  
          lcd.clear();
          
          lcd.setCursor(2, 0);
          lcd.print("Voce escolheu");
          lcd.setCursor(3, 1);
          lcd.print("Remedio B");
          delay(tempo);
          
          lcd.clear();
      
          AjustarHoraAlarm_B();
          
          lcd.clear();
          
          lcd.print("O remedio B vai");
          lcd.setCursor(0, 1);
          lcd.print("alarmar as");
          delay(tempo);
          
          lcd.clear();

          lcd.setCursor(4,0);
          lcd.print("REMEDIO B");
          lcd.setCursor(4,1);
          if (horas_B < 10) {
            lcd.print("0");
          }
          lcd.print(horas_B);
          lcd.print(":");
          if (minutos_B < 10) {
            lcd.print("0");
          }
          lcd.print(minutos_B);
          lcd.print(":");
          if (segundos_B < 10) {
            lcd.print("0");
          }
          lcd.print(segundos_B);
          delay(tempo);   
                  
          lcd.clear();

          op = 1;
          break;
  
        case 'C': ///////////////////////////////////////////////
  
          lcd.clear();
          
          lcd.setCursor(2, 0);
          lcd.print("Voce escolheu");
          lcd.setCursor(3, 1);
          lcd.print("Remedio C");
          delay(tempo);
          
          lcd.clear();
      
          AjustarHoraAlarm_C();
          
          lcd.clear();

          lcd.print("O remedio C vai");
          lcd.setCursor(0, 1);
          lcd.print("alarmar as");
          delay(tempo);
          
          lcd.clear();

          lcd.setCursor(4,0);
          lcd.print("REMEDIO C");
          lcd.setCursor(4,1);
          if (horas_C < 10) {
            lcd.print("0");
          }
          lcd.print(horas_C);
          lcd.print(":");
          if (minutos_C < 10) {
            lcd.print("0");
          }
          lcd.print(minutos_C);
          lcd.print(":");
          if (segundos_C < 10) {
            lcd.print("0");
          }
          lcd.print(segundos_C);
          delay(tempo);   
                  
          lcd.clear();

          op = 1;
          break;
  
        case 'D': ///////////////////////////////////////////////
  
          lcd.clear();
          
          lcd.setCursor(2, 0);
          lcd.print("Voce escolheu");
          lcd.setCursor(3, 1);
          lcd.print("Remedio D");
          delay(tempo);
          
          lcd.clear();
      
          AjustarHoraAlarm_D();
          
          lcd.clear();
          
          lcd.print("O remedio D vai");
          lcd.setCursor(0, 1);
          lcd.print("alarmar as");
          delay(tempo);
          
          lcd.clear();

          lcd.setCursor(4,0);
          lcd.print("REMEDIO D");
          lcd.setCursor(4,1);
          if (horas_D < 10) {
            lcd.print("0");
          }
          lcd.print(horas_D);
          lcd.print(":");
          if (minutos_D < 10) {
            lcd.print("0");
          }
          lcd.print(minutos_D);
          lcd.print(":");
          if (segundos_D < 10) {
            lcd.print("0");
          }
          lcd.print(segundos_D);
          delay(tempo);   
                  
          lcd.clear();

          op = 1;
          break;
  
        default: ///////////////////////////////////////////////
  
          lcd.clear();
  
          lcd.print("Comando Invalido");
          delay(tempo);
  
          lcd.clear();
  
          lcd.setCursor(2, 0);
          lcd.print("Tente de Novo");
          op = 0;
          break;
     }
    }   
}

///////////////////////////////////////////////////
//
//  SAIR
//
///////////////////////////////////////////////////

void Sair(){ 
  
    lcd.clear();
  
   //Apresentação da função
    lcd.setCursor(2, 0);
    lcd.print("Voce escolheu");
    lcd.setCursor(6, 1);
    lcd.print("SAIR");
    delay(tempo);
    
    lcd.clear();
    
    lcd.setCursor(4, 0);
    lcd.print("Aguarde!");
    lcd.setCursor(3, 1);
    lcd.print("Saindo...");
    delay(tempo);
      
    lcd.clear();
}