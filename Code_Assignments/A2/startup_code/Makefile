.default: all

all: ppd

clean:
	rm -rf ppd *.o *.dSYM behaviours/*.o

ppd: Coin.o Node.o LinkedList.o behaviours/DefaultBehavior.o behaviours/EnhancedBehavior.o ppd.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^

behaviours/%.o: behaviours/%.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^ -o $@
