#include "Component.h"

void Gate::connectInput(int index, std::shared_ptr<Gate> source) {
    if (index >= 0 && index < (int)m_inputs.size()) {
        m_inputs[index] = source;
    } else {
        std::cerr << "FEHLER: Pin " << index << " existiert nicht am Gatter '"
                  << m_name << "'!" << std::endl;
    }
}
