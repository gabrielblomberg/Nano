#ifndef TRANSCEIVER_H
#define TRANSCEIVER_H

#include "Accelerometer.hpp"

// Reference: https://github.com/nRF24/RF24
#include <RF24.h>

#define DEFAULT_TX_PIPE_ADDR "P03Nano1"
#define DEFAULT_RX_PIPE_ADDR "P03Nano2"
#define DEFAULT_RX_PIPE_NUMBER 1
#define DEFAULT_ACCESS_CODE "P03 Nano"
#define DEFAULT_CHIP_ENABLE_PIN 9
#define DEFAULT_CHIP_SELECT_PIN 10

// Class for transceiver that interfaces with the base station
class Transceiver
{
    public:

        Transceiver();

        // Transmits accelerational data to the base station
        void PushAcceleration(const AccelerationalData& data);

        // Transmits the access code to the base station and returns whether it
        // was successful or not
        inline bool TransmitAccessCode() {
            return m_rf.write(&m_access_code, sizeof(m_access_code));
        }

    private:

        // Pipe address length is 5 bytes. There are 5 pipes. Rx pipes 1 - 5
        // have addresses differing only by the first byte, and pipe 0 may have
        // any 5 byte address. The Tx pipe address is 5 bytes long and is the
        // node address of the receiver.
        unsigned char m_addresses[2][9];

        // Access code for the base station - expects 20 characters
        const char m_access_code[20];

        // Underlying transceiver class instance
        RF24 m_rf;
};

#endif // TRANSCEIVER_H