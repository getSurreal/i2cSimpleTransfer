#include <Arduino.h>
#include <Wire.h>

template <typename T> unsigned int i2cSimpleWrite (const T& value) {
    Wire.write((byte *) &value, sizeof (value));
    return sizeof (value);
}

template <typename T> unsigned int i2cSimpleRead(T& value) {
    byte * p = (byte*) &value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
        *p++ = Wire.read();
    return i;
}