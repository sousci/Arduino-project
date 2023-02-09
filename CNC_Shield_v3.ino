// CNC Shield v3

const int X_STEP = 2;
const int Y_STEP = 3;
const int Z_STEP = 4;
const int A_STEP = 12;

const int X_DIR = 5;
const int Y_DIR = 6;
const int Z_DIR = 7;
const int A_DIR = 13;

const int EN = 8;

void setup() {
  pinMode(X_STEP, OUTPUT);
  pinMode(Y_STEP, OUTPUT);
  pinMode(Z_STEP, OUTPUT);
  pinMode(A_STEP, OUTPUT);
  pinMode(X_DIR, OUTPUT);
  pinMode(Y_DIR, OUTPUT);
  pinMode(Z_DIR, OUTPUT);
  pinMode(A_DIR, OUTPUT);
   pinMode(EN, OUTPUT);

  digitalWrite(EN, LOW); // ENABLE:LOW, DISABLE:HIGH
  digitalWrite(X_DIR, LOW);
  
}

void loop() {
  digitalWrite(X_STEP, HIGH);
  delay(1);
  digitalWrite(X_STEP, LOW);
  delay(1);
}
