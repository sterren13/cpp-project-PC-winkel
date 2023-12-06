//
// Created by arno on 2/12/23.
//

#include "Motherboard.h"
#include <iostream>
#include <iomanip>
#include "Input.h"

Motherboard::Motherboard(std::string manufacturer, std::string name, float price, unsigned int stock,
                         ComponentType_t type, ComputerType_t computerType, unsigned int componentID,
                         std::string socket, std::string formFactor, unsigned int maxMemorySlots) :
                         ComponentBase(std::move(manufacturer), std::move(name), price, stock, type, computerType, componentID),
                         my_socket(std::move(socket)), my_formFactor(std::move(formFactor)), my_maxMemorySlots(maxMemorySlots){

}

std::shared_ptr<Motherboard> Motherboard::Create(unsigned int componentID) {
    std::string manufacturer;
    std::string name;
    float price;
    unsigned int stock;
    ComputerType_t type;
    std::string socket;
    std::string formFactor;
    unsigned int maxMemorySlots;

    std::cout << "Enter manufacturer: ";
    std::getline(std::cin, manufacturer);
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter price: ";
    price = input<float>();
    std::cout << "Enter stock: ";
    stock = input<unsigned int>();
    std::cout << "Enter socket: ";
    std::getline(std::cin,socket);
    std::cout << "Enter form factor: ";
    std::getline(std::cin, formFactor);
    std::cout << "Enter max memory slots: ";
    maxMemorySlots = input<unsigned int>();
    type = selectComputerType();
    return std::make_shared<Motherboard>(manufacturer, name, price, stock, ComponentType_t::MOTHERBOARD, type, componentID, socket, formFactor, maxMemorySlots);
}

void Motherboard::printHeader(bool indexed) {
    // Print index column
    if (indexed)
        std::cout << std::setw(5) << "Index" << " | ";

    // Print header columns
    std::cout   << std::setw(10) << "ID" << " | "
                << std::setw(MAX_MANUFACTURER_LENGTH) << "Manufacturer" << " | "
                << std::setw(MAX_COMPONENT_NAME_LENGTH) << "Name" << " | "
                << std::setw(10) << "Price" << " | "
                << std::setw(10) << "Stock" << " | "
                << std::setw(11) << "Type" << " | "
                << std::setw(15) << "Computer Type" << " | "
                << std::setw(10) << "Socket" << " | "
                << std::setw(15) << "Form Factor" << " | "
                << std::setw(15) << "Max Memory Slots" << " | " << std::endl;

    // Print horizontal line
    if (indexed)
        std::cout << std::string(5+10+MAX_MANUFACTURER_LENGTH+MAX_COMPONENT_NAME_LENGTH+10+10+11+15+24, '-') << std::endl;
    else
        std::cout << std::string(10+MAX_MANUFACTURER_LENGTH+MAX_COMPONENT_NAME_LENGTH+10+10+11+15+21, '-') << std::endl;
}

void Motherboard::printRow(int index) const {
    ComponentBase::printBase(index);
    std::cout   << std::setw(10) << my_socket.c_str() << " | "
                << std::setw(15) << my_formFactor.c_str() << " | "
                << std::setw(15) << my_maxMemorySlots << " | " << std::endl;
}

void Motherboard::update() {
    ComponentBase::update();
    std::string temp;
    std::cout << "Current socket: " << my_socket.c_str() << std::endl;
    if (changeQuestion("Change socket?")) {
        std::cout << "Enter new socket: ";
        std::getline(std::cin, temp);
        my_socket = temp;
    }
    std::cout << "Current form factor: " << my_formFactor.c_str() << std::endl;
    if (changeQuestion("Change form factor?")) {
        std::cout << "Enter new form factor: ";
        std::getline(std::cin, temp);
        my_formFactor = temp;
    }
    std::cout << "Current max memory slots: " << my_maxMemorySlots << std::endl;
    if (changeQuestion("Change max memory slots?")) {
        std::cout << "Enter new max memory slots: ";
        my_maxMemorySlots = input<unsigned int>();
    }
}