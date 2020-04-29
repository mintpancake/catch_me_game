FLAGS = -pedantic-errors -std=c++11

welcome.o: welcome.cpp welcome.h
	g++ $(FLAGS) -c $<

game_app.o: game_app.cpp game_app.h welcome.h
	g++ $(FLAGS) -c $<

game_app: welcome.o game_app.o
	g++ $(FLAGS) $^ -o $@

clean:


tar:


.PHONY: clean tar

# g++ -pedantic-errors -std=c++11 welcome.cpp keyboard.cpp menu.cpp main.cpp -o main.exe