#ifndef ENHANCEDBEHAVIOR_H
#define ENHANCEDBEHAVIOR_H

#include "Behavior.h"
#include <string>

class EnhancedBehavior : public Behavior {
public:
    void print_menu() override;
    void process_option_2(LinkedList& itemList, Coin& coinList) override;
    Coin initializeCoins(const std::string& coin_file) override;
    // Other methods...
};

#endif // ENHANCEDBEHAVIOR_H
