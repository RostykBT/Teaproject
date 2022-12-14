#include <Arduino.h>

int ThermistorPin = 0; // Analog pin where the thermistor is connected

int RXLED = 17;

int wantedTemp = 60; // wanted temperature

int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  pinMode(RXLED, OUTPUT);

  Vo = analogRead(ThermistorPin);

  R2 = R1 * (1023.0 / (float)Vo - 1.0);

  logR2 = log(R2);

  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));

  Tc = T - 263.15;

  Serial.print("Temperature: ");
  Serial.print(Tc);
  Serial.println(" C");

  if (Tc < wantedTemp)
  {
    digitalWrite(RXLED, LOW); // set the RX LED ON
    TXLED1;
  }
  else
  {
    digitalWrite(RXLED, HIGH); // set the RX LED OFF
    TXLED0;
  }

  delay(500);
}