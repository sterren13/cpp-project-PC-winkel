//
// Created by arno on 2/12/23.
//

#ifndef PC_WINKLE_COMPANY_H
#define PC_WINKLE_COMPANY_H
#include "Customer.h"

class Company : public Customer {
public:

    Company(Name_t name, Address_t address, unsigned int customerID, float vat, float discount, unsigned int yearlyBuy);

    [[nodiscard]] inline float getVat() const { return my_vat; }
    [[nodiscard]] inline float getDiscount() const { return my_discount; }
    [[nodiscard]] inline unsigned int getYearlyBuy() const { return my_yearlyBuy; }

    inline void setVat(float vat) { my_vat = vat; }
    inline void setDiscount(float discount) { my_discount = discount; }
    inline void setYearlyBuy(unsigned int yearlyBuy) { my_yearlyBuy = yearlyBuy; }

private:
    float my_vat;
    float my_discount;
    unsigned int my_yearlyBuy;
};


#endif //PC_WINKLE_COMPANY_H
