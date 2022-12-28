// pin driver motor R & L
int Rrpwm = 23;
int Rlpwm = 22;

int Lrpwm = 19;
int Llpwm = 18;

int belok = 70;

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

//fungsi membaca sensor
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

// fungsi maju
void maju()
{
  // motor kanan
  analogWrite(Rrpwm, 252);
  analogWrite(Rlpwm, 0);

  // motor kiri
  analogWrite(Lrpwm, 255);
  analogWrite(Llpwm, 0);
  
  
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
  analogWrite(Rlpwm, 70);

  // motor kiri
  analogWrite(Lrpwm, 152);
  analogWrite(Llpwm, 0);
}

void belok_kanan_awal()
{
  
  // motor kanan
  analogWrite(Rrpwm,0);
  analogWrite(Rlpwm,50);

  // motor kiri
  analogWrite(Lrpwm, 120);
  analogWrite(Llpwm, 0);
}

// fungsi belok kiri
void belok_kiri()
{
  
  // motor kanan
  analogWrite(Rrpwm, 152);
  analogWrite(Rlpwm, 0);

  // motor kiri
  analogWrite(Lrpwm, 0);
  analogWrite(Llpwm, 70);
}
void belok_kiri_awal()
{
  // motor kanan
  analogWrite(Rrpwm, 120);
  analogWrite(Rlpwm, 0);

  // motor kiri
  analogWrite(Lrpwm, 0);
  analogWrite(Llpwm, 50);
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

  // mengatur motor R & L sesuai dengan inputan sensor line
  switch (baca_sensor)
  {
  // hasil baca sensor untuk belok kanan
  case 11001:
  case 11101:
    belok_kanan_awal();
    break;
  case 11110:
  case 11000:
  case 10000:
  case 11100:
    belok_kanan();
    break;
  case 00000:
    berhenti();
    break;
    
  // hasil baca sensor untuk arah maju
  case 11011:
  case 10001:
    maju();
    break;

  // hasil baca sensor untuk belok kiri
  case 10011:
  case 10111:
    belok_kiri_awal();
    break;
  case 1111:
  case 111:
  case 11:
  case 1:
    belok_kiri();
    break;
  }
}

void jarak(){
  //input sensor ultrasonik
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


  // mengatur berhenti dan jalan motor dengan ultrasonik
  if ((jarak1 < 30) or (jarak2 < 30))
  {
    berhenti();
  }
  else if ((jarak1 > 30) or (jarak2 > 30))
  {
    maju();
  }
}
