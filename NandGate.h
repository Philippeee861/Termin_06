#pragma once
#include "Component.h"

/**
 * NAND-Gatter durch Komposition: NAND = NOT(AND)
 * Nutzt intern m_inputs direkt (kein sub-gate mehr nötig mit der neuen Architektur)
 */
class NandGate : public Gate {
public:
    NandGate();
    NandGate(std::string n);

    void evaluate() override;
    void printState() const override;
};
