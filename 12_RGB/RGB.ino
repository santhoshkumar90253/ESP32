void setup() {
  //defining LED pins as OUTPUT
  pinMode(12,OUTPUT);  
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
}

void loop() {
  digitalWrite(12,HIGH);//turn on RED while keeping GREEN,BLUE in off state.
  digitalWrite(13,LOW);
  digitalWrite(14,LOW);
  delay(2000); 
  
  digitalWrite(12,LOW);//turn on GREEN while keeping RED,BLUE in off state.
  digitalWrite(13,HIGH);
  digitalWrite(14,LOW);
  delay(2000);
  
  digitalWrite(12,LOW);//turn on BLUE while keeping GREEN,RED in off state.
  digitalWrite(13,LOW);
  digitalWrite(14,HIGH);
  delay(2000);
}