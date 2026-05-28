#pragma once

#include <string>
#include <vector>
#include <memory>       // Teil A: #include <memory> hinzugefügt
#include "Component.h"

/**
 * Die LogicEngine verwaltet Komponenten mit Smart Pointern (RAII).
 * Keine nackten Pointer, kein manuelles delete, kein Memory Leak.
 */
class LogicEngine {
private:
    std::string circuitName;
    int tickCount;
    // Teil A: Vektor verwendet jetzt unique_ptr statt rohe Pointer
    std::vector<std::unique_ptr<Gate>> circuit;

public:
    LogicEngine();
    ~LogicEngine();

    void setCircuitName(std::string name);

    // Teil A: Methode nimmt unique_ptr entgegen (übernimmt Ownership)
    void addComponent(std::unique_ptr<Gate> c);

    void doTick();
    int getComponentCount() const;
};
