#include <iostream>
#include <fstream>
#include "LinkedList.h"


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
        char* stock_file = argv[1];
        char* coin_file = argv[2];
        std::fstream file;
        std::fstream file2;
        file.open(stock_file);
        file2.open(coin_file);
        if (file && file2){
            std::cout<< "it works apparently";
        }
        else{
            std::cout<< "File Name/s seems to be wrongs, please check file name again";
        }
    
        file.close();
        

    }
    return EXIT_SUCCESS;
}
