/** 
   EJEMPLO SENCILLO PARA LECTURA DE TEMPERATURA CON TERMISTOR NTC. EL PROGRAMA
   ESTÁ DISENADO PARA TERMISTORES NTC DE 10K NOMINALES A 25 GRADOS CENTIGRADOS.
   EL TERMISTOR DEBE SER CONECTADO A LA ENTRADA DEL ADC MEDIANTE UN ARREGLO DE
   DIVISOR RESISTIVO REALIZADO CON RESISTENCIA DE 10K Y EL TERMISTOR EN SERIE.
   EL ALGORITMO UTILIZADO PARA OBTENER LA TEMPERATURA A PARTIR DE LA RESISTENCIA
   DEL TERMISTOR ES UNA IMPLEMENTACIÓN DE LA ECUACIÓN DE STEINHART-HART
*/

#include <Arduino.h>
#include <math.h>
 
// Configurar el pin utilizado para la medicion de voltaje del divisor resistivo del NTC
#define CONFIG_THERMISTOR_ADC_PIN A0
// configurar el valor de la resistencia que va en serie con el termistor NTC en ohms
#define CONFIG_THERMISTOR_RESISTOR 9900l
 
/**
 * adcval: Valor medido por el convertidor analógico a digital.
 */
int32_t thermistor_get_resistance(uint16_t adcval)
{
  // Calculamos la resistencia del NTC a partir del valor del ADC
  return (CONFIG_THERMISTOR_RESISTOR * ((1023.0 / adcval) - 1));
}
 
/**
 * resistance Resistencia actual del termistor.
 */
float thermistor_get_temperature(int32_t resistance)
{
  // Variable de almacenamiento temporal, evita realizar varias veces el calculo de log
  float temp;
 
  // calculamos logaritmo natural, se almacena en variable para varios calculos
  temp = log(resistance);
 
  temp = 1 / (0.001129148 + (0.000234125 * temp) + (0.0000000876741 * temp * temp * temp));
 
  // Convertir el resultado de kelvin a centigrados y retornar
  return temp - 273.15;
}
 
void setup()
{
  // preparar serial
  Serial.begin(115200);
  while (!Serial);
}
 
void loop()
{
  // Variable para almacenar la temperatura y resistencia
  float temperatura;
  uint32_t resistencia;
 
  // Calcular la resistencia electrica del termistor usando la lectura del ADC
  resistencia = thermistor_get_resistance(analogRead(CONFIG_THERMISTOR_ADC_PIN));
  // Calcular la temperatura segun dicha resistencia
  temperatura = thermistor_get_temperature(resistencia);
 
  Serial.print(F("Resistencia del NTC: "));
  Serial.print(resistencia);
  Serial.print(" Temperatura: ");
  Serial.println(temperatura, 1);
 
  delay(5000);
}
