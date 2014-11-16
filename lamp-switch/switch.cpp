#include <stdlib.h>
#include <unistd.h>
#include <../RF24/RPi/RF24/RF24.h>

using namespace std;
RF24 radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_15, BCM2835_SPI_SPEED_8MHZ);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup(void){
    //Prepare the radio module
    radio.begin();
    radio.setRetries(15, 15);
    radio.setChannel(0x4c);
    radio.setPALevel(RF24_PA_MAX);
    radio.setPALevel(RF24_PA_MAX);

    radio.openWritingPipe(pipes[0]);
}

bool switchLight(int action){
    //This function send a message to the arduino
    if (action != 1) {
        action = 0;
    }
    unsigned long message = action;

    
    //Send the message
    bool sent = radio.write( &message, sizeof(unsigned long) );
    return sent;
}  

int main( int argc, char ** argv){

    char choice;
    setup();

    //Define the options
    if((choice = getopt( argc, argv, "m:")) != -1){
        if (choice == 'm'){
            int action = atoi(optarg);
            switchLight(action);
            radio.stopListening();
            printf("Switch turned %s\n", action == 1 ? "ON" : "OFF");
            return 0;
        }
    }
    return 1;
}
