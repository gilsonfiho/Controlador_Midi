#include <MIDI.h>

// Define os pinos dos botões
const int buttonPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1};

// Define os canais MIDI correspondentes para cada botão
const int buttonChannels[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

// Define as mensagens MIDI correspondentes para cada botão
const int buttonMIDI[] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61};

// Define o número de botões
const int numButtons = 14;

// Define o tempo de debounce para os botões
const int debounceTime = 50;

// Define a instância da classe MIDI
MIDI_CREATE_DEFAULT_INSTANCE();

// Define uma variável para armazenar o estado anterior dos botões
int lastButtonStates[numButtons];

void setup() {
		// Configura os pinos dos botões como entrada
		for (int i = 0; i < numButtons; i++) {
				pinMode(buttonPins[i], INPUT_PULLUP);
		}
		
		// Inicializa o estado anterior dos botões
		for (int i = 0; i < numButtons; i++) {
				lastButtonStates[i] = HIGH;
		}
		
		// Inicializa a comunicação MIDI
		MIDI.begin();
}

void loop() {
			// Verifica o estado atual dos botões
		for (int i = 0; i < numButtons; i++) {
				int buttonState = digitalRead(buttonPins[i]);
		
				// Verifica se o botão foi pressionado
				if (buttonState == LOW && lastButtonStates[i] == HIGH) {
					  // Envia a mensagem MIDI correspondente para o REAPER
					  MIDI.sendNoteOn(buttonMIDI[i], 127, buttonChannels[i]);
					
					  // Define o estado anterior do botão como pressionado
					  lastButtonStates[i] = LOW;
				}
		
				// Verifica se o botão foi solto
				if (buttonState == HIGH && lastButtonStates[i] == LOW) {
					  // Envia a mensagem MIDI correspondente para o REAPER
					  MIDI.sendNoteOff(buttonMIDI[i], 0, buttonChannels[i]);
					
					  // Define o estado anterior do botão como solto
					  lastButtonStates[i] = HIGH;
				}
		
			// Aguarda o tempo de debounce antes de verificar o próximo botão
			delay(debounceTime);
		}
}
