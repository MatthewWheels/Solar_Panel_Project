 //Reading data from SD card with Arduino
#include <SPI.h>
#include <SD.h>
File myFile;
char fileName[] = "DATA.txt";
const int chipSelect = 10;

  
  int minute=0;
  int hour=0;
  int day=0;
  int weekAmount=1;
  int dayAmount=1;

  
  int averages[7][24];
  int minuteValue[60];
  int total=0;
  int hourAverage[24];

  
  boolean weekComplete=false;


  int led = 9;
  float brightness = 0;


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600); 

  pinMode(led, OUTPUT);

  setUpSD();
}

void loop() 
{

minute++;

  if(minute>59)
  {
    calculateHourAverage(day, hour); 
     compileDataToSD(day, hour);
    hour++;
     adjustBrightness(hourAverage[hour]);
    minute=0;
   
  }

  if(hour>23)
  {
   
      calculateOverallHourAverages();
    
    day++;
    dayAmount++;
    hour=0;
  }

  if(day>6)
  {
    weekComplete=true;
    weekAmount++;
    finishWeekOfData();
    day=0;
  }
  delay(60000);
 
  int sensorValue=analogRead(A0);
 storeMinuteData(sensorValue, minute);



 analogWrite(led, brightness);
}

void adjustBrightness(int value)

{
  
  brightness=map((float)value, 0, 500, 0, 255); 

  if(brightness>255)
  {
    brightness=255;
  }
  if(brightness<0)
  {
    brightness=0;
  }

}

void storeMinuteData(int voltage, int minute)
  {
    minuteValue[minute]=voltage;
  }
  
  void calculateHourAverage(int day, int hour)
  {
    for(int i=0; i<60; i++)
    {
      total-=minuteValue[i];
    }
   averages[day][hour]=((int)total/60);
   total=0;
  }
  
  void calculateOverallHourAverages()
  {

    if(dayAmount >=7)
    {
      
      for(int hours=0; hours<24; hours++)
      {
        for(int days=0; days<7; days++)
        {
          total+=averages[days][hours];
        }
       hourAverage[hours]=(total/7);
       total=0; 
      }
    }
    else
    {
      for(int hours=0; hours<24; hours++)
      {
        for(int days=0; days<dayAmount; days++)
        {
          total+=averages[days][hours];
        }
       hourAverage[hours]=(total/7);
       total=0; 
      }
    }
    
  }
  
  int getAverage(int day, int hour)
  {
    return averages[day][hour];
  }
  
  int getHourAverage(int hour)
  {
    return hourAverage[hour];
  }

void setUpSD()
{
    if (SD.begin(chipSelect))
    {
    Serial.println("SD card is present & ready");
    } 
    else
    {
    Serial.println("SD card missing or failure");
    while(1);  //wait here forever
    }

    myFile = SD.open(fileName, FILE_WRITE);
}
  void compileDataToSD(int days, int hours)
  {
    
    if(myFile)
    {
    Serial.println("Writing to DATA.txt");
    
    myFile.println("Day: "  +  (String)dayAmount + ", Hour: "  +  (String)hours + ", Intensity Value: "  +  (String)averages[days][hours]);
    Serial.println();
    myFile.flush();
    Serial.println("finished writing to SD");
    }
    else
      Serial.println("Error opening DATA.txt");
  }


void finishWeekOfData()
{
  if(myFile)
    {
    Serial.println("Writing to DATA.txt");
    myFile.println();
    myFile.println("End of Week: " + weekAmount);
    myFile.println();
     Serial.println();
    myFile.flush();
    Serial.println("finished writing to SD");
    }
    else
      Serial.println("Error opening DATA.txt");
}
