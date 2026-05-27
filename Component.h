#pragma once

#include <string>
#include <iostream>

/**
 * Component (Basisklasse) - Abstraktion für alle Logikgatter
 */
class Component {
protected:
    std::string name;
    bool inA;
    bool inB;
    bool output;

public:
    Component(std::string n);

    virtual void setInputA(int val);
    virtual void setInputB(int val);
    bool getOutput() const;

    virtual bool evaluate() = 0;
    virtual void printState() const = 0;

    // Vorbereitung: Destruktor mit Konsolenausgabe (beweist Memory-Freigabe)
    virtual ~Component() {
        std::cout << "Zerstöre Bauteil: " << name << std::endl;
    }
};
