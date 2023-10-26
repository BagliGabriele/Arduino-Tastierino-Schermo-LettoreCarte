#include <avr/wdt.h>

const int portaIngresso = 10;
unsigned long startTime = 0;
double tempoDiVolo = 0;
double altezzaSalto = 0;
boolean timerIniziato = false;

int input_analogico = A0;
int sensorValue=0;
int peso = 0;
int misura = 0;
int potenza = 0;

void setup() {
  //wdt_enable(WDTO_8S);
  pinMode(portaIngresso, INPUT);
  Serial.begin(9600);
  Serial.println("Start");
}

void loop () {

  if (misura==0){
    for (int indice = 1; indice <= 30; indice = indice+1) {
      sensorValue = analogRead(input_analogico);
      peso=sensorValue/8;
      
      if (indice < 10) { //Index test
        Serial.print("0");
      }
      Serial.print(indice);
      Serial.print(" - ");
      
      Serial.println(peso);
    
      delay(200);
      misura=misura+1;
    }

    Serial.println("Pronto per saltare");
  }

  int livelloLogicoIngresso = digitalRead(portaIngresso);

  if (livelloLogicoIngresso == LOW && !timerIniziato) {
    startTime = millis();
    timerIniziato = true;
    Serial.println("Il salto è iniziato");
    delay(200);
  }

  if (timerIniziato && livelloLogicoIngresso == HIGH) {
    unsigned long tempoAttuale = millis();
    tempoDiVolo = tempoAttuale - startTime;

    if (tempoDiVolo > 2000) {
      wdt_disable();

      asm volatile (" jmp 0");
    }

    wdt_reset();
    
    Serial.println("atterrato");
    tempoDiVolo = tempoDiVolo/1000;
    Serial.print("secondi in volo: ");
    Serial.print(tempoDiVolo);
    Serial.println(" secondi");
    altezzaSalto = 0.5 * 9.81 * (tempoDiVolo * tempoDiVolo) / 4;
    Serial.print("metri saltati: ");
    Serial.print(altezzaSalto);
    Serial.println(" metri");
    potenza = peso * 9.81 * altezzaSalto / tempoDiVolo;
    Serial.print("potenza di salto: ");
    Serial.print(potenza);
    Serial.println(" Watt");
    Serial.println("-------------------------");
    timerIniziato = false;
  }
}
