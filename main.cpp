//mbed compile -f --sterm --baudrate 115200
#include "mbed.h"

DigitalOut led(LED1);

int main() {
    while(true) {
        led =! led;
        ThisThread::sleep_for(200ms);
    }
    return 0;
}