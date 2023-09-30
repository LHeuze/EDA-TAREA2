#include <iostream>
#include "maze.hpp"

using namespace std;
int main(){
	maze::Maze laberinto(10,10);
	laberinto.print();
	std::cout << laberinto.solve_queue(0,0,8,5);
	return 0;
}