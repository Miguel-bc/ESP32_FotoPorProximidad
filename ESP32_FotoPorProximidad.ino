#include "esp_camera.h"
#include "FS.h"                // Sistema de archivos
#include "SD_MMC.h"            // Tarjeta SD

// Select camera model
#define CAMERA_MODEL_WROVER_KIT 
#include "camera_pins.h"

// Define pins EPS32
#define LED 2
#define trigPin 33
#define echoPin 32

// Define Ultrasonic
#define MAX_DISTANCE 700 
float timeOut = MAX_DISTANCE * 60; 
int soundVelocity = 340; 

// Definir variables

int photoCount = 0;

void setup() {

  pinMode(LED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println("\nInicializando cámara...");

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // Si tiene PSRAM, usa alta resolución
  if (psramFound()) {
    config.frame_size = FRAMESIZE_UXGA; 
    config.jpeg_quality = 10;
    config.fb_count = 2;
    Serial.println("PSRAM detectada ✅");
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
    Serial.println("PSRAM NO detectada ❌");
  }

  // Inicializar la cámara
  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("Error al iniciar la cámara");
    return;
  }
  Serial.println("Cámara inicializada correctamente");

  // Código de inicialización de la tarjeta SD

  Serial.println("\nInicializando tarjeta SD...");
  if (!SD_MMC.begin("/sdcard", true)) { 
    Serial.println("Error al inicializar la tarjeta SD ❌");
    return;
  }
  Serial.println("Tarjeta SD inicializada correctamente ✅");
}

String getFileName() {
  photoCount++;
  return "/foto_" + String(photoCount) + ".jpg";
}

void tomarFoto() {
  Serial.println("Tomando foto...");
  camera_fb_t * fb = esp_camera_fb_get(); // Capturar imagen

  if (!fb) {
    Serial.println("Error al capturar la foto");
    return;
  }

  Serial.printf("Foto capturada, tamaño: %zu bytes\n", fb->len);

  digitalWrite(LED, HIGH);
  delay(3000);
  digitalWrite(LED, LOW);
  delay(3000);
  
  // Guardar la imagen en la tarjeta SD

  File file = SD_MMC.open(getFileName(), FILE_WRITE);
  if (!file) {
    Serial.println("Error al crear el archivo");
  } else {
    file.write(fb->buf, fb->len);
    Serial.println("Foto guardada correctamente");
  }
  
  file.close();
  esp_camera_fb_return(fb); // Liberar memoria
}

float getSonar(){
  unsigned long pingTime;
  float distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pingTime = pulseInLong(echoPin, HIGH, timeOut);  
  distance = (float)pingTime * soundVelocity / 2 / 10000; 
  return distance;
}

void loop() {
  float distanciamedida;
  distanciamedida = getSonar();
  delay(100);  
  Serial.printf("Distance: ");    
  Serial.print(distanciamedida);  
  Serial.println("cm");  
  if (distanciamedida > 10 && distanciamedida < 20) {     
    tomarFoto();
    delay(1000);
    Serial.println("Foto Tomada");
  }  
}
