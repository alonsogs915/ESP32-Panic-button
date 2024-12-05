const int buttonPin = 12;  // Pin donde está conectado el botón
int buttonState = 0;       // Variable para leer el estado del botón

void setup() {
  pinMode(buttonPin, INPUT);  // Configura el pin del botón como entrada
  Serial.begin(9600);         // Inicia la comunicación serial
}

void loop() {
  buttonState = digitalRead(buttonPin);  // Lee el estado del botón

  if (buttonState == HIGH) {
    Serial.println("Botón presionado");
  } else {
    Serial.println("Botón no presionado");
  }

  delay(100);  // Pequeña pausa para evitar lecturas erráticas
}
