g++ -std=c++14 LinkedList.cpp ppd.cpp Node.cpp Coin.cpp -o ppd
./ppd stock.dat coins.dat

./ppd stock.dat coins.dat < <testname>.input > <testname>.actual_ppd_out
diff -w <testname>.output <testname>.actual_ppd_out
diff -w -y <testname>.expcoins <actual_ppd_save_coins>