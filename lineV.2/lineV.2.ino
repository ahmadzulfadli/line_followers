// pin driver motor R & L
int Rrpwm = 23;
int Rlpwm = 22;

int Lrpwm = 19;
int Llpwm = 18;

// pin sensor 1-5 Line sensor
int pin_sensor[] = {26, 25, 33, 32, 35};
int baca_sensor;
int inp;
int hasil_baca[] = {0, 0, 0, 0, 0};


// SPEED CINTER
// =============================================================================== 

void SpeedLogic(int spdL, int spdR) {

  Serial.print("\n");
  Serial.print("spdr = ");
  Serial.print(spdR);
  
  Serial.print("\n");
  Serial.print("senLine = ");
  Serial.print(spdL);

  if (spdR > spdL) {
    // Belok Kanan
    int sp1 = spdR;
    int sp2 = spdL;
    Serial.print("Kanan");

    // motor kanan
    analogWrite(Rrpwm, 0);
    analogWrite(Rlpwm, sp2);
  
    // motor kiri
    analogWrite(Lrpwm, sp1);
    analogWrite(Llpwm, 0);

  } else if (spdL > spdR) {
    //Belok Kiri
    int sp1 = spdL;
    int sp2 = spdR;
    Serial.print("Kiri");
    // motor kanan
    analogWrite(Rrpwm, sp1);
    analogWrite(Rlpwm, 0);
  
    // motor kiri
    analogWrite(Lrpwm, 0);
    analogWrite(Llpwm, sp2);
    
  } else {
    //Lurus
    // motor kanan
    analogWrite(Rrpwm, spdR);
    analogWrite(Rlpwm, 0);
    
    // motor kiri
    analogWrite(Lrpwm, spdL);
    analogWrite(Llpwm, 0);
  }
} 
//================================================================================================
// LOGIC CINTER 

int Error = 0;
int outlineCnt = 0;

void sensLogic(int X) {
  switch (X) {
    case 11111:
      outlineCnt=0;
      Error=Error;
      break;
      
    case 00000:
      outlineCnt=0;
      Error = 0;
      break;
      
    case 11101:
    case 11001:
      outlineCnt = 0;
      Error = 1;
      break;
      
    case 11110:
    case 11100:
    case 11000:
      outlineCnt = 0;
      Error = 2;
      break;
      
    case 11011:
      outlineCnt = 0;
      Error = 0;
      break;
      
    case 10111:
    case 10011:
      outlineCnt = 0;
      Error = -1;
      break;
      
    case 1111:
    case 111:
    case 11:
      outlineCnt = 0;
      Error = -2;
      break;
      
    default:
      outlineCnt=0;
      Error=Error;
      break;
  }

  if (outlineCnt > 2) {
    SpeedLogic(0,0);
  } else {
    
    float ctrl = calcPid(Error);
    SpeedLogic(105-ctrl,105+ctrl);
  }
}
//===============================================================================================

// PID 
float Kp = 40;
float Ki = 0.45;
float Kd = 1000;
float error, errorLast, erroInte;

float calcPid(float input) {
  float errorDiff;
  float output;
  error = error * 0.7 + input * 0.3; // filter
  //error = input;
  errorDiff = error - errorLast;
  erroInte = constrain(erroInte + error, -20, 20);
  output = Kp * error + Ki * erroInte + Kd * errorDiff;

  errorLast = error;

  return output;
}
// TRACE ===================================================================================
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
//========================================================================================

void setup() {
  Serial.begin(9600);

  int a;
  while (a < 5)
  {
    pinMode(pin_sensor[a], INPUT);
    a = a + 1;
  }
  pinMode(Rrpwm, OUTPUT);
  pinMode(Rlpwm, OUTPUT);
  pinMode(Lrpwm, OUTPUT);
  pinMode(Llpwm, OUTPUT);

}
//======================================================================================================

int pos;
void loop() {
  delay(4);
  pos = readOut(pin_sensor);
  sensLogic(pos);
}
