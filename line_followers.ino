// pin driver motor R & L
int Rrpwm = 23;
int Llpwm = 22;

int Lrpwm = 19;
int Rlpwm = 18;

// mengatur kecepatan motor R & L
int speed1 = 252;
int speed2 = 255;

// pin sensor 1-5 Line sensor
int pin_sensor[] = {26, 25, 33, 32, 35};
int baca_sensor;
int inp;
int hasil_baca[] = {0, 0, 0, 0, 0};

// pin sensor 1-2 Ultrasonik sensor
int echo1 = 12;
int trig1 = 13;

int echo2 = 12;
int trig2 = 13;

long durasi1, durasi2, jarak1, jarak2;

// fungsi maju
void maju()
{
  // motor kanan
  analogWrite(Rrpwm, 0);
  analogWrite(Rlpwm, speed1);

  // motor kiri
  analogWrite(Lrpwm, 0);
  analogWrite(Llpwm, speed1);
  
  
}

void mundur()
{
  // motor kanan
  analogWrite(Rrpwm, 0);
  analogWrite(Rlpwm, speed1);

  // motor kiri
  analogWrite(Lrpwm, 0);
  analogWrite(Llpwm, speed1);

  delay(2000);

  analogWrite(Rrpwm, 0);
  analogWrite(Rlpwm, 100);

  // motor kiri
  analogWrite(Lrpwm, 0);
  analogWrite(Llpwm, 255);

  delay(2000);

  analogWrite(Rrpwm, 0);
  analogWrite(Rlpwm, 255);

  // motor kiri
  analogWrite(Lrpwm, 0);
  analogWrite(Llpwm, 100);

  delay(2000);
}
// fungsi berhenti
void berhenti()
{
  // motor kanan
  analogWrite(Rrpwm, 0);
  analogWrite(Rlpwm, 0);

  // motor kiri
  analogWrite(Lrpwm, 0);
  analogWrite(Llpwm, 0);
}

// fungsi belok kanan
void belok_kanan()
{
  // motor kanan
  analogWrite(Rrpwm, 0);
  analogWrite(Rlpwm,100);

  // motor kiri
  analogWrite(Lrpwm, 0);
  analogWrite(Llpwm, 255);
}

// fungsi belok kiri
void belok_kiri()
{
  // motor kanan
  analogWrite(Rrpwm, 0);
  analogWrite(Rlpwm, 255);

  // motor kiri
  analogWrite(Lrpwm, 0);
  analogWrite(Llpwm, 100);
}

void setup()
{
  Serial.begin(115200);
  // mendefinisikan pin motor
  pinMode(Rrpwm, OUTPUT);
  pinMode(Rlpwm, OUTPUT);
  pinMode(Lrpwm, OUTPUT);
  pinMode(Llpwm, OUTPUT);

  // mendefinisikan pin sensor line
  int a;
  while (a < 5)
  {
    pinMode(pin_sensor[a], INPUT);
    a = a + 1;
  }

  // mendefinisikan pin sensor ultrasonik
  pinMode(echo1, INPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig2, OUTPUT);
}

void loop()
{
  // input sensor line
  baca_sensor = readOut(pin_sensor);

  // input sensor ultrasonik
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  durasi1 = pulseIn(echo1, HIGH);

  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  durasi2 = pulseIn(echo2, HIGH);

  // perhitungan untuk dijadikan jarak
  jarak1 = durasi1 / 58.2;
  jarak2 = durasi2 / 58.2;

  // menampilkan nilai sensor ke serial monitor
  Serial.print("\n");
  Serial.print("senLine = ");
  Serial.print(baca_sensor);

  Serial.print("\n");
  Serial.print("jarak1 = ");
  Serial.print(jarak1);

  Serial.print("\n");
  Serial.print("jarak2 = ");
  Serial.print(jarak2);

  // mengatur berhenti dan jalan motor dengan ultrasonik
  if ((jarak1 < 30) or (jarak2 < 30))
  {
    berhenti();
  }
  else if ((jarak1 > 30) or (jarak2 > 30))
  {
    maju();

  // mengatur motor R & L sesuai dengan inputan sensor line
  switch (baca_sensor)
  {
  // hasil baca sensor untuk belok kiri
  case 11110:
  case 11000:
  case 11100:
  case 11101:
  case 10000:
    Serial.println("Belok Kanan");
    belok_kiri();
    break;

  // hasil baca sensor untuk arah maju
  case 11001:
  case 11011:
  case 10011:
    Serial.println("Maju");
    maju();
    break;

  // hasil baca sensor untuk belok kanan
  case 10111:
  case 111:
  case 11:
  case 1111:
  case 1:
    Serial.println("Belok Kiri");
    belok_kanan();
    break;

  // baca hitam semua=stop
  case 0:
    Serial.println("Stop");
    berhenti();
    break;
  }

  }
  delay(100);
}

int readOut(int pin_sensor[])
{
  int a, b = 0;
  inp = 0;
  for (a = 0; a < 5; a++)
  {
    hasil_baca[a] = digitalRead(pin_sensor[a]);
  }
  while (b < 5)
  {
    inp = inp * 10 + hasil_baca[b];
    b = b + 1;
  }
  return inp;
}
