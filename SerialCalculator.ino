// Thanks ChatGPT for code

#include <Arduino.h>
#include <math.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Calculator");
    Serial.println("Enter an expression (e.g., 5+3 or sin(30)):");
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        
        char op;
        float num1 = 0, num2 = 0, result = 0;
        
        if (input.startsWith("sin(")) {
            num1 = input.substring(4, input.length() - 1).toFloat();
            result = sin(radians(num1));
        } else if (input.startsWith("cos(")) {
            num1 = input.substring(4, input.length() - 1).toFloat();
            result = cos(radians(num1));
        } else if (input.startsWith("tan(")) {
            num1 = input.substring(4, input.length() - 1).toFloat();
            result = tan(radians(num1));
        } else {
            int opIndex = -1;
            for (int i = 0; i < input.length(); i++) {
                if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
                    op = input[i];
                    opIndex = i;
                    break;
                }
            }
            
            if (opIndex != -1) {
                num1 = input.substring(0, opIndex).toFloat();
                num2 = input.substring(opIndex + 1).toFloat();
                
                switch (op) {
                    case '+': result = num1 + num2; break;
                    case '-': result = num1 - num2; break;
                    case '*': result = num1 * num2; break;
                    case '/':
                        if (num2 != 0) result = num1 / num2;
                        else {
                            Serial.println("Error: Division by zero");
                            lcd.clear();
                            lcd.setCursor(0, 0);
                            lcd.print("Division error");
                            return;
                        }
                        break;
                    default:
                        Serial.println("Error: Unknown operator");
                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print("Unknown operator");
                        return;
                }
            } else {
                Serial.println("Error: Invalid input format");
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Invalid input");
                return;
            }
        }
        Serial.println("Result on screen");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Result:");
        lcd.setCursor(0, 1);
        lcd.print(result);
        Serial.println("Enter a new expression:");
    }
}
