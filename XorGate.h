#pragma once
#include "Component.h"

/**
 * XOR-Gatter: Ausgabe ist 1 wenn die Eingänge unterschiedlich sind
 */
class XorGate : public Gate {
public:
    XorGate();
    XorGate(std::string n);

    void evaluate() override;
    void printState() const override;
};
