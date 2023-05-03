#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include <string>
#include <cmath>

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
            // intialize linked list
            LinkedList linkedList;
           
            // Use a while loop together with the getline() function to read the file line by line
            while (getline (file1, myText)) {
                // Output the text from the file
                char separator = '|';
                int i = 0;
                // Temporary string used to split the string.
                string s; 
                // count varible to check which type of item it is
                int count = 0;
                //Varibles to add into node data:                
                //the unique id for this item
                std::string id;
                //the name of this item
                std::string name;
                //the description of this item   
                std::string description;
                //the price of this item
                //Price price;
                // how many of this item do we have on hand? 
                //unsigned on_hand;    
                // fill nodes with data 
                while (myText[i] != '\0') {
                    //intialize node data 
                    string id;
                    
                    if (myText[i] != separator ) {
                        // Append the char to the temp string.
                        s += myText[i]; 

                    } 
                    else{
                        //intialize node data
                        if (count ==0){ //intialize item id
                            cout << "ItemId : ";
                            id = s;
                            
                        }
                        else if (count ==1){ // itialize ItemName
                            cout << "ItemName : ";
                            // curr_node->data->name = s;
                            name = s;
                        }
                        else if (count ==2){// itialize Item Desc
                            cout << "ItemDesc : ";
                            // curr_node->data->description = s;
                            description = s;

                        }
                         else if (count ==3){// itialize Item Price
                            cout << "Price : ";
                           
                        }
                         else if (count ==4){//intialize number of items
                            cout << "NumberOnHand  : ";

                        }
                        // cout <<"count number: " << count << endl;
                        cout << s << endl;
                        s.clear();
                        count ++;
                        
                    }
                    i++;
                    
                }
                if (count ==4){
                    cout << "NumberOnHand  : ";
                    cout << s << endl;
                    //on_hand = stoi(s);
                }
                 // intiazlize head node
                // Node node(string id, string name, string descrption, Price price,  unsigned on_hand);
                // Node* curr_node= &node;
                // linkedList.appendNode(&curr_node);
                // p = strtok(, " "); 
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