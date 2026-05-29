#include "NotGate.h"

NotGate::NotGate() {
    m_inputs.resize(1);
}

NotGate::NotGate(std::string n) : Gate(n) {
    m_inputs.resize(1);
}

void NotGate::evaluate() {
    if (m_isCalculated) return; // Cache Hit! Sofortiger Abbruch der Rekursion.
    // 1. DFS: Vorgänger zwingen, sich zu berechnen!
    if (m_inputs[0] != nullptr) m_inputs[0]->evaluate();
     
    // 2. Werte sicher auslesen (mit Fallback bei fehlendem Kabel)
    bool valA = (m_inputs[0] != nullptr) ? m_inputs[0]->getOutput() : false;
    
    // 3. Eigene Logik anwenden
    m_output = !valA;
    m_isCalculated = true; // Gedächtnis versiegeln
}

void NotGate::printState() const {
    bool a = m_inputs[0] ? m_inputs[0]->getOutput() : false;
    std::cout << "NotGate [" << m_name << ": A=" << a
              << "] => Output=" << m_output << std::endl;
}
