// Define os pinos do encoder
const int encoderPinA = 2;
const int encoderPinB = 3;
const int encoderSwitchPin = 4;

// Define a posição atual do encoder
int encoderPos = 0;

// Define o pino do buzzer
const int buzzerPin = 5;

// Define o estado do botão do encoder
int encoderSwitchState;
int lastEncoderSwitchState = LOW;

// Define a variável que controla se o som está ligado ou desligado
bool isSoundOn = false;

void setup() {
// Define o pino do buzzer como saída digital
pinMode(buzzerPin, OUTPUT);

// Define os pinos do encoder como entrada digital
pinMode(encoderPinA, INPUT);
pinMode(encoderPinB, INPUT);

// Define o pino do botão do encoder como entrada digital com resistor pull-up
pinMode(encoderSwitchPin, INPUT_PULLUP);
}

void loop() {
// Lê o valor do botão do encoder
encoderSwitchState = digitalRead(encoderSwitchPin);

// Liga ou desliga o som quando o botão do encoder é pressionado
if (encoderSwitchState != lastEncoderSwitchState) {
if (encoderSwitchState == LOW) {
// O botão foi pressionado
isSoundOn = !isSoundOn; // Alterna entre ligar e desligar o som
if (isSoundOn) {
// Se o som estiver ligado, toca um som inicial
tone(buzzerPin, 1000);
delay(100);
noTone(buzzerPin);
} else {
// Se o som estiver desligado, para a reprodução do som
noTone(buzzerPin);
}
}
}

lastEncoderSwitchState = encoderSwitchState;

// Se o som estiver ligado, ajusta a frequência do som com base na posição do encoder
if (isSoundOn) {
int frequency = map(encoderPos, 0, 100, 100, 1000); // Mapeia a posição do encoder para a frequência do som
tone(buzzerPin, frequency); // Toca o som do buzzer com a frequência atual
}

// Lê os valores dos pinos A e B do encoder
int encoderA = digitalRead(encoderPinA);
int encoderB = digitalRead(encoderPinB);

// Determina a direção em que o encoder está sendo girado
if (encoderA != encoderB) {
encoderPos++;
} else {
encoderPos--;
}

// Limita a posição do encoder entre 0 e 100
if (encoderPos < 0) {
encoderPos = 0;
}
if (encoderPos > 100) {
encoderPos = 100;
}
}
