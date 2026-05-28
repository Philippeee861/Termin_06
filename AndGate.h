#pragma once
#include "Component.h"

/**
 * AND-Gatter: Ausgabe ist 1 nur wenn beide Eingänge 1 sind
 */
class AndGate : public Gate {
public:
    AndGate();
    AndGate(std::string n);

    void evaluate() override;
    void printState() const override;
};
