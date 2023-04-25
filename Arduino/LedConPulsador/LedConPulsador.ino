//Definicion de pines
int pin_entrada = 23; 
int pin_salida = 22;

void setup(){
  pinMode(pin_entrada,INPUT_PULLDOWN); 
  pinMode(pin_salida, OUTPUT);
}

void loop(){
  int v_state = digitalRead(pin_entrada); 

  if(v_state == HIGH){
    digitalWrite(pin_salida, HIGH);
    delay(1000); 
    digitalWrite(pin_salida, LOW);
    delay(1000); 
  }
}
