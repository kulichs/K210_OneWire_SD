#include <Arduino.h>
#include <OneWire.h> // Má upravena knihovna pro K210
#include <DallasTemperature.h>

// Určíme na kterem pinu je připojena OneWire sběrnice - tady na pinu 30
#define ONE_WIRE_BUS 30

//Nastaví oneWire pro komunikaci s jakýmkoli zařízením na OneWire
OneWire oneWire(ONE_WIRE_BUS);

//Předame na knihovnu Dallas Temperature
DallasTemperature sensors(&oneWire);

int pocetZarizeni; //Počet nalezenych čidel

DeviceAddress adresaZarizeni  //Adresa nalezeného čidla

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
