#include <dht.h>
#define dht_pin 7 // Analog Pin sensor is connected to
 
dht DHT;
 
void setup()
{
 
  Serial.begin(9600);
  delay(500);
}
 
void loop()
{
  DHT.read11(dht_pin);
 
  Serial.print("Humidity: ");
  Serial.print(DHT.humidity);
  Serial.println("%  ");
 
  Serial.print("Temperature: ");
  Serial.print(DHT.temperature);
  Serial.println("°C  ");
  Serial.println();
  delay(2000);
}
