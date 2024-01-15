#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>
#include <math.h>
#include <string>

// definitions
#define IO0 14 // AND gate
#define IO1 18 // trigger reset

#define ANA0 5 // analog input pin for the first SiPM
#define ANA1 6 // analog input pin for the second SiPM
#define ANA2 7 // analog input pin for the third (lone) SiPM

const int threshold = -1; // ampltiude threshold to flash LED
const std::string filename = 'tbd';
File myFile;
const bool groundMode = true; // set to False when sending to ISS. REMOVE LED before sending to space. Light leak could cause false detection.

//Calibration fit data for 10k,10k,249,10pf; 20nF,100k,100k, 0,0,57.6k,  1 point
// use arbitrary wave form generator to get our own values.
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
  pinMode(IO0,  INPUT);
  pinMode(IO1, OUTPUT);
  pinMode(ANA0, INPUT);
  pinMode(ANA1, INPUT);
  pinMode(ANA2, INPUT);

  attachInterrupt(DI1, on_detection(), RISING);
}

void loop(){ // flicker LEDs for debugging purposes
    if groundMode {
      adc1 = analogRead(ANA1);
      adc2 = analogRead(ANA2);
      adc3 = analogRead(ANA3);
      
      if (adc1 > threshold){
        digitalWrite(LED1, HIGH);
      }
      if (adc2 > threshold){
        digitalWrite(LED2, HIGH);
      }
      if (adc3 > threshold){
        digitalWrite(LED3, HIGH);
      }
      // TODO: change to use pulse width modulation
      delay(10); //wait for 0.1 second
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
    }
}
// *************************************************************************************************

void on_detection(){
    noInterrupts();
    adc0 = analogRead(ANA0);
    adc1 = analogRead(ANA1);
    adc2 = analogRead(ANA2);

    measurement_deadtime = total_deadtime;
    time_stamp = millis() - start_time;
    measurement_t1 = micros();

    digitalWrite(IO1, HIGH)  // Turn on reset switch

    // put this between reset digital writes as delay.
    output_str = (String)count + " " + time_stamp+ " " + adc1 + " " adc2 + " " adc3 + " " +
                get_sipm_voltage(adc1) + get_sipm_voltage(adc2)+ " " + get_sipm_voltage(adc3)+ " " + 
                  measurement_deadtime+ " " + temperatureC + "\r\n" // add other variables like temperature and magnetic field later
    

    Serial.print(output_str);
    //dataappend(output_str)
    //myFile.print(output_str);
    //myFile.flush(); // is this needed every loop? 
        
    digitalWrite(IO1, LOW); // Turn off reset switch

    // while(analogRead(ANA1) > RESET_THRESHOLD){
    //   Serial.println('Something went wrong*. Check waveform');
    // }

    total_deadtime += (micros() - measurement_t1) / 1000.;
    interrupts();
}

// unfinished pseudocode: ignore for now
void benchmark_di(){ // do the same for analogRead.
  // start timer
    for (int i=0; i<=1000; i++){
        Serial.print("Time: ");
        pinTime = millis();

        digitalRead(DI1);
        Serial.println(pinTime);
    } 
}

