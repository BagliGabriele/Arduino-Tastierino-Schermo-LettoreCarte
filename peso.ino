int input_analogico = A0;    // select the input pin for the potentiometer
int sensorValue=0;
int peso = 0;
int misura=0;
void setup() {
  Serial.begin(9600);
}

void loop() {

  if (misura==0){
  for (int indice = 1; indice <= 150; indice = indice+1) {
    sensorValue = analogRead(input_analogico);
    peso=sensorValue/8;
   // Serial.println(indice);
    Serial.println(peso);
  
    delay(100);
    misura=misura+1;
   // break;
  }
}

    Serial.println("\f");
    //Serial.println("stop");
    //delay(100);

}
