#include <iostream>
#include "maze.hpp"

using namespace std;
int main(){
	maze::Maze laberinto(7,5);
	laberinto.print();
	std::cout << laberinto.solve_queue(0,0,7,2);
	return 0;
}