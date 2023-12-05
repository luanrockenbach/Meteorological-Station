/*
 Created by: Luan Rockenbach da Silva
 30/11/2023
 @ CTISM - UFSM
*/

/* 

 Ler pluviômetro - chave de contato DONE
 Ler anemômetro - read switch
 Direção do vento - encouder
 Temperatura e Humidade - DHT 22 DONE
 Luminosidade - GY-302 DONE
 Display
 Cloud
 Cartão de memória
 Configurações via bluetooth
 aplicativo móvel
*/

#include "DHT.h"
#include "Wire.h"
#include "BH1750.h"

#define water 2

#define DHTPIN 4
#define DHTTYPE DHT11

BH1750 lightMeter;
DHT dht(DHTPIN, DHTTYPE);


int rain;
float waterBounce =0, humidity, temperature, heat, lux=0;

void raining(){
  if(digitalRead(water) == HIGH && (millis() - waterBounce) >= 100){
    waterBounce = millis();
    rain += 10;
  }
}

void dhtRead(){

  humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temperature = dht.readTemperature();
  // Compute heat index in Celsius (isFahreheit = false)
  heat = dht.computeHeatIndex(temperature, humidity, false);

}

float light(){
  if(lightMeter.measurementReady()){
    lux = lightMeter.readLightLevel();
  }
  return lux;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire1.begin(21,22);
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &Wire1);
  dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  dhtRead();
  Serial.print("H: ");
  Serial.print(humidity);
  Serial.print("          T: ");
  Serial.println(temperature);
  
  Serial.println("  ");
  Serial.print("Lux: ");
  Serial.print(light());
  Serial.print("    ");

  delay(100);
}
