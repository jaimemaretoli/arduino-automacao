#include <Servo.h> // IMPORTANDO BIBLIOTECA DO SERVO MOTOR
#include <Keypad.h> // IMPORTANDO BIBLIOTECA DO TECLADO MATRICIAL

#define ROWS 4 // DEFININDO A QUANTIDADE DE LINHAS DO TECLADO MATRICIAL
#define COLUMNS 4 // DEFININDO A QUANTIDADE DE COLUNAS DO TECLADO MATRICIAL

Servo motor; // INSTANCIANDO DA BIBLIOTECA DO SERVO MOTOR, UMA VARIÁVEL MOTOR DO TIPO SERVO

char senha[3] = {'1', '2', '3'}; // ARMAZENANDO SENHA CADASTRADA, COMO EXEMPLO, EM UM VETOR TIPO CHAR DE 3 ÍNDICES
char senhaDigitada[3]; // CRIANDO VARIÁVEL DO TIPO CHAR PARA ARMAZENAR A SENHA INFORMADA PELO USUÁRIO
int i; // CRIANDO VARIÁVEL DO TIPO INTEIRO PARA A CONTAGEM DO ÍNDICES

// ABAIXO É FEITO O MAPEAMENTO DAS TECLAS DO TECLADO MATRICIAL, ARMAZENANDO EM UM VETOR TIPO CHAR DE 4 LINHAS E 4 COLUNAS
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
