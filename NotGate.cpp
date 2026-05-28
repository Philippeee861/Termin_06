#include "NotGate.h"

NotGate::NotGate() {
    m_inputs.resize(1);
}

NotGate::NotGate(std::string n) : Gate(n) {
    m_inputs.resize(1);
}

void NotGate::evaluate() {
    if (m_inputs[0] == nullptr) throw FloatingPinException(m_name, 0);
    m_output = !m_inputs[0]->getOutput();
}

void NotGate::printState() const {
    bool a = m_inputs[0] ? m_inputs[0]->getOutput() : false;
    std::cout << "NotGate [" << m_name << ": A=" << a
              << "] => Output=" << m_output << std::endl;
}
