//Definición de pines
int pinPulsador = 23; 

void setup(){
Serial.begin(9600);
pinMode(pinPulsador, INPUT); 
}

void loop(){
  
int v_state = digitalRead(pinPulsador); 

if(v_state == HIGH){
Serial.println("Pulsado!"); 
}

delay(100);
}
