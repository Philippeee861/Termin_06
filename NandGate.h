#pragma once

#include "AndGate.h"
#include "NotGate.h"

/**
 * NAND-Gatter durch Komposition
 * Kombiniert ein AndGate mit einem NotGate
 * NAND = NOT(AND)
 */
class NandGate {
private:
    AndGate andGate;
    NotGate notGate;

public:
    /**
     * Konstruktor: Nimmt einen Namen entgegen
     * @param n Der Name dieses NAND-Gatters
     */
    NandGate(std::string n);

    /**
     * Setzt Eingang A für das interne AND-Gatter
     */
    void setInputA(int val);

    /**
     * Setzt Eingang B für das interne AND-Gatter
     */
    void setInputB(int val);

    /**
     * Berechnet: NAND = NOT(AND(inA, inB))
     */
    void update();

    /**
     * Gibt das Ausgangssignal zurück
     */
    bool getOutput() const;

    /**
     * Gibt den Zustand aus
     */
    void printState() const;
};
