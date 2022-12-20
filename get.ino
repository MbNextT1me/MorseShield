#define DATA_LEVEL LOW
#define SPACE_LEVEL HIGH
#define DATA_PIN 2
#define TU 1000

String ENCODE[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int N = 26;

long start_data, start_space;

long duration[20];
long duration_space[20];
bool color[20];

int index = 0;
int previous = SPACE_LEVEL;
bool isEndWord = false;
String message = "";


void decode(){
  bool isEditing = false;
  for (int i=0; i < index; i++){
    if (duration[i] >= 3 and color[i] == false){
      String code = "";
      for (int j=0; j < i; j++){
        Serial.println(duration[j]);
        if (duration[j] == 3 and color[j]){
          code += '-';
        }
        else if (duration[j] == 1 and color[j]){
          code += '.';
        }
        duration[j] = 0;
      }
      duration[i] = 0;
      Serial.println(code);
      for (int il=0; il < N; il++){
        if (code == ENCODE[il]){
         isEditing = true;
         message += LETTERS[il];
         Serial.print(message);
        }
      }
    }
    if (isEditing && isEndWord)
    {
      Serial.print("\n");
      index = 0;
      isEndWord = false;
    }
  }
  if (isEditing)
  {
    index = 0;
    message = "";
  }
}

void fillArr(){
  int current = digitalRead(DATA_PIN);
  if (current == DATA_LEVEL && previous == SPACE_LEVEL){
    start_data = millis();
    duration[index] = int((millis() - start_space + 0.5 * TU) / TU);
    color[index] = false;
    index++;
  }
  else if (current == SPACE_LEVEL && previous == DATA_LEVEL){
    isEndWord = false;
    start_space = millis();
    duration[index] = int((millis() - start_data + 0.5 * TU) / TU);
    color[index] = true;
    index++;
  }
  else if (isEndWord == false && current == SPACE_LEVEL && previous == SPACE_LEVEL){
    long temp = millis() - start_space;
    if (temp > TU * 7)
    {
      isEndWord = true;
      duration[index] = 7;
        index++;
    }
  }
  previous = current;
}


void setup() {
  Serial.begin(9600);
  pinMode(DATA_PIN, INPUT);
}

void loop() {
  fillArr();
  decode();
}