#include "main.hpp"


unsigned long timerTest = 0;

bool flagStart = false;
bool flarPos = false, flarNeg = false;


/**
 * @brief 
 * 
 */
void setup() 
{
    pinMode(POS_GERCON, INPUT);     digitalWrite(POS_GERCON, HIGH);
    pinMode(NEG_GERCON, INPUT);     digitalWrite(NEG_GERCON, HIGH);

    pinMode(PIN_RELE, OUTPUT);      digitalWrite(PIN_RELE, LOW);

    Serial.begin(BAUNDRATE);

    // Serial.println("OK");
}

/**
 * @brief 
 * 
 */
void loop() 
{
    if(Serial.available())
    {
        delay(20);
        String message = "";
        
        while(Serial.available()) 
        {
            message += char(Serial.read());
            delay(2);
        }

        Serial.println(message);
        
        message.replace(" ","");
        message.replace("\r","");
        message.replace("\n","");
        
        if (message.indexOf("START") > -1)
        {
            // Serial.println("{\"result\":\"OK\"}");

            digitalWrite(PIN_RELE, HIGH);

            timerTest = millis();
            flagStart = true;
        }
    }

    if(flagStart == true && millis() > timerTest + TIME_PRESS)
    {
        digitalWrite(PIN_RELE, LOW);
    }

    if(flagStart == true && millis() < timerTest + TIME_PROC)
    {

        // digitalWrite(PIN_RELE, LOW);


        if(digitalRead(POS_GERCON) == LOW)
        {
            flarPos = true;
        }

        if(digitalRead(NEG_GERCON) == LOW)
        {
            flarNeg = true;
        } 
    }

    if(flagStart == true && millis() >= timerTest + TIME_PROC) 
    {
        String res = "";

        res += "{\"result\":";
        res += flarPos;
        res += flarNeg;
        res += "\"}";

        Serial.println(res);

        flagStart = false;
        flarPos = false;
        flarNeg = false;
    } 
}