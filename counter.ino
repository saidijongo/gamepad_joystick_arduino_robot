void setup() 
{
Serial.begin(115200);
}

void loop() {
  static int counter = 0; 
  Serial.print("Jongo, Arduino-Processing Conn test! Counter: "); 
  Serial.println(counter); 
  counter++; // Increment the counter
  delay(3000);
}

