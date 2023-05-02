#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include <string>

// using 
using std::endl;
using std::cout;
using std::string;

//function protypes
void print_menu();




/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{
    /* validate command line arguments */
    // TODOls

    // check if the number of command line arguments is not invalid. 
    if(argc!=3){
        std::cout << "Not correct amount of command line arguments given "<< std::endl;
    }else{
        // tokenize filenames presented in command line arguments
        string stock_file = argv[1];
        string coin_file = argv[2];
        // intialize varibles to open files
        std::fstream file1;
        std::fstream file2;
        file1.open(stock_file);
        file2.open(coin_file);
        //if file opened do this
        if (file1 && file2){
            //string to read file
            string myText;
            // Use a while loop together with the getline() function to read the file line by line
            while (getline (file1, myText)) {
                // Output the text from the file
                // char separator = '|';
                // int i = 0;
                // char arr[5];
                // // Temporary string used to split the string.
                // string s; 
                // while (arr[i] != '\0') {
                //     if (arr[i] != separator) {
                //         // Append the char to the temp string.
                //         s += arr[i]; 
                //     } else {
                //         cout << s << endl;
                //         s.clear();
                //     }
                //     i++;

                // }
                
                // // p = strtok(, " "); 
                // cout << arr[0]<<endl;

            }

            //print_menu();
            

        }//if file didnt open do this
        else{
            cout<< "File Name/s seems to be wrongs, please check file name again"<< endl;
        }
    
        file1.close();
        file2.close();

    }
    return EXIT_SUCCESS;
}


//function to print menu
void print_menu(){
    cout<<"Main Menu:"<< endl;
    cout<<"\t1.Display Items"<< endl;
    cout<<"\t2.Purchase Items"<< endl;
    cout<<"\t3.Save and Exit"<< endl;
    cout<<"Administrator-Only Menu:"<< endl;
    cout<<"\t4.Add Item"<< endl;
    cout<<"\t5.Remove Item"<< endl;
    cout<<"\t6.Display Coins"<< endl;
    cout<<"\t7.Reset Stock"<< endl;
    cout<<"\t8.Reset Coins"<< endl;
    cout<<"\t9.Abort Program"<< endl;
    cout<<"Select your option (1-9):"<< endl;





}