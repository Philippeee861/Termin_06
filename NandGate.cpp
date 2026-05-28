#include "NandGate.h"

NandGate::NandGate() {
    m_inputs.resize(2);
}

NandGate::NandGate(std::string n) : Gate(n) {
    m_inputs.resize(2);
}

void NandGate::evaluate() {
    if (m_inputs[0] == nullptr) throw FloatingPinException(m_name, 0);
    if (m_inputs[1] == nullptr) throw FloatingPinException(m_name, 1);
    m_output = !(m_inputs[0]->getOutput() && m_inputs[1]->getOutput());
}

void NandGate::printState() const {
    bool a = m_inputs[0] ? m_inputs[0]->getOutput() : false;
    bool b = m_inputs[1] ? m_inputs[1]->getOutput() : false;
    std::cout << "NandGate [" << m_name << ": A=" << a << ", B=" << b
              << "] => Output=" << m_output << std::endl;
}
