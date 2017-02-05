Collision: Main.o Particella.o Spazio.o MyLibrary.o
	g++ -o Collision Main.o Particella.o Spazio.o MyLibrary.o 
Main.o: Main.cpp
	g++ -c Main.cpp
Particella.o: Particella.cpp Particella.hpp
	g++ -c Particella.cpp
Spazio.o: Spazio.cpp Spazio.hpp
	g++ -c Spazio.cpp
MyLibrary.o: MyLibrary.cpp MyLibrary.hpp
	g++ -c MyLibrary.cpp
clean:
	rm *.o *.exe
