//Autor madsci1016
//https://github.com/madsci1016/Arduino-PS2X/tree/master/PS2X_lib 
#include <PS2X_lib.h>

//PINOS CONTROLE
#define PS2_DAT   8  //PINO MARROM + RESISTOR
#define PS2_CMD   11  //PINO LARANJA
#define PS2_SEL   10  //PINO AMARELO
#define PS2_CLK   12  //PINO AZUL

//PINOS LEDS
#define PIN_LED1      6   //D6 PRETO
#define PIN_LED2      5   //D5 BRANCO
#define PIN_LED3      4   //D4 CINZA
#define PIN_LED4      3   //D3 ROXO

//MODOS DO CONTROLE
#define pressures   false
#define rumble      false

//REFERENCIA DA CLASSE PS2 CONTROLLER
PS2X ps2x;

//STATUS LED
bool LED1 = false;
bool LED2 = false;
bool LED3 = false;
bool LED4 = false;

int error = 0;
/*
 * error = 0
 * CONTROLE ENCONTRADO E CONFIGURADO COM SUCESSO
 * 
 * error = 1
 * CONTROLE NAO ENCONTRADO
 * 
 * error = 2
 * CONTROLE ENCONTRADO MAS NAO ACEITA COMANDOS
 * 
 * error = 3
 * CONTROLE RECUSANDO-SE A ENTRAR NO MODO PRESSURES
 * 
 */

void Configura_Controle(){

  delay(300);
 
  //DEFINE PINAGEM DO CONTROLE E ARMAZENA RESULTADO
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  //EXIBE RESULTA DE CONFIGURAÇÃO
  if(error == 0){
    Serial.println("CONTROLE ENCONTRO E CONFIGURADO COM SUCESSO.");
    Serial.print("PRESSURES = ");
    if (pressures)
      Serial.print("TRUE ");
    else
      Serial.print("FALSE ");
    Serial.print("RUMBLE = ");
    if (rumble)
      Serial.println("TRUE");
    else
      Serial.println("FALSE");
  }  
  else if(error == 1)
    Serial.println("CONTROLE NAO FOI ENCONTRADO");
   
  else if(error == 2)
    Serial.println("CONTROLE ENCONTRADO MAS NAO ACEITA COMANDOS");

  else if(error == 3)
    Serial.println("CONTROLE RECUSANDO-SE A ENTRAR NO MODO PRESSURES");
}

void setup() {
  
  //ABRE PORTA SERIAL COM TAXA DE TRANSFERENCIA DE 57600 bps
  Serial.begin(57600);

  //CONFIGURA CONTROLE
  Configura_Controle();

  //SETA PINAGEM DOS LEDS
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_LED4, OUTPUT);
}

void loop() {
  //SE CONTROLE NAO FOR ENCONTRADO
  if(error == 1){
    Configura_Controle();
    delay(1000);
  }
  else{
    if(ps2x.NewButtonState(PSB_SQUARE)){
      LED1 = !LED1;
      digitalWrite(PIN_LED1, LED1);
    }
    if(ps2x.NewButtonState(PSB_CROSS)){
      LED2 = !LED2;
      digitalWrite(PIN_LED2, LED2);
    }
    if(ps2x.NewButtonState(PSB_CIRCLE)){
      LED3 = !LED3;
      digitalWrite(PIN_LED3, LED3);
    }
    if(ps2x.NewButtonState(PSB_TRIANGLE)){
      LED4 = !LED4;
      digitalWrite(PIN_LED4, LED4);
    }
  }
}
