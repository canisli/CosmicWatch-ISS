// definitions
#define DI1 30 // digital input pin for the AND gate
#define DO1 tbd // digital output of the reset switch

#define ANA1 tbd // analog input pin for the first SiPM
#define ANA2 tbd // analog input pin for the second SiPM
#define ANA3 tbd // analog input pin for the third SiPM

#define LED1 tbd // digital output to led1
#define LED2 tbd // digital output to led2
#define LED3 tbd // digital output to led3 

const int threshold = tbd // ampltiude threshold to flash LED
const string myFile = tbd // location to SD card file

//Calibration fit data for 10k,10k,249,10pf; 20nF,100k,100k, 0,0,57.6k,  1 point
const long double cal[] = {-9.085681659276021e-27, 4.6790804314609205e-23, -1.0317125207013292e-19,
  1.2741066484319192e-16, -9.684460759517656e-14, 4.6937937442284284e-11, -1.4553498837275352e-08,
   2.8216624998078298e-06, -0.000323032620672037, 0.019538631135788468, -0.3774384056850066, 12.324891083404246};

float get_sipm_voltage(float adc_value){
  float voltage = 0;
  for (int i = 0; i < (sizeof(cal)/sizeof(float)); i++) {
    voltage += cal[i] * pow(adc_value,(sizeof(cal)/sizeof(float)-i-1));
    }
    return voltage;
}

// **************************************
// DESIGN
// **************************************
// sipm1 -> | -> a1
//        |
//        | -> AND gate - > di
//        |
// sipm2 -> | -> a2
//
// sipm3 -> a3
// **************************************



// *************************************************************************************************
void setup(){
  pinMode(DI1, INPUT)
  pinMode(DO1, OUTPUT)
  pinMode(ANA1, INPUT)
  pinMode(ANA2, INPUT)
  pinMode(ANA3, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  attachInterrupt(io1, on_detection, RISING);
}
void loop(){ // flicker LEDs for debugging purposes
    adc1 = analogRead(ANA1)
    adc2 = analogRead(ANA2)
    adc3 = analogRead(ANA3)
    
    if (adc1 > threshold){
      digitalWrite(LED1, HIGH);
    }
    if (adc2 > threshold){
      digitalWrite(LED2, HIGH);
    }
    if (adc3 > threshold){
      digitalWrite(LED3, HIGH);
    }
    delay(100); //wait for 0.1 second
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
}
// *************************************************************************************************

void on_detection(){
   noInterrupts()
   adc1 = analogRead(ANA1)
   adc2 = analogRead(ANA2)
   adc3 = analogRead(ANA3)
   temperatureC = ... // maybe read from tempertaure sensor   
   hall_probe1 = ...
   hall_probe2 = ...
   measurement_deadtime = total_deadtime;
   time_stamp = millis() - start_time;
   measurement_t1 = micros();  

   digitalWrite(DO1, HIGH)  // Turn on reset switch

   // put this between reset digital writes as delay.
   output_str = (String)count + " " + time_stamp+ " " + adc1 + " " adc2 + " " adc3 + " " +
                get_sipm_voltage(adc1) + get_sipm_voltage(adc2)+ " " + get_sipm_voltage(adc3)+ " " + 
                  measurement_deadtime+ " " + temperatureC // add other variables like temperature and magnetic field later
   Serial.println(output_str)
   myFile.println(output_str);
   myFile.flush(); // is this needed every loop? 
        
   digitalWrite(DO1, LOW) // Turn off reset switch

   while(analogRead(ANA1) > RESET_THRESHOLD){continue;} // Wait until reset actually works // Is this necessary?
   
   total_deadtime += (micros() - measurement_t1) / 1000.;}
   interrupts()
}

// unfinished pseudocode: ignore for now
void benchmark_di(){ // do the same for analogRead.
  // start timer
    for (int i=0; i<=1000; i++){
        Serial.print("Time: ");
        pinTime = millis();

        digitalRead(DI1);
        Serial.println(pinTime);
      } )
}
}
