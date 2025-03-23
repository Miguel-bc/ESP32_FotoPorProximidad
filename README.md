## Proyecto: Captura de Fotos con ESP32-CAM y Sensor Ultrasónico

Este proyecto utiliza una **ESP32-CAM** junto con un **sensor ultrasónico** para capturar fotos cuando un objeto se encuentra dentro de un rango de distancia específico. Las fotos se almacenan en una tarjeta **SD**.

### 🚀 Descripción del Proyecto

La ESP32-CAM toma una foto cuando el sensor ultrasónico detecta un objeto a una distancia entre 10 cm y 20 cm. La imagen se guarda en la tarjeta SD con un nombre único para evitar sobrescribir archivos.

### 📌 Funcionalidades Principales

- **Captura automática de fotos** al detectar un objeto dentro del rango especificado.
- **Almacenamiento en tarjeta SD** con nombres únicos para evitar sobrescritura.
- **Indicador LED** que se enciende al capturar una foto.
- **Medición de distancia** en tiempo real con un sensor ultrasónico HC-SR04.

### 🛠️ Tecnologías Utilizadas

- **ESP32-CAM**: Para capturar y procesar imágenes.
- **SD_MMC**: Para gestionar la tarjeta SD y almacenar las fotos.
- **HC-SR04**: Sensor ultrasónico para medir distancia.
- **Arduino IDE**: Para programar la ESP32-CAM.

### 📷 Capturas de Pantalla

A continuación, se muestra una imagen de referencia del proyecto en acción:

![ESP32-CAM con Sensor Ultrasónico](https://upload.wikimedia.org/wikipedia/commons/6/6a/Esp32_cam.jpg)

### 📌 ¿Cómo Usar?

1. **Sube el código** a la ESP32-CAM utilizando Arduino IDE.
2. **Inserta una tarjeta microSD** en la ESP32-CAM.
3. **Coloca el sensor ultrasónico** y la ESP32-CAM apuntando hacia el área de detección.
4. **Conéctala y abre el monitor serie** para ver la distancia en tiempo real.
5. **Cuando un objeto esté entre 10 cm y 20 cm**, la ESP32-CAM tomará una foto y la guardará en la SD.

### 📌 Conexiones del Hardware

| Componente      | Pin ESP32-CAM |
|---------------|--------------|
| **Trigger (TRIG)** del HC-SR04 | GPIO 33 |
| **Echo (ECHO)** del HC-SR04 | GPIO 32 |
| **LED** | GPIO 2 |

### 📝 Código Fuente

El código del proyecto está disponible en el repositorio [aquí](https://github.com/Miguel-bc/ESP32_FotoPorProximidad).

### 📌 Requisitos

- **ESP32-CAM**
- **Módulo de tarjeta microSD**
- **Sensor ultrasónico HC-SR04**
- **Arduino IDE con soporte para ESP32**

### 📜 Licencia

Este proyecto está bajo la licencia **MIT**, lo que significa que puedes usarlo y modificarlo libremente. 😊
