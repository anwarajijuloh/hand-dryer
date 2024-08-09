#define TRIG_PIN 9
#define ECHO_PIN 8
#define FAN_PIN 6

int speed;

void setup()
{
  pinMode(FAN_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

void loop()
{
  long duration, distance;
  
  // Mengirimkan pulse ke TRIG_PIN
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Mengukur waktu perjalanan echo
  duration = pulseIn(ECHO_PIN, HIGH);

  // Menghitung jarak dalam cm
  distance = duration * 0.034 / 2;

  // Logika pengaturan kecepatan kipas berdasarkan jarak
  if (distance >= 5) {
    speed = 0; // Kipas mati
  } else if (distance > 1 && distance <= 5) {
    speed = map(distance, 1, 5, 255, 0); // Semakin dekat, semakin cepat
  } else {
    speed = 255; // Jarak jauh, kipas lambat
  }

  analogWrite(FAN_PIN, speed);  // Atur kecepatan kipas
  delay(100);
}