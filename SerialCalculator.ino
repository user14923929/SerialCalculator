#include <Arduino.h>
#include <math.h>

void setup() {
    Serial.begin(9600);
    Serial.println("Введите выражение (например, 5+3 или sin(30)):");
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        
        char op;
        float num1 = 0, num2 = 0;
        
        if (input.startsWith("sin(")) {
            num1 = input.substring(4, input.length() - 1).toFloat();
            Serial.print("Результат: ");
            Serial.println(sin(radians(num1)));
        } else if (input.startsWith("cos(")) {
            num1 = input.substring(4, input.length() - 1).toFloat();
            Serial.print("Результат: ");
            Serial.println(cos(radians(num1)));
        } else if (input.startsWith("tan(")) {
            num1 = input.substring(4, input.length() - 1).toFloat();
            Serial.print("Результат: ");
            Serial.println(tan(radians(num1)));
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
                float result;
                
                switch (op) {
                    case '+': result = num1 + num2; break;
                    case '-': result = num1 - num2; break;
                    case '*': result = num1 * num2; break;
                    case '/':
                        if (num2 != 0) result = num1 / num2;
                        else {
                            Serial.println("Ошибка: деление на ноль");
                            return;
                        }
                        break;
                    default:
                        Serial.println("Ошибка: неизвестный оператор");
                        return;
                }
                Serial.print("Результат: ");
                Serial.println(result);
            } else {
                Serial.println("Ошибка: неверный формат ввода");
            }
        }
        Serial.println("Введите новое выражение:");
    }
}
