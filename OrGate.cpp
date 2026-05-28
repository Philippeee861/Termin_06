#include "OrGate.h"

OrGate::OrGate() {
    m_inputs.resize(2);
}

OrGate::OrGate(std::string n) : Gate(n) {
    m_inputs.resize(2);
}

void OrGate::evaluate() {
    if (m_inputs[0] == nullptr) throw FloatingPinException(m_name, 0);
    if (m_inputs[1] == nullptr) throw FloatingPinException(m_name, 1);
    m_output = m_inputs[0]->getOutput() || m_inputs[1]->getOutput();
}

void OrGate::printState() const {
    bool a = m_inputs[0] ? m_inputs[0]->getOutput() : false;
    bool b = m_inputs[1] ? m_inputs[1]->getOutput() : false;
    std::cout << "OrGate [" << m_name << ": A=" << a << ", B=" << b
              << "] => Output=" << m_output << std::endl;
}
