#define DATA_LEVEL LOW
#define SPACE_LEVEL HIGH
#define DATA_PIN 9
#define TU 1000

String ENCODE[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int N = 26;

void send_letter(String code) {
  Serial.println(code);
  int code_len = code.length(); 
  for (int i = 0; i < code_len; i++){
     char symbol = code[i];
     if (symbol == '.'){
       digitalWrite(DATA_PIN, DATA_LEVEL);
       delay(TU);
      }
      else{
        digitalWrite(DATA_PIN, DATA_LEVEL);
        delay(3 * TU);
      }
      digitalWrite(DATA_PIN, SPACE_LEVEL);
      delay(TU);
   }
   delay(2 * TU);
}

void send_sep_word(){
  digitalWrite(DATA_PIN, SPACE_LEVEL);
  delay(4 * TU);
  Serial.print(" ");
}

void setup() {
  Serial.begin(9600);
  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, SPACE_LEVEL);
}

void loop() {
  if(Serial.available() >= 1){
    char letter = Serial.read();
    if (letter == ' '){
      send_sep_word();
    }
    else{
      for (int il = 0; il < N; il++){
        if (letter == LETTERS[il]){
          String code = ENCODE[il];
          send_letter(code);
        }
      }
    }  
  }
}