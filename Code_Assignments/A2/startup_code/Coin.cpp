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

void Coin::Tally() {
this->ten_cent += 1;
}

int Coin::Change() {
    return 0;
}

int Coin::Difference() {
    return 0;
    
}
 // implement functions for managing coins; this may depend on your design.
// Kelvin was here