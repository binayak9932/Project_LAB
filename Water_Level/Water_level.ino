#include <WiFi.h>

#define WATER_SENSOR_PIN 34

#define FULL_LED 25
#define MEDIUM_LED 26
#define LOW_LED 27

const char *ssid = "ESP32_WaterSensor";
const char *password = "12345678";

WiFiServer server(80);

String getHTML();



void setup() {
    Serial.begin(115200);
    pinMode(FULL_LED, OUTPUT);
    pinMode(MEDIUM_LED, OUTPUT);
    pinMode(LOW_LED, OUTPUT);
    WiFi.softAP(ssid, password);
    Serial.println("WiFi AP Started");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
    server.begin();
}

void loop() {
    WiFiClient client = server.available();
    if (client) {
        String request = client.readStringUntil('\r');
        client.flush();

        if (request.indexOf("/getLevel") != -1) {
            int sensorValue = analogRead(WATER_SENSOR_PIN);
            String waterLevel = getWaterLevel(sensorValue);

            String jsonResponse = "{\"sensorValue\":" + String(sensorValue) + 
                                  ", \"waterLevel\":\"" + waterLevel + "\"}";

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type: application/json");
            client.println();
            client.println(jsonResponse);
            client.println();
            client.stop();
            return;
        }

        client.println("HTTP/1.1 200 OK");
        client.println("Content-type: text/html");
        client.println();
        client.println(getHTML());
        client.println();
        client.stop();
    }
}

String getWaterLevel(int sensorValue) {
    String level;
    
    if (sensorValue >= 400 && sensorValue <= 1000) {
        level = "FULL";
        digitalWrite(FULL_LED, HIGH);
        digitalWrite(MEDIUM_LED, LOW);
        digitalWrite(LOW_LED, LOW);
    } 
    else if (sensorValue >= 1900 && sensorValue <= 2200) {
        level = "MEDIUM";
        digitalWrite(FULL_LED, LOW);
        digitalWrite(MEDIUM_LED, HIGH);
        digitalWrite(LOW_LED, LOW);
    } 
    else if (sensorValue >= 2300) {
        level = "LOW";
        digitalWrite(FULL_LED, LOW);
        digitalWrite(MEDIUM_LED, LOW);
        digitalWrite(LOW_LED, HIGH);
    } 
    else {
        level = "UNKNOWN";
        digitalWrite(FULL_LED, LOW);
        digitalWrite(MEDIUM_LED, LOW);
        digitalWrite(LOW_LED, LOW);
    }
    return level;
}

String getHTML() {
    return R"rawliteral(
        <!DOCTYPE html>
        <html>
        <head>
            <title>ESP32 Water Level</title>
            <meta name="viewport" content="width=device-width, initial-scale=1">
            <style>
                body { font-family: Arial, sans-serif; text-align: center; margin: 50px; }
                h1 { color: #0275d8; }
                .container { max-width: 400px; margin: auto; padding: 20px; border-radius: 10px; 
                             box-shadow: 0px 0px 10px rgba(0,0,0,0.1); background: #f9f9f9; }
                .level-box { font-size: 24px; padding: 15px; margin-top: 10px; border-radius: 5px; }
                .full { background: #28a745; color: white; }
                .medium { background: #ffc107; color: black; }
                .low { background: #dc3545; color: white; }
                .unknown { background: gray; color: white; }
            </style>
            <script>
                function updateLevel() {
                    fetch('/getLevel')
                    .then(response => response.json())
                    .then(data => {
                        document.getElementById("sensorValue").innerText = "Sensor Value: " + data.sensorValue;
                        let levelBox = document.getElementById("waterLevelBox");
                        levelBox.innerText = "Water Level: " + data.waterLevel;
                        levelBox.className = "level-box " + data.waterLevel.toLowerCase();
                    });
                }
                setInterval(updateLevel, 2000); // Auto-refresh every 2 seconds
            </script>
        </head>
        <body>
            <h1>ESP32 Water Level Monitor</h1>
            <div class="container">
                <p id="sensorValue">Sensor Value: --</p>
                <div id="waterLevelBox" class="level-box unknown">Water Level: --</div>
            </div>
            <p>Auto-updating every 2 seconds...</p>
        </body>
        </html>
    )rawliteral";
}