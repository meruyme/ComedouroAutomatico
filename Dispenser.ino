
#include <TimeAlarms.h>
#include <Time.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#define BotaoControlarComida A0
#define BotaoConfirma A1
#define BotaoAumenta A2


Servo servo1; Servo servo2; Servo servo3;
LiquidCrystal lcd(12,11,5,4,3,2);
int minuto1= 0, minuto2 = 0, minuto = 0;
int hora1 = 0, hora2 = 0, hora = 0;
int conversao_minuto = 0;                                
int horatotal = 0;
int EstadoBotaoConfirma = 0;
int EstadoBotaoAumenta = 0;
int EstadoBotaoControlarComida = 0;
int cont = 0;
int AlarmID;
int segundos = 0;
int milisegundos_final = 0;
int cont2 = 0;
int contador_hora = 0, contador_minuto = 0;

void setup(){
 lcd.begin(16, 2);
 iniciarCadastro();
 Serial.begin(9600);
 servo1.attach(7); 
 servo2.attach(13);
 servo3.attach(8);
}

void loop(){
  setTempo();
  cadastrarQuantidadeComida();
      
        if(cont2 == 3 && cont == 5){
            cronometro();
        }
        
 Alarm.delay(400); 
}


void colocarComida() {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Colocando comida");
    servo1.write(10);
    for(int i=(milisegundos_final/1000);i>0;i--){
        servo2.write(180);delay(500);servo2.write(0);
        servo3.write(180);delay(500);servo3.write(0);
    }
    servo1.write(80);
    lcd.clear();
    Alarm.delay(1000);
}

void cronometro(){
  lcd.clear();
  lcd.setCursor(0,0);
  contador_hora = hora;
  contador_minuto = minuto;
  int contador_segundo;

  delay(1000);
  lcd.print("   CRONOMETRO:  ");
  if(contador_segundo == 0){
    contador_minuto--;
    contador_segundo = 59;
  }
  if(contador_minuto<0){
      contador_hora--;
      contador_minuto = 59;
    }
  for(int y = 0; y<contador_segundo; y--){
    
    if(contador_hora<10){
      lcd.setCursor(4,1);
      lcd.print("0");
      lcd.print(contador_hora);
      lcd.print(":");
    }
    else{
      
      lcd.setCursor(4,1);
      lcd.print(contador_hora);
      lcd.print(":");
    }
    if(contador_minuto<10){
      
      lcd.print("0");
      lcd.print(contador_minuto);
      lcd.print(":");
    }
    else{
      
      lcd.print(contador_minuto);
      lcd.print(":");
    }
    if(contador_segundo < 10){
      
      lcd.print("0");
      lcd.print(contador_segundo);
      lcd.noBlink();
    }
    else{ 
      lcd.print(contador_segundo);
      lcd.noBlink();
    }
    contador_segundo--;
    if(contador_segundo<0){
      contador_minuto--;
      contador_segundo=59;
    }
    if(contador_minuto<0){
      contador_hora--;
      contador_minuto = 59;
    }
    delay(1000);

    if(digitalRead(BotaoConfirma) == HIGH){
      iniciarCadastro();
      Alarm.disable(AlarmID);
      break;
    }

    if((contador_minuto<=0) && (contador_hora<=0) && (contador_segundo <= 0)) {
      lcd.clear();

      break; 
     }
  }
        
}

void iniciarCadastro(){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Tempo:");
      lcd.setCursor(0,1);
      lcd.print("00:00");
      lcd.setCursor(0,1);
      lcd.blink();
      servo1.write(80);
      cont = 0; segundos = 0; cont2 = 0;
      hora1 = 0; hora2 = 0; minuto1 = 0; minuto2 = 0;
}


void setTempo(){
  EstadoBotaoControlarComida = digitalRead(BotaoControlarComida);
  EstadoBotaoAumenta = digitalRead(BotaoAumenta);
  EstadoBotaoConfirma = digitalRead(BotaoConfirma);
  
  if(EstadoBotaoConfirma == HIGH){
    
    if(cont == 1){
      cont = cont+2;
      lcd.setCursor(cont,1); lcd.blink();
    }
    else if(cont == 0 || cont > 1){
      cont++;
      lcd.setCursor(cont,1); lcd.blink();
    }
    
    if(cont == 5){

      if(hora1 == 0 && hora2 == 0 && minuto1 == 0 && minuto2==0){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ERRO: Informe um");
        lcd.setCursor(0,1);
        lcd.print("valor antes.");
        lcd.noBlink();
        delay(5000);
        cont++;
      }
      else{
      conversao_minuto = (hora1*600)+(hora2*60)+(minuto1*10)+minuto2;
      minuto = (minuto1*10)+minuto2;
      hora = (hora1*10)+hora2;
      horatotal = conversao_minuto*60;

      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Tempo de abertu-");
      lcd.setCursor(0,1);
      lcd.print("ra: ");
      lcd.setCursor(4,1);
      lcd.noBlink();
      }
    }
    
    
    if(cont>5){
        iniciarCadastro();
        Alarm.disable(AlarmID);
    }

    delay(100);
    
  }
  
  if (EstadoBotaoAumenta == HIGH){
    if(cont == 0){
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

void cadastrarQuantidadeComida(){
  EstadoBotaoControlarComida = digitalRead(BotaoControlarComida);

      if(EstadoBotaoControlarComida == HIGH && cont == 5){
          cont2++;
      }

         if(cont2==1 && cont == 5){
            Serial.print("Entrou em controlar comida");
            servo1.write(10);
            segundos++;
            lcd.setCursor(4,1);
            lcd.print(segundos);
            lcd.print("s");
            servo2.write(180);delay(350);servo2.write(0);
            servo3.write(180);delay(350);servo3.write(0);
        }

        if(cont2 == 2 && cont == 5){
         servo1.write(80);
         milisegundos_final = segundos*1000;
         
         AlarmID = Alarm.timerRepeat(horatotal,colocarComida);
         cont2 = 3;
         lcd.clear();
         
        }
}
