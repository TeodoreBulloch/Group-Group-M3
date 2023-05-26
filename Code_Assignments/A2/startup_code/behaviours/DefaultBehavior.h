#ifndef DEFAULTBEHAVIOR_H
#define DEFAULTBEHAVIOR_H

#include "Behavior.h"
#include <string>


class DefaultBehavior : public Behavior {
public:
    void print_menu() override;
    void process_option_2(LinkedList& itemList, Coin& coinList) override;
    Coin initializeCoins(const std::string& coin_file) override;
    // Other methods...
};

#endif // DEFAULTBEHAVIOR_H
