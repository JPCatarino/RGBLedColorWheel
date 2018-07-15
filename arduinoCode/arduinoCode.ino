// Arduino Color Wheel

const int R_LED = 9;
const int G_LED = 10;
const int B_LED = 11;
const int BUTTON = 12;

int btn = LOW;
int old_btn = LOW;
int state = 0;
byte r = 0;
byte g = 0;
byte b = 0;
byte inByte = 0;
int pointer = 0;
char buffer[7];

void setup() {
  Serial.begin(9600);
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  if(Serial.available() > 0){
    inByte = Serial.read();
    // If '#' is found, we know the next 6 characters are part of a color
    if(inByte == '#'){
      while(pointer < 6){
        buffer[pointer] = Serial.read();
        pointer++;
      }
      // Since we have the RGB values stored as hex, we need to decode them accordingly
      r = hex2dec(buffer[1]) + hex2dec(buffer[0]) * 16;
      g = hex2dec(buffer[3]) + hex2dec(buffer[2]) * 16;
      b = hex2dec(buffer[5]) + hex2dec(buffer[4]) * 16;
      pointer = 0;
    }
  }

  btn = digitalRead(BUTTON); 

  if ((btn == HIGH) && (old_btn == LOW)){
    state = 1 - state;
  }

  old_btn = btn; 

  if (state == 1) { 
    analogWrite(R_LED,r);
    analogWrite(G_LED,g);
    analogWrite(B_LED,b);
  } 
  else {
    analogWrite(R_LED, 0);  
    analogWrite(G_LED, 0);
    analogWrite(B_LED, 0);
  }
  
  delay(100);
}

// converts one HEX character into a number
// taken from Make: Getting Started with Arduino 
int hex2dec(byte c) { 
    if (c >= '0' && c <= '9') {
      return c - '0';
    } else if (c >= 'A' && c <= 'F') {
      return c - 'A' + 10;
    }
}

