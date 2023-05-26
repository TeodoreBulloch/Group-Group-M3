#include "EnhancedBehavior.h"
#include <iostream>
#include <string>
#include <list>
#include <exception>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::cin;
using std::list;
using std::exception;
using std::ifstream;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLD    "\033[1m"       /* Bold */

void EnhancedBehavior::print_menu() {
    cout << BLUE << "Main Menu:" << RESET << endl;
    cout << BLUE << "\t1.Display Items" << RESET << endl;
    cout << BLUE << "\t2.Purchase Items" << RESET << endl;
    cout << BLUE << "\t3.Save and Exit" << RESET << endl;
    cout << GREEN << "Administrator-Only Menu:" << RESET << endl;
    cout << GREEN << "\t4.Add Item" << RESET << endl;
    cout << GREEN << "\t5.Remove Item" << RESET << endl;
    cout << GREEN << "\t6.Display Coins" << RESET << endl;
    cout << GREEN << "\t7.Reset Stock" << RESET << endl;
    cout << GREEN << "\t8.Reset Coins" << RESET << endl;
    cout << RED << "\t9.Abort Program" << RESET << endl;
    cout << MAGENTA << "\t0.Switch to Default Version" << RESET << endl;
    cout << "Select your option (0-9):" << endl;
}

void EnhancedBehavior::process_option_2(LinkedList& itemList, Coin& coinList) {
    string item_id;
    string input;
    int payment = -1;

    cout << YELLOW << "Purchase Item" << endl;
    cout << "-------------" << RESET << endl;
    cout << "Please enter the id of the item you wish to purchase: ";
    getline(cin ,item_id);
    getline(cin ,item_id);
    cout << "item ID : " << item_id << endl;
    // Find the item with the given ID in the linked list
    Node* itemNode = itemList.findItem(item_id);

    if (itemNode == nullptr) {
        cout << RED << "Item not found." << RESET << endl;
        return;
    }

    Stock item = itemNode->data;
    int item_cost = item.price.dollars * 100 + item.price.cents;

    coinList.Set_Cost(item_cost);

    cout << "You have selected \"" << item.name << "\". This will cost you $" << GREEN << item.price.dollars << "." << item.price.cents << "." << RESET << endl;
    cout << "Please hand over the money - type in the value of each note/coin in cents." << endl;
    cout << "Press enter or ctrl-d on a new line to cancel this purchase:" << endl;

    bool purchasing = true;
    while (purchasing) {
        bool valid = false;
        while (!valid){
            getline(cin, input);
            
            if(input == "") {
                coinList.RefundCoins();
                purchasing = false;
                valid = true;
            }
            else {
                
                try{
                    std::size_t count = 0;
                    while (count < input.length()){
                        if (input[count] ==' '){
                            throw std::invalid_argument("invalid argument");
                        }
                        count++;
                    }
                    payment = stoi(input);
                    cout << "Checking Coin input" << GREEN << payment << RESET << endl;
                    valid = true;
                }
                catch(exception &errc){
                    cout << RED << "Please input a valid amount: " << RESET << endl;
                }
            }
        }
        // Check for valid denominations
        if (purchasing){
            if (payment == 1000 || payment == 500 || payment == 200 || payment == 100 || payment == 50 || payment == 20 || payment == 10 || payment == 5) {
                if (coinList.Pay(payment)) {
                    int change = coinList.Difference(coinList.GetProductCost());

                    if (!coinList.CanMakeChange(change)) {
                        coinList.RefundCoins();
                        cout << RED << "Sorry, the machine does not have enough change for this transaction. Your payment has been refunded." << RESET << endl;
                        purchasing = false;
                    }
                    else {
                        list<int> returned_change = coinList.Change(change);

                        cout << "Here is your " << GREEN << item.name << RESET << " and your change of" << GREEN << "$" << GREEN << change/100.00 << RESET << ": ";
                        for (int coin : returned_change) {
                            if (coin < 100) {
                                cout << GREEN << coin << "c " << RESET;  // Print as cents if the coin is less than a dollar
                            } else {
                                cout << GREEN << "$" << (coin / 100.0) << " " << RESET;  // Otherwise, print as dollars
                            }
                        }
                        cout << endl;

                        // Decrease the stock of the purchased item
                        itemNode->data.on_hand--;
                        purchasing = false;
                    }
                }
            } else {
                cout << RED << "Error: " << payment << " is not a valid denomination of money. Please try again." << RESET << endl;
                cout << "You still need to give us $" << GREEN << (coinList.GetProductCost() / 100) << "." << (coinList.GetProductCost() % 100) << RESET << ": ";
            }
        }    
    }
}

Coin EnhancedBehavior::initializeCoins(const string& coin_file) {
    Coin coin;
    ifstream file(coin_file);

    if (file.is_open()) {
        int coin_values[16];
        int count = 0;

        while (count < 16 && file >> coin_values[count]) {
            // Read the comma
            file.ignore(1);
            count++;
        }

        // Initialize the coin stock
        coin.StartStock(coin_values);
    } else {
        cout << RED << "Unable to open coin file: " << coin_file << RESET << endl;
    }

    return coin;
}
