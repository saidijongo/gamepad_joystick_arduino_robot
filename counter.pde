import processing.serial.*;
import cc.arduino.*;



Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port
Arduino arduino;

void setup()
{
  println(Arduino.list());
  String portName = Serial.list()[0]; 
  myPort = new Serial(this, portName, 115200);
}


void draw()
{
  if ( myPort.available() > 0) 
  {  // If data is available,
  val = myPort.readStringUntil('\n');  
  } 
println(val);
}