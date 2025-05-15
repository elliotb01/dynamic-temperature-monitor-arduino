#include <math.h>

const int B = 4275000;            // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;     // Grove - Temperature Sensor connect to A0

const int max_sample = 60;  // Max sample size
int sample = 12; // Size set at start
int sample_delay = 5000;

float temp_reading[max_sample];       //
float magnitude[max_sample];          //
float temp_diff = 0;                  //
float temp = 0;                       // Global
float prev_temp = 0;                  // Variables
float frequency = 0;                  //
float dominant_frequency = 1.0;       //
int sample_rate = 12;                 //

const int aisPin  = A0;               //
const int numReadings  = 10;          //
int readings [numReadings];           //
int readIndex  = 0;                   //  Moving average
long total  = 0;                      //
                                      //
int aisVal  = 0;                      //


#if defined(ARDUINO_ARCH_AVR)
#define debug Serial
#elif defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_SAM)
#define debug SerialUSB
#else
#define debug Serial
#endif

void setup() {

  Serial.begin(9600);
  Serial.println(F("Initialize System"));
  //Init AnalogSmooth
  pinMode(aisPin, INPUT);

  Serial.println("60 seconds until output");
  delay(500);
  Serial.println("Index | Temperature | Frequency | Magnitude");  // Format of the data that will be outputted

}

void loop() {

  readAnalogSmooth();
  Serial.print(F("ais avg : ")); Serial.println(smooth());
  delay(200);

  collect_temperature_data();       //
  apply_dft();                      //  
  calculate_dominant_frequency();   // Functions that
  update_sample_rate();             // are loop called
  send_data_to_pc();                //
  decide_power_mode();              //

}

void readAnalogSmooth( ) { /* function readAnalogSmooth */
  ////Test routine for AnalogSmooth
  aisVal = analogRead(aisPin);
  Serial.print(F("ais val ")); Serial.println(aisVal);
}

long smooth() { /* function smooth */
  ////Perform average on sensor readings
  long average;
  // subtract the last reading:
  total = total - readings[readIndex];
  // read the sensor:
  readings[readIndex] = analogRead(aisPin);
  // add value to total:
  total = total + readings[readIndex];
  // handle index
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;

  return average;
}

void collect_temperature_data() {

  prev_temp = 0;

  for (int i = 0; i < sample; i++) {

    int a = analogRead(pinTempSensor);
    float R = 1023.0 / a - 1.0;
    R = R0 * R;
    temp = 1.0 / (log(R / R0) / B + 1 / 298.15) - 273.15;
    temp_reading[i] = temp;

    if (i > 0) {

      temp_diff = abs(temp - prev_temp);

      if (temp_diff > 0.1) {

        Serial.println("High temperature change, active mode enabled");
        sample = 30;
        sample_delay = 5000;
        break;
      }
    }

    prev_temp = temp;
    delay(sample_delay);
  }
}

void apply_dft() {
  for (int i = 0; i < sample; i++) {

    float real = 0;
    float imag = 0;

    for (int j = 0; j < sample; j++) {

      real += temp_reading[j] * cos((2 * PI * i * j) / sample);     // To calculate
      imag -= temp_reading[j] * sin((2 * PI * i * j) / sample);     // magnitude

    }

    magnitude[i] = sqrt(real * real + imag * imag);
  }
}

void calculate_dominant_frequency() {
  float sum_freq = 0;
  float sum_freq_mag = 0;

  for (int i = 0; i < sample; i++) {

    frequency = ((float)i * ((float)sample_delay / 1000.0)) / (float)sample;
    sum_freq += frequency;
    sum_freq_mag += frequency * magnitude[i];

  }

  dominant_frequency = (sum_freq != 0) ? sum_freq_mag / sum_freq : 1.0; // Stops it from being set to zero and round it to closest number so it is the correct format
  Serial.print("Dominant Frequency: ");
  Serial.println(dominant_frequency);
}

void update_sample_rate() {

  float new_sample_rate = 2 * dominant_frequency * 60.0;  // Calculating the number of samples to be taken in a minute
  sample = (int)new_sample_rate;

  if (sample < 3) {     // If too low of a sample it will set it to the minimum

    sample = 3;
    Serial.println("Low power mode");

  } else if (sample > max_sample) {

    sample = max_sample;
  }

  Serial.print("Updated Sample Rate: ");
  Serial.println(sample);
}

void send_data_to_pc() {

  for (int i = 0; i < sample; i++) {
    float freq = ((float)i * ((float)sample_delay / 1000.0)) / (float)sample;

    Serial.print(i);                    //
    Serial.print(" | ");                //
    Serial.print(temp_reading[i]);      //
    Serial.print(" | ");                // Outputting the data in the format in the setup function
    Serial.print(freq);                 //
    Serial.print(" | ");                //
    Serial.println(magnitude[i]);       //

    delay(100);
  }
}

void decide_power_mode() {

  float total_diff = 0;
  float power_down_count = 0;

  for (int i = 1; i < sample; i++) {

    total_diff += abs(temp_reading[i] - temp_reading[i - 1]); // Calculating total difference between temperatures to check temperature variation from room temp

  }

  if (total_diff > 2.0) {
    Serial.println("Active power mode");
    sample = 30;
    sample_delay = 5000;
  } else {
    power_down_count++;

    if (power_down_count >= 5) {      // Implemented to activate a low power mode

      Serial.println("Low power mode");
      sample = 3;
      sample_delay = 60000;
      power_down_count = 0;

    } else {

      Serial.println("Idle power mode");
      sample = 12;
      sample_delay = 20000;

    }
  }
}
