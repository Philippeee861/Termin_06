#include <iostream>
#include <vector>
#include <memory>
// Hier Ihre Gatter-Header inkludieren
#include "Component.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "XorGate.h"
#include "NandGate.h"

int main() {
    // 1. Globaler Test-Status
    bool testPassed = true;
    std::cout << "--- STARTE AUTOMATISIERTE WAHRHEITSTABELLEN-TESTS ---" << std::endl;

    // ---------------------------------------------------------
    // TESTBLOCK 1: AND-Gatter (4 Testfälle)
    // ---------------------------------------------------------
    {
        auto andGate = std::make_unique<AndGate>("Test-AND");
        // Test-Matrix: InputA, InputB, Erwartetes Ergebnis
        int testCases[4][3] = {
            {0, 0, 0},
            {0, 1, 0},
            {1, 0, 0},
            {1, 1, 1}
        };
        for (int i = 0; i < 4; ++i) {
            andGate->setInputA(testCases[i][0]);
            andGate->setInputB(testCases[i][1]);
            andGate->evaluate();

            if (andGate->getOutput() != testCases[i][2]) {
                std::cerr << "❌ TEST FAILED: AND bei Inputs A=" << testCases[i][0]
                          << " B=" << testCases[i][1]
                          << " -> Erhalten: " << andGate->getOutput()
                          << " (Erwartet: " << testCases[i][2] << ")" << std::endl;
                testPassed = false;
            }
        }
    }

    // ---------------------------------------------------------
    // TESTBLOCK 2: OR-Gatter (4 Testfälle)
    // ---------------------------------------------------------
    {
        auto orGate = std::make_unique<OrGate>("Test-OR");
        int testCases[4][3] = {
            {0, 0, 0},
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 1}
        };
        for (int i = 0; i < 4; ++i) {
            orGate->setInputA(testCases[i][0]);
            orGate->setInputB(testCases[i][1]);
            orGate->evaluate();

            if (orGate->getOutput() != testCases[i][2]) {
                std::cerr << "❌ TEST FAILED: OR bei Inputs A=" << testCases[i][0]
                          << " B=" << testCases[i][1]
                          << " -> Erhalten: " << orGate->getOutput()
                          << " (Erwartet: " << testCases[i][2] << ")" << std::endl;
                testPassed = false;
            }
        }
    }

    // ---------------------------------------------------------
    // TESTBLOCK 3: XOR-Gatter (4 Testfälle)
    // ---------------------------------------------------------
    {
        auto xorGate = std::make_unique<XorGate>("Test-XOR");
        int testCases[4][3] = {
            {0, 0, 0},
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}
        };
        for (int i = 0; i < 4; ++i) {
            xorGate->setInputA(testCases[i][0]);
            xorGate->setInputB(testCases[i][1]);
            xorGate->evaluate();

            if (xorGate->getOutput() != testCases[i][2]) {
                std::cerr << "❌ TEST FAILED: XOR bei Inputs A=" << testCases[i][0]
                          << " B=" << testCases[i][1]
                          << " -> Erhalten: " << xorGate->getOutput()
                          << " (Erwartet: " << testCases[i][2] << ")" << std::endl;
                testPassed = false;
            }
        }
    }

    // ---------------------------------------------------------
    // TESTBLOCK 4: NAND-Gatter (4 Testfälle)
    // ---------------------------------------------------------
    {
        auto nandGate = std::make_unique<NandGate>("Test-NAND");
        int testCases[4][3] = {
            {0, 0, 1},
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}
        };
        for (int i = 0; i < 4; ++i) {
            nandGate->setInputA(testCases[i][0]);
            nandGate->setInputB(testCases[i][1]);
            nandGate->evaluate();

            if (nandGate->getOutput() != testCases[i][2]) {
                std::cerr << "❌ TEST FAILED: NAND bei Inputs A=" << testCases[i][0]
                          << " B=" << testCases[i][1]
                          << " -> Erhalten: " << nandGate->getOutput()
                          << " (Erwartet: " << testCases[i][2] << ")" << std::endl;
                testPassed = false;
            }
        }
    }

    // ---------------------------------------------------------
    // TESTBLOCK 5: NOT-Gatter (2 Testfälle)
    // ---------------------------------------------------------
    {
        auto notGate = std::make_unique<NotGate>("Test-NOT");
        // Test-Matrix für 1 Input: InputA, Erwartetes Ergebnis
        int testCases[2][2] = {
            {0, 1},
            {1, 0}
        };
        for (int i = 0; i < 2; ++i) {
            notGate->setInputA(testCases[i][0]);
            // Ein NOT-Gatter hat keinen B-Eingang
            notGate->evaluate();

            if (notGate->getOutput() != testCases[i][1]) {
                std::cerr << "❌ TEST FAILED: NOT bei Input A=" << testCases[i][0]
                          << " -> Erhalten: " << notGate->getOutput()
                          << " (Erwartet: " << testCases[i][1] << ")" << std::endl;
                testPassed = false;
            }
        }
    }

    // 3. Finale Auswertung für die CI-Pipeline
    if (!testPassed) {
        std::cerr << "--- 🔴 PIPELINE-ABSTURZ: TESTS FEHLGESCHLAGEN ---" << std::endl;
        return 1; // Signalisiert GitHub Actions (oder anderer CI): FEHLER!
    }

    std::cout << "--- 🟢 ALLE TESTS BESTANDEN (18/18) ---" << std::endl;
    return 0; // Signalisiert GitHub Actions: ERFOLG!
}