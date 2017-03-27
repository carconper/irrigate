
const short VALVE_PIN = 3;  

void setup() {
  // Setting up Serial console
  Serial.begin(57600);
  
  // put your setup code here, to run once:
  pinMode(VALVE_PIN, OUTPUT);     //Solenoid pin
  digitalWrite(VALVE_PIN, LOW);   //Make sure the valve is off
  pinMode(13, OUTPUT);
}

void loop() {      
  // put your main code here, to run repeatedly:
  Serial.println("Set to off");
  digitalWrite(13, LOW);
  digitalWrite(VALVE_PIN, LOW);
  Serial.println("Lets wait for 5 seconds");
  delay(5000);
  Serial.println("Set to on");
  digitalWrite(13, HIGH);
  digitalWrite(VALVE_PIN, HIGH);
  Serial.println("Leave on 3 seconds");
  delay(3000);
}
