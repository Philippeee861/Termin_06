#include "AndGate.h"
#include <iostream>

/**
 * Konstruktor des AndGate
 * Der Name wird an die Basisklasse Component weitergegeben
 */
AndGate::AndGate(std::string n) : Component(n) {
    std::cout << "[" << name << "] AND-Gatter aktiviert" << std::endl;
}

/**
 * Berechnet die AND-Logik:
 * output = inA AND inB (beide müssen true sein)
 * 
 * Wir greifen auf die protected Attribute der Basisklasse zu
 */

bool AndGate::evaluate() {
    output = inA && inB;
    return output; // ← fehlt!
}

/**
 * Gibt den Zustand dieses AND-Gatters aus
 */
void AndGate::printState() const {
    std::cout << "AndGate [" << name << ": A=" << (inA ? 1 : 0) 
              << ", B=" << (inB ? 1 : 0) 
              << "] => Output=" << (output ? 1 : 0) << std::endl;
}
