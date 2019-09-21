#include "Transceiver.hpp"

#include <Arduino.h>

#include "Debug.hpp"
#include "Accelerometer.hpp"

Transceiver::Transceiver()
    : m_rf(RF24(9, 10))
    , m_tx_pipe_addr("1Node")
    , m_rx_pipe_addr("2Node")
    , m_rx_pipe_number(1)
{
    // Assume runs correctly given there is little error checking from the
    // provided library
    m_rf.begin();
    m_rf.openWritingPipe(m_tx_pipe_addr);
    m_rf.openReadingPipe(m_rx_pipe_number, m_rx_pipe_addr);
}

void Transceiver::PushAcceleration(const AccelerationalData& data)
{
    if (!m_rf.write(&data, sizeof(data))) {
        DEBUG_PRINT("Accelerational data was not transmitted\n");
        DEBUG_PRINT("X Acceleration: "); DEBUG_PRINTLN(data.ax);
        DEBUG_PRINT("Y Acceleration: "); DEBUG_PRINTLN(data.ay);
        DEBUG_PRINT("Z Acceleration: "); DEBUG_PRINTLN(data.az);
        DEBUG_PRINTLN();
    }
}

void Transceiver::Test()
{
    
}
