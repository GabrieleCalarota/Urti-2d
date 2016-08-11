Collision: Main.o Particella.o Spazio.o Mylibrary.o
	g++ -o Collision Main.o Particella.o Spazio.o Mylibrary.o
Main.o: Main.cpp
	g++ -c Main.cpp
Particella.o: Particella.cpp Particella.hpp
	g++ -c Particella.cpp
Spazio.o: Spazio.cpp Spazio.hpp
	g++ -c Spazio.cpp
Mylibrary.o: Mylibrary.cpp Mylibrary.hpp
	g++ -c Mylibrary.cpp
clean:
	rm *.o *.exe