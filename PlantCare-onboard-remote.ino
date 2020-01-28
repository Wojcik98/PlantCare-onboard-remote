#include <TinyWireS.h>
#include <usiTwiSlave.h>

/* PINS - D - Digital, A - Analog
 * P0 - D0,
 * P1 - LED, D1
 * P2 - D2, A1
 * P3 - D3, A3
 * P4 - D4, A2
 * P5 - reset
 */

#define ADDRESS 0x40

#define A0 0
#define A1 1
#define A2 2
#define A3 3

#define SDA 0
#define COIL 1
#define SCL 2
#define MOISTURE A3
#define LIGHT A2
#define RESET_PIN 5

#define MEASURE_CMD 0
#define COIL_ON_CMD 1
#define COIL_OFF_CMD 2

#define ACK 42
#define BAD_REQUEST 33

int cmd = 0;
int light = 0;
int moisture = 0;

void setup() {
    TinyWireS.begin(ADDRESS);
    pinMode(COIL, OUTPUT);
}

void loop() {
    while (!TinyWireS.available()); // wait for request
    cmd = TinyWireS.receive();

    if (cmd == MEASURE_CMD) {
        light = analogRead(LIGHT);
        moisture = analogRead(MOISTURE);

        TinyWireS.send(light >> 8);
        TinyWireS.send(light & 0xFF);
        TinyWireS.send(moisture >> 8);
        TinyWireS.send(moisture & 0xFF);
    } else if (cmd == COIL_ON_CMD) {
        digitalWrite(COIL, HIGH);
        TinyWireS.send(ACK);
    } else if (cmd == COIL_OFF_CMD) {
        digitalWrite(COIL, LOW);
        TinyWireS.send(ACK);
    } else {
        TinyWireS.send(BAD_REQUEST);
    }
}
