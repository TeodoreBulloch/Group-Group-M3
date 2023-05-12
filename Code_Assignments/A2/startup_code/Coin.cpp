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
}

void Coin::Set_Cost(int cost) {
    this->product_cost = cost;
}

bool Coin::Pay(int pay) {

    this->product_cost -= pay;
    if (pay == 5) {
        this->five_cent += 1;
        refund_5 += 1;
    }
    else if (pay == 10) {
        this->ten_cent += 1;
        refund_10 += 1;
    }
    else if (pay == 20) {
        this->twenty_cent += 1;
        refund_20 += 1;
    }
    else if (pay == 50) {
        this->fifty_cent += 1;
        refund_50 += 1;
    }
    else if (pay == 100) {
        this->one_dollar += 1;
        refund_100 += 1;
    }
    else if (pay == 200) {
        this->two_dollar += 1;
        refund_200 += 1;
    }
    else if (pay == 500) {
        this->five_dollar += 1;
        refund_500 += 1;
    }
    else if (pay == 1000) {
        this->ten_dollar += 1;
        refund_1000 += 1;
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
    this->ten_dollar = DEFAULT_COIN_COUNT;
    this->five_dollar = DEFAULT_COIN_COUNT;
    this->two_dollar = DEFAULT_COIN_COUNT;
    this->one_dollar = DEFAULT_COIN_COUNT;
    this->fifty_cent = DEFAULT_COIN_COUNT;
    this->twenty_cent = DEFAULT_COIN_COUNT;
    this->ten_cent = DEFAULT_COIN_COUNT;
    this->five_cent = DEFAULT_COIN_COUNT;
    std::cout << "All coins have been reset to the default level of " << DEFAULT_COIN_COUNT << std::endl;
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

void Coin::SaveCoins(std::string coinFile) const{
    // Change test_coins.txt to Coins.dat later
    std::ofstream MyFile(coinFile);

    MyFile << "1000," << this->ten_dollar << std::endl;
    MyFile << "500," << this->five_dollar << std::endl;
    MyFile << "200," << this->two_dollar << std::endl;
    MyFile << "100," << this->one_dollar << std::endl;
    MyFile << "50," << this->fifty_cent << std::endl;
    MyFile << "20," << this->twenty_cent << std::endl;
    MyFile << "10," << this->ten_cent << std::endl;
    MyFile << "5," << this->five_cent << std::endl;

    MyFile.close();
}

void Coin::RefundCoins() {
    this->five_cent -= refund_5;
    this->ten_cent -= refund_10;
    this->twenty_cent -= refund_20;
    this->fifty_cent -= refund_50;
    this->one_dollar -= refund_100;
    this->two_dollar -= refund_200;
    this->five_dollar -= refund_500;
    this->ten_dollar -= refund_1000;

    this->refund_5 = 0;
    this->refund_10 = 0;
    this->refund_20 = 0;
    this->refund_50 = 0;
    this->refund_100 = 0;
    this->refund_200 = 0;
    this->refund_500 = 0;
    this->refund_1000 = 0;
    std::cout << "Transaction cancelled your money has been refunded." << std::endl;
}

bool Coin::CanMakeChange(int difference) {
    int changeRequired = difference;

    if (changeRequired >= 1000 && this->ten_dollar > 0) changeRequired %= 1000;
    if (changeRequired >= 500 && this->five_dollar > 0) changeRequired %= 500;
    if (changeRequired >= 200 && this->two_dollar > 0) changeRequired %= 200;
    if (changeRequired >= 100 && this->one_dollar > 0) changeRequired %= 100;
    if (changeRequired >= 50 && this->fifty_cent > 0) changeRequired %= 50;
    if (changeRequired >= 20 && this->twenty_cent > 0) changeRequired %= 20;
    if (changeRequired >= 10 && this->ten_cent > 0) changeRequired %= 10;
    if (changeRequired >= 5 && this->five_cent > 0) changeRequired %= 5;

    return changeRequired == 0;  // If we can make the exact change, return true.
}

 // implement functions for managing coins; this may depend on your design.
// Kelvin was here