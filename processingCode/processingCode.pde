import controlP5.*;
import processing.serial.*;

ControlP5 cp5;

ColorWheel cw;
int c;
String cs;
Serial serialP;

void setup(){
  size(800,800);
  noStroke();
  cp5 = new ControlP5(this);
  cw = cp5.addColorWheel("wheel",0,0,800);
  // If the first port on Serial.list() is not your Arduino
  // change accordingly
  try{
    String arduinoP = Serial.list()[0];
    serialP = new Serial(this, arduinoP, 9600);
  }
  catch(ArrayIndexOutOfBoundsException e){
    println("ERROR: No COM port on that index.");
    printArray(Serial.list());
    exit();
  }
}

void draw() {  
  background(0);
}

void mouseReleased() {
  c = cp5.get(ColorWheel.class,"wheel").getRGB();
  cs = "#" + hex(c, 6); // Prepares a string to be sent to arduino. The '#' is used to we can identify we're receiving a color
  println(cs);
  serialP.write(cs);  // writes to arduino
}
