#include <Wire.h>
#include <i2cSimpleTransfer.h>

/*
    https://github.com/getsurreal/i2cSimpleTransfer

    This example simulates a Slave Arduino sending data to the Master upon request from the Master.

    In addition, the Slave receives configuration changes sent from the Master.

    We start with a simulated sensor value.  Everytime the Master requests the value we increment the value.

    Initially the value is incrementing by one.  
    When the Master recieves the 100th request, it sends a configuration change to the Slave to start incrementing by 100.

*/

#define i2c_sensor_slave 17

// You can add more variables into the struct, but the default limit for transfer size in the Wire library is 32 bytes
struct SLAVE_DATA {
    uint16_t sensor;  // use specific declarations to ensure communication between 16bit and 32bit controllers
};

struct MASTER_DATA {
    uint8_t val;     // use specific declarations to ensure communication between 16bit and 32bit controllers
};

SLAVE_DATA slave_data;
MASTER_DATA master_data;

void setup() {
    Wire.begin();     // Begin i2c Master
    Serial.begin(115200);
}

void loop() {
    Wire.requestFrom( i2c_sensor_slave, sizeof(slave_data) );    // request data from the Slave device the size of our struct

    if ( Wire.available() == sizeof(slave_data) ) {
        i2cSimpleRead(slave_data);
    }

/*
    ToDo  Test a second slave device

    Wire.requestFrom(i2c_sensor_slave2, sizeof(slave2_data));    // request data from the Slave2 device the size of our struct

    while (Wire.available()) {
        i2cSimpleRead(slave2_data);
    }

*/

    Serial.println(slave_data.sensor);

    if (slave_data.sensor == 100) {
        master_data.val = 100;
        Wire.beginTransmission(i2c_sensor_slave);
        i2cSimpleWrite(master_data);
        Wire.endTransmission();
    }

    delay(200);     // Just for example use.  Use some sort of timed action for implementation
}

