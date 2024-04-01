#include <M5Cardputer.h> // Include the M5Cardputer library
#include <TinyGPSPlus.h> // Include the TinyGPSPlus library

const uint32_t gpsBaudRate = 9600; // Set the GPS baud rate
const int lineSpacing = 20; // Set the line spacing for the display
const int leftMargin = 10; // Set the left margin for the display

TinyGPSPlus gps; // Create a TinyGPSPlus object
HardwareSerial ss(2); // Create a HardwareSerial object on UART2

void displayclear() // Function to clear the display
{
  M5.Lcd.fillScreen();
}

void setup() // Setup function runs once when the device starts
{
  auto cfg = M5.config(); // Get the M5 configuration
  M5.begin(cfg); // Initialize the M5
  M5.Power.begin(); // Initialize the M5 power
  ss.begin(gpsBaudRate, SERIAL_8N1, 1, 2); // Begin the serial communication with the GPS
  M5.Lcd.setRotation(1); // Set the LCD rotation
  M5.Lcd.setTextSize(4); // Set the LCD text size

  M5.Lcd.setCursor(85, 60); // Set the LCD cursor position
  M5.Lcd.printf("GPS"); // Print "GPS" to the LCD
  delay(2000); // Wait for 2 seconds
  M5.Lcd.clear(); // Clear the LCD
  M5.Lcd.setTextSize(2); // Set the LCD text size
}

void displayGPSData() // Function to display the GPS data
{
  int currentLine = 0; // Initialize the current line

  M5.Lcd.setCursor(leftMargin, lineSpacing * currentLine++); // Set the LCD cursor position
  M5.Lcd.printf("Lat: %.8f\n", gps.location.lat()); // Print the latitude to the LCD

  M5.Lcd.setCursor(leftMargin, lineSpacing * currentLine++); // Set the LCD cursor position
  M5.Lcd.printf("Long: %.8f\n", gps.location.lng()); // Print the longitude to the LCD

  M5.Lcd.setCursor(leftMargin, lineSpacing * currentLine++); // Set the LCD cursor position
  M5.Lcd.printf("Speed: %.2f km/h\n", gps.speed.kmph()); // Print the speed to the LCD

  M5.Lcd.setCursor(leftMargin, lineSpacing * currentLine++); // Set the LCD cursor position
  M5.Lcd.printf("Satelites: %d\n", gps.satellites.value()); // Print the number of satellites to the LCD

  M5.Lcd.setCursor(leftMargin, lineSpacing * currentLine++); // Set the LCD cursor position
  M5.Lcd.printf("Date: %02d/%02d/%02d\n", gps.date.day(), gps.date.month(), gps.date.year()); // Print the date to the LCD

  int hour = gps.time.hour() - 4; // Adjust the hour for the time zone
  if (hour < 0)
    hour += 24; // If the hour is negative, add 24

  M5.Lcd.setCursor(leftMargin, lineSpacing * currentLine++); // Set the LCD cursor position
  M5.Lcd.printf("Time: %02d:%02d:%02d\n", hour, gps.time.minute(), gps.time.second()); // Print the time to the LCD
}

void readGPSData() // Function to read the GPS data
{
  while (ss.available() > 0) // While there is data available from the GPS
  {
    if (gps.encode(ss.read())) // If the GPS data is successfully encoded
    {
      displayGPSData(); // Display the GPS data
    }
  }
}

void loop() // Loop function runs continuously after the setup function
{
  M5.update(); // Update the M5

  if (M5.BtnA.wasPressed()) // If button A was pressed
  {
    displayclear(); // Clear the display
  }

  readGPSData(); // Read the GPS data
}
