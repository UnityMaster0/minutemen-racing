#include <Arduino.h>

#define AFR_POS_PIN A0
#define AFR_NEG_PIN A1

#define RPM_PIN A2

#define TPS_PIN A3

#define IPS_PIN A4

long readVcc()
{
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);

  delay(2);                         // Wait for Vref to settle
  ADCSRA |= _BV(ADSC);              // Start conversion
  while (bit_is_set(ADCSRA, ADSC)); // Wait for conversion to complete

  long result = ADC;
  result = 1125300L / result;       // Calculate Vcc (in mV); 1125300 = 1.1 * 1023 * 1000
  return result;
}

void setup()
{
  Serial.begin(115200);
  Serial.println("");
}

void loop()
{
  if (Serial.available() > 0)
  {
    char command = Serial.read();

    if (command == 'd')
    {
      Serial.print(analogRead(AFR_POS_PIN) - analogRead(AFR_NEG_PIN));
      Serial.print(",");
      Serial.print(analogRead(RPM_PIN));
      Serial.print(",");
      Serial.print(analogRead(TPS_PIN));
      Serial.print(",");
      Serial.println(analogRead(IPS_PIN));
    }

    else if (command == 'v')
    {
      Serial.println(readVcc());
    }
  }
  Serial.println("Testing");
}