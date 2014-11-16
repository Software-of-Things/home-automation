#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int relay = 8;

RF24 radio(9, 10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup(void) {

  Serial.begin(57600);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);

  radio.begin();
  radio.setRetries(15,15);

  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();
}

void loop(void) {

    if ( radio.available() ) {
        unsigned long message;
        bool done = false;

        while (!done) {
            // Fetch the payload, and see if this was the last one.
            done = radio.read( &message, sizeof(unsigned long) );

            // Spew it
            if (message == 1){
                digitalWrite(relay, LOW);
            } else {
                digitalWrite(relay, HIGH);
            }

        }
    }
}
