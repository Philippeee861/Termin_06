#pragma once
#include "Component.h"

/**
 * NOT-Gatter: Ausgabe ist invertiert – nur 1 Eingang (Index 0)
 */
class NotGate : public Gate {
public:
    NotGate();
    NotGate(std::string n);

    void evaluate() override;
    void printState() const override;
};
