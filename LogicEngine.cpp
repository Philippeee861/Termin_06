#include "LogicEngine.h"
#include <iostream>

LogicEngine::LogicEngine() 
    : circuitName("Unbenannt"), tickCount(0) {
    std::cout << "[LogicEngine] Engine initialisiert" << std::endl;
}

/**
 * Destruktor: unique_ptr-Elemente im Vektor werden automatisch zerstört.
 * Kein manuelles delete nötig – das ist RAII!
 */
LogicEngine::~LogicEngine() {
    std::cout << "[LogicEngine] Engine wird zerstört. Komponenten werden automatisch freigegeben..." << std::endl;
    // circuit.clear() ist nicht nötig, passiert automatisch
    // Aber wir rufen es explizit auf, damit die Destruktor-Ausgaben vor dieser Meldung erscheinen
    circuit.clear();
    std::cout << "[LogicEngine] Alle Komponenten freigegeben." << std::endl;
}

void LogicEngine::setCircuitName(std::string name) {
    circuitName = name;
    std::cout << "[LogicEngine] Schaltungsname gesetzt: " << circuitName << std::endl;
}

/**
 * Teil A: Nimmt unique_ptr entgegen und übernimmt den Besitz via std::move.
 * Ein unique_ptr kann nicht kopiert werden – nur verschoben!
 */
void LogicEngine::addComponent(std::unique_ptr<Gate> c) {
    if (c != nullptr) {
        circuit.push_back(std::move(c));  // Teil A: std::move übergibt Ownership
        std::cout << "[LogicEngine] Komponente hinzugefügt. Gesamt: " << circuit.size() << std::endl;
    }
}

/**
 * doTick(): Polymorphe Evaluation aller Komponenten.
 * Der Smart Pointer verhält sich wie ein normaler Pointer beim Zugriff.
 */
void LogicEngine::doTick() {
    tickCount++;
    std::cout << "\n[Tick " << tickCount << "] Evaluiere " << circuit.size() 
              << " Komponenten:" << std::endl;
    
    for (const auto& c : circuit) {
        // unique_ptr unterstützt -> wie ein normaler Pointer
        bool result = c->evaluate();
        c->printState();
        std::cout << "  => Ergebnis: " << (result ? "true" : "false") << std::endl;
    }
}

int LogicEngine::getComponentCount() const {
    return circuit.size();
}
