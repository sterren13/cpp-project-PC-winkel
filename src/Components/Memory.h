//
// Created by arno on 2/12/23.
//

#ifndef PC_WINKLE_MEMORY_H
#define PC_WINKLE_MEMORY_H
#include "ComponentBase.h"
#include <memory>

class Memory : public ComponentBase {
public:
    Memory(std::string manufacturer,
           std::string name,
           float price,
           unsigned int stock,
           ComponentType_t type,
           ComputerType_t computerType,
           unsigned int componentID,
           unsigned int size,
           float clockSpeed);

    [[nodiscard]] inline unsigned int getSize() const { return my_size; }
    [[nodiscard]] inline float getClockSpeed() const { return my_clockSpeed; }

    inline void setSize(unsigned int size) { this->my_size = size; }
    inline void setClockSpeed(float clockSpeed) { this->my_clockSpeed = clockSpeed; }

    void print() const final;
    void update() final;

    static std::shared_ptr<Memory> Create(unsigned int componentID);

private:
    unsigned int my_size;
    float my_clockSpeed;
};


#endif //PC_WINKLE_MEMORY_H
