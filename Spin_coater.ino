
#include <Keypad.h>
#include <Keyboard.h>
#include <Servo.h>//Using servo library to control ESC
#include <LiquidCrystal.h>
Servo esc;
String value = "";
String value1 = "";
String a = "";
String b = "";
String c = "";
const byte numRows = 4; //number of rows on the keypad
const byte numCols = 4; //number of columns on the keypad
unsigned long sum = 0, i = 0, j = 0, k, sp = 0, tp = 0, p = 0, q = 0, r, t, tim[100], ck, vul, val = -100, sp1 = 0, tim1[100], x, y, f = 0, z;
int led = 13;
LiquidCrystal lcd(32, 30, 28, 26, 24, 22);

//Serial.println(LED ON);
char keymap[numRows][numCols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {9, 8, 7, 6}; //Rows 0 to 3
byte colPins[numCols] = {5, 4, 3, 2}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup()
{
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.print("F-SPIN : IPD, BCSIR");
  lcd.setCursor(0, 1);
  Serial.begin(115200);
  pinMode(led, OUTPUT);

  esc.attach(10); //Specify the esc signal pin,Here as D8


  esc.writeMicroseconds(val); //initialize the signal to 1000


}

void loop()
{
  unsigned long  rpm[100], rpm1[100];
  sum = 0, i = 0, j = 0, k, sp = 0, tp = 0, p = 0, q = 0, r, t, tim[100] = {0}, rpm[100] = {0};
  while (j <= sp * 2) {
    char keypresse = myKeypad.getKey();
    if (keypresse != NO_KEY)
    {
      if (keypresse == 'A') {
        for (int i = 1; i <= sp1; i++) {
          Serial.print("Step=");
          Serial.println(i);

          Serial.print("RPM=");
          Serial.println(rpm1[i - 1]);

          //Serial.println(val);

          Serial.print("Time=");
          Serial.println(tim1[i - 1]);

          unsigned long  currentTime = millis();
          //Serial.print("currentTime=");
          //Serial.println(currentTime);
          //Serial.print("ExecuteTime=");
          //Serial.println(currentTime + tim[i-1] * 1000);

          while (millis() < (currentTime + tim1[i - 1] * 1000)) {
            lcd.setCursor(2, 1);           //this line is for line 3 of display if your display don't have line 3,4 delete these 4 lines with (//)
            lcd.print("STEP:") ;
            lcd.print(i);
            lcd.setCursor(2, 2);
            lcd.print("RPM:");
            lcd.print(rpm1[i - 1]);
            lcd.setCursor(1, 3);
            lcd.print(" TIME:");
            lcd.print(tim1[i - 1]); //
            Serial.print("Map value=");
            Serial.println(rpm1[i - 1]);
            val = (rpm[i - 1] * 0.14695) - 35;
            val = map(val, 0, 1023, 1000, 2000);
            esc.writeMicroseconds(val);

          }
          delay(1000);
          lcd.clear();
          lcd.print("F-SPIN : IPD, BCSIR");
          lcd.setCursor(0, 1);
        }
        esc.writeMicroseconds(-100); //using val as the signal to esc delay(3000);
        digitalWrite(led, HIGH);
        Serial.println("LED ON");
        value = "";
        lcd.print("   STEP END");
        delay(2000);
        lcd.clear();
        lcd.print("F-SPIN : IPD, BCSIR");
        lcd.setCursor(0, 1);
      }
      if (value.equals("A")) {
        value = "";
      }
      if (keypresse == 'C') {
        if (ck == 1) {
          i = 0;
        }
        if (ck == 2) {
          j--;
          rpm[p--] = 0;
          rpm1[x--] = 0;
        }
        if (ck == 3) {
          j--;
          tim[q--] = 0;
          tim1[y--] = 0;
        }
        vul = 1;
        value = "";
        z--;
      }
      if (keypresse == 'D')
      {
        //
        if (vul == 1) {
          value.remove(0, 1);
          vul = 0;
        }

        if (i == 0) {
          a = value;
          lcd.setCursor(0, 1);
          Serial.print("Step=");
          Serial.println(a);
          lcd.print("TOTAL STEP:") ;
          lcd.print(a);
          sp = a.toInt();
          sp1 = a.toInt();
          //z= a.toInt();
          z = 1;
          j = 0;
          value1 = value;
          value = "";
          tim[sp + 1], rpm[sp + 1];
          ck = 1;
          delay(2000);
          lcd.clear();
          lcd.print("F-SPIN : IPD, BCSIR");
          lcd.setCursor(0, 1);

        }
        if (j % 2 == 1 && j != 0) {
          b = value;
          lcd.setCursor(2, 1);
          lcd.print("STEP:") ;
          lcd.print(z);
          Serial.print("RPM=");
          Serial.println(b);
          lcd.setCursor(1, 2);
          lcd.print(" RPM:") ;
          lcd.print(b);
          r = b.toInt();
          rpm[p] = r;
          rpm1[x] = r;
          // Serial.println(rpm[p]);
          value1 = value;
          value = "";
          p++;
          x++;
          ck = 2;
          z++;
        }
        if (j % 2 == 0 && j != 0) {
          c = value;
          Serial.print("Time=");
          Serial.println(c);
          lcd.setCursor(1, 3);
          lcd.print(" T:");
          lcd.print(c);//
          t = c.toInt();
          tim[q] = t;
          tim1[y] = t;
          //Serial.println(tim[q]);
          value1 = value;
          value = "";
          q++;
          y++;
          ck = 3;
          delay(2000);
          lcd.clear();
          lcd.print("F-SPIN : IPD, BCSIR");
          lcd.setCursor(0, 1);

        }
        if (i == 0) {
          i++;
        }

        j++;
      }
      if (keypresse == 'D') {
        continue;
      }


      else {
        value = value + keypresse;
      }
    }
  }
  if (j == sp * 2 + 1) {
    z = 1;
    for (int i = 1; i <= sp; i++) {
      lcd.clear();

      lcd.print("F-SPIN : IPD, BCSIR");
      lcd.setCursor(0, 1);
      Serial.print("Step=");
      Serial.println(i);

      Serial.print("RPM=");
      Serial.println(rpm[i - 1]);


      Serial.print("Time=");
      Serial.println(tim[i - 1]);
      unsigned long  currentTime = millis();
      //Serial.print("currentTime=");
      //Serial.println(currentTime);
      //Serial.print("ExecuteTime=");
      //Serial.println(currentTime + tim[i-1] * 1000);
      delay(1000);
      while (millis() < (currentTime + tim[i - 1] * 1000)) {
        lcd.setCursor(2, 1);           //this line is for line 3 of display if your display don't have line 3,4 delete these 4 lines with (//)
        lcd.print("STEP:") ;
        lcd.print(i);
        lcd.setCursor(2, 2);
        lcd.print("RPM:");
        lcd.print(rpm[i - 1]);
        lcd.setCursor(1, 3);
        lcd.print(" TIME:");
        lcd.print(tim[i - 1]); //
        Serial.print("Map value=");
        Serial.println(rpm[i - 1]);
        val = (rpm[i - 1] * 0.14695) - 35;
        val = map(val, 0, 1023, 1000, 2000);
        esc.writeMicroseconds(val);

      }
      delay(1000);
      lcd.clear();
      lcd.print("F-SPIN : IPD, BCSIR");
      lcd.setCursor(0, 1);
    }
    esc.writeMicroseconds(-100); //using val as the signal to esc delay(3000);
    digitalWrite(led, HIGH);
    Serial.println("LED ON");
    lcd.print("   STEP END");
    delay(2000);
    lcd.clear();
    lcd.print("F-SPIN : IPD, BCSIR");
    lcd.setCursor(0, 1);

  }
  i = 0;
  j = 0;
  sp = 0;
}
