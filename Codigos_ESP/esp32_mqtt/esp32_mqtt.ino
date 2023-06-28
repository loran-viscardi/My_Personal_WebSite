#include <WiFi.h>
#include "PubSubClient.h"
#include <ArduinoJson.h>

// ### Definições para as conexões ###
const char* ssid = "Seu SSID"; // Nome da Rede Wi-Fi
const char* password = "SuaSenha@123"; // Senha da Rede Wi-Fi
const char* mqttServer = "seu.server.mqtt"; // Local que está o servidor MQTT 
const int mqttPort = 1883; // Porta que está locado o server MQTT
const char* mqttUser = "Seu_Usuario_MQTT"; // Nome de usuário para acessar o serviço MQTT
const char* mqttPassword = "senha_seu_usuario_mqtt"; // Senha do usuário para acessar o serviço MQTT
const char* mqttTopic = "Topico_Publica_MQTT"; // Nome do tópico MQTT (Tanques)
const char* clientId = "ESP32"; // Nome do Client

// ### Define os pinos do MCU ###
const int analogEtanol = 36; // Pino que recebe o Sensor do Tanque de Etanol
const int analogGas = 35; // Pino que recebe o Sensor do Tanque de Gasolina
const int analogDiesel = 34; // Pino que recebe o Sensor do Tanque de Diesel
int lastSensorValueEtanol = 0; 
int lastSensorValueGas = 0;
int lastSensorValueDiesel = 0;
const int ledEtanol = 15;
const int ledGas = 2;
const int ledDiesel = 4;

WiFiClient espClient; // Cria um objeto chamado "espClient"
PubSubClient client(espClient); // Cria um objeto PubSubClient chamado "client" usando "espClient" como parâmetro

// ### Função Setup ###
void setup() {
  // ### Configura os pinos como entrada ou saída ###
  pinMode(ledEtanol, OUTPUT);
  pinMode(ledGas, OUTPUT);
  pinMode(ledDiesel, OUTPUT);

// ### Inicia a comunicação serial ###
  Serial.begin(115200);
// ### Inica a comunicação Wi-Fi, conecta-se a rede ###  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) { // Checa a conexão com a rede
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

// ### Conecta-se ao servidor MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect(clientId, mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT");
      client.subscribe(mqttTopic);
    } else {
      Serial.print("MQTT connection failed, retrying in 5 seconds...");
      delay(5000);
    }
  }
}

// ### Função Loop ###
void loop() {
  client.loop();

   int sensorValueEtanol = analogRead(analogEtanol); // Lê o pino analógico "analogEtanol" e envia o valor para a variável "sensorValueEtanol"
   int sensorValueGas = analogRead(analogGas); // Lê o pino analógico "analogGas" e envia o valor para a variável "sensorValueGas"
   int sensorValueDiesel = analogRead(analogDiesel); //Lê o pino analógico "analogDiesel" e envia o valor para a variável "sensorValueDiesel"

  if ((abs(sensorValueEtanol - lastSensorValueEtanol) >= 100) || (abs(sensorValueGas - lastSensorValueGas) >= 100) || (abs(sensorValueDiesel - lastSensorValueDiesel) >=100))  // Analisa se os sensores tiveram uma variação maior que 10
    {
    lastSensorValueEtanol = sensorValueEtanol;
    lastSensorValueGas = sensorValueGas;
    lastSensorValueDiesel = sensorValueDiesel;
    float valorEtanol=((float)sensorValueEtanol/4095)*10000; // Converte o valor para volume (no caso o tanque possui 10000 L)
    float valorGas = ((float)sensorValueGas/4095)*10000;
    float valorDiesel = ((float)sensorValueDiesel/4095)*10000;
     mqttSendJson(valorEtanol,valorGas, valorDiesel); // Chama a função "mqttSendJson" e envia os valores, para serem enviados em formato JSON ao servidor MQTT
    }

  delay(100);
}


 // ### Função mqttSendJson ###
 // A função envia uma mensagem JSON contendo o valor analógico para o tópico "esp32/out"
void mqttSendJson(float valorEtanol, float valorGas, float valorDiesel){
    //Envia a mensagem ao broker
     /// . produzindo mensagem
    DynamicJsonDocument doc(1024);
    doc["device"] = "ESP32";
    doc["analogicoEtanol"] = valorEtanol;
    doc["analogicoGas"] = valorGas;
    doc["analogicoDiesel"] = valorDiesel;
    char JSONmessageBuffer[200];
    serializeJson(doc, JSONmessageBuffer);
    client.publish("Leitura_ESP32_Sensores", JSONmessageBuffer);
    Serial.print("msg json enviado: ");
    Serial.println(JSONmessageBuffer);
}


// ### Função callback ###
// A função é chamada sempre que uma mensagem é recebida no tópico "Led/Etanol"
// Ela verifica o conteúdo da mensagem e dependo do valor recebido (ON ou OFF), liga ou desliga o Led
void callback(char* topic, byte* payload, unsigned int length) {
  String topicStr = topic;
  if (topicStr.equals("Led/IndicaTanque")) {
    String payloadStr = "";
    for (int i = 0; i < length; i++) {
      payloadStr += (char)payload[i];
    }

    if (payloadStr.equals("onEtanol")) {
      digitalWrite(ledEtanol, HIGH);
    } else if (payloadStr.equals("offEtanol")) {
      digitalWrite(ledEtanol, LOW);
    }

        if (payloadStr.equals("onGas")) {
      digitalWrite(ledGas, HIGH);
    } else if (payloadStr.equals("offGas")) {
      digitalWrite(ledGas, LOW);
    }

            if (payloadStr.equals("onDiesel")) {
      digitalWrite(ledDiesel, HIGH);
    } else if (payloadStr.equals("offDiesel")) {
      digitalWrite(ledDiesel, LOW);
    }
  }

}