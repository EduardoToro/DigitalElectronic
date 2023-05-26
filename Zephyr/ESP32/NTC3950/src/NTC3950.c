//#include "NTC3950.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float AdcToCelsius(double adcIn){ 
    //Variables Definition
    double resistanceNTC = (adcIn * R2) / (4095 - adcIn); 
    double logNTC = log(resistanceNTC); 
    double temp = 1 / (A + (B * logNTC) + (C * logNTC * logNTC * logNTC));
    temp = temp - KELVINCONSTANT;

    return temp; 
}

double getTemp(int size){
    
    double sum = 0;
    for(int i =0;i<size;i++){
        double raw_temp = measure();
        double temp = AdcToCelsius(raw_temp);
        sum += temp;
        k_msleep(1/size*1000);
    }
    return sum/size;
}

