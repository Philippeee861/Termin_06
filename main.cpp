#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include "Component.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "NandGate.h"
#include "XorGate.h"
#include "LogicEngine.h"

/**
 * Parser: Liest die Datei schaltzustaende.txt und parst die Ziffern
 */
std::vector<int> parseInputFile(const std::string& filename) {
    std::vector<int> signals;
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "FEHLER: Datei '" << filename << "' konnte nicht geöffnet werden!" << std::endl;
        return signals;
    }

    std::cout << "[Parser] Datei '" << filename << "' geöffnet." << std::endl;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        int value;
        while (ss >> value) {
            if (value == 0 || value == 1) {
                signals.push_back(value);
                std::cout << "[Parser] Signal gelesen: " << value << std::endl;
            } else {
                std::cerr << "[Parser WARNUNG] Ungültiger Wert: " << value << std::endl;
            }
        }
    }

    inputFile.close();
    std::cout << "[Parser] Insgesamt " << signals.size() << " Signale gelesen." << std::endl;
    return signals;
}


int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "Laboranweisung 3: Vererbung & Architektur" << std::endl;
    std::cout << "Der Digitalschaltungs-Simulator - Musterlösung" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // ================================================
    // TEIL B & C: Neue Architektur mit Component
    // ================================================

    std::cout << "--- TEIL B & C: Basisklasse Component & Refactoring ---\n" << std::endl;

    std::cout << "\n1. Gatter-Instanziierung mit benannten Konstruktoren:\n" << std::endl;
    AndGate andGatter("Haupt-AND");
    OrGate orGatter("Haupt-OR");
    NotGate notGatter("Haupt-NOT");
    NandGate nandGatter("Haupt-NAND");
    XorGate xorGatter("Haupt-XOR");
    std::cout << std::endl;

    // ================================================
    // TEIL D: Wahrheitstabellen verifizieren
    // ================================================

    std::cout << "\n--- TEIL D: Wahrheitstabellen-Verifikation ---\n" << std::endl;

    std::cout << "\n=== AND-Gatter ===" << std::endl;
    for (int a = 0; a <= 1; a++) {
        for (int b = 0; b <= 1; b++) {
            andGatter.setInputA(a);
            andGatter.setInputB(b);
            andGatter.evaluate();
            std::cout << "A=" << a << " B=" << b << " => ";
            andGatter.printState();
        }
    }

    std::cout << "\n=== OR-Gatter ===" << std::endl;
    for (int a = 0; a <= 1; a++) {
        for (int b = 0; b <= 1; b++) {
            orGatter.setInputA(a);
            orGatter.setInputB(b);
            orGatter.evaluate();
            std::cout << "A=" << a << " B=" << b << " => ";
            orGatter.printState();
        }
    }

    std::cout << "\n=== NOT-Gatter ===" << std::endl;
    for (int a = 0; a <= 1; a++) {
        notGatter.setInputA(a);
        notGatter.evaluate();
        std::cout << "A=" << a << " => ";
        notGatter.printState();
    }

    std::cout << "\nWarnung beim Versuch, setInputB zu setzen:" << std::endl;
    notGatter.setInputB(1);

    std::cout << "\n=== XOR-Gatter (NEU!) ===" << std::endl;
    for (int a = 0; a <= 1; a++) {
        for (int b = 0; b <= 1; b++) {
            xorGatter.setInputA(a);
            xorGatter.setInputB(b);
            xorGatter.evaluate();
            std::cout << "A=" << a << " B=" << b << " => ";
            xorGatter.printState();
        }
    }

    // ================================================
    // ZUSATZAUFGABE 1: Parsen
    // ================================================

    std::cout << "\n\n--- ZUSATZAUFGABE 1: Dateien-Parser ---\n" << std::endl;
    std::vector<int> inputSignals = parseInputFile("schaltzustaende.txt");

    if (!inputSignals.empty()) {
        std::cout << "\n--- Simulation mit eingelesenen Signalen ---\n" << std::endl;

        for (size_t i = 0; i < inputSignals.size(); i++) {
            int signalA = inputSignals[i];
            int signalB = inputSignals[(i + 1) % inputSignals.size()];

            andGatter.setInputA(signalA);
            andGatter.setInputB(signalB);
            andGatter.evaluate();

            std::cout << "Schritt " << (i + 1) << ": A=" << signalA << " B=" << signalB << " => ";
            andGatter.printState();
        }
    } else {
        std::cout << "Datei nicht vorhanden - übersprungen." << std::endl;
    }

    // ================================================
    // ZUSATZAUFGABE 2: Upcasting
    // ================================================

    std::cout << "\n\n--- ZUSATZAUFGABE 2: Upcasting ---\n" << std::endl;

    std::vector<Component*> meineSchaltung;
    meineSchaltung.push_back(new AndGate("Gatter-1"));
    meineSchaltung.push_back(new OrGate("Gatter-2"));
    meineSchaltung.push_back(new XorGate("Gatter-3"));

    std::cout << "\nAlle Gatter wurden hinzugefügt!\n" << std::endl;

    for (Component* comp : meineSchaltung) {
        comp->setInputA(1);
        comp->setInputB(0);
        comp->evaluate();
        comp->printState();
    }

    std::cout << "\nMemory freigeben:" << std::endl;
    for (Component* comp : meineSchaltung) {
        delete comp;
        std::cout << "Gatter gelöscht." << std::endl;
    }
    meineSchaltung.clear();

    // ================================================
    // AUFGABE 3: LogicEngine mit Vektor-Management testen
    // ================================================

    std::cout << "\n\n--- AUFGABE: LogicEngine Simulation ---\n" << std::endl;

    LogicEngine engine;
    engine.setCircuitName("Testschaltung");

    // Verschiedene Gatter-Typen zur Engine hinzufügen (Aufgabe 3)
    // Eigentümerschaft liegt bei der Engine — sie gibt den Speicher im Destruktor frei
    AndGate* engineAnd = new AndGate("Engine-AND");
    OrGate*  engineOr  = new OrGate("Engine-OR");
    XorGate* engineXor = new XorGate("Engine-XOR");
    NotGate* engineNot = new NotGate("Engine-NOT");

    // Eingänge vor dem ersten Tick setzen
    engineAnd->setInputA(1); engineAnd->setInputB(1); // AND(1,1) = 1
    engineOr ->setInputA(0); engineOr ->setInputB(1); // OR(0,1)  = 1
    engineXor->setInputA(1); engineXor->setInputB(1); // XOR(1,1) = 0
    engineNot->setInputA(1);                           // NOT(1)   = 0

    engine.addComponent(engineAnd);
    engine.addComponent(engineOr);
    engine.addComponent(engineXor);
    engine.addComponent(engineNot);

    // Tick 1
    engine.doTick();

    // Eingänge für Tick 2 ändern
    engineAnd->setInputA(0); engineAnd->setInputB(0); // AND(0,0) = 0
    engineOr ->setInputA(1); engineOr ->setInputB(1); // OR(1,1)  = 1
    engineXor->setInputA(1); engineXor->setInputB(0); // XOR(1,0) = 1
    engineNot->setInputA(0);                           // NOT(0)   = 1

    // Tick 2
    engine.doTick();

    std::cout << "\n[Engine] Simulation beendet nach " << engine.getTickCount() << " Ticks." << std::endl;

    // ================================================
    // Abschluss
    // ================================================

    std::cout << "\n========================================" << std::endl;
    std::cout << "Refactoring erfolgreich abgeschlossen!" << std::endl;
    std::cout << "Die neue Architektur ist wartbar und erweiterbar." << std::endl;
    std::cout << "========================================\n" << std::endl;

    return 0;
}
