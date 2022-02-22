import processing.serial.*;

Serial myPort;  // Create object from Serial class
static String rawString;    // Data received from the serial port
int sensorVal = 0;

color c;  
void setup()
{
  size(800,800);
  background(200);

  String portName = "COM3";// Change the number (in this case ) to match the corresponding port number connected to your ESP32. 
  myPort = new Serial(this, portName, 9600);
}

void draw()
{
  
  if ( myPort.available() > 0) {  // If data is available,
  rawString = myPort.readStringUntil('\n'); 
  
  try {
    String[] rgb = split(rawString,",");
    String rgbText = rgb[0] + ", " + rgb[1] + ", " + rgb[2];
    println(rgbText);
    
    c = color( int(rgb[0]), int(rgb[1]), int(rgb[2].trim())) ;  // color of the observed values

    background(200); //clear UI by setting background
    
    //text to show the measured RGB values 
    fill(c); 
    textSize(48);
    text(rgbText, 400, 700); 
    textAlign(CENTER);
    
    //Draw Rectangle of detected Color
    fill(c);    
    rect(200, 200, 400, 400, 10);  
  }
  catch(Exception e) {
    println(rawString);  
  }
  }  
}
