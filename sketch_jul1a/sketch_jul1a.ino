int state = 0;
//Gibt den aktuellen Zustand an
void setup(){
  Serial.begin(9600);
  // Legt den Kommunikationskanal auf 9600
  pinMode(5, INPUT);
  pinMode(4, OUTPUT);
  //D4 LED Farbe Grün
  pinMode(3, OUTPUT);
  //D3 LED Farbe Gelb
  pinMode(2, OUTPUT);
  //D2 LED Farbe Rot
}

void loop()
{
  if(digitalRead(5) == HIGH) {
    state = state + 1;
    delay(200);
    Serial.println(state);
  } 
  if(state > 3){
    state = 0;
    Serial.println(state);
  }


  switch (state)
  {
  case 0:
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH);
    
    //Ampel ist Rot
    break;

  case 1:
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(2, HIGH);
    // Ampel ist Rot/Gelb
    break;

  case 2:
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
    //Gelb
    break;
    
  case 3:
    digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    //Grün
    break;

  

  default:
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    break;
  }
  
  
  
  

 
}