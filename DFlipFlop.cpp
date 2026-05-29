#include "DFlipFlop.h"

DFlipFlop::DFlipFlop() {
    m_inputs.resize(1);
}

DFlipFlop::DFlipFlop(std::string n) : Gate(std::move(n)) {
    m_inputs.resize(1);
}

void DFlipFlop::evaluate(){
m_output = m_storedState;
m_isCalculated = true;
}

void DFlipFlop::onClockTick(){
    m_storedState = getOutput();
    //m_isCalculated = true;
    m_output = getOutput();
}
void DFlipFlop::printState() const {};

