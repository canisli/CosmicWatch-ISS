// definitions
io1 = ... // digital input pin for the AND gate
a1 = ... // analog input pin for the first SiPM
a2 = ... // analog input pin for the second SiPM
a3 = ... // analog input pin for the third SiPM
do1 = … digital output of the reset module 
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


void run_when_interrupted():
  // nointerrpts() stops interrupts
  // measure ADC and print to file and reset
  // turn interrupts() back on
}


void write_to_SD(){
  while(1){
      if test_mode{
        // flash the three LEDs when they are each above cutoffs
      }
      // use external interrupt instead so that LED mode doesn't prevent coincidence detections: run this piece of code when I see a high signal


      if (digitalRead(io1) == HIGH){ // Google how to fast digital read to read it one clock cycle // right now it takes 200 ns but another one takes 64 ns.
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
      }
  }
}


void benchmark_di(){ // do the same for analogRead.
  // start timer
  for i // 1000:
  digitalRead(di) // try with fast digital read
  // end timer
  print(time)
}
