#include "DefaultBehavior.h"
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

void DefaultBehavior::print_menu() {
    cout << "Main Menu:" << endl;
    cout << "\t1.Display Items" << endl;
    cout << "\t2.Purchase Items" << endl;
    cout << "\t3.Save and Exit" << endl;
    cout << "Administrator-Only Menu:" << endl;
    cout << "\t4.Add Item" << endl;
    cout << "\t5.Remove Item" << endl;
    cout << "\t6.Display Coins" << endl;
    cout << "\t7.Reset Stock" << endl;
    cout << "\t8.Reset Coins" << endl;
    cout << "\t9.Abort Program" << endl;
    cout << "\t0.Switch to Enhanced Version" << endl;
    cout << "Select your option (0-9):" << endl;
}

void DefaultBehavior::process_option_2(LinkedList& itemList, Coin& coinList) {


    string item_id;
    string input;
    int payment = -1;

    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;
    cout << "Please enter the id of the item you wish to purchase: ";
    getline(cin ,item_id);
    getline(cin ,item_id);
    cout << "item ID : " << item_id << endl;
    // Find the item with the given ID in the linked list
    Node* itemNode = itemList.findItem(item_id);

    if (itemNode == nullptr) {
        cout << "Item not found." << endl;
        return;
    }

    Stock item = itemNode->data;
    int item_cost = item.price.dollars * 100 + item.price.cents;

    coinList.Set_Cost(item_cost);

    cout << "You have selected \"" << item.name << "\". This will cost you $" << item.price.dollars << "." << item.price.cents << "." << endl;
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
                    std::size_t count =0;
                    while (count<input.length()){
                        if (input[count] ==' '){
                            throw std::invalid_argument("invalid argument");
                        }
                        count++;

                    }
                    payment = stoi(input);
                    cout<<"Checking Coin input" << payment << endl;
                    valid = true;
                }
                catch(exception &errc){
                    cout<< "please input a valid amount: " << endl;

                }
            }
        }
        // Check for valid denominations
        if(purchasing){
            if (payment == 1000 || payment == 500 || payment == 200 || payment == 100 || payment == 50 || payment == 20 || payment == 10 || payment == 5) {
                if (coinList.Pay(payment)) {
                    int change = coinList.Difference(coinList.GetProductCost());

                    if (!coinList.CanMakeChange(change)) {
                        coinList.RefundCoins();
                        cout << "Sorry, the machine does not have enough change for this transaction. Your payment has been refunded." << endl;
                        purchasing = false;
                    }
                    else {
                        list<int> returned_change = coinList.Change(change);

                        cout << "Here is your " << item.name << " and your change of $" << change/100.00 << ": ";
                        for (int coin : returned_change) {
                            if (coin < 100) {
                                cout << coin << "c ";  // Print as cents if the coin is less than a dollar
                            } else {
                                cout << "$" << (coin / 100.0) << " ";  // Otherwise, print as dollars
                            }
                        }
                        cout << endl;

                        // Decrease the stock of the purchased item
                        itemNode->data.on_hand--;
                        purchasing = false;
                    }
                }
            } else {
                cout << "Error: $" << payment << " is not a valid denomination of money. Please try again." << endl;
                cout << "You still need to give us $" << (coinList.GetProductCost() / 100) << "." << (coinList.GetProductCost() % 100) << ": ";
            }
        }    
    }

}

Coin DefaultBehavior::initializeCoins(const string& coin_file) {
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
        cout << "Unable to open coin file: " << coin_file << endl;
    }

    return coin;
}