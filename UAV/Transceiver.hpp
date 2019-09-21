#ifndef TRANSCEIVER_H
#define TRANSCEIVER_H

#include "Accelerometer.hpp"
#include <RF24.h>

// Class for the transceiver used for ENGG1200 2019. Under normal circumstances
// there would be less constants however this class is designed for interfacting
// wit the provided base station
class Transceiver
{
    public:
        Transceiver();
        ~Transceiver();

        // Transmits accelerational data to the base station
        void PushAcceleration(const AccelerationalData& data);

        void Test();

        // Transmits the access code to the base station and returns whether it
        // was successful or not
        inline bool TransmitAccessCode() {
            return m_rf.write(&m_access_code, sizeof(m_access_code));
        }

    private:

        // Pipe address length is 5 bytes. Rx pipes 1 - 5 have addresses
        // differing only by the first byte, and pipe 0 may have any 5 byte
        // address. The Tx pipe address is 5 bytes long and is the node address
        // of the receiver.
        const unsigned char m_tx_pipe_addr[6];
        const unsigned char m_rx_pipe_addr[6];
        const unsigned char m_rx_pipe_number;

        // Access code for the base station - implemented in example this way
        // Ever tried initialising a class member char array? Kms
        const char m_access_code[20] = "P03 Nano";

        // Underlying transceiver class instance
        RF24 m_rf;
};

#endif // TRANSCEIVER_H
