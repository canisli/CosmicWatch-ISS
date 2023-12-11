/**
 * 
 *                 20231110 Version 1.0
   @file flying.ino
   @author howell ivy
   @brief Logic for experiment My-Cool-Experiment
   @version 1.0
   @date 2023-07-15

  20231120 CLI_V1.0 Required to make a complete program - this file, CLI_V1.0,Quest_CLI.h, Quest_Flight.h,Quest_flight.cpp
                  cmd_takeSphot , cmd_takeSpiphoto, nophotophoto, nophoto30K --,clean up code for understanding.
                  
*/

#include "Quest_Flight.h"
#include "Quest_CLI.h"

//////////////////////////////////////////////////////////////////////////
//    This defines the timers used to control flight operations
//////////////////////////////////////////////////////////////////////////
//  Fast clock --- 1 hour = 5 min = 1/12 of an  hour
//     one millie -- 1ms
//
#define SpeedFactor 1    // = times faster
//
//
//////////////////////////////////////////////////////////////////////////
//
#define one_sec   1000                       //one second = 1000 millis
#define one_min   60*one_sec                 // one minute of time
#define one_hour  60*one_min                 // one hour of time
//
//
#define TimeEvent1_time     ((one_sec * 30))      //take a photo time
//#define Sensor1time         ((one_sec * 11))      //Time to make Sensor1 readings 
//#define Sensor2time         ((one_sec * 1.7)) 
//
  int counts = 0;     //counter of times coincidence has been measured
  int deadtime = 0; // keep track of deadtime
  int State =   0;          //FOR TESTING ONLY WILL SWITCH FROM SPI CAMERA TO SERIAL CAMERA EVERY HOUR
//
///////////////////////////////////////////////////////////////////////////
/**
   @brief Flying function is used to capture all logic of an experiment during flight.
*/
//************************************************************************
//   Beginning of the flight program setup
//
//
void Flying() {
  Serial.println("Here to Run flight program, not done yet 20230718");
  Serial.println(" 20231116 working on it");
  //
  uint32_t TimeEvent1 = millis();               //set TimeEvent1 to effective 0
//  uint32_t Sensor1Timer = millis();             //clear sensor1Timer to effective 0
//  uint32_t Sensor2Timer = millis();             //clear sensor1Timer to effective 0
//  uint32_t Sensor1Deadmillis = millis();        //clear mills for difference
//  uint32_t Sensor2Deadmillis = millis();        //clear mills for difference
  //
  uint32_t one_secTimer = millis();             //set happens every second
  uint32_t sec60Timer = millis();               //set minute timer

  //*****************************************************************
  //   Here to set up flight conditions i/o pins, atod, and other special condition
  //   of your program
  pinMode(IO0,  INPUT);
  pinMode(IO1, OUTPUT);
  pinMode(ANA0, INPUT);
  pinMode(ANA1, INPUT);
  pinMode(ANA2, INPUT);
  //
  //******************************************************************

  //------------ flying -----------------------

  Serial.println("Flying NOW  -  x=abort");                 //terminal output for abort back to test
  Serial.println("Terminal must be reset after abort");     //terminal reset requirement upon soft reset

  missionMillis = millis();     //Set mission clock millis, you just entered flight conditions
  //
  //
  /////////////////////////////////////////////////////
  //----- Here to start a flight from a reset ---------
  /////////////////////////////////////////////////////
  //
  DateTime now = rtc.now();                   //get time now
  currentunix = (now.unixtime());             //get current unix time, don't count time not flying
  writelongfram(currentunix, PreviousUnix);   //set fram Mission time start now counting seconds unix time
  //
  //***********************************************************************
  //***********************************************************************
  //  All Flight conditions are now set up,  NOW to enter flight operations
  //
  //***********************************************************************
  //***********************************************************************
  //
  while (1) {
    //
    //----------- Test for terminal abort command (x) from flying ----------------------
    //
    while (Serial.available()) {      //Abort flight program progress
      byte x = Serial.read();         //get the input byte
      if (x == 'x') {                 //check the byte for an abort x
        return  ;                     //return back to poeration sellection
      }                               //end check
    }                                 //end abort check

    if (digitalRead(IO0 == HIGH)) {
      noInterrupts();
      uint32_t t_start = millis();
      
      digitalWrite(IO1, HIGH);  // Trigger reset
      Serial.println("Got coincidence measurment!");
      counts += 1;
      int adc0 = analogRead(ANA0);
      int adc1 = analogRead(ANA1);
      int adc2 = analogRead(ANA2);
      
      dataappend(counts, adc0, adc1, adc2, deadtime); 
      digitalWrite(IO1, LOW); // Turn off trigger reset
      deadtime = millis() - t_start;
      interrupts();
    }
//------------------------------------------------------------------
//
//*********** Timed Event 1 test ***************************************
//
    //  this test if TimeEvent1 time has come
    //  See above for TimeEvent1_time settings between this event
    //
    if ((millis() - TimeEvent1) > TimeEvent1_time) {
      TimeEvent1 = millis();
      Serial.println("Running nophoto30K");
      dataappend(0,0,0,0,0); // Sanity check for the SD card
      nophoto30K();               //Use photo buffer for data
    }                                               //end of TimeEvent1_time
    //------------------------------------------------------------------
    //
//*******************************************************************************
//*********** One second counter timer will trigger every second ****************
//*******************************************************************************
    //  Here one sec timer - every second
    //
    if ((millis() - one_secTimer) > one_sec) {      //one sec counter
      one_secTimer = millis();                      //reset one second timer
      DotStarYellow();                              //turn on Yellow DotStar to Blink for running
      //
//****************** NO_NO_NO_NO_NO_NO_NO_NO_NO_NO_NO_ *************************
// DO NOT TOUCH THIS CODE IT IS NECESARY FOR PROPER MISSION CLOCK OPERATIONS
//    Mission clock timer
//    FRAM keep track of cunlitive power on time
//    and RTC with unix seconds
//------------------------------------------------------------------------------
      DateTime now = rtc.now();                           //get the time time,don't know how long away
      currentunix = (now.unixtime());                     //get current unix time
      Serial.print(currentunix); Serial.print(" ");      //testing print unix clock
      uint32_t framdeltaunix = (currentunix - readlongFromfram(PreviousUnix)); //get delta sec of unix time
      uint32_t cumunix = readlongFromfram(CumUnix);       //Get cumulative unix mission clock
      writelongfram((cumunix + framdeltaunix), CumUnix);  //add and Save cumulative unix time Mission
      writelongfram(currentunix, PreviousUnix);           //reset PreviousUnix to current for next time
//
//********* END_NO_END_NO_END_NO_END_NO_END_NO_END_NO_ **************************
      //
      //  This part prints out every second
      //
      Serial.print(": Mission Clock = ");      //testing print mission clock
      Serial.print(readlongFromfram(CumUnix));        //mission clock
      Serial.print(" is ");                        //spacer
      //
      //------Output to the terminal  days hours min sec
      //
      getmissionclk();
      Serial.print(xd); Serial.print(" Days  ");
      Serial.print(xh); Serial.print(" Hours  ");
      Serial.print(xm); Serial.print(" Min  ");
      Serial.print(xs); Serial.println(" Sec");
      //
      //
       DotStarOff();
    }  // end of one second routine    
  }       // End of while 
}         //End nof Flighting
//
//
//
////FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
//  Function to write into a 30K databuffer
//    char databuffer[30000];         // Create a character buffer with a size of 2KB
//    int databufferLength = 0;       // Initialize the buffer length
//  Append data to the large data buffer buffer always enter unit time of data added
//  enter: void dataappend(int counts, int ampli, int SiPM, int Deadtime) (4 values)
//
void dataappend(int counts,int adc0,int adc1, int adc2, int Deadtime) {          //entry, add line with values to databuffer
  //----- get and set time to entry -----
  DateTime now = rtc.now();                                               //get time of entry
  String stringValue = String(now.unixtime());                            //convert unix time to string
  const char* charValue = stringValue.c_str();                            //convert to a C string value
  appendToBuffer(charValue);                                              //Sent unix time to databuffer
  //----- add formated string to buffer -----
  String results = " - " + String(counts) + " " + String(adc0) + " " + String(adc1) + " " + String(adc2) + " " + String (Deadtime) + "\r\n";  //format databuffer entry
  const char* charValue1 = results.c_str();                               //convert to a C string value
  appendToBuffer(charValue1);                                             //Send formated string to databuff
  //
  //  Serial.println(databufferLength);                                   //print buffer length for testing only
}
//-----------------------                                               //end dataappend
//----- sub part od dataappend -- append to Buffer -----
//-----------------------
void  appendToBuffer(const char* data) {                                   //enter with charator string to append
  int dataLength = strlen(data);                                          //define the length of data to append
      // ----- Check if there is enough space in the buffer                           //enough space?
  if (databufferLength + dataLength < sizeof(databuffer)) {               //enouth space left in buffer
      // ----- Append the data to the buffer
    strcat(databuffer, data);                                             //yes enough space, add data to end of buffer
    databufferLength += dataLength;                                       //change to length of the buffer
  } else {
    Serial.println("Buffer is full. Data not appended.");                 //Not enough space, say so on terminal
  }       //end not enough space
}         //end appendToBuffer
//

//=================================================================================================================
// Events to simulate cosmic ray detections
//if ((millis() - Sensor1Timer) > Sensor1time) {    //Is it time to read?
//      t_start = millis(); //set millis this visit
//      Serial.println("WOW BIG COSMIC RAY!!!!!!!!!!!!!!");
//      Sensor1Timer = millis();                        //Yes, lets read the sensor1
//      counts++;
//      //
//      //  Here to calculate and store data
//      //
//      //
//      //**** now get ampli and SiPM *****
//      int ampli = 9000;              //SIMULATED
//      int SiPM  = random(9000);              //SIMULATED
//      //***** end simulated *************
//      //
//      dataappend(sensor1count, 0, ampli, SiPM, Deadtime);
//      int Deadtime = millis()-t_start;      
//    }     // End of Sensor1 time event
//    //
//
//    if ((millis() - Sensor2Timer) > Sensor2time) {    //Is it time to read?
//      Serial.println("Cosmic ray measurment!");
//      Sensor2Timer = millis();                        //Yes, lets read the sensor1
//      counts++;
//      //
//      //  Here to calculate and store data
//      //
//      int Deadtime = millis()-Sensor2Deadmillis;      //time in millis sence last visit
//      Sensor2Deadmillis = millis(); //set millis this visit
//      //
//      //**** now get ampli and SiPM *****
//      int ampli = random(300);              //SIMULATED
//      int SiPM  = 77;              //SIMULATED
//      //***** end simulated *************
//      //
//      dataappend(counts , 0, ampli, SiPM, Deadtime);
//      }
