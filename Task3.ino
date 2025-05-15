# include <math.h>

const int B = 4275000;            // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;     // Grove - Temperature Sensor connect to A0
const int max_sample = 180;
int sample = 180;
int sample_delay = 1000;

float temp_reading[max_sample];
float magnitude[max_sample];

# if defined(ARDUINO_ARCH_AVR)
# define debug  Serial
# elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
# define debug  SerialUSB
# else
# define debug  Serial
# endif

void setup() {

    Serial.begin(9600);

    //Serial.print(sample);
    //Serial.println(" seconds until output");
    //delay(500);
    //Serial.println("Index | Temperature | Frequency | Magnitude");

    


}

void loop() {

    collect_temperature_data();
    apply_dft();
    send_data_to_pc();
    decide_power_mode();

}

void collect_temperature_data() {

    if (sample_delay == 1000) {

        sample = 180;

        for (int i = 0; i < 180; i++){

            int a = analogRead(pinTempSensor);
            float R = 1023.0/a-1.0;
            R = R0*R;
            float temp = 1.0/(log(R/R0)/B+1/298.15)-273.15;
            temp_reading[i] = temp;
            delay(sample_delay);
            //Serial.println("Taking temperature on high power");
        

    }

    } else if (sample_delay == 5000) {

        sample = 36;

        for (int i = 0; i < 36; i++){

            int a = analogRead(pinTempSensor);
            float R = 1023.0/a-1.0;
            R = R0*R;
            float temp = 1.0/(log(R/R0)/B+1/298.15)-273.15;
            temp_reading[i] = temp;
            delay(sample_delay);
           // Serial.println("Taking temperature on medium power");
        

    }

    } else if (sample_delay == 30000) {

        sample = 6;

        for (int i = 0; i < 6; i++){

            int a = analogRead(pinTempSensor);
            float R = 1023.0/a-1.0;
            R = R0*R;
            float temp = 1.0/(log(R/R0)/B+1/298.15)-273.15;
            temp_reading[i] = temp;
            delay(sample_delay);
           // Serial.println("Taking temperature on low power");

    }

    } else {

        Serial.println("Sample error");

    }

}

void apply_dft() {

    for (int i = 0; i < sample; i++) {

        float real = 0;
        float imag = 0;

        for (int j = 0; j < sample; j++) {

            real += temp_reading[j] * cos((2 * PI * i * j) / sample);
            imag -= temp_reading[j] * sin((2 * PI * i * j) / sample);

        }

        magnitude[i] = sqrt(real*real + imag*imag);

    }

}

void send_data_to_pc() {

    for (int i = 0; i < sample; i++) {

        float frequency = ((float)i*((float)sample_delay/(1000)))/(float)sample;
        
        Serial.print(i);
        Serial.print(" | ");
        Serial.print(temp_reading[i]);
        Serial.print(" | ");
        Serial.print(frequency);
        Serial.print(" | ");
        Serial.println(magnitude[i]);

        delay(200);

    }



}

void decide_power_mode() {

    float frequency_total = 0;

    for (int i = 0; i < sample; i++) {

        frequency_total += ((float)i*((float)sample_delay/(1000)))/(float)sample;

    }

    float frequency_avg = (float)frequency_total/(float)sample;

    if (frequency_avg > 0.5) { 

        //Serial.println("ACTIVE POWER MODE");
        sample_delay = 1000;

    } else if (frequency_avg <= 0.5 && frequency_avg > 0.1) {

        //Serial.println("IDLE POWER MODE");
        sample_delay = 5000;

    } else {

        //Serial.println("POWER DOWN MODE");
        sample_delay = 30000;
        
    }


}


