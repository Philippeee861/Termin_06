#include <iostream>
#include <memory>
#include "Component.h"
#include "Switch.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "XorGate.h"
#include "NandGate.h"
#include "XnorGate.h"

// ============================================================
// Phase 4: Halbaddierer (Half Adder)
// Summe  = A XOR B
// Carry  = A AND B
// ============================================================
bool testHalbaddierer() {
    bool allPassed = true;

    auto swA = std::make_shared<Switch>("A");
    auto swB = std::make_shared<Switch>("B");
    auto xorGate = std::make_shared<XorGate>("XOR-Sum");
    auto andGate = std::make_shared<AndGate>("AND-Carry");

    xorGate->connectInput(0, swA);
    xorGate->connectInput(1, swB);
    andGate->connectInput(0, swA);
    andGate->connectInput(1, swB);

    std::cout << "\n=== HALBADDIERER ===" << std::endl;

    int testCases[4][4] = {
        // A, B, ExpectedSum, ExpectedCarry
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 1}
    };

    try {
        for (int i = 0; i < 4; i++) {
            swA->setState(testCases[i][0]);
            swB->setState(testCases[i][1]);

            xorGate->evaluate();
            andGate->evaluate();

            bool sum   = xorGate->getOutput();
            bool carry = andGate->getOutput();

            if (sum != (bool)testCases[i][2] || carry != (bool)testCases[i][3]) {
                std::cerr << "FEHLER bei A=" << testCases[i][0]
                          << ", B=" << testCases[i][1]
                          << " -> Sum=" << sum << " (erwartet " << testCases[i][2]
                          << "), Carry=" << carry << " (erwartet " << testCases[i][3] << ")" << std::endl;
                allPassed = false;
            } else {
                std::cout << "OK: A=" << testCases[i][0] << ", B=" << testCases[i][1]
                          << " -> Sum=" << sum << ", Carry=" << carry << std::endl;
            }
        }
    } catch (const FloatingPinException& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return allPassed;
}

// ============================================================
// Zusatzaufgabe 1: Volladdierer (Full Adder)
// Summe  = A XOR B XOR Cin
// Carry  = (A AND B) OR ((A XOR B) AND Cin)
//
// Aufbau: 2x XOR, 2x AND, 1x OR
// ============================================================
bool testVolladdierer() {
    bool allPassed = true;

    auto swA   = std::make_shared<Switch>("A");
    auto swB   = std::make_shared<Switch>("B");
    auto swCin = std::make_shared<Switch>("Cin");

    // Halbaddierer 1: xor1 = A XOR B,  and1 = A AND B
    auto xor1 = std::make_shared<XorGate>("XOR1");
    auto and1 = std::make_shared<AndGate>("AND1");

    // Halbaddierer 2: xor2 = xor1 XOR Cin (= Summe),  and2 = xor1 AND Cin
    auto xor2 = std::make_shared<XorGate>("XOR2");
    auto and2 = std::make_shared<AndGate>("AND2");

    // Carry-Out: or1 = and1 OR and2
    auto or1  = std::make_shared<OrGate>("OR-Carry");

    // Verkabelung
    xor1->connectInput(0, swA);
    xor1->connectInput(1, swB);

    and1->connectInput(0, swA);
    and1->connectInput(1, swB);

    xor2->connectInput(0, xor1);
    xor2->connectInput(1, swCin);

    and2->connectInput(0, xor1);
    and2->connectInput(1, swCin);

    or1->connectInput(0, and1);
    or1->connectInput(1, and2);

    std::cout << "\n=== VOLLADDIERER ===" << std::endl;

    // Wahrheitstabelle: A, B, Cin, ExpectedSum, ExpectedCarry
    int testCases[8][5] = {
        {0, 0, 0,  0, 0},
        {0, 0, 1,  1, 0},
        {0, 1, 0,  1, 0},
        {0, 1, 1,  0, 1},
        {1, 0, 0,  1, 0},
        {1, 0, 1,  0, 1},
        {1, 1, 0,  0, 1},
        {1, 1, 1,  1, 1}   // 1+1+1 = Summe=1, Carry=1
    };

    try {
        for (int i = 0; i < 8; i++) {
            swA->setState(testCases[i][0]);
            swB->setState(testCases[i][1]);
            swCin->setState(testCases[i][2]);

            // Pull-Prinzip: in Reihenfolge evaluieren
            xor1->evaluate();
            and1->evaluate();
            xor2->evaluate();
            and2->evaluate();
            or1->evaluate();

            bool sum   = xor2->getOutput();
            bool carry = or1->getOutput();

            if (sum != (bool)testCases[i][3] || carry != (bool)testCases[i][4]) {
                std::cerr << "FEHLER bei A=" << testCases[i][0]
                          << ", B=" << testCases[i][1]
                          << ", Cin=" << testCases[i][2]
                          << " -> Sum=" << sum << " (erwartet " << testCases[i][3]
                          << "), Carry=" << carry << " (erwartet " << testCases[i][4] << ")" << std::endl;
                allPassed = false;
            } else {
                std::cout << "OK: A=" << testCases[i][0]
                          << ", B=" << testCases[i][1]
                          << ", Cin=" << testCases[i][2]
                          << " -> Sum=" << sum << ", Carry=" << carry << std::endl;
            }
        }
    } catch (const FloatingPinException& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return allPassed;
}

// ============================================================
// Zusatzaufgabe 2: FloatingPinException testen
// ============================================================
void testFloatingPin() {
    std::cout << "\n=== FLOATING PIN EXCEPTION TEST ===" << std::endl;
    try {
        auto gate = std::make_shared<AndGate>("Test-AND");
        // Kein connectInput -> m_inputs[0] == nullptr -> Exception
        gate->evaluate();
        std::cerr << "FEHLER: Exception hätte geworfen werden müssen!" << std::endl;
    } catch (const FloatingPinException& e) {
        std::cout << "Exception korrekt abgefangen: " << e.what() << std::endl;
    }
}

int main() {
    bool allTestsPassed = true;

    allTestsPassed &= testHalbaddierer();
    allTestsPassed &= testVolladdierer();
    testFloatingPin();

    std::cout << "\n=== ERGEBNIS ===" << std::endl;
    if (!allTestsPassed) {
        std::cerr << "PIPELINE-FEHLER: Mindestens ein Test fehlgeschlagen!" << std::endl;
        return 1;
    }
    std::cout << "ALLE TESTS BESTANDEN" << std::endl;
    return 0;
}
