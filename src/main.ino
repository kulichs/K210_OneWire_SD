#include <Arduino.h>
#include <OneWire.h> // Má upravena knihovna pro K210
#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>

File soubor;
// Určíme na kterem pinu je připojena OneWire sběrnice
#define ONE_WIRE_BUS 9

//Nastaví oneWire pro komunikaci s jakýmkoli zařízením na OneWire
OneWire oneWire(ONE_WIRE_BUS);

//Předame na knihovnu Dallas Temperature
DallasTemperature sensors(&oneWire);

int pocetZarizeni; //Počet nalezenych čidel

DeviceAddress adresaZarizeni;  //Adresa nalezeného čidla

// Funkce pro výpis adresy zařízení
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}

// Funkce pro výpis adresy zařízení do souboru
void souborAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
      soubor.print(deviceAddress[i], HEX);
  }
}

void setup() {
  //Spuštění serial portu a nastaveni rychlosti komunikace
  Serial.begin(9600);
  //Spuštění SD knihovny
  Serial.print("Inicalizuji SD kartu...");

  if (!SD.begin(29)) {
    Serial.println("inicializace se nepovedla!");
    while (1);
  }
  Serial.println("inicializace hotova.");
  //Spuštění knihovny DallasTemperature
  sensors.begin();
  //Počet zařízení na sběrnici
  pocetZarizeni = sensors.getDeviceCount();
  // Nalezenych zařízení na sběrnici
  Serial.println("Hledám zařízení...");
  Serial.print("Nalezeno ");
  Serial.print(pocetZarizeni, DEC);
  Serial.println(" zařízení.");

  // Smyčka pro prochazení zařízení a vypíše jejich adresu
  for(int i=0;i<pocetZarizeni; i++) {
    // Hledám adresu
    if(sensors.getAddress(adresaZarizeni, i)) {
      Serial.print("Nalezeno zařízení  ");
      Serial.print(i, DEC);
      Serial.print(" s adresou: ");
      printAddress(adresaZarizeni);
      Serial.println();
    } else {
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }
  }
}

void loop() {
  sensors.requestTemperatures(); // Pošleme příkaz pro získaní teploty
  // Procházím zařízení a ypisuji teplotu
for(int i=0;i<pocetZarizeni; i++) {
  // Hledám na sběrnici zařízeni s adresou
  if(sensors.getAddress(adresaZarizeni, i)){

  // Výstup zařízeni ID
  Serial.print("Teplota zařízení: ");
  //Serial.print(i,DEC);
  printAddress(adresaZarizeni);
  // Výpis dat
  float tempC = sensors.getTempC(adresaZarizeni);
  Serial.print(" = ");
  Serial.print(tempC);
  Serial.print(" °C ");
  Serial.println();
  soubor = SD.open("cidla.csv", FILE_WRITE);
  souborAddress(adresaZarizeni);
  soubor.print(" = ");
  soubor.print(tempC);
  soubor.println();
  soubor.close();
  }
 }
  delay(10000);
}
