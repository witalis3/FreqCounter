#include "Arduino.h"
// Frequency Counter Lib example
/*
  Martin Nawrath KHM LAB3
  Kunsthochschule fÂ¸r Medien KË†ln
  Academy of Media Arts
  http://www.khm.de
  https://interface.khm.de/index.php/lab/interfaces-advanced/arduino-frequency-counter-library/index.html
  inne: https://interface.khm.de/index.php/lab/interfaces-advanced/index.html
  - wejście: pin 5

  - testy
  	  - liczy do około 7,5MHz (bramka 1ms)
  	  - liczy nieco powyżej 7515 zamiast 7500; nie da się skompensować (można tylko w drugą stronę)
  	  	  - nie szkodzi ;-)

 */
#include <FreqCounter.h>

unsigned long frq;
int cnt;
int pinLed=13;

void setup()
{
  pinMode(pinLed, OUTPUT);
  pinMode(12, OUTPUT);	// cała pętla
  pinMode(11, OUTPUT); // pomiar bramki
  Serial.begin(115200);        // connect to the serial port
  Serial.println("Frequency Counter on Nano");
  FreqCounter::f_comp=0;   // Cal Value / Calibrate with professional Freq Counter
}

void loop() {
static bool liczy;
  // wait if any serial is going on
if ( not liczy)
{
	 FreqCounter::start(10);  // Gate Time [ms]; 10ms jest lepiej niż 1ms -> mniejszy błąd pomiaru
	 liczy = true;
}


  //while (FreqCounter::f_ready == 0)
  if (FreqCounter::f_ready)
  {
	  frq=FreqCounter::f_freq;
	  liczy = false;
	  PORTB = PORTB ^ (1 << PB3); // D11
  }

  Serial.print(cnt++);
  Serial.print("  Freq: ");
  Serial.println(frq);
  delay(1000);
  digitalWrite(pinLed, !digitalRead(pinLed));  // blink Led

  PORTB = PORTB ^ (1 << PB4);  				// pomiar pętli D12
}

