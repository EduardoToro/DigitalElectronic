#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "esp_http_server.h"

static esp_err_t api_get_handler(httpd_req_t *req){
    httpd_resp_send(req, "Hello World", HTTPD_RESP_USE_STRLEN);
    return ESP_OK; 
};

//Configuración para las URI
static const httpd_uri_t api = {
    .uri = "/api",
    .method = HTTP_GET,
    .handler = api_get_handler
};

//Inicializacion del servidor
void web_server_init(){
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_register_uri_handler(server, &api); 
        return; 
    }
    printf("Error al iniciar el servidor\n");
};

void app_main(void)
{
    nvs_flash_init(); 

    //Inicilizar la interfaz de red para wifi
    esp_netif_init(); 

    //Se crea el event loop para los procesos de conexión
    esp_event_loop_create_default(); 

    example_connect(); 

    //Obtener la información de la dirección IP asignada
    esp_netif_ip_info_t ip_info; 
    esp_netif_t* netif = NULL;
    netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF"); 

    if (netif == NULL)
    {
        printf("No hay interfaz\n"); 
    }else{
        esp_netif_get_ip_info(netif, &ip_info);
        printf("IP: %d.%d.%d.%d\n", IP2STR(&ip_info.ip)); 

        web_server_init(); 
    }
}