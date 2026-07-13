#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

bool st, st1, n1, n2, n3, p1, p2, p3, test;
int dly, n, p, tr;
int v1, v2, v3;
void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("   TRANSISTOR   ");
  lcd.setCursor(0, 1);
  lcd.print("     TESTER     ");
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(17, INPUT_PULLUP);
  digitalWrite(2, 0);
  digitalWrite(3, 0);
  digitalWrite(4, 0);


  //while(1);
  ////------------
}

void loop() {
  delay(30);
  if (dly > 1) dly--;
  if (dly == 1) {
    dly = 0;
    st1 = 1;
  }
  if (digitalRead(17)) st = 0;
  if (st1) {
    st1 = 0;
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(200);
    lcd.setCursor(0, 0);
    lcd.print("   TRANSISTOR   ");
    lcd.setCursor(0, 1);
    lcd.print("     TESTER     ");
  }
  if (!digitalRead(17) && !st) {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(200);
    st = 1;
    test = 1;
  }
  if (test) {


    if (tr == 0) {
      lcd.setCursor(0, 0);
      lcd.print("TESTING.");
    } else lcd.print(".");

    n1 = n2 = n3 = p1 = p2 = p3 = 0;
    dly = v1 = v2 = v3 = 0;

    //---sq n1
    digitalWrite(2, 1);
    digitalWrite(3, 0);
    digitalWrite(4, 0);

    v1 = analogRead(A0);
    v2 = analogRead(A1);
    v3 = analogRead(A2);
    Serial.print("N1");
    Serial.print(" v1:");
    Serial.print(v1);
    Serial.print(" v2:");
    Serial.print(v2);
    Serial.print(" v3:");
    Serial.println(v3);


    if (v1 > 10 && v2 > 10 && v3 > 10) n1 = 1;
    //if(v2>v3&&n1)n=1;
    //---sq n2
    digitalWrite(2, 0);
    digitalWrite(3, 1);
    digitalWrite(4, 0);

    v1 = analogRead(A0);
    v2 = analogRead(A1);
    v3 = analogRead(A2);
    Serial.print("N2");
    Serial.print(" v1:");
    Serial.print(v1);
    Serial.print(" v2:");
    Serial.print(v2);
    Serial.print(" v3:");
    Serial.println(v3);

    if (v1 > 10 && v2 > 10 && v3 > 10) n2 = 1;
    if (v3 > v1 && n2) n = 2;
    else if (v1 > v3 && n2) n = 3;
    //---sq n3
    digitalWrite(2, 0);
    digitalWrite(3, 0);
    digitalWrite(4, 1);

    v1 = analogRead(A0);
    v2 = analogRead(A1);
    v3 = analogRead(A2);
    Serial.print("N3");
    Serial.print(" v1:");
    Serial.print(v1);
    Serial.print(" v2:");
    Serial.print(v2);
    Serial.print(" v3:");
    Serial.println(v3);
    pinMode(4, OUTPUT);
    if (v1 > 10 && v2 > 10 && v3 > 10) n3 = 1;
    //if(v2>v1&&n3)n=4;
    //---sq N1
    digitalWrite(2, 0);
    digitalWrite(3, 1);
    digitalWrite(4, 1);

    v1 = analogRead(A0);
    v2 = analogRead(A1);
    v3 = analogRead(A2);
    Serial.print("P1");
    Serial.print(" v1:");
    Serial.print(v1);
    Serial.print(" v2:");
    Serial.print(v2);
    Serial.print(" v3:");
    Serial.println(v3);
    if (v1 > 10 && v2 > 10 && v3 > 10) p1 = 1;
    if (v2 > v1 && n3) n = 4;
    digitalWrite(2, 0);
    digitalWrite(3, 0);
    digitalWrite(4, 1);

    v1 = analogRead(A0);
    v2 = analogRead(A1);
    v3 = analogRead(A2);
    if (v3 > v2 && p3) p = 1;
    //---sq n1
    digitalWrite(2, 1);
    digitalWrite(3, 0);
    digitalWrite(4, 1);

    v1 = analogRead(A0);
    v2 = analogRead(A1);
    v3 = analogRead(A2);
    Serial.print("P2");
    Serial.print(" v1:");
    Serial.print(v1);
    Serial.print(" v2:");
    Serial.print(v2);
    Serial.print(" v3:");
    Serial.println(v3);
    if (v1 > 10 && v2 > 10 && v3 > 10) p2 = 1;
    if (v1 > v3 && p2) p = 2;
    if (v3 > v1 && p2) p = 3;
    //---sq P3
    digitalWrite(2, 1);
    digitalWrite(3, 1);
    digitalWrite(4, 0);

    v1 = analogRead(A0);
    v2 = analogRead(A1);
    v3 = analogRead(A2);
    Serial.print("P3");
    Serial.print(" v1:");
    Serial.print(v1);
    Serial.print(" v2:");
    Serial.print(v2);
    Serial.print(" v3:");
    Serial.println(v3);
    if (v1 > 10 && v2 > 10 && v3 > 10) p3 = 1;
    if (v2 > v3 && n1) n = 1;

    digitalWrite(2, 1);
    digitalWrite(3, 0);
    digitalWrite(4, 0);

    v1 = analogRead(A0);
    v2 = analogRead(A1);
    v3 = analogRead(A2);
    if (v1 > v2 && p3) p = 4;
   if (((n1 + n2 + n3) == 1 && n > 0) ||
    ((p1 + p2 + p3) == 1 && p > 0 && tr < 6)) {
      delay(1000);
      lcd.setCursor(0, 0);
      lcd.print("                ");
      delay(200);

      if (n1 + n2 + n3 == 1 && p1 + p2 + p3 != 0) {
        Serial.println("NPN");
        lcd.setCursor(0, 0);
        lcd.print("TRANSISTOR NPN");
        lcd.setCursor(0, 1);

        if (n == 1) {
          Serial.println("BCE");
          lcd.print("PINS 1=B 2=C 3=E");
        } else if (n == 2) {
          Serial.println("EBC");
          lcd.print("PINS 1=E 2=B 3=C");
        } else if (n == 3) {
          Serial.println("CBE");
          lcd.print("PINS 1=C 2=B 3=E");
        } else if (n == 4) {
          Serial.println("ECB");
          lcd.print("PINS 1=E 2=C 3=B");
        }

      } else if (n1 + n2 + n3 != 0 && p1 + p2 + p3 == 1) {
        Serial.println("PNP");
        lcd.setCursor(0, 0);
        lcd.print("TRANSISTOR PNP");
        lcd.setCursor(0, 1);
        if (p1 == 1) {
          Serial.println("BCE");
          lcd.print("PINS 1=B 2=C 3=E");
        } else if (p == 2) {
          Serial.println("EBC");
          lcd.print("PINS 1=E 2=B 3=C");
        } else if (p == 3) {
          Serial.println("CBE");
          lcd.print("PINS 1=C 2=B 3=E");
        } else if (p3 == 1) {
          Serial.println("ECB");
          lcd.print("PINS 1=E 2=C 3=B");
        }
      } else {
        Serial.println("UK");
        lcd.setCursor(0, 0);
        lcd.print("UNKNOWN , DAMAGE");
        lcd.setCursor(0, 1);
        lcd.print("or NO TRANSISTOR");
      }

      dly = 600;
      test = 0;
      tr = 0;
    } else {
      tr++;
      if (tr >= 5) {
        Serial.println("UK");
        lcd.setCursor(0, 0);
        lcd.print("UNKNOWN , DAMAGE");
        lcd.setCursor(0, 1);
        lcd.print("or NO TRANSISTOR");
        dly = 600;
        test = 0;
        tr = 0;
      }

      else delay(300);
    }
  }
}
