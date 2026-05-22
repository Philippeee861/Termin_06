#include "OrGate.h"
#include <iostream>

/**
 * Konstruktor des OrGate
 * Der Name wird an die Basisklasse Component weitergegeben
 */
OrGate::OrGate(std::string n) : Component(n) {
    std::cout << "[" << name << "] OR-Gatter aktiviert" << std::endl;
}

/**
 * Berechnet die OR-Logik:
 * output = inA OR inB (mindestens einer muss true sein)
 * 
 * Wir greifen auf die protected Attribute der Basisklasse zu
 */

bool OrGate::evaluate() {
    output = inA || inB;
    return output;
}

/**
 * Gibt den Zustand dieses OR-Gatters aus
 */
void OrGate::printState() const {
    std::cout << "OrGate [" << name << ": A=" << (inA ? 1 : 0) 
              << ", B=" << (inB ? 1 : 0) 
              << "] => Output=" << (output ? 1 : 0) << std::endl;
}
