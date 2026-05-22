#pragma once

#include <string>
#include <vector>
#include "Component.h"

/**
 * Die LogicEngine ist der Kern unseres Simulators.
 * Sie verwaltet eine Liste von Bauteilen (Component*) und
 * simuliert jeden Taktschritt durch Aufruf von evaluate().
 */
class LogicEngine {
private:
    std::string circuitName;
    int tickCount;
    int currentOutput;

    // Aufgabe 1: Vektor von Component-Zeigern
    std::vector<Component*> circuit;

public:
    // Konstruktor
    LogicEngine();

    // Destruktor: gibt den Speicher aller Komponenten frei
    ~LogicEngine();

    // Setzt den Namen der Schaltung
    void setCircuitName(std::string name);

    // Aufgabe 1: Fügt ein Bauteil zum Vektor hinzu
    void addComponent(Component* component);

    // Aufgabe 2: Iteriert über alle Bauteile und ruft evaluate() auf
    void doTick();

    // Gibt den aktuellen Ausgangswert zurück
    int getOutputState() const;

    // Gibt die Anzahl bisheriger Ticks zurück
    int getTickCount() const;
};
