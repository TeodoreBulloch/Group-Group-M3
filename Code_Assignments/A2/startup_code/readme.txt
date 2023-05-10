g++ -std=c++11 ~/APT_folder/APT_A2_M12/Group-Group-/Code_Assignments/A2/startup_code/LinkedList.cpp ~/APT_folder/APT_A2_M12/Group-Group-/Code_Assignments/A2/startup_code/ppd.cpp ~/APT_folder/APT_A2_M12/Group-Group-/Code_Assignments/A2/startup_code/Node.cpp ~/APT_folder/APT_A2_M12/Group-Group-/Code_Assignments/A2/startup_code/Coin.cpp -o ppd
./ppd ~/APT_folder/APT_A2_M12/Group-Group-/Code_Assignments/A2/startup_code/stock.dat ~/APT_folder/APT_A2_M12/Group-Group-/Code_Assignments/A2/startup_code/coins.dat

./ppd stock.dat coins.dat < <testname>.input > <testname>.actual_ppd_out
diff -w <testname>.output <testname>.actual_ppd_out
diff -w -y <testname>.expcoins <actual_ppd_save_coins>