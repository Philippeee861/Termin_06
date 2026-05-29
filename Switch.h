#pragma once
#include "Component.h"

/**
 * Switch (Schalter) - Phase 3
 * Datenquelle: Ein Gatter mit 0 Eingängen.
 * setState() setzt den Ausgabewert direkt.
 * evaluate() bleibt leer, da keine Vorgänger existieren.
 */
class Switch : public Gate {
public:
    Switch() { m_inputs.resize(0); }
    Switch(std::string n) : Gate(n) { m_inputs.resize(0); }

    void setState(bool state) { m_output = state; }

    void evaluate() override { /* Keine Vorgänger – nichts zu tun */ }

    void printState() const override {
        std::cout << "Switch [" << m_name << "] => Output=" << (m_output ? 1 : 0) << std::endl;
    }
    virtual void reset() {
    m_isCalculated = false;
    }
};
