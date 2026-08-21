#include <Wire.h>

const uint8_t lcdAddr = 0x27;

// Podstawowa funkcja wysyłająca bajt do LCD (nie zmieniaj jej)
void lcd_send(uint8_t value, uint8_t mode) {
  uint8_t highNibble = value & 0xF0;
  uint8_t lowNibble = (value << 4) & 0xF0;
  
  uint8_t data[4];
  data[0] = highNibble | 0x08 | mode; 
  data[1] = highNibble | 0x0C | mode; 
  data[2] = lowNibble | 0x08 | mode;
  data[3] = lowNibble | 0x0C | mode;  
  
  Wire.beginTransmission(lcdAddr);
  for(int i=0; i<4; i++) {
    Wire.write(data[i]);
    if(i % 2 != 0) {
      Wire.endTransmission();
      delayMicroseconds(50);
    }
    if(i % 2 != 0 && i < 3) Wire.beginTransmission(lcdAddr);
  }
}

// USTAWIENIE KURSORA (wiersz 0 lub 1, kolumna 0-15)
void setCursor(uint8_t col, uint8_t row) {
  uint8_t adresy[] = {0x80, 0xC0}; // Adresy startowe dla wierszy 0 i 1
  lcd_send(adresy[row] + col, 0);
}

// FUNKCJA WYPISUJĄCA TEKST (String lub char*)
void printLCD(String tresc) {
  for(int i = 0; i < tresc.length(); i++) {
    lcd_send(tresc[i], 1);
  }
}

// CZYSZCZENIE EKRANU
void clearLCD() {
  lcd_send(0x01, 0);
  delay(2);
}

void setup() {
  Wire.begin();
  
  // Inicjalizacja wyświetlacza
  lcd_send(0x02, 0); 
  lcd_send(0x28, 0); 
  lcd_send(0x0C, 0); 
  lcd_send(0x06, 0); 
  clearLCD();

  // --- PRZYKŁAD UŻYCIA ---
  setCursor(3, 0);        // Kolumna 3, Wiersz 0 (pierwszy)
  printLCD("Witaj ESP32");
  
  setCursor(0, 1);        // Kolumna 0, Wiersz 1 (drugi)
  printLCD(String("Czas: ") + 21 + ":" + 42);
}

void loop() {
  // Tutaj możesz np. aktualizować zegar
}
