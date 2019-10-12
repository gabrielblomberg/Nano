#ifndef TRANSCEIVER_H
#define TRANSCEIVER_H

#include "Accelerometer.hpp"

// Reference: https://github.com/nRF24/RF24
#include <RF24.h>

#define DEFAULT_TX_PIPE_ADDR "1Node"
#define DEFAULT_RX_PIPE_ADDR "2Node"
#define DEFAULT_RX_PIPE_NUMBER 1
#define DEFAULT_ACCESS_CODE "P03 Nano"

// Class for the transceiver used for ENGG1200 2019. Under normal circumstances
// there would be less constants however this class is designed for interfacting
// wit the provided base station
class Transceiver
{
    public:

        // This is non-ideal. There should be arguments with default
        // parameters here, however passing in a char array as a pointer
        // that must be a strict size to a class constructor without
        // std::string is hard and convuluted
        Transceiver();
        ~Transceiver();

        // Transmits accelerational data to the base station
        void PushAcceleration(const AccelerationalData& data);

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
        int m_rx_pipe_number;

        // Access code for the base station - implemented in provided code this
        // way. Ever tried initialising a class member char array In Arduino C?
        // No, just no.
        const char m_access_code[20];

        // Underlying transceiver class instance
        RF24 m_rf;
};


#endif // TRANSCEIVER_H
