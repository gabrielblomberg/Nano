#include "Transceiver.hpp"

#include "Debug.hpp"

Transceiver::Transceiver()
    : m_rf(RF24(DEFAULT_CHIP_ENABLE_PIN, DEFAULT_CHIP_SELECT_PIN))
    , m_tx_pipe_addr(DEFAULT_TX_PIPE_ADDR)
    , m_rx_pipe_addr(DEFAULT_TX_PIPE_ADDR)
    , m_rx_pipe_number(DEFAULT_RX_PIPE_NUMBER) // 0 - 5 inclusive
    , m_access_code(DEFAULT_ACCESS_CODE)
{
    m_rf.begin();
    if (!m_rf.isChipConnected()) {
        DEBUG_PRINTLN("Transceiver connection failed.");
    }
    else {
        DEBUG_PRINTLN("Transceiver connected!");
    }

    m_rf.openWritingPipe(m_tx_pipe_addr);
    m_rf.openReadingPipe(m_rx_pipe_number, m_rx_pipe_addr);

    DEBUG_PRINT("TX Address: ");
    for (unsigned char x : m_tx_pipe_addr) {DEBUG_PRINT(char(x));}
    DEBUG_PRINTLN();
    DEBUG_PRINT("RX Address: ");
    for (unsigned char x : m_rx_pipe_addr) {DEBUG_PRINT(char(x));}
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