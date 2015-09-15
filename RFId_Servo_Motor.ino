#include <Servo.h> // IMPORTAÇÃO DA BIBLIOTECA DO SERVO

// IMPORTAÇÃO DA BIBLIOTECA PADRÃO DA PLACA ARDUINO
#include <SPI.h>
#include <MFRC522.h> // IMPORTAÇÃO DA BIBLIOTECA DO RFId

#define SS_PIN 10 // DEFINIÇÃO DE PINO SDA DO RFId
#define RST_PIN 9 // DEFINIÇÃO DO PINO RST DO RFId

// DEFINIÇÃO DE PINOS DE COMUNICAÇÃO, PINO 10 E 9, SDA E RST.
MFRC522 mfrc522(SS_PIN, RST_PIN);

char st[20]; // CRIAÇÃO DE VETOR CHAR

// INSTANCIANDO DA BIBLIOTECA DO SERVO
// VARIÁVEL motor, TIPO Servo
Servo motor;
// FUNÇÃO DE DEFINIÇÃO DAS VARIÁVEIS
void setup() {
  // ABRINDO A COMUNICAÇÃO SERIAL, LIBERANDO A PORTA
  Serial.begin(9600); // BAUD RATE DE 9600
  SPI.begin(); // INICIA O PROTOCOLO SPI
  mfrc522.PCD_Init(); // INICIA MFRC522, RFId
  
  // IMPRESSÃO DE FRASE INICIAL NA PORTA SERIAL
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println(); // QUEBRA DE LINHA
  pinMode(2, OUTPUT);  // PINO DOIS, SAÍDA, LED VERDE, PERMITIDO
  pinMode(3, OUTPUT);  // PINO TRÊS, SAÍDA, LED VERMELHO, NÃO PERMITIDO
  motor.attach(8); // SINAL DE ENERGIA DO SERVO, PINO 8
}
// INÍCIO DA FUNÇÃO QUE FICARÁ REPETINDO ATÉ DESLIGAMENTO DA PLACA
void loop() {
  // AGUARDA A APROXIMAÇÃO DO CARTÃO
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  // FUNÇÃO PARA A LEITURA DO CARTÃO
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  Serial.print("ID da tag: "); // IMPRESSÃO PORTA SERIAL
  String conteudo = ""; // VARIÁVEL QUE ARMAZENA O CÓDIGO DA TAG
  // VARIÁVEL QUE COLETA OS BYTES LIDOS
  byte letra; // APÓS A LEITURA É CONVERTIDA NA VARIÁVEL conteudo
  // LAÇO DE REPETIÇÃO PARA IMPRESSÃO DO ID DA TAG RFId, E CONCATENAÇÃO
  for (byte i = 0; i < mfrc522.uid.size; i++) { 
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  Serial.println(); // QUEBRA DE LINHA
  Serial.print("Mensagem: "); // IMPRESSÃO DE MENSAGEM PORTA SERIAL
  conteudo.toUpperCase(); // PASSANDO TAG PARA MAIÚSCULAS
  
  // CONDICIONAL PARA IGUALAR ID DA TAG CADASTRADA
  if (conteudo.substring(1) == "04 81 CF 1E") { // ID da Tag cadastrada
      motor.write(90); // POSICIONAR MOTOR EM 90 GRAUS, ABRIR PORTA
      Serial.println("Acesso liberado!"); // IMPRESSÃO PORTA SERAL
      Serial.println(); // QUEBRA DE LINHA
      digitalWrite(2, HIGH); // ACENDENDO LED VER, PERMITIDO, PORTA 2
      delay(1000); // AGUARDANDO 1 SEGUNDO
      motor.write(1); // POSICIONANDO MOTOR EM 1 GRAU
      delay(3000); // AGUARDANDO 3 SEGUNDOS
      delay(3000); // AGUARDANDO 3 SEGUNDOS
      digitalWrite(2, LOW); // DESLIGANDO LED VERDE
      motor.write(90); // VOLTANDO MOTOR, POSICIONANDO EM 90 GRAUS
   } else { // CONDICIONAL, SE TAG NÃO CADASTRADA
      digitalWrite(3, HIGH); // LIGANDO LED VERMELHO, NÃO PERMITIDO
      Serial.println("Acesso negado!"); // IMPRESSÃO PORTA SERAL
      Serial.println(); // QUEBRA DE LINHA
      delay(3000); // AGUARDANDO 3 SEGUNDOS
      digitalWrite(3, LOW); // DESLIGANDO LED VERMELHO, NÃO PERMITIDO
   } // FECHAMENTO DE CONDICIONAL
} // FECHAMENTO DE FUNÇÃO LOOP (REPETIÇÃO)
