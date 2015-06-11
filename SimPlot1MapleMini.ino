/*

SimPlot
From Analog to PC plot
http://www.negtronics.com/simplot
Samples Analog Input and sends them over serial port to be plotted in SimPlot. 
For details of SimPlot go to
www.negtronics.com/simplot

2015 06 11 by zoomx
Changed for MapleMini
int -> uint16

*/

uint16 buffer[20]; //Buffer needed to store data packet for transmission
uint16 data1;

void setup() 
{ 
  Serial.begin(57600);
  Serial.println("SimPlot");
} 

void loop() 
{ 

  //Read Analog channels. You can connect accelerometer, gyro, temperature sensor etc to these channels
  data1 = analogRead(3);
  //data2 = analogRead(4);
  //data3 = analogRead(5);
  //data4 = analogRead(6);
  
  //You can plot upto 4 channels of data. Uncomment only one of the options below
 
//  plot(data1,data2,data3,data4);   //Plots 4 channels of data
//  plot(data1,data2,data3);      //Plots 3 channels of data
//  plot(data1,data2);            //Plots 2 channels of data
  plot(data1);                  //Plots 1 channel of data
  
  delay(10); //Read and plot analog inputs every 10ms.  
} 


//Function that takes 1 integer value and generates a packet to be sent to SimPlot.
void plot(int data1)
{
  /*
  int pktSize;
  
  buffer[0] = 0xCDAB;             //SimPlot packet header. Indicates start of data packet
  buffer[1] = 1*sizeof(int);      //Size of data in bytes. Does not include the header and size fields
  buffer[2] = data1;
    
  pktSize = 2 + 2 + (1*sizeof(int)); //Header bytes + size field bytes + data
  
  //IMPORTANT: Change to serial port that is connected to PC
  Serial.write((uint8_t * )buffer, pktSize);
  */
  buffer[0] = 0xCDAB;             //SimPlot packet header. Indicates start of data packet
  buffer[1] = 2;      //Size of data in bytes. Does not include the header and size fields
  buffer[2] = data1;

  Serial.write((uint8_t * )buffer,6);
}
