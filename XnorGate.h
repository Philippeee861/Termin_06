#pragma once
#include "Component.h"

/**
 * XNOR-Gatter: Ausgabe ist 1 wenn beide Eingänge gleich sind
 */
class XnorGate : public Gate {
public:
    XnorGate();
    XnorGate(std::string n);

    void evaluate() override;
    void printState() const override;
};
