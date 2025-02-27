//
// Created by arno on 2/12/23.
//

#include "CPU.h"
#include <iostream>
#include <iomanip>
#include "Input.h"
#define ROW_WIDTH (MAX_COMPONENT_ID_LENGTH + MAX_MANUFACTURER_LENGTH + MAX_COMPONENT_NAME_LENGTH + \
                  MAX_PRICE_LENGTH + MAX_STOCK_LENGTH + MAX_COMPONENT_TYPE_LENGTH + MAX_COMPUTER_TYPE_LENGTH + \
                  MAX_CLOCK_SPEED_LENGTH + MAX_CORE_COUNT_LENGTH + MAX_SOCKET_LENGTH + 30)

CPU::CPU() : ComponentBase("", "", 0, 0, ComponentType_t::CPU, ComputerType_t::DESKTOP, 0), my_clockSpeed(0),
             my_coreCount(0), my_socket("") {}

CPU::CPU(std::string manufacturer, std::string name, float price, unsigned int stock, ComponentType_t type,
         ComputerType_t computerType, unsigned int componentID, float clockSpeed, unsigned int coreCount, std::string socket) :
        ComponentBase(std::move(manufacturer), std::move(name), price, stock, type, computerType, componentID),
        my_clockSpeed(clockSpeed), my_coreCount(coreCount), my_socket(socket){}

std::shared_ptr<CPU> CPU::Create(unsigned int componentID) {
    std::string manufacturer;
    std::string name;
    float price;
    unsigned int stock;
    ComputerType_t type;
    float clockSpeed;
    unsigned int coreCount;
    std::string socket;

    std::cout << "Enter manufacturer: ";
    std::getline(std::cin, manufacturer);
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter price: ";
    price = input<float>();
    std::cout << "Enter stock: ";
    stock = input<unsigned int>();
    std::cout << "Enter clock speed: ";
    clockSpeed = input<float>();
    std::cout << "Enter core count: ";
    coreCount = input<unsigned int>();
    std::cout << "Enter socket: ";
    std::getline(std::cin, socket);
    type = selectComputerType();
    return std::make_shared<CPU>(manufacturer, name, price, stock, ComponentType_t::CPU, type, componentID, clockSpeed, coreCount, socket);
}

void CPU::printHeader(bool indexed) {
    // Print index column
    if (indexed)
        std::cout << std::setw(5) << "Index" << " | ";

    // Print header columns
    std::cout   << std::setw(MAX_COMPONENT_ID_LENGTH) << "ID" << " | "
                << std::setw(MAX_MANUFACTURER_LENGTH) << "Manufacturer" << " | "
                << std::setw(MAX_COMPONENT_NAME_LENGTH) << "Name" << " | "
                << std::setw(MAX_PRICE_LENGTH) << "Price" << " | "
                << std::setw(MAX_STOCK_LENGTH) << "Stock" << " | "
                << std::setw(MAX_COMPONENT_TYPE_LENGTH) << "Type" << " | "
                << std::setw(MAX_COMPUTER_TYPE_LENGTH) << "Computer Type" << " | "
                << std::setw(MAX_CLOCK_SPEED_LENGTH) << "Clock Speed" << " | "
                << std::setw(MAX_CORE_COUNT_LENGTH) << "Core Count" << " | "
                << std::setw(MAX_SOCKET_LENGTH) << "Socket" << " | " << std::endl;

    // Print horizontal line
    if (indexed)
        std::cout << std::string(5+3+ROW_WIDTH, '-') << std::endl;
    else
        std::cout << std::string(ROW_WIDTH, '-') << std::endl;
}


void CPU::printRow(int index) const {
    ComponentBase::printBase(index);
    std::cout   << std::setw(MAX_CLOCK_SPEED_LENGTH) << my_clockSpeed << " | "
                << std::setw(MAX_CORE_COUNT_LENGTH) << my_coreCount << " | "
                << std::setw(MAX_SOCKET_LENGTH) << my_socket.c_str() << " | ";
}

void CPU::update() {
    ComponentBase::update();
    std::string temp;

    std::cout << "Current clock speed: " << my_clockSpeed << std::endl;
    if (yesNoQuestion("Change clock speed? ")) {
        std::cout << "Enter new clock speed: ";
        my_clockSpeed = input<float>();
    }
    std::cout << "Current core count: " << my_coreCount << std::endl;
    if (yesNoQuestion("Change core count? ")) {
        std::cout << "Enter new core count: ";
        my_coreCount = input<int>();
    }
    std::cout << "Current socket: " << my_socket.c_str() << std::endl;
    if (yesNoQuestion("Change socket? ")) {
        std::cout << "Enter new socket: ";
        std::getline(std::cin, temp);
        my_socket = temp;
    }
}

void CPU::selectFilter(ComponentView &view) {
    std::cout   << "Select filter:"
                << "\n\t1. Manufacturer"
                << "\n\t2. Name"
                << "\n\t3. Price"
                << "\n\t4. Price higher than"
                << "\n\t5. Price lower than"
                << "\n\t6. Stock"
                << "\n\t7. Computer Type"
                << "\n\t8. Clock Speed"
                << "\n\t9. Core Count"
                << "\n\t10. Socket" << std::endl;

    switch (inputRange(1, 10)) {
        case 1:
            ComponentBase::filterManufacturer(view);
            break;
        case 2:
            ComponentBase::filterName(view);
            break;
        case 3:
            ComponentBase::filterPrice(view);
            break;
        case 4:
            ComponentBase::filterPriceHigher(view);
            break;
        case 5:
            ComponentBase::filterPriceLower(view);
            break;
        case 6:
            ComponentBase::filterStock(view);
            break;
        case 7:
            ComponentBase::filterComputerType(view);
            break;
        case 8:
            filterClockSpeed(view);
            break;
        case 9:
            filterCoreCount(view);
            break;
        case 10:
            filterSocket(view);
            break;
    }
}

void CPU::filterClockSpeed(ComponentView &view) {
    std::cout << "Enter clock speed: ";
    float clockSpeed = input<float>();
    view.filter([&clockSpeed](const std::weak_ptr<ComponentBase>& component) {
        return std::dynamic_pointer_cast<CPU>(component.lock())->my_clockSpeed != clockSpeed;
    });
}

void CPU::filterCoreCount(ComponentView &view) {
    std::cout << "Enter core count: ";
    int coreCount = input<int>();
    view.filter([&coreCount](const std::weak_ptr<ComponentBase>& component) {
        return std::dynamic_pointer_cast<CPU>(component.lock())->my_coreCount != coreCount;
    });
}

void CPU::filterSocket(ComponentView &view) {
    std::cout << "Enter socket: ";
    std::string socket;
    std::getline(std::cin, socket);
    view.filter([&socket](const std::weak_ptr<ComponentBase>& component) {
        return std::dynamic_pointer_cast<CPU>(component.lock())->my_socket != socket;
    });
}
