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
#include "DFlipFlop.h"

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



int main() {
    //Hier: Termin_10
    auto FlipFlop = std::make_shared<DFlipFlop>("FLIPFLOP");
    auto andGate0 = std::make_shared<AndGate>("AND0");
    auto swD = std::make_shared<Switch>("D");
    auto swE = std::make_shared<Switch>("E");
    std::vector<std::shared_ptr<Gate>>allGates = { andGate0 };
    std::vector<std::shared_ptr<DFlipFlop>>allFlipFlops = { FlipFlop };
    andGate0->connectInput(0, swD);
    andGate0->connectInput(1, swE);

    bool testCases[4][2] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    };
    FlipFlop->connectInput(0, andGate0);
    
    for(int i = 0; i < 10; i++){
    for (const auto& gate : allGates) gate->reset();

    swD->setState(testCases[i % 4][0]);
    swE->setState(testCases[i % 4][1]);

    andGate0->evaluate();
    FlipFlop->evaluate();          // ← das fehlte

    std::cout << "Takt " << i << ": FF=" << FlipFlop->getOutput() << std::endl;

    for(const auto& flipFlop : allFlipFlops) flipFlop->onClockTick();
}




    bool zahlA = 1;
    bool zahlB = 1;

    auto swA = std::make_shared<Switch>("A");
    auto swB = std::make_shared<Switch>("B");
    auto swC = std::make_shared<Switch>("C");

    auto andGate1 = std::make_shared<AndGate>("AND1");
    auto andGate2 = std::make_shared<AndGate>("AND1");
    auto xorGate1 = std::make_shared<XorGate>("Xor1");
    auto xorGate2 = std::make_shared<XorGate>("Xor2");
    auto orGate = std::make_shared<OrGate>("OR1");

    

    andGate1->connectInput(0, swA);
    andGate1->connectInput(1, swB);

    xorGate1->connectInput(0,swA);
    xorGate1->connectInput(1,swB);

    andGate2->connectInput(0,xorGate1);
    andGate2->connectInput(1,swC);

    xorGate2->connectInput(0,xorGate1);
    xorGate2->connectInput(1,swC);


    orGate->connectInput(0, andGate1);
    orGate->connectInput(1,andGate2);

    swA->setState(zahlA);
    swB->setState(zahlB);
    swC->setState(1);


    xorGate2->evaluate();
    orGate->evaluate();
    std::cout << "Summe: " << xorGate2->getOutput() << std::endl;
    std::cout << "Carry: " << orGate->getOutput() << std::endl; 


    bool allTestsPassed = true;

    std::cout << "\n=== ERGEBNIS ===" << std::endl;
    if (!allTestsPassed) {
        std::cerr << "PIPELINE-FEHLER: Mindestens ein Test fehlgeschlagen!" << std::endl;
        return 1;
    }
    std::cout << "ALLE TESTS BESTANDEN" << std::endl;
    return 0;
}
