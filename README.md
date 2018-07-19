# i2cSimpleTransfer
i2c bi-directional communication for Arduinos

### Description
This example simulates a Slave Arduino sending data to the Master upon request from the Master.

In addition, the Slave receives configuration changes sent from the Master.

We start with a simulated sensor value.  Everytime the Master requests the value we increment the value.

Initially the value is incrementing by one.  When the Master recieves the 100th request, it sends a configuration change to the Slave to start incrementing by 100.