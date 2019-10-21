#include "Transceiver.hpp"

#include "Debug.hpp"

Transceiver::Transceiver()
    : m_addresses{DEFAULT_TX_PIPE_ADDR, DEFAULT_RX_PIPE_ADDR}
    , m_access_code( DEFAULT_ACCESS_CODE )
    , m_rf( RF24(DEFAULT_CHIP_ENABLE_PIN, DEFAULT_CHIP_SELECT_PIN) )
{
    m_rf.begin();
    
    if (!m_rf.isChipConnected()) {
        DEBUG_PRINTLN("Transceiver connection failed.");
    }
    else {
        DEBUG_PRINTLN("Transceiver connected!");
    }

    // Open the reading and writing pipes
    m_rf.openWritingPipe(m_addresses[1]);
    m_rf.openReadingPipe(DEFAULT_RX_PIPE_NUMBER, m_addresses[0]);

    DEBUG_PRINT("TX Address: ");
    for (unsigned char x : m_addresses[1]) {DEBUG_PRINT(char(x));}
    DEBUG_PRINTLN();
    DEBUG_PRINT("RX Address: ");
    for (unsigned char x : m_addresses[2]) {DEBUG_PRINT(char(x));}
    DEBUG_PRINTLN();
}

void Transceiver::PushAcceleration(const AccelerationalData& data)
{
    // According to the documentation, blocks until ACKed or until timeout
    // is reached, that is 60-70 ms. Chokepoint if no base station present.
    if (!m_rf.write(&data, sizeof(data))) {
        DEBUG_PRINT("Accelerational data was not transmitted\n");
        DEBUG_PRINT("X Acceleration: "); DEBUG_PRINTLN(data.ax);
        DEBUG_PRINT("Y Acceleration: "); DEBUG_PRINTLN(data.ay);
        DEBUG_PRINT("Z Acceleration: "); DEBUG_PRINTLN(data.az);
        DEBUG_PRINTLN();
    }
}