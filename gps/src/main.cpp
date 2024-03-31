#include <M5Cardputer.h>
#include <TinyGPSPlus.h>

const uint32_t gpsBaudRate = 9600;
const int lineSpacing = 20;
const int leftMargin = 10;

TinyGPSPlus gps;
HardwareSerial ss(2);

void displayclear()
{
  M5.Lcd.fillScreen();
}

void setup()
{

  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Power.begin();
  ss.begin(gpsBaudRate, SERIAL_8N1, 1, 2);
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(4);

  M5.Lcd.setCursor(85, 60);
  M5.Lcd.printf("GPS");
  delay(2000);
  M5.Lcd.clear();
  M5.Lcd.setTextSize(2);
}

void displayGPSData()
{
  int currentLine = 0;

  M5.Lcd.setCursor(leftMargin, lineSpacing * currentLine++);
  M5.Lcd.printf("Lat: %.8f\n", gps.location.lat());

  M5.Lcd.setCursor(leftMargin, lineSpacing * currentLine++);
  M5.Lcd.printf("Long: %.8f\n", gps.location.lng());

  M5.Lcd.setCursor(leftMargin, lineSpacing * currentLine++);
  M5.Lcd.printf("Speed: %.2f km/h\n", gps.speed.kmph());

  M5.Lcd.setCursor(leftMargin, lineSpacing * currentLine++);
  M5.Lcd.printf("Satelites: %d\n", gps.satellites.value());

  M5.Lcd.setCursor(leftMargin, lineSpacing * currentLine++);
  M5.Lcd.printf("Date: %02d/%02d/%02d\n", gps.date.day(), gps.date.month(), gps.date.year());

  int hour = gps.time.hour() - 4;
  if (hour < 0)
    hour += 24;

  M5.Lcd.setCursor(leftMargin, lineSpacing * currentLine++);
  M5.Lcd.printf("Time: %02d:%02d:%02d\n", hour, gps.time.minute(), gps.time.second());
}

void readGPSData()
{
  while (ss.available() > 0)
  {
    if (gps.encode(ss.read()))
    {
      displayGPSData();
    }
  }
}

void loop()
{
  M5.update();

  if (M5.BtnA.wasPressed())
  {
    displayclear();
  }

  readGPSData();
}