#include <DHT.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(13, DHT11);
#define kirmizi_led 7
#define yesil_led 8

long sonYazma = 0;     
long yazmaraligi = 1000;  

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);  
  lcd.setCursor(0, 1);
  lcd.print("NEM :");

  pinMode(kirmizi_led, OUTPUT);  
  pinMode(yesil_led, OUTPUT);   
}

void loop() {

  float sicaklik = dht.readTemperature();
  float nem = dht.readHumidity();

  if (isnan(sicaklik) || isnan(nem)) {
    Serial.println("okunmadı:)");
    return;
  }

  if (sicaklik < 25) {
    digitalWrite(yesil_led, LOW);   
    digitalWrite(kirmizi_led, HIGH);   
  } else {
    digitalWrite(kirmizi_led, 0);   
    digitalWrite(yesil_led, 1);   
  }

  long suan = millis(); 
  if (suan -  sonYazma >= yazmaraligi) {
     sonYazma = suan; 
    lcd.setCursor(0, 0);   
    lcd.print("SICAKLIK :" );
    lcd.print(sicaklik);
    lcd.setCursor(0, 1);
    lcd.print("NEM :");
    lcd.print(nem);
    Serial.print("Sicaklik: ");
    Serial.print(sicaklik);
    Serial.print(" C, Nem: ");
    Serial.print(nem);
    Serial.println(" %");
  }
}
