#pragma once
#include "Component.h"

/**
 * OR-Gatter: Ausgabe ist 1 wenn mindestens ein Eingang 1 ist
 */
class OrGate : public Gate {
public:
    OrGate();
    OrGate(std::string n);

    void evaluate() override;
    void printState() const override;
};
