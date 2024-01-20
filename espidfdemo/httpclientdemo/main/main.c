#include "esp_http_client.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_tls.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/param.h>
// #include <ctype.h>

#include "chip.h"
#include "spiffs_demo.h"
#include "wifi_sta_demo.h"
#include "main.h"

esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    static char *output_buffer;  // 响应内容缓存
    static int output_len;       // 响应内容长度
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            // ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
            printf("HTTP_EVENT_ERROR\n");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            // ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
            printf("============================================\n");
            printf("HTTP_EVENT_ON_CONNECTED\n");
            break;
        case HTTP_EVENT_HEADER_SENT:
            // ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
            printf("HTTP_EVENT_HEADER_SENT\n");
            break;
        case HTTP_EVENT_ON_HEADER:
            // ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            printf("HTTP_EVENT_ON_HEADER, key=%s, value=%s\n", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            // ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            printf("HTTP_EVENT_ON_DATA, len=%d\n", evt->data_len);
            // 在新请求时清除缓存
            if (output_len == 0 && evt->user_data) {
                memset(evt->user_data, 0, MAX_HTTP_OUTPUT_BUFFER);
            }
            /*
             *  Check for chunked encoding is added as the URL for chunked encoding used in this example returns binary data.
             *  However, event handler can also be used in case chunked encoding is used.
             */
            if (!esp_http_client_is_chunked_response(evt->client)) {
                // If user_data buffer is configured, copy the response into the buffer
                int copy_len = 0;
                if (evt->user_data) {
                    // The last byte in evt->user_data is kept for the NULL character in case of out-of-bound access.
                    copy_len = MIN(evt->data_len, (MAX_HTTP_OUTPUT_BUFFER - output_len));
                    if (copy_len) {
                        memcpy(evt->user_data + output_len, evt->data, copy_len);
                    }
                } else {
                    int content_len = esp_http_client_get_content_length(evt->client);
                    if (output_buffer == NULL) {
                        // We initialize output_buffer with 0 because it is used by strlen() and similar functions therefore should be null terminated.
                        output_buffer = (char *) calloc(content_len + 1, sizeof(char));
                        output_len = 0;
                        if (output_buffer == NULL) {
                            // ESP_LOGE(TAG, "Failed to allocate memory for output buffer");
                            printf("Failed to allocate memory for output buffer\n");
                            return ESP_FAIL;
                        }
                    }
                    copy_len = MIN(evt->data_len, (content_len - output_len));
                    if (copy_len) {
                        memcpy(output_buffer + output_len, evt->data, copy_len);
                    }
                }
                output_len += copy_len;
            }

            break;
        case HTTP_EVENT_ON_FINISH:
            // ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
            printf("HTTP_EVENT_ON_FINISH\n");
            if (output_buffer != NULL) {
                // Response is accumulated in output_buffer. Uncomment the below line to print the accumulated response
                // ESP_LOG_BUFFER_HEX(TAG, output_buffer, output_len);
                free(output_buffer);
                output_buffer = NULL;
            }
            output_len = 0;
            break;
        case HTTP_EVENT_DISCONNECTED:
            // ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            printf("HTTP_EVENT_DISCONNECTED\n");
            int mbedtls_err = 0;
            esp_err_t err = esp_tls_get_and_clear_last_error((esp_tls_error_handle_t)evt->data, &mbedtls_err, NULL);
            if (err != 0) {
                // ESP_LOGI(TAG, "Last esp error code: 0x%x", err);
                printf("Last esp error code: 0x%x\n", err);
                // ESP_LOGI(TAG, "Last mbedtls failure: 0x%x", mbedtls_err);
                printf("Last mbedtls failure: 0x%x\n", mbedtls_err);
            }
            if (output_buffer != NULL) {
                free(output_buffer);
                output_buffer = NULL;
            }
            output_len = 0;
            printf("============================================\n");
            break;
        case HTTP_EVENT_REDIRECT:
            // ESP_LOGD(TAG, "HTTP_EVENT_REDIRECT");
            printf("HTTP_EVENT_REDIRECT\n");
            esp_http_client_set_header(evt->client, "From", "user@example.com");
            esp_http_client_set_header(evt->client, "Accept", "text/html");
            esp_http_client_set_redirection(evt->client);
            break;
    }
    return ESP_OK;
}

static void http_rest_with_url(void)
{
    // 设置缓存块，多出一字节 是 c 字符串结尾。
    char local_response_buffer[MAX_HTTP_OUTPUT_BUFFER + 1] = {0};
    /**
     * NOTE: All the configuration parameters for http_client must be spefied either in URL or as host and path parameters.
     * If host and path parameters are not set, query parameter will be ignored. In such cases,
     * query parameter should be specified in URL.
     *
     * If URL as well as host and path parameters are specified, values of host and path will be considered.
     */
     char target_url[512];

    esp_http_client_config_t config = {
        .host = CONFIG_EXAMPLE_HTTP_ENDPOINT,
        .port = CONFIG_EXAMPLE_HTTP_PORT,
        .path = "/get",
        .query = "esp",
        .event_handler = _http_event_handler,
        .user_data = local_response_buffer,        // Pass address of local buffer to get response
        .disable_auto_redirect = true,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);

    // GET
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        // ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %"PRId64,
        printf("HTTP GET Status = %d, content_length = %"PRId64"\n",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        // ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
        printf("HTTP GET request failed: %s\n", esp_err_to_name(err));
    }
    // ESP_LOG_BUFFER_HEX(TAG, local_response_buffer, strlen(local_response_buffer));
    printf(local_response_buffer, strlen(local_response_buffer));

    // POST
    const char *post_data = "{\"field1\":\"value1\"}";
    sprintf(target_url, "http://%s:%d/%s", CONFIG_EXAMPLE_HTTP_ENDPOINT, CONFIG_EXAMPLE_HTTP_PORT, "post");
    esp_http_client_set_url(client, target_url);
    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_post_field(client, post_data, strlen(post_data));
    err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        // ESP_LOGI(TAG, "HTTP POST Status = %d, content_length = %"PRId64,
        printf("HTTP POST Status = %d, content_length = %"PRId64"\n",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        // ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
        printf("HTTP POST request failed: %s\n", esp_err_to_name(err));
    }

    //PUT
    sprintf(target_url, "http://%s:%d/%s", CONFIG_EXAMPLE_HTTP_ENDPOINT, CONFIG_EXAMPLE_HTTP_PORT, "put");
    esp_http_client_set_url(client, target_url);
    esp_http_client_set_method(client, HTTP_METHOD_PUT);
    err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        // ESP_LOGI(TAG, "HTTP PUT Status = %d, content_length = %"PRId64,
        printf("HTTP PUT Status = %d, content_length = %"PRId64"\n",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        // ESP_LOGE(TAG, "HTTP PUT request failed: %s", esp_err_to_name(err));
        printf("HTTP PUT request failed: %s\n", esp_err_to_name(err));
    }

    //PATCH
    sprintf(target_url, "http://%s:%d/%s", CONFIG_EXAMPLE_HTTP_ENDPOINT, CONFIG_EXAMPLE_HTTP_PORT, "patch");
    esp_http_client_set_url(client, target_url);
    esp_http_client_set_method(client, HTTP_METHOD_PATCH);
    esp_http_client_set_post_field(client, NULL, 0);
    err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        // ESP_LOGI(TAG, "HTTP PATCH Status = %d, content_length = %"PRId64,
        printf("HTTP PATCH Status = %d, content_length = %"PRId64"\n",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        // ESP_LOGE(TAG, "HTTP PATCH request failed: %s", esp_err_to_name(err));
        printf("HTTP PATCH request failed: %s\n", esp_err_to_name(err));
    }

    //DELETE
    sprintf(target_url, "http://%s:%d/%s", CONFIG_EXAMPLE_HTTP_ENDPOINT, CONFIG_EXAMPLE_HTTP_PORT, "delete");
    esp_http_client_set_url(client, target_url);
    esp_http_client_set_method(client, HTTP_METHOD_DELETE);
    err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        // ESP_LOGI(TAG, "HTTP DELETE Status = %d, content_length = %"PRId64,
        printf("HTTP DELETE Status = %d, content_length = %"PRId64"\n",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        // ESP_LOGE(TAG, "HTTP DELETE request failed: %s", esp_err_to_name(err));
        printf("HTTP DELETE request failed: %s\n", esp_err_to_name(err));
    }

    //HEAD
    sprintf(target_url, "http://%s:%d/%s", CONFIG_EXAMPLE_HTTP_ENDPOINT, CONFIG_EXAMPLE_HTTP_PORT, "get");
    esp_http_client_set_url(client, target_url);
    esp_http_client_set_method(client, HTTP_METHOD_HEAD);
    err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        // ESP_LOGI(TAG, "HTTP HEAD Status = %d, content_length = %"PRId64,
        printf("HTTP HEAD Status = %d, content_length = %"PRId64"\n",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        // ESP_LOGE(TAG, "HTTP HEAD request failed: %s", esp_err_to_name(err));
        printf("HTTP HEAD request failed: %s\n", esp_err_to_name(err));
    }
    printf("============================================\n");

    esp_http_client_cleanup(client);
}

static void http_test_task(void *pvParameters)
{
    http_rest_with_url();
//     http_rest_with_hostname_path();
// #if CONFIG_ESP_HTTP_CLIENT_ENABLE_BASIC_AUTH
//     http_auth_basic();
//     http_auth_basic_redirect();
// #endif
// #if CONFIG_ESP_HTTP_CLIENT_ENABLE_DIGEST_AUTH
//     http_auth_digest_md5();
//     http_auth_digest_sha256();
// #endif
//     http_encoded_query();
//     http_relative_redirect();
//     http_absolute_redirect();
//     http_absolute_redirect_manual();
// #if CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
//     https_with_url();
// #endif
//     https_with_hostname_path();
//     http_redirect_to_https();
//     http_download_chunk();
//     http_perform_as_stream_reader();
//     https_async();
//     https_with_invalid_url();
//     http_native_request();
// #if CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
//     http_partial_download();
// #endif

    // ESP_LOGI(TAG, "Finish http example");
    printf("Finish http example\n");
#if !CONFIG_IDF_TARGET_LINUX
    vTaskDelete(NULL);
#endif
}

void app_main(void) {
  printf("http client example app_main start\n");
  init_nvc_demo();
  printf("NVS ok.\n");

  init_wifi_sta_demo();
  printf("Wifi Connect.\n");

  xTaskCreate(&http_test_task, "http_test_task", 8192, NULL, 5, NULL);
  printf("http  client test start.\n");

  print_chip_info();
  spiffs_action();
  // wait_s_restart(10);
}