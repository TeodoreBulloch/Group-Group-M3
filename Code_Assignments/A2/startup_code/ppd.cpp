#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>

// using 
using std::endl;
using std::cout;
using std::string;
using std::cin;
using namespace std;

//function protypes
void print_menu();
void process_option_1(const LinkedList& itemList);
void process_option_2(const LinkedList& itemList, Coin& coinList);
void process_option_3(Coin& coinList,const LinkedList& itemList);
void process_option_4(const LinkedList& itemList);
void process_option_6(Coin& coinList);
void process_option_8(Coin& coinList);
LinkedList initializeLinkedList(const string& stock_file);
Coin initializeCoins(const string& coin_file);


/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{

    if (argc != 3) {
        std::cout << "Not correct amount of command line arguments given " << std::endl;
        return EXIT_FAILURE;
    }

    string stock_file = argv[1];
    string coin_file = argv[2];
    LinkedList itemList = initializeLinkedList(stock_file);
    Coin coinList = initializeCoins(coin_file);

    int menu_choice;

    while (true)
    {
        print_menu();
        std::cin >> menu_choice;

        if (menu_choice == 1) {
            process_option_1(itemList);
        }

        else if (menu_choice == 2)
        {
            process_option_2(itemList, coinList);
        }
        else if (menu_choice == 3)
        {
            // Save and exit the program
            process_option_3(coinList,itemList);
            return EXIT_SUCCESS;
        }
        else if (menu_choice == 4)
        {
            // adding a new menu item.
            process_option_4(itemList);
        }
        else if(menu_choice == 6){
            process_option_6(coinList);
        }
        else if(menu_choice == 8){
            process_option_8(coinList);
        }
        else if (menu_choice == 9)
        {
            // Abort the program
            return EXIT_FAILURE;
        }
        else
        {
            std::cout << "Invalid option. Please choose a number between 1 and 9." << std::endl;
            std::cout << "Press enter to continue..." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }

    return EXIT_SUCCESS;
}

void print_menu()
{
    cout << "Main Menu: (fixing available)" << endl;
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
    cout << "Select your option (1-9):" << endl;
}

LinkedList initializeLinkedList(const string& stock_file) {
    std::fstream file1;
    file1.open(stock_file);
    LinkedList itemList;

    if (file1) {
        string myText;

        while (getline(file1, myText)) {
            char separator = '|';
            int i = 0;
            string s;
            int count = 0;
            string id;
            string name;
            string available;
            string price;

            while (myText[i] != '\0')
            {
                if (myText[i] != separator)
                {
                    s += myText[i];
                }
                else
                {
                    if (count == 0)
                    {
                        id = s;
                    }
                    else if (count == 1)
                    {
                        name = s;
                    }
                    else if (count == 3)
                    {
                        price = s;
                    }
                    else if (count == 4)
                    {
                        available = s;
                    }
                    s.clear();
                    count++;
                }
                i++;
            }

            if (count == 4)
            {
                available = s;
            }

            // Create a new Node and Stock objects
            Node* newNode = new Node;
            newNode->data.id = id;
            newNode->data.name = name;
            newNode->data.on_hand = std::stoi(available);

            // Parse price and store dollars and cents separately
            size_t dotPos = price.find('.');
            newNode->data.price.dollars = std::stoi(price.substr(0, dotPos));
            newNode->data.price.cents = std::stoi(price.substr(dotPos + 1));

            // Add the new node to the linked list
            itemList.appendNode(newNode);
        }
    } else {
        cout << "File Name seems to be wrong, please check file name again" << endl;
    }

    file1.close();
    return itemList;
}

Coin initializeCoins(const string& coin_file) {
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

void process_option_1(const LinkedList& itemList) {
    itemList.displayItems();
    std::cin.get();
}

void process_option_2(const LinkedList& itemList, Coin& coinList) {
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
                    payment = stoi(input);
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
                    list<int> returned_change = coinList.Change(change);

                    cout << "Here is your " << item.name << " and your change of $" << change/100.00 << ": ";
                    for (int coin : returned_change) {
                        cout << "$" << (coin / 100.0) << " ";
                    }
                    cout << endl;
                    purchasing = false;
                }
            } else {
                cout << "Error: $" << payment << " is not a valid denomination of money. Please try again." << endl;
                cout << "You still need to give us $" << (coinList.GetProductCost() / 100) << "." << (coinList.GetProductCost() % 100) << ": ";
            }
        }    
    }
}


void process_option_3(Coin& coinList,const LinkedList& itemList)
{
    // Implement the logic for option 3 here
    coinList.SaveCoins();

    itemList.saveStock();

  // Write to the file
   
}

void process_option_4(const LinkedList& itemList)
{
    itemList.addItem();
}

void process_option_6(Coin& coinList)
{
   coinList.DisplayCoins();
}
void process_option_8(Coin& coinList)
{
    coinList.Reset();
}
