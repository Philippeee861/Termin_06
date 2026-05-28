#include "XnorGate.h"

/**
 * Konstruktor des XNOR-Gatters
 * Ruft den Konstruktor der Basisklasse Component auf
 */
XnorGate::XnorGate(std::string name) : Gate(name) {}

/**
 * Implementierung der XNOR-Logik
 * XNOR = NOT XOR = true, wenn beide Eingänge gleich sind
 * 
 * Wahrheitstabelle:
 * A=0, B=0 → true
 * A=0, B=1 → false
 * A=1, B=0 → false
 * A=1, B=1 → true
 */
bool XnorGate::evaluate() {
    output = !(inA ^ inB);  // XOR und dann negieren
    return output;
}