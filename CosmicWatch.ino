// definitions
io0 = ... // digital input pin for the AND gate
a1 = ... // analog input pin for the first SiPM
a2 = ... // analog input pin for the second SiPM
a3 = ... // analog input pin for the third SiPM
do0 = … digital output of the reset module
do1 = ... led1
do2 = ... led2
do3 = ... lde3 
threshold = ... // ampltiude threshold to flash LED
myFile = ... // location to SD card file


int get_sipm_voltage(adc):
  // ...
}

// sipm1 -> | -> a1
//        |
//        | -> AND gate - > di
//        |
// sipm2 -> | -> a2
//
// sipm3 -> a3


// make somes tests for flashing LED and writing to file

// *************************************************************************************************
void setup(){
  pinMode(io0, INPUT)
  pinMode(a1, INPUT)
  pinMode(a2, INPUT)
  pinMode(a3, INPUT)
  pinMode(do0, OUTPUT);
  pinMode(do1, OUTPUT);//initialize digital pin LED_BUILTIN as an output
  pinMode(do2, OUTPUT);
  pinMode(do3, OUTPUT);

  attachInterrupt(io1, on_detection, RISING);
}
void loop(){
    adc1 = analogRead(a1)
    adc2 = analogRead(a2)
    adc3 = analogRead(a3)
    
    if (adc1 > threshold){
      digitalWrite(do1, HIGH);
    }
    if (adc2 > threshold){
      digitalWrite(do2, HIGH);
    }
    if (adc3 > threshold){
      digitalWrite(do3, HIGH);
    }
    delay(100); //wait for 0.1 second
    digitalWrite(do1, LOW);
    digitalWrite(do2, LOW);
    digitalWrite(do3, LOW);
}
// *************************************************************************************************

void on_detection(){
   noInterrupts()
   adc1 = analogRead(a1)
   adc2 = analogRead(a2)
   adc3 = analogRead(a3)
   temperatureC = ... // maybe read from tempertaure sensor   
   hall_probe1 = ...
   hall_probe2 = ...
   measurement_deadtime = ...

   digitalWrite(do1, HIGH)  // Turn on reset switch

   // put this between reset digital writes as delay.
   output_str = (String)count + " " + time_stamp+ " " + adc1 + " " adc2 + " " adc3 + " " +
                get_sipm_voltage(adc1) + get_sipm_voltage(adc2)+ " " + get_sipm_voltage(adc3)+ " " + 
                  measurement_deadtime+ " " + temperatureC // add other variables like temperature and magnetic field later
   Serial.println(output_str)
   myFile.println(output_str);
   myFile.flush(); // is this needed every loop? 
        
   digitalWrite(do1, LOW) // Turn off reset switch
   
   measurement_deadtime = ...
   interrupts()
}
  
void benchmark_di(){ // do the same for analogRead.
  // start timer
  for i // 1000:
  digitalRead(di) // try with fast digital read
  // end timer
  print(time)
}
