#define USING_UNIT_CARDKB2
#define USING_I2C_FOR_CARDKB2

#include <M5Unified.h>
#include <M5UnitUnified.h>
#include <M5UnitUnifiedKEYBOARD.h>
#include <M5HAL.hpp>
#include <M5Utility.h>
#include <Wire.h>

m5::unit::UnitUnified Units;
m5::unit::UnitCardKB2 keyboard;

String textBuffer = "";

void drawScreen() {
  M5.Display.fillScreen(TFT_BLACK);

  M5.Display.setTextColor(TFT_GREEN, TFT_BLACK);
  M5.Display.setTextSize(2);
  M5.Display.setCursor(10, 10);
  M5.Display.println("CardKB2 Terminal");

  M5.Display.drawLine(0, 38, 319, 38, TFT_DARKGREY);

  M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Display.setTextSize(2);
  M5.Display.setCursor(10, 55);
  M5.Display.print("> ");

  M5.Display.print(textBuffer);

  M5.Display.print("_");

  M5.Display.setTextSize(1);
  M5.Display.setTextColor(TFT_DARKGREY, TFT_BLACK);
  M5.Display.setCursor(10, 220);
  M5.Display.print("Enter:new line  BS:delete");
}

void setup() {
  Serial.begin(115200);

  auto cfg = M5.config();
  M5.begin(cfg);

  M5.Display.setRotation(1);
  M5.Display.fillScreen(TFT_BLACK);

  // Basic V2.7 Port A
  // SDA = GPIO21
  // SCL = GPIO22
  Wire.end();
  Wire.begin(21, 22, 100000);

  if (!Units.add(keyboard, Wire) || !Units.begin()) {
    M5.Display.fillScreen(TFT_RED);
    M5.Display.setTextColor(TFT_WHITE, TFT_RED);
    M5.Display.setTextSize(2);
    M5.Display.setCursor(10, 40);
    M5.Display.println("CardKB2 ERROR");
    M5.Display.println();
    M5.Display.println("Fn + Sym + 1");
    M5.Display.println("for I2C mode");

    Serial.println("CardKB2 initialization failed");
    while (true) {
      delay(1000);
    }
  }

  Serial.println("CardKB2 ready");
  Serial.printf("Firmware: %02X\n", keyboard.firmwareVersion());

  drawScreen();
}

void loop() {
  M5.update();
  Units.update();

  bool changed = false;

  if (keyboard.updated()) {
    while (keyboard.available()) {
      char c = keyboard.getchar();

      Serial.printf("Key: 0x%02X", (uint8_t)c);

      if (c >= 32 && c <= 126) {
        Serial.printf(" '%c'\n", c);

        textBuffer += c;
        changed = true;
      }
      else if (c == '\b' || c == 0x7F) {
        Serial.println(" Backspace");

        // Backspace / Delete
        if (textBuffer.length() > 0) {
          textBuffer.remove(textBuffer.length() - 1);
          changed = true;
        }
      }
      else if (c == '\r' || c == '\n') {
        Serial.println(" Enter");

        textBuffer += '\n';
        changed = true;
      }
      else {
        Serial.println();
      }

      keyboard.discard();
    }
  }

  if (changed) {
    drawScreen();
  }

  delay(5);
}