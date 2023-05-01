#include <stdio.h>
#include "esp_chip_info.h"

void app_main(void)
{
    esp_chip_info_t chipInfo; 
    esp_chip_info(&chipInfo); 
    printf("Hello World, Im Eduardo\n");
    printf("This is a type %s chip and has %d cores!\n", 
            CONFIG_IDF_TARGET,
            chipInfo.cores);
}
