#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "behaviours/Behavior.h"
#include "behaviours/DefaultBehavior.h"
#include "behaviours/EnhancedBehavior.h"
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>
#include <stdexcept>

// using 
using std::endl;
using std::cout;
using std::string;
using std::cin;
using namespace std;

//function protypes
void print_menu();
void process_option_0(Behavior*& behavior, bool& useEnhanced);
void process_option_1(const LinkedList& itemList, Behavior* behavior);
void process_option_2(Behavior* behavior, LinkedList& itemList, Coin& coinList);
void process_option_3(Coin& coinList,const LinkedList& itemList, string stockFile, string coinFile);
void process_option_4(LinkedList& itemList);
void process_option_5(LinkedList& itemList);
void process_option_6(Coin& coinList);
void process_option_7(LinkedList& itemList);
void process_option_8(Coin& coinList);
LinkedList initializeLinkedList(const string& stock_file);
Coin initializeCoins(Behavior* behavior, const string& coin_file);
Behavior* initializeBehavior(bool useEnhanced);

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
    bool useEnhanced = false;
    Behavior* behavior = initializeBehavior(useEnhanced);
    LinkedList itemList = initializeLinkedList(stock_file);
    Coin coinList = initializeCoins(behavior, coin_file);

    string menu_choice;

    while (true)
    {
        behavior->print_menu();
        string input;
        std::cin >> menu_choice;

        if (menu_choice == "0") {
            process_option_0(behavior, useEnhanced);
        }
        else if (menu_choice == "1") {
            process_option_1(itemList, behavior);
        }
        else if (menu_choice == "2")
        {
            process_option_2(behavior, itemList, coinList);
        }
        else if (menu_choice == "3")
        {
            // Save and exit the program
            process_option_3(coinList,itemList,stock_file,coin_file);
            return EXIT_SUCCESS;
        }
        else if (menu_choice == "4")
        {
            // adding a new menu item.
            process_option_4(itemList);
        }
        else if (menu_choice == "5")
        {
            // adding a new menu item.
            process_option_5(itemList);
        }
        else if(menu_choice == "6"){
            process_option_6(coinList);
        }
        else if(menu_choice == "7"){
            process_option_7(itemList);
        }
        else if(menu_choice == "8"){
            process_option_8(coinList);
        }
        else if (menu_choice == "9")
        {
            // Abort the program
            return EXIT_FAILURE;
        }
        else if (menu_choice == "help")
        {
            
            std::cout << "In the main Menu please choose a number between 1 and 9." << std::endl;
            std::cout << "For example, you can input 2 to purchase an Item " << std::endl;
            std::cout << "Press enter to go back to the main menu" << std::endl;
            std::cin.get();
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

    delete behavior;
    return EXIT_SUCCESS;
}

void print_menu()
{
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
            string description;
            string available;
            string price;
            LinkedList* item_options = nullptr;

            while (myText[i] != '\0') {
                if (myText[i] != separator) {
                    s += myText[i];
                } else {
                    if (count == 0) {
                        id = s;
                    } else if (count == 1) {
                        name = s;
                    } else if (count == 2) {
                        description = s;
                    } else if (count == 3) {
                        price = s;
                    } else if (count == 4) {
                        available = s;
                    } else {
                        // Create a new LinkedList if it doesn't exist
                        if (item_options == nullptr) {
                            item_options = new LinkedList();
                        }

                        // Add item options to the linked list
                        if (!s.empty()) { // Check if s is not empty
                            std::istringstream ss(s);
                            std::string option;
                            while (std::getline(ss, option, ',')) {
                                Node* optionNode = new Node;
                                optionNode->data.name = option;
                                item_options->appendNode(optionNode);
                            }
                        }
                    }
                    s.clear();
                    count++;
                }
                i++;
            }

            if (count == 4) {
                available = s;
            }

            // Create a new Node and Stock objects
            Node* newNode = new Node;
            newNode->data.id = id;
            newNode->data.name = name;
            newNode->data.description = description;
            newNode->data.item_options = item_options;
        
            bool validNode = true;

            //Handle conversion from string to int
            try {
                newNode->data.on_hand = std::stoi(available);
            } catch (std::invalid_argument& e) {
                std::cerr << "Invalid number of items available: " << available << std::endl;
                validNode = false;
            } catch (std::out_of_range& e) {
                std::cerr << "Number of items available out of range: " << available << std::endl;
                validNode = false;
            }

            // Parse price and store dollars and cents separately
            size_t dotPos = price.find('.');
            if (dotPos == std::string::npos || dotPos == 0 || dotPos == price.size() - 1) {
                std::cerr << "Invalid price format: " << price << ". Expected format: 'dollars.cents'" << std::endl;
                delete newNode; // prevent memory leak
                validNode = false;
            } else if (validNode) {
                try {
                    newNode->data.price.dollars = std::stoi(price.substr(0, dotPos));
                    newNode->data.price.cents = std::stoi(price.substr(dotPos + 1));
                } catch (std::invalid_argument& e) {
                    std::cerr << "Invalid price: " << price << std::endl;
                    delete newNode; // prevent memory leak
                    validNode = false;
                } catch (std::out_of_range& e) {
                    std::cerr << "Price out of range: " << price << std::endl;
                    delete newNode;
                    validNode = false;
                }
            }

            // Add the new node to the linked list only if it is valid
            if (validNode) {
                itemList.appendNode(newNode);
            }
        }
    } else {
        cout << "File Name seems to be wrong, please check file name again" << endl;
    }

    file1.close();
    return itemList;
}

Coin initializeCoins(Behavior* behavior, const string& coin_file) {
    return behavior->initializeCoins(coin_file);
}

void process_option_0(Behavior*& behavior, bool& useEnhanced) {
    delete behavior;
    useEnhanced = !useEnhanced;
    behavior = initializeBehavior(useEnhanced);
}

void process_option_1(const LinkedList& itemList, Behavior* behavior) {
    EnhancedBehavior* enhancedBehavior = dynamic_cast<EnhancedBehavior*>(behavior);
    if (enhancedBehavior != nullptr) {
        itemList.displayItems();
    } else {
        itemList.displayItemsOG();
    }
    std::cin.get();
}


void process_option_2(Behavior* behavior, LinkedList& itemList, Coin& coinList) {
    behavior->process_option_2(itemList, coinList);
}

void process_option_3(Coin& coinList,const LinkedList& itemList, string stockFile, string coinFile)
{
    // Implement the logic for option 3 here
    coinList.SaveCoins(coinFile);

    itemList.saveStock(stockFile);

  // Write to the file
   
}

void process_option_4(LinkedList& itemList)
{
    itemList.addItem();
    std::cin.get();
}

void process_option_5(LinkedList& itemList)
{
    itemList.removeItem();
    std::cin.get();
}

void process_option_6(Coin& coinList)
{
   coinList.DisplayCoins();
   std::cin.get();
}

void process_option_7(LinkedList& itemList) 
{
    itemList.Reset();
    std::cin.get();
}

void process_option_8(Coin& coinList)
{
    coinList.Reset();
    std::cin.get();
}

Behavior* initializeBehavior(bool useEnhanced) {
    if (useEnhanced) {
       return new EnhancedBehavior();
    } else {
        return new DefaultBehavior();
    }
}
