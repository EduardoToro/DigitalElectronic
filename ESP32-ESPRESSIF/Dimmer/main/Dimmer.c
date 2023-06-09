#include <stdio.h>
#include "string.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "esp_http_server.h"
#include "driver/ledc.h"


int32_t led_r = 0, led_g = 0, led_b = 0; 

#define LEDC_TIMER  LEDC_TIMER_0
#define LEDC_MODE   LEDC_HIGH_SPEED_MODE
#define LEDC_OUTPUT_IO_R (5)
#define LEDC_OUTPUT_IO_G (18)
#define LEDC_OUTPUT_IO_B (19)
#define LEDC_CHANNEL_R LEDC_CHANNEL_0
#define LEDC_CHANNEL_G LEDC_CHANNEL_1
#define LEDC_CHANNEL_B LEDC_CHANNEL_2
#define LEDC_DUTY_RES LEDC_TIMER_8_BIT
#define LEDC_FREQUENCY 5000
#define LEDC_DUTY 0
#define LEDC_HPOINT 0

static esp_err_t api_get_handler(httpd_req_t *req){
    //ip/api?r=0&g=0&b=0
    char* buf; 
    size_t buf_len; 

    buf_len = httpd_req_get_url_query_len(req) + 1;

    if (buf_len > 1)
    {
        buf = malloc(buf_len);
        if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK)
        {
            char param[3]; 
            if (httpd_query_key_value(buf, "r", param, sizeof(param)) == ESP_OK)
            {
                led_r = atoi(param);
                printf("r: %ld\n", led_r); 
            }
            if (httpd_query_key_value(buf, "g", param, sizeof(param)) == ESP_OK)
            {
                led_g = atoi(param);
                printf("g: %ld\n", led_g); 
            }
            if (httpd_query_key_value(buf, "b", param, sizeof(param)) == ESP_OK)
            {
                led_b = atoi(param);
                printf("b: %ld\n", led_b); 
            }
        }
        free(buf); 
    }

    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_R, led_r); 
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_R); 
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_G, led_g); 
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_G);
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_B, led_b); 
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_B);

    httpd_resp_set_hdr(req, "Content-Type", "application/json");

    char res[30]; 
    sprintf(res, "{ \"r\": %ld, \"g\": %ld, \"b\": %ld }", led_r, led_g, led_b);
    httpd_resp_send(req, res, HTTPD_RESP_USE_STRLEN);
    return ESP_OK; 
};

static const httpd_uri_t api = {
    .uri = "/api",
    .method = HTTP_GET,
    .handler = api_get_handler
};

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
    esp_netif_init(); 
    esp_event_loop_create_default(); 

    example_connect(); 

    esp_netif_ip_info_t ip_info; 
    esp_netif_t* netif = NULL;
    netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF"); 

    if (netif == NULL)
    {
        printf("No hay interfaz\n"); 
    }else{
        esp_netif_get_ip_info(netif, &ip_info);
        printf("IP: %d.%d.%d.%d\n", IP2STR(&ip_info.ip)); 

        ledc_timer_config_t ledc_timer = {
            .speed_mode = LEDC_MODE, 
            .timer_num = LEDC_TIMER,
            .duty_resolution = LEDC_DUTY_RES,
            .freq_hz = LEDC_FREQUENCY,
            .clk_cfg = LEDC_AUTO_CLK
        }; 
        ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer)); 

        ledc_channel_config_t ledc_channel_r = {
            .speed_mode = LEDC_MODE,
            .channel = LEDC_CHANNEL_R,
            .timer_sel = LEDC_TIMER,
            .intr_type = LEDC_INTR_DISABLE,
            .gpio_num = LEDC_OUTPUT_IO_R, 
            .duty = LEDC_DUTY,
            .hpoint = LEDC_HPOINT
        }; 
        ledc_channel_config(&ledc_channel_r); 

        ledc_channel_config_t ledc_channel_g = {
            .speed_mode = LEDC_MODE,
            .channel = LEDC_CHANNEL_G,
            .timer_sel = LEDC_TIMER,
            .intr_type = LEDC_INTR_DISABLE,
            .gpio_num = LEDC_OUTPUT_IO_G, 
            .duty = LEDC_DUTY,
            .hpoint = LEDC_HPOINT
        }; 
        ledc_channel_config(&ledc_channel_g); 

        ledc_channel_config_t ledc_channel_b = {
            .speed_mode = LEDC_MODE,
            .channel = LEDC_CHANNEL_B,
            .timer_sel = LEDC_TIMER,
            .intr_type = LEDC_INTR_DISABLE,
            .gpio_num = LEDC_OUTPUT_IO_B, 
            .duty = LEDC_DUTY,
            .hpoint = LEDC_HPOINT
        }; 
        ledc_channel_config(&ledc_channel_b); 

        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_R, led_r); 
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_R); 
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_G, led_g); 
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_G);
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_B, led_b); 
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_B);

        web_server_init(); 
    }
}