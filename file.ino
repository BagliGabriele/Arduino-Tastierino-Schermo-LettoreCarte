// #include <Keypad.h>
// #include <LiquidCrystal.h>

// #define ROWS 4
// #define COLS 4

// char keymap[ROWS][COLS] = {
//   {'1', '2', '3', 'A'},
//   {'4', '5', '6', 'B'},
//   {'7', '8', '9', 'C'},
//   {'*', '0', '#', 'D'},
// };

// byte rowPins[ROWS] = {22, 24, 26, 28};
// byte colPins[COLS] = {30, 32, 34, 36};
// Keypad keypad = Keypad(makeKeymap(keymap), rowPins, colPins, ROWS, COLS);
// LiquidCrystal lcd(52, 50, 48, 46, 44, 42);

// int X = 0;
// int Y = 0;
// unsigned long previousMillis = 0;
// const long interval = 3000;
// const int password = "1234";

// String printedText = "";

// void setup() {
//   Serial.begin(9600);
//   lcd.begin(16, 2);
//   lcd.clear();
// }

// void loop() {
//   unsigned long currentMillis = millis();
//   char key = keypad.getKey();

//   if (key) {
//     if (X == 16 && Y == 0) {
//       X = 0;
//       Y = 1;
//     } else if (X == 16 && Y == 1) {
//       lcd.clear();
//       printedText = "";
//       X = 0;
//       Y = 0;
//     }

//     lcd.setCursor(X, Y);
//     lcd.print(key);
//     X++;

//     previousMillis = currentMillis;

//     printedText += key;
//   }

//   if (currentMillis - previousMillis >= interval) {
//     lcd.clear();
//     Serial.println(printedText);

//     if (printedText == password) {
//       lcd.print("Authorized");
//       delay(1000);
//       lcd.clear();
//       X = 0;
//       Y = 0;
//     } else {
//       lcd.print("NOT Authorized");
//       delay(1000);
//       lcd.clear();
//       X = 0;
//       Y = 0;
//     }

//     printedText = ""; 
//     previousMillis = currentMillis;
//   }
// }

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 47
#define RST_PIN 40
MFRC522 mfrc522(SS_PIN, RST_PIN);

const int ledGreen = 45;
int state = 0;

void setup()
{
  pinMode(ledGreen, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}

void loop()
{
  digitalWrite(ledGreen, HIGH);
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    // Serial.println("TEST1");
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial())
  {
    // Serial.println("TEST2");
    return;
  }

  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "53 14 5F FC")
  {
    Serial.println("Authorized access");
    if (state == 0)
    {
      state = 1;
      digitalWrite(ledGreen, HIGH);
      delay(2500);
    }
    else
    {
      state = 0;
      digitalWrite(ledGreen, LOW);
      delay(2500);
    }
  }
  else
  {
    Serial.println(" Access denied");
  }
}
