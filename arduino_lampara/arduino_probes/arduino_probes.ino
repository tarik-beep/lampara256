// Arduino server for Color LEGO_Arduino.vbai 

const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data
char estat = 'R';
char estatRGB = 'R';

boolean newData = false;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(8,INPUT_PULLUP);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  buttonPres();
  recvWithEndMarker();
  if (newData == true){
    procesData();
    //sendData(); 
    newData = false; 
  }    
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
   
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();
    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void buttonPres(){
  if(digitalRead(8)==LOW){
     Serial.write('S');
     delay(500);
  }
}

void procesData() {
  if (strcmp(receivedChars, "PASS")==0){
    digitalWrite(13,LOW);
    digitalWrite(12,LOW);
    delay(300);
    digitalWrite(12,HIGH);
    estat = 'P';
    //Serial.println("PASS");
  }
  if (strcmp(receivedChars, "FAIL")==0){
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    delay(300);
    digitalWrite(13,HIGH);
    estat = 'F';
    //Serial.println("FAIL");
  }
  if (estatRGB == 'R'){
    int number = atoi( receivedChars );
    analogWrite(3, number);
    estatRGB ='G';
  }
  else if (estatRGB == 'G'){
    int number = atoi( receivedChars );
    analogWrite(5, number);
    estatRGB ='B';
  }
  else if (estatRGB == 'B'){
    int number = atoi( receivedChars );
    analogWrite(6, number);
    analogWrite(9, number);
    estatRGB ='R';
  }
  else{
    
  }
}

void sendData(){
  Serial.write(estat);
}
