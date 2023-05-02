# ESP32-CAM servidor web para la captura de imágenes

Este proyecto utiliza el módulo ESP32-CAM para capturar imágenes y transmitirlas a través de un servidor web. Para ello, se utilizan las librerías esp32cam y WebServer.

## Configuración

Antes de utilizar el proyecto, es necesario crear un archivo 'credentials.h' en la carpeta 'esp32cam-web-server' y configurar las credenciales para conectarse a una red Wi-Fi.

```C++
// WiFi credentials
#define WIFI_SSID         "SSID_EXAMPLE"
#define WIFI_PASSWORD     "12345678"
```

Debe configurar la variable 'WIFI_SSID' con el nombre de su red Wi-Fi y la variable 'WIFI_PASSWORD' con la contraseña correspondiente.

## Uso

Una vez que se han configurado las credenciales de Wi-Fi, puede cargar el código en el ESP32-CAM y conectarlo a una fuente de alimentación. Luego, el módulo comenzará a capturar imágenes automáticamente.

Para acceder a las imágenes, debe ingresar la dirección IP del módulo en un navegador web. La dirección IP se muestra en la consola serial después de que el ESP32-CAM se conecta a la red Wi-Fi.

## Dependencias

Este proyecto utiliza las siguientes librerías:

- esp32cam: https://github.com/yoursunny/esp32cam
- WebServer: https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer

## Créditos

Este proyecto utiliza la librería [esp32cam](https://github.com/yoursunny/esp32cam) y [WebServer](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer). Además, se inspira en el tutorial de [How2electronics](https://how2electronics.com/color-detection-tracking-with-esp32-cam-opencv/#Source_CodeProgram_for_ESP32_CAM_Module).
