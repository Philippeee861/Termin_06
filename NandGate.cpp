#include "NandGate.h"
#include <iostream>

/**
 * Konstruktor des NandGate
 * Erstellt interne AndGate- und NotGate-Instanzen mit aussagekräftigen Namen
 */
NandGate::NandGate(std::string n) 
    : andGate(n + "-AND"), notGate(n + "-NOT") {
    std::cout << "[" << n << "] NAND-Gatter aktiviert (Komposition: AND + NOT)" << std::endl;
}

/**
 * Setzt Eingang A - weitergeleitet an das interne AND-Gatter
 */
void NandGate::setInputA(int val) {
    andGate.setInputA(val);
}

/**
 * Setzt Eingang B - weitergeleitet an das interne AND-Gatter
 */
void NandGate::setInputB(int val) {
    andGate.setInputB(val);
}

/**
 * Berechnet NAND = NOT(AND):
 * 1. AND-Gatter mit beiden Eingängen berechnen
 * 2. Ergebnis des AND an das NOT-Gatter weitergeben
 * 3. NOT-Gatter aktualisieren
 */
void NandGate::update() {
    andGate.evaluate();                              // Objekt, nicht Klasse
    notGate.setInputA(andGate.getOutput() ? 1 : 0);
    notGate.evaluate();                              // konsistenterweise auch hier
}

/**
 * Gibt das Ausgangssignal des NAND-Gatters zurück
 * (das ist die Ausgabe des internen NOT-Gatters)
 */
bool NandGate::getOutput() const {
    return notGate.getOutput();
}

/**
 * Gibt den kompletten Zustand des NAND-Gatters aus
 */
void NandGate::printState() const {
    std::cout << "NandGate (AND + NOT combination)" << std::endl;
    andGate.printState();
    notGate.printState();
}
