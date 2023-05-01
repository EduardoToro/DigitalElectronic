#include <stdio.h>
#include "freertos/FreeRTOS.h"
//Libreria para trabajar con la memoria flash
#include "nvs_flash.h"
//Libreria que contiene todas las funciones disponibles
#include "nvs.h"

void app_main(void)
{
    printf("Start!\n");

    //Inicializar el NVS
    esp_err_t err = nvs_flash_init(); 
    printf("NVS Init\n"); 
    printf((err != ESP_OK) ? "FAILED\n" : "DONE\n");
    
    //Acceder a una partición
    nvs_handle_t my_storage; 
    err = nvs_open("storage", NVS_READWRITE, &my_storage); 
    printf("NVS Open\n"); 
    printf((err != ESP_OK) ? "FAILED\n" : "DONE\n");

    //Escribir en NVS
    err = nvs_set_i32(my_storage, "number", 10); 
    printf("NVS Set\n"); 
    printf((err != ESP_OK) ? "FAILED\n" : "DONE\n");

    //Guardar en NVS
    err = nvs_commit(my_storage);
    printf("NVS Commit\n"); 
    printf((err != ESP_OK) ? "FAILED\n" : "DONE\n");

    //Leer NVS
    int32_t number; 
    err = nvs_get_i32(my_storage, "number", &number); 
    printf("NVS Get\n"); 
    printf((err != ESP_OK) ? "FAILED\n" : "DONE\n");

    //Mostrar datos en consola
    printf("El valor recuperado es: %ld\n", number);

    //Limpiar memoria
    nvs_close(my_storage); 
    printf("End!\n"); 
}
