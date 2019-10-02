//BSides Augusta - Binary Badges 2019         - Twitter and IG @BSidesAugusta
//David Ray      - David@DREAM-Enterprise.com - Twitter and IG @MakeAugusta
//Ashwin Hamal   - ashes09@gmail.com

const int row[4]  = {5,4,3,2};
const int col[6]  = {18,19,16,17,14,15};
int pixels[4][6];

int funct_1  = 12;
int funct_2  = 13;

int led      =  6;

int switch_cond;
int switch_1 =  9;

//internal clock variables
int second_col[2] = {15, 14}; 
int minute_col[2] = {17, 16};
int hour_col[2]   = {19, 18};

unsigned long t_clock;
int i, j, k;
long t;
long offset_t;
byte seconds, mins, hours;
byte s0, s1, m0, m1, h0, h1;
long increment = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("    BSides Augusta   ");
  Serial.println("  2019 Binary Badge  ");
  Serial.println("  October 5th, 2019  ");
  Serial.println("www.BSidesAugusta.org");
  Serial.println();
  Serial.println(" Badges Sponsored by ");
  Serial.println(" SANS - www.sans.org ");
  Serial.println();
  Serial.println(" Badges Designed By: ");
  Serial.println("David Ray Electronics");
  Serial.println("       and More      ");
  Serial.println(" DREAM-Enterprise.com");
  Serial.println();
  
  offset_t = 43200;  //Sets start time to 12:00:00

  //Set pinMode for buttons and LED matrix pins.
  pinMode(funct_1, INPUT_PULLUP);
  pinMode(funct_2, INPUT_PULLUP);

  pinMode(switch_1, INPUT);

  for (i = 0; i < 6; i++) {
    pinMode(col[i], OUTPUT);
    digitalWrite(col[i], HIGH);
  }
  for (i = 0; i < 4; i++)
    pinMode(row[i], OUTPUT);

  //blink status led
  digitalWrite(led, HIGH); delay(250);
  digitalWrite(led, LOW);  delay(250);
  digitalWrite(led, HIGH); delay(250);
  digitalWrite(led, LOW);  delay(250);
  digitalWrite(led, HIGH); delay(250);
  digitalWrite(led, LOW);
}


void loop() {
  
  if (digitalRead(switch_1) == 1){
    t = offset_t + millis() / 1000;  
    
    seconds = t % 60;
    s0 = seconds % 10;
    s1 = seconds / 10;    
    t /= 60;
    mins = t % 60;
    m0 = mins % 10;
    m1 = mins / 10;
    
    t /= 60;
    hours = t % 24;
    h0 = hours % 10;
    h1 = hours / 10;
    t /= 24;
   
    displayTime();
  }
  
}


void displayTime() {  
  if (digitalRead(funct_1) == LOW){
    offset_t -= increment / 100;
    increment += 1;
    offset_t = offset_t % 86400;
  }
  else if (digitalRead(funct_2) == LOW){
    offset_t += increment / 100;
    increment += 1;
    offset_t = offset_t % 86400;
  }
  else {
    increment = 0;
  }

  flickerAt(second_col[0], s0);
  flickerAt(second_col[1], s1);
  flickerAt(minute_col[0], m0);
  flickerAt(minute_col[1], m1);
  flickerAt(hour_col[0], h0);
  flickerAt(hour_col[1], h1);
}

void flickerAt(int col, byte b){
  digitalWrite(col, LOW);
  byteRowOnWith(b);
  delay(2);
  clearByteRow();
  digitalWrite(col, HIGH);
}

void byteRowOnWith(byte b){
  for (i = 0; i < 4; i++){
    digitalWrite(row[i], b & 1);
    b /= 2;
  }
}

void clearByteRow(){
  for (i = 0; i < 4; i++){
    digitalWrite(row[i], LOW);
  }
}
