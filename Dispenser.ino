#include <TimeAlarms.h>
#include <Time.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#define BUTTON A1
#define BotaoConfirma A0
#define BotaoAumenta A2

Servo servo1;
LiquidCrystal lcd(12,11,5,4,3,2);
int minuto1= 0, minuto2 = 0;
int hora1 = 0, hora2 = 0;
int conversao_minuto = 0;
int horatotal = 0;
int btn = 0;
int teste = 5;
int EstadoBotaoConfirma = 0;
int EstadoBotaoAumenta = 0;
int cont = 0;

void setup(){
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 lcd.print("Tempo:");
 lcd.setCursor(0,1);
 lcd.print("00:00");
 //setTime(20,20,30,21,02,2019); 
 Serial.begin(9600);
 //setTempo();
 servo1.attach(A0); 
 servo1.write(0); 
}
void loop(){
  btn = digitalRead(BUTTON); 
  EstadoBotaoConfirma = digitalRead(BotaoConfirma);
  setTempo();

  if(EstadoBotaoConfirma == HIGH){
    if(cont > 4){
      cont = 0;
      //setTempo();
    }
  }
  
  if (btn == HIGH){
    colocarComida();
 }
  mostrarHora();
 Alarm.delay(1000); 
}


void mostrarHora()
{                    
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
   Serial.print('0');
  Serial.print(digits);
}


void colocarComida() {
    servo1.write(170);
    Alarm.delay(3000);
    servo1.write(1);
    Alarm.delay(1500);
    lcd.setCursor(0,0);
    lcd.print("Comida:         ");
}

/*void cronometro(){
   EstadoBotao3 = digitalRead(Botao3);
 if (EstadoBotao3 == HIGH){
 if((hora==0) && (minuto==0)){
 //nao faz nada
 }
 else{
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print(" START ");
 delay(1000);
 if(minuto==0){
 hora--;
 minuto=59;
 }
 for(int y = 0; y<minuto; y--){
 if(hora<10){
 lcd.setCursor(5,1);
 lcd.print("0");
 lcd.print(hora);
 lcd.print(":");
 }
 else{
 lcd.setCursor(5,1);
 lcd.print(hora);
 lcd.print(":");
 }
}if(minuto<10){
 lcd.print("0");
 lcd.print(minuto);
 }
 else{
 lcd.print(minuto);
 }
 minuto--;
 if(minuto<0){
 hora--;
 minuto=59;
 }
 delay(1000); //base de tempo de 1 segundo
 //para deixar timer mais rápido, diminuir aqui
 if((minuto<=0) && (hora<=0)) {
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("ACABOU O TEMPO!");
 break; //sai do loop for
 }
 }
 inicializacao();
 }
}.
*/

void setTempo(){
  EstadoBotaoAumenta = digitalRead(BotaoAumenta);
  EstadoBotaoConfirma = digitalRead(BotaoConfirma);
  if(EstadoBotaoConfirma == HIGH){
    
    if(cont == 1){
      cont = cont+2;
    }
    else if(cont == 4){

      conversao_minuto = (hora1*600)+(hora2*60)+(minuto1*10)+minuto2;
      
      horatotal = conversao_minuto*60;
      Alarm.timerRepeat(horatotal,colocarComida);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Sucesso!");
      lcd.setCursor(0,1);
      lcd.print("        ");
      lcd.setCursor(4,1);
      lcd.noBlink();
    }
    else{
      if(cont == 0){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Tempo:");
        lcd.setCursor(0,1);
        lcd.print("00:00");
      }
      cont++;
    }

    delay(150);
    
  }
  
  if (EstadoBotaoAumenta == HIGH){
    if(cont == 0){
      //delay(150);
      hora1++;
      if(hora1 > 2){
        hora1 = 0;
      }
      lcd.setCursor(cont,1);
      lcd.print(hora1);
      lcd.setCursor(cont,1);
      lcd.blink();
    }

    if(cont == 1){
      //delay(150);
      hora2++;
      if(hora1 == 2){
        if(hora2 > 4){
          hora2 = 0;
        }
      }
      else{
        if(hora2 > 9){
          hora2 = 0;
        }
      }
      lcd.setCursor(cont,1);
      lcd.print(hora2);
      lcd.setCursor(cont,1);
      lcd.blink();
    }

    if(cont == 3){
      //delay(150);
      minuto1++;
      if(minuto1 >  5){
        minuto1 = 0;
      }
      if(hora1 == 2 && hora2 == 4){
        minuto1 = 0;
      }
      lcd.setCursor(cont,1);
      lcd.print(minuto1);
      lcd.setCursor(cont,1);
      lcd.blink();
    }
    
    if(cont == 4){
      //delay(150);
      minuto2++;
      if(minuto2 >  9){
        minuto2 = 0;
      }
      if(hora1 == 2 && hora2 == 4){
        minuto2 = 0;
      }
      lcd.setCursor(cont,1);
      lcd.print(minuto2);
      lcd.setCursor(cont,1);
      lcd.blink();
    }
    delay(100);
 }
}

 
