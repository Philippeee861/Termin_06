#pragma once
#include "Component.h"

class XnorGate : public Gate {
public:
    // Konstruktor – übergibt den Namen an die Basisklasse
    XnorGate(std::string name);

    // XNOR-Logik: true wenn beide Eingänge gleich sind
    bool evaluate() override;
};