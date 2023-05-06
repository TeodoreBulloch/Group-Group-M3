#include "Coin.h"
Coin::Coin() 
{

}

void Coin::StartStock(int coin []) {
    this->ten_dollar = coin[0];
    this->five_dollar = coin[1];
    this->two_dollar = coin[2];
    this->one_dollar = coin[3];
    this->fifty_cent = coin[4];
    this->twenty_cent = coin[5];
    this->ten_cent = coin[6];
    this->five_cent = coin[7];
}

void Coin::Set_Cost(int cost) {
    this->product_cost = cost;
}

bool Coin::Pay(int pay) {
    this->product_cost -= pay;
    if (this->product_cost > 0) {
        std::cout << "Amount left to pay: $" << this->product_cost/100 << std::endl;
        return false;
    }
    else {
        Coin::Difference(this->product_cost);
        return true;
    }
}

int Coin::GetProductCost() const {
    return product_cost;
}


std::list<std::string> Coin::Change(int difference) {
    std::list<std::string> change;
    while (1000 >= difference && difference > 0 && this->ten_dollar > 0 && difference >= 1000) {
        change.push_back("$10");
        difference = difference - 1000;
        this->ten_dollar -= 1;
    }
    while (500 >= difference && difference > 0 && this->five_dollar > 0 && difference >= 500) {
        change.push_back("$5");
        difference = difference - 500;
        this->five_dollar -= 1;
    }
    while (200 >= difference && difference > 0 && this->two_dollar > 0 && difference >= 200) {
        change.push_back("$2");
        difference = difference - 200;
        this->two_dollar -= 1;
    }
    while (100 >= difference && difference > 0 && this->one_dollar > 0 && difference >= 100) {
        change.push_back("$1");
        difference = difference - 100;
        this->one_dollar -= 1;
    }
    while (50 >= difference && difference > 0 && this->fifty_cent > 0 && difference >= 50) {
        change.push_back("50c");
        difference = difference - 50;
        this->fifty_cent -= 1;
    }
    while (20 >= difference && difference > 0 && this->twenty_cent > 0 && difference >= 20) {
        change.push_back("20c");
        difference = difference - 20;
        this->twenty_cent -= 1;
    }
    while (10 >= difference && difference > 0 && this->ten_cent > 0 && difference >= 10) {
        change.push_back("10c");
        difference = difference - 10;
        this->ten_cent -= 1;
    }
    while (difference > 0 && this->five_cent > 0 && difference >= 5) {
        change.push_back("5c");
        difference = difference - 5;
        this->five_cent -= 1;
    }
    // might need to change the return depending on what format the return is needed in
    return change;
}

int Coin::Difference(int overpay) {
    int difference = abs(overpay);

    return difference;
    
}
 // implement functions for managing coins; this may depend on your design.
// Kelvin was here