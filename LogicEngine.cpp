#include "LogicEngine.h"
#include <iostream>

LogicEngine::LogicEngine() {
    circuitName = "Unbenannt";
    tickCount = 0;
    currentOutput = 0;
}

// Destruktor: gibt den Speicher aller Komponenten frei
LogicEngine::~LogicEngine() {
    for (Component* c : circuit) {
        delete c;
    }
    circuit.clear();
    std::cout << "[Engine] Speicher freigegeben." << std::endl;
}

void LogicEngine::setCircuitName(std::string name) {
    circuitName = name;
    std::cout << "[Engine] Schaltungsname gesetzt auf: " << circuitName << std::endl;
}

// Aufgabe 1: Bauteil zum Vektor hinzufügen
void LogicEngine::addComponent(Component* component) {
    circuit.push_back(component);
    std::cout << "[Engine] Bauteil hinzugefügt. Anzahl Bauteile: " << circuit.size() << std::endl;
}

// Aufgabe 2: Simulations-Schleife — ruft evaluate() auf jedem Bauteil auf
void LogicEngine::doTick() {
    tickCount++;
    std::cout << "\n[Engine] === Tick #" << tickCount << " ===" << std::endl;

    for (Component* c : circuit) {
        c->evaluate(); // C++ findet automatisch die richtige Gatter-Logik (Polymorphismus)!
        c->printState();
    }
}

int LogicEngine::getOutputState() const {
    return currentOutput;
}

int LogicEngine::getTickCount() const {
    return tickCount;
}
