//
// Created by arno on 2/12/23.
//

#include "Case.h"
#include <iostream>

Case::Case(std::string manufacturer, std::string name, float price, unsigned int stock, ComputerType_t computerType,
           unsigned int componentID, std::string color, std::string MotherboardSize,
           std::string material) : ComponentBase(std::move(manufacturer), std::move(name), price, stock, ComponentType_t::CASE,
                                                 computerType, componentID), my_color(std::move(color)),
                                   MotherboardSize(std::move(MotherboardSize)), my_material(std::move(material)) {

}

void Case::print() const {
    ComponentBase::print();
}

void Case::update() {
    ComponentBase::update();
    std::cout << "Current color: " << my_color.c_str() << std::endl;
    if (changeQuestion("Change color? ")) {
        std::cout << "Enter new color: ";
        std::cin >> my_color;
    }
    std::cout << "Current MotherboardSize: " << MotherboardSize.c_str() << std::endl;
    if (changeQuestion("Change MotherboardSize? ")) {
        std::cout << "Enter new MotherboardSize: ";
        std::cin >> MotherboardSize;
    }
    std::cout << "Current material: " << my_material.c_str() << std::endl;
    if (changeQuestion("Change material? ")) {
        std::cout << "Enter new material: ";
        std::cin >> my_material;
    }
}

std::shared_ptr<Case> Case::Create(unsigned int componentID) {
    std::string manufacturer;
    std::string name;
    float price;
    unsigned int stock;
    ComputerType_t type;
    std::string color;
    std::string MotherboardSize;
    std::string material;

    std::cout << "Enter manufacturer: ";
    std::cin >> manufacturer;
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter price: ";
    std::cin >> price;
    std::cout << "Enter stock: ";
    std::cin >> stock;
    std::cout << "Enter color: ";
    std::cin >> color;
    std::cout << "Enter MotherboardSize: ";
    std::cin >> MotherboardSize;
    std::cout << "Enter material: ";
    std::cin >> material;
    type = selectComputerType();

    return std::make_shared<Case>(manufacturer, name, price, stock, type, componentID, color, MotherboardSize, material);
}
