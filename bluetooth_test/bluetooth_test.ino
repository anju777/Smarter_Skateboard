int bluetoothRx = 2;
int bluetoothTx = 3;

void setup() {
  pinMode(bluetoothRx, INPUT);
  pinMode(bluetoothTx, OUTPUT);
  Serial.begin(9600);
}

void loop() {
}
