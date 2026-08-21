#include <Wire.h>

// Adres I2C wyświetlacza (zazwyczaj 0x27 lub 0x3F)
const uint8_t lcdAddr = 0x27; 

// Funkcja wysyłająca dane do LCD
void lcd_write(uint8_t value, uint8_t mode) {
  // mode: 0 = komenda, 1 = dane
  uint8_t highNibble = value & 0xF0;
  uint8_t lowNibble = (value << 4) & 0xF0;
  
  // Przesyłamy w dwóch krokach (tryb 4-bitowy)
  uint8_t data[4];
  data[0] = highNibble | 0x08 | mode; // 0x08 to podświetlenie (LED)
  data[1] = highNibble | 0x0C | mode; // E=1
  data[2] = lowNibble | 0x08 | mode;
  data[3] = lowNibble | 0x0C | mode;  // E=1
  
  Wire.beginTransmission(lcdAddr);
  for(int i=0; i<4; i++) {
    Wire.write(data[i]);
    if(i % 2 != 0) Wire.endTransmission(true); // Wyślij każdą półbajtową paczkę
    if(i % 2 != 0) Wire.beginTransmission(lcdAddr);
  }
  delayMicroseconds(50);
}

void setup() {
  Wire.begin();
  delay(50);

  // Inicjalizacja wyświetlacza w trybie 4-bitowym
  lcd_write(0x02, 0); // Powrót do 4 bitów
  lcd_write(0x28, 0); // 4 bity, 2 linie, 5x8
  lcd_write(0x0C, 0); // Włącz ekran, wyłącz kursor
  lcd_write(0x06, 0); // Przesuwaj kursor w prawo
  lcd_write(0x01, 0); // Czyść ekran
  delay(2);

  // Wypisanie tekstu
  char tekst[] = "Hello World!";
  for(int i=0; tekst[i] != '\0'; i++) {
    lcd_write(tekst[i], 1);
  }
}

void loop() {
  // Pusty
}
