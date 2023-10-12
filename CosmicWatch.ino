// definitions
io1 = ... // digital input pin for the AND gate
a1 = ... // analog input pin for the first SiPM
a2 = ... // analog input pin for the second SiPM
a3 = ... // analog input pin for the third SiPM
do1 = … digital output of the reset module
do2 = ... led1
do3 = ... led2
do4 = ... lde3 
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

void setup(){
  pinMode(do2, OUTPUT);//initialize digital pin LED_BUILTIN as an output
  pinMode(do3, OUTPUT);
  pinMode(do4, OUTPUT);
}

void run_when_interrupted():
  // nointerrpts() stops interrupts
  // measure ADC and print to file and reset
  // turn interrupts() back on
  attachInterrupt(do1, on_detection, RISE);
}


void on_detection(){
   noInterrupts()
   adc1 = analogRead(a1)
   adc2 = analogRead(a2)
   adc3 = analogRead(a3)
   temperatureC = ... // maybe read from tempertaure sensor   
   hall_probe1 = ...
   hall_probe2 = ...
   measurement_deadtime = ...

   digitalWrite(do1, HIGH)  // 200 ns might be enough (test). But we can analogRead just to slow things down


   // put this between reset digital writes as delay.
   // Serial.println(...)
   myFile.println((String)count + " " + time_stamp+ " " + adc1 + " " adc2 + " " adc3 + get_sipm_voltage(adc1) + get_sipm_voltage(adc2)+ " " + get_sipm_voltage(adc3)+ " " + measurement_deadtime+ " " + temperatureC + ...);
   myFile.flush(); // is this needed every loop? 
         
   digitalWrite(do1, LOW)
   // update measurement_deadtime
   interrupts()
}
  
void write_to_SD(){
  while(1){
    adc1 = analogRead(a1)
    adc2 = analogRead(a2)
    adc3 = analogRead(a3)
    
    if (adc1 > threshold){
      digitalWrite(LED_BUILTIN, HIGH);
    }
    if (adc2 > threshold){
      digitalWrite(LED_BUILTIN, HIGH);
    }
    if (adc3 > threshold){
      digitalWrite(LED_BUILTIN, HIGH);
    }
    delay(100); //wait for 0.1 second
    digitalWrite(LED_BUILTIN, LOW);
  }
}


void benchmark_di(){ // do the same for analogRead.
  // start timer
  for i // 1000:
  digitalRead(di) // try with fast digital read
  // end timer
  print(time)
}
