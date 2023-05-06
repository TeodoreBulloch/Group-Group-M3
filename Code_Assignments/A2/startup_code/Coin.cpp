#include "Coin.h"
Coin::Coin() 
{

}

void Coin::StartStock(int coin []) {
    this->ten_dollar = coin[1];
    this->five_dollar = coin[3];
    this->two_dollar = coin[5];
    this->one_dollar = coin[7];
    this->fifty_cent = coin[9];
    this->twenty_cent = coin[11];
    this->ten_cent = coin[13];
    this->five_cent = coin[15];

    this->reset_ten_dollar = coin[1];
    this->reset_five_dollar = coin[3];
    this->reset_two_dollar = coin[5];
    this->reset_one_dollar = coin[7];
    this->reset_fifty_cent = coin[9];
    this->reset_twenty_cent = coin[11];
    this->reset_ten_cent = coin[13];
    this->reset_five_cent = coin[15];
}

void Coin::Set_Cost(int cost) {
    this->product_cost = cost;
}

bool Coin::Pay(int pay) {
    this->product_cost -= pay;
    if (pay == 5) {
        this->five_cent += 1;
    }
    else if (pay == 10) {
        this->ten_cent += 1;
    }
    else if (pay == 20) {
        this->twenty_cent += 1;
    }
    else if (pay == 50) {
        this->fifty_cent += 1;
    }
    else if (pay == 100) {
        this->one_dollar += 1;
    }
    else if (pay == 200) {
        this->two_dollar += 1;
    }
    else if (pay == 500) {
        this->five_dollar += 1;
    }
    else if (pay == 1000) {
        this->ten_dollar += 1;
    }
    if (this->product_cost > 0) {
        std::cout << "Amount left to pay: $" << this->product_cost/100.0 << std::endl;
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


std::list<int> Coin::Change(int difference) {
    std::list<int> change;
    while (this->ten_dollar > 0 && difference >= 1000) {
        change.push_back(1000);
        difference = difference - 1000;
        this->ten_dollar -= 1;
    }
    while (this->five_dollar > 0 && difference >= 500) {
        change.push_back(500);
        difference = difference - 500;
        this->five_dollar -= 1;
    }
    while (this->two_dollar > 0 && difference >= 200) {
        change.push_back(200);
        difference = difference - 200;
        this->two_dollar -= 1;
    }
    while (this->one_dollar > 0 && difference >= 100) {
        change.push_back(100);
        difference = difference - 100;
        this->one_dollar -= 1;
    }
    while (this->fifty_cent > 0 && difference >= 50) {
        change.push_back(50);
        difference = difference - 50;
        this->fifty_cent -= 1;
    }
    while (this->twenty_cent > 0 && difference >= 20) {
        change.push_back(20);
        difference = difference - 20;
        this->twenty_cent -= 1;
    }
    while (this->ten_cent > 0 && difference >= 10) {
        change.push_back(10);
        difference = difference - 10;
        this->ten_cent -= 1;
    }
    while (difference > 0 && this->five_cent > 0 && difference >= 5) {
        change.push_back(5);
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

void Coin::Reset() {
    this->ten_dollar = this->reset_ten_dollar;
    this->five_dollar = this->reset_five_dollar;
    this->two_dollar = this->reset_two_dollar;
    this->one_dollar = this->reset_one_dollar;
    this->fifty_cent = this->reset_fifty_cent;
    this->twenty_cent = this->reset_twenty_cent;
    this->ten_cent = this->reset_ten_cent;
    this->five_cent = this->reset_five_cent;
}

void Coin::DisplayCoins() {
    std::cout << "Coins Summary" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Denomination  |   Count" << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "5 Cents       |       " << this->five_cent << std::endl;
    std::cout << "10 Cents      |       " << this->ten_cent << std::endl;
    std::cout << "20 Cents      |       " << this->twenty_cent << std::endl;
    std::cout << "50 Cents      |       " << this->fifty_cent << std::endl;
    std::cout << "1 Dollar      |       " << this->one_dollar << std::endl;
    std::cout << "2 Dollar      |       " << this->two_dollar << std::endl;
    std::cout << "5 Dollar      |       " << this->five_dollar << std::endl;
    std::cout << "10 Dollar     |       " << this->ten_dollar << std::endl;
}

void Coin::SaveCoins() {
    std::ofstream MyFile("test_coins.txt");

    MyFile << "1000," << this->ten_dollar;
    MyFile << "500," << this->five_dollar;
    MyFile << "200," << this->two_dollar;
    MyFile << "100," << this->one_dollar;
    MyFile << "50," << this->fifty_cent;
    MyFile << "20," << this->twenty_cent;
    MyFile << "10," << this->ten_cent;
    MyFile << "5," << this->five_cent;

    MyFile.close();
}
 // implement functions for managing coins; this may depend on your design.
// Kelvin was here