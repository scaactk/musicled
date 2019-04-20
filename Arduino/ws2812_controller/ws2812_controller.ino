/*
 * 参考资料:https://github.com/scottlawsonbc/audio-reactive-led-strip
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include <WiFiUdp.h>
#include "ws2812_i2s.h"

#define NUM_LEDS 120 //LED灯数量

#define BUFFER_LEN 1024

#define PRINT_FPS 1


const char* ssid     = "319a"; //WIFI SSID  //只支持2.4g，wifi，，，大坑。。。。。
const char* password = "319319ws.."; //passwords
unsigned int localPort = 7777;
char packetBuffer[BUFFER_LEN];


static WS2812 ledstrip;
static Pixel_t pixels[NUM_LEDS];
WiFiUDP port;


IPAddress ip(192, 168, 2, 150); //esp8266的ip地址

IPAddress gateway(192, 168, 2, 1); //网关

IPAddress subnet(255, 255, 255, 0); //子网掩码
void setup() {
    Serial.begin(115200);
    WiFi.config(ip, gateway, subnet);
    WiFi.begin(ssid, password);
    Serial.println("");
    // Connect to wifi and print the IP address over serial
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    port.begin(localPort);
    ledstrip.init(NUM_LEDS);
}

uint8_t N = 0;
#if PRINT_FPS
    uint16_t fpsCounter = 0;
    uint32_t secondTimer = 0;
#endif

void loop() {
    // Read data over socket
    int packetSize = port.parsePacket();
    // If packets have been received, interpret the command
    if (packetSize) {
        int len = port.read(packetBuffer, BUFFER_LEN);
        for(int i = 0; i < len; i+=4) {
            packetBuffer[len] = 0;
            N = packetBuffer[i];
            pixels[N].R = (uint8_t)packetBuffer[i+1];
            pixels[N].G = (uint8_t)packetBuffer[i+2];
            pixels[N].B = (uint8_t)packetBuffer[i+3];
        } 
        ledstrip.show(pixels);
        #if PRINT_FPS
            fpsCounter++;
        #endif
    }
    #if PRINT_FPS
        if (millis() - secondTimer >= 1000U) {
            secondTimer = millis();
            Serial.printf("FPS: %d\n", fpsCounter);
            fpsCounter = 0;
        }   
    #endif
}
