#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <exception>

/**
 * FloatingPinException (Zusatzaufgabe 2)
 * Wird geworfen, wenn ein Eingangs-Pin nicht verbunden ist
 */
class FloatingPinException : public std::exception {
private:
    std::string m_message;
public:
    FloatingPinException(const std::string& gateName, int pinIndex)
        : m_message("FloatingPinException: Pin " + std::to_string(pinIndex) +
                    " am Gatter '" + gateName + "' ist nicht verbunden!") {}

    const char* what() const noexcept override {
        return m_message.c_str();
    }
};

/**
 * Gate (Basisklasse) - Abstraktion für alle Logikgatter
 * Phase 1: Universelle Anschlussleiste mit shared_ptr
 */
class Gate {
protected:
    std::string m_name;
    std::vector<std::shared_ptr<Gate>> m_inputs;
    bool m_output = false;
    bool m_isCalculated = false; // Unser Cache-Flag

public:
    Gate() : m_name("unnamed") {}
    Gate(std::string n) : m_name(n) {}
    virtual void reset() {
    m_isCalculated = false;
    m_output = false;
}

    /**
     * Verbindet einen Eingangs-Pin mit einem anderen Gatter (das "Kabel")
     * Phase 1, Schritt 3
     */
    void connectInput(int index, std::shared_ptr<Gate> source);

    bool getOutput() const { return m_output; }
    std::string getName() const { return m_name; }

    virtual void evaluate() = 0;
    virtual void printState() const = 0;

    virtual ~Gate() {}
};
