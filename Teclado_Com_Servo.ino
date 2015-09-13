#include <Servo.h> // Biblioteca Servo
#include <Keypad.h> // Biblioteca Teclado
// Definimos a quantidade de linhas e colunas do teclado.
#define ROWS 4
#define COLUMNS 4

Servo motor; // Instacia da Biblioteca Servo

char senha[3] = {'1', '2', '3'}; // senha cadastrada
char senhaDigitada[3]; // senha digitada
int i; // contador

// Fazemos o mapeamento das teclas.
char keyMap[ROWS][COLUMNS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

// Definimos que quais pinos conectamos as linhas e colunas do teclado.
byte rowPins[ROWS] = { 11, 10, 9, 8 };
byte colPins[COLUMNS] = { 7, 6, 5, 4 };

Keypad keypad = Keypad(makeKeymap(keyMap), rowPins, colPins, ROWS, COLUMNS);

void setup() {
   Serial.begin(9600);
   pinMode(A0, OUTPUT);
   pinMode(A1, OUTPUT);
   motor.attach(A2); // sinal servo pino 2
   Serial.print("Digite senha: "); // printar
}

void loop() {
  char key = keypad.getKey();
  
    // Se foi pressionada uma tecla, mostramos qual foi.
    if (key != NO_KEY){
      //Serial.print("Teclas pressionadas: ");
      Serial.print(key);
      Serial.print(" ");
      senhaDigitada[i] = key;
      i++;
      if(i == 3){
          senhaDigitada[i] = '\0'; // Fechando vetor
          Serial.println(" "); // quebra de linha
          if(senha[0] == senhaDigitada[0] && senha[1] == senhaDigitada[1] && senha[2] == senhaDigitada[2]){
            digitalWrite(A1, HIGH); // ligando led permitido, porta A1
            motor.write(1); // posicionar-se 1 grau, TESTE
            Serial.println(" "); // quebra de linha
            Serial.print("SENHA CORRETA!\n\n"); //
            delay(2000); // aguardo dois segundos
            i = 0; // zerando contador
            delay(3000); // aguardo tres segundos
            delay(3000); // aguardo tres segundos
            motor.write(90); // motor posicionar-se ao normal em 90 graus
            digitalWrite(A1, LOW); // desligando led permitido, porta A1
            Serial.print("Digite senha: "); // pritando serial
            } else {
              Serial.println(" "); // quebra de linha
              Serial.print("SENHA INCORRETA!\n\n");
              digitalWrite(A0, HIGH);
              Serial.print("Digite senha novamente: ");
              delay(2000);
              digitalWrite(A0, LOW);
              i = 0;
              }
      }
    }
}
