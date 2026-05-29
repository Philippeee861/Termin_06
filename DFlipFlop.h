#pragma once
#include "Component.h"



class DFlipFlop : public Gate {
public:
    DFlipFlop();
    DFlipFlop(std::string n);

    void evaluate() override;
    void onClockTick();
    void printState() const override;

private:
    bool m_storedState = false;
};