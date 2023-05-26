#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "../LinkedList.h"
#include "../Coin.h"
#include <string>

class Behavior {
public:
    virtual ~Behavior() {}
    virtual void print_menu() = 0;
    virtual void process_option_2(LinkedList& itemList, Coin& coinList) = 0;
    virtual Coin initializeCoins(const std::string& coin_file) = 0;
    // Other methods...
};

#endif // BEHAVIOR_H
