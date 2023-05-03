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
void process_option_1(const string& stock_file, const string& coin_file);
void process_option_2();
void process_option_3();

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{
    int menu_choice;

    while (true)
    {
        print_menu();
        std::cin >> menu_choice;

        if (menu_choice == 1)
        {
            if (argc != 3)
            {
                std::cout << "Not correct amount of command line arguments given " << std::endl;
            }
            else
            {
                string stock_file = argv[1];
                string coin_file = argv[2];

                process_option_1(stock_file, coin_file); 
            }
        }

        else if (menu_choice == 2)
        {
            // Implement the logic for option 2 here
        }
        else if (menu_choice == 3)
        {
            // Save and exit the program
            return EXIT_SUCCESS;
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

void process_option_1(const string& stock_file, const string& coin_file)
{
    std::fstream file1;
    file1.open(stock_file);

    if (file1)
    {
        const int idWidth = 5;
        const int nameWidth = 40;
        const int availableWidth = 7;
        const int priceWidth = 12;

        cout << "Items Menu" << endl;
        cout << "----------" << endl;
        cout << setw(idWidth) << left << "ID" << " | "
             << setw(nameWidth) << left << "Name" << " | "
             << setw(availableWidth) << left << "Available" << " | "
             << setw(priceWidth) << left << "Price" << endl;
        cout << "-------------------------------------------------------------------" << endl;

        string myText;
        
        while (getline(file1, myText))
        {
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
                        price = "$ " + s;
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

            // Add this line to assign the last value to available
            if (count == 4)
            {
                available = s;
            }

            cout << setw(idWidth) << left << id << " | "
                 << setw(nameWidth) << left << name << " | "
                 << setw(availableWidth) << left << available << " | "
                 << setw(priceWidth) << left << price << endl;
        }
    }
    else
    {
        cout << "File Name/s seems to be wrongs, please check file name again" << endl;
    }

    file1.close();
    std::cin.get();
}

void process_option_2()
{
    // Implement the logic for option 2 here
}

void process_option_3()
{
    // Implement the logic for option 3 here
}