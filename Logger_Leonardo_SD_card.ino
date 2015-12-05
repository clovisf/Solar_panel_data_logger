// Variables used on this code
unsigned long timet;
unsigned long previousTime;
boolean enterFunction= true;
//-----------------------

#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

int voltagePin = A0;
int currentPin = A1;
int tensaoPainel = 0;
int correntePainel = 0;

void setup()
{


  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    // don't do anything more:
    return;
  }

  File dataFile = SD.open("datasol.csv", FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println("Tensao Painel,Corrente Painel,Segundos");
    dataFile.close();
    }else {
    
  }
  
}

void loop()
{
  timet = micros();
  if (enterFunction == true){
    previousTime= timet;
    Serial.println(previousTime); // for debugging

    // Start your code below 
    //-----------------------

     tensaoPainel = analogRead(voltagePin);
     correntePainel = analogRead(currentPin);
    
  // make a string for assembling the data to log:  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datasol.csv", FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print(tensaoPainel);
    dataFile.print(",");
    dataFile.print(correntePainel);
    dataFile.print(",");
    dataFile.println(previousTime/1000000 );    
    dataFile.close();
    }else {
    
  }

  //-----------------------
    // End of your code
  }
  
  // The DELAY time is adjusted in the constant below >> 
  if (timet - previousTime < 4999990){ // 1 million microsencods= 1 second delay
    /* I have actually used 0.999990 seconds, in a trial to compensate the time that
       this IF function takes to be executed. this is really a point that
       need improvement in my code */   
    enterFunction= false;
  } 
  else {
    enterFunction= true;
  }

}









