#include <Wire.h>
#include <i2cSimpleTransfer.h>
/*
    https://github.com/getsurreal/i2cSimpleTransfer

    This example simulates a Slave Arduino sending data to the Master upon request from the Master.

    In addition, the Slave can accept configuration changes sent from the Master

    We start with a sensor value.  Everytime the Master requests the value we increment the value.

    We start incrementing by one.  
    When the Master recieves the 100th request, he tells the Slave to start incrementing by 100

*/

#define i2c_slave_address 17

// You can add more variables into the struct, but the default limit for transfer size in the Wire library is 32 bytes
struct SLAVE_DATA {
    uint16_t sensor;     // use specific declarations to ensure communication between 16bit and 32bit controllers
};

struct MASTER_DATA {
    uint8_t val;        // use specific declarations to ensure communication between 16bit and 32bit controllers
};

SLAVE_DATA slave_data;
MASTER_DATA master_data;

void setup() {
    Wire.begin(i2c_slave_address);    // i2c Slave address
    Wire.onRequest(requestEvent);     // when the Master makes a request, run this function
    Wire.onReceive (receiveEvent);    // when the Master sends us data, run this function
    master_data.val = 1;              // This is how much we increment after each request
}

void loop() {

}

void requestEvent() {
    i2cSimpleWrite(slave_data);            // Send the Master the sensor data
    slave_data.sensor += master_data.val;  // Simulate updated sensor data
}

void receiveEvent (int payload) {
 if (payload >= (sizeof master_data)){
       i2cSimpleRead(master_data);         // Receive new data from the Master
   }
 }