#include <Arduino.h>
//#include <main.h>

// bool led_builtin_was_on = false;
/*
void blink_builtin_led(int ms)
{
    unsigned long startMillis = 0;
    int ledState = LOW;
    unsigned long cM = millis();
    if (cM - startMillis >= ms)
    {
        digitalWrite(LED_BUILTIN, ledState); // turn the LED on (HIGH is the voltage level)

        if (ledState == LOW){ 
            ledState = HIGH;
            }
        else{ 
            ledState = LOW;
            }
        startMillis = millis();
    }
}
*/

void blink_builtin_led_delay(int ms)
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(ms);
    digitalWrite(LED_BUILTIN, LOW);
    delay(ms);
}

void setupLED() {
    pinMode(LED_BUILTIN, OUTPUT);
}

// void loopLED() {
//     // placeholder for code consistency
// }
