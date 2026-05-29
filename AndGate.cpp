#include "AndGate.h"

AndGate::AndGate() {
    m_inputs.resize(2);
}

AndGate::AndGate(std::string n) : Gate(n) {
    m_inputs.resize(2);
}

void AndGate::evaluate() {
    if (m_isCalculated) return; // Cache Hit! Sofortiger Abbruch der Rekursion.
    // 1. DFS: Vorgänger zwingen, sich zu berechnen!
    if (m_inputs[0] != nullptr) m_inputs[0]->evaluate();
    if (m_inputs[1] != nullptr) m_inputs[1]->evaluate();
     
    // 2. Werte sicher auslesen (mit Fallback bei fehlendem Kabel)
    bool valA = (m_inputs[0] != nullptr) ? m_inputs[0]->getOutput() : false;
    bool valB = (m_inputs[1] != nullptr) ? m_inputs[1]->getOutput() : false;
    
    // 3. Eigene Logik anwenden
    m_output = valA && valB;
    m_isCalculated = true; // Gedächtnis versiegeln
}

void AndGate::printState() const {
    bool a = m_inputs[0] ? m_inputs[0]->getOutput() : false;
    bool b = m_inputs[1] ? m_inputs[1]->getOutput() : false;
    std::cout << "AndGate [" << m_name << ": A=" << a << ", B=" << b
              << "] => Output=" << m_output << std::endl;
}

