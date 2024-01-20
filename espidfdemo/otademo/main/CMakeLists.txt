idf_build_get_property(project_dir PROJECT_DIR)
idf_component_register(
    SRCS "main.c" "chip.c" "spiffs_demo.c" "wifi_sta_demo.c"
    INCLUDE_DIRS ""
    EMBED_TXTFILES ${project_dir}/ca_cert.pem
)