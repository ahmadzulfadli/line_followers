//pin driver motor R & L
int rpwm = 23;
int lpwm = 22;


//mengatur kecepatan motor R & L
int speed1 = 252;
 

void setup() {
  Serial.begin(115200);
  // mendefinisikan pin motor
  pinMode(rpwm,OUTPUT);
  pinMode(lpwm,OUTPUT);

}

void loop() {
  analogWrite(rpwm,255);
  analogWrite(lpwm,0);
  
}
