/*
   BabyBuddy AI Health Monitor (ESP32)
   Sensors:
   - MAX30102 (AdvancedOximeter) → HR & SpO2
   - SW420 → Vibration detection
   - Doppler Sensor → Breathing / Motion
   - OLED Display (SSD1306 0.96")
   - Neopixel LED + Buzzer
   - AI Mood Detection (TinyML-style)
   - MATLAB serial output
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <AdvancedOximeter.h>

// ---------- Pin Setup ----------
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_ADDR 0x3C
#define NEOPIXEL_PIN 4
#define BUZZER_PIN 15
#define SW420_PIN 34
#define DOPPLER_PIN 35
#define BUTTON_PIN 27

// ---------- Display ----------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------- LED ----------
Adafruit_NeoPixel pixels(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// ---------- Sensors ----------
AdvancedOximeter max30102;

// ---------- Variables ----------
float hr = 0, spo2 = 0;
int vibration = 0;
float dopplerVal = 0;
bool matlabMode = false;

// ---------- Simple AI Mood Function ----------
String detectMood(float hr, float doppler, int vib) {
  if (hr > 120 && doppler > 2000) return "Anxious ";
  if (hr < 60 && doppler < 800) return "Calm ";
  if (vib == 1) return "Disturbed ";
  return "Normal ";
}

// ---------- OLED Helper Function ----------
void showText(int x, int y, String text) {
  display.setCursor(x, y);
  display.println(text);
}

// ---------- Setup ----------
void setup() {
  Serial.begin(115200);
  Wire.begin(OLED_SDA, OLED_SCL);

  pinMode(SW420_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(DOPPLER_PIN, INPUT);

  pixels.begin();
  pixels.clear();
  pixels.show();

  // OLED Initialization
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED not detected!");
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 24);
  display.println("BabyBuddy Initializing...");
  display.display();

  // MAX30102 Initialization
  if (!max30102.begin()) {
    Serial.println("MAX30102 not found!");
    display.clearDisplay();
    display.setCursor(10, 24);
    display.println("MAX30102 Not Found!");
    display.display();
    while (1);
  }

  delay(1500);
  display.clearDisplay();
  display.setCursor(20, 24);
  display.println("BabyBuddy Ready!");
  display.display();
  delay(1000);
}

// ---------- Loop ----------
void loop() {
  // Button toggle for MATLAB mode
  if (digitalRead(BUTTON_PIN) == LOW) {
    matlabMode = !matlabMode;
    delay(400);  // debounce
  }

  // Read all sensors
  vibration = digitalRead(SW420_PIN);
  dopplerVal = analogRead(DOPPLER_PIN);
  max30102.update();
  hr = max30102.getHeartRate();
  spo2 = max30102.getSpO2();

  // AI Mood detection
  String mood = detectMood(hr, dopplerVal, vibration);

  // ---------- OLED Display Update ----------
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  showText(0, 0, matlabMode ? "MATLAB MODE" : "NORMAL MODE");
  showText(0, 14, "HR: " + String(hr, 1) + " bpm");
  showText(0, 26, "SpO2: " + String(spo2, 1) + " %");
  showText(0, 38, "Doppler: " + String(dopplerVal, 0));
  showText(0, 50, "Vib: " + String(vibration) + " Mood: " + mood);
  display.display();

  // ---------- LED & Buzzer Alerts ----------
  if (hr > 130 || hr < 50 || vibration == 1) {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));  // Red alert
    pixels.show();
    tone(BUZZER_PIN, 1000, 200);
  } else {
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));  // Green safe
    pixels.show();
    noTone(BUZZER_PIN);
  }

  // ---------- MATLAB Serial Output ----------
  if (matlabMode) {
    // Send CSV line for MATLAB
    Serial.print(hr); Serial.print(",");
    Serial.print(spo2); Serial.print(",");
    Serial.print(dopplerVal); Serial.print(",");
    Serial.print(vibration); Serial.print(",");
    Serial.println(mood);  // newline guarantees readline() works
  }

  delay(300);
}
