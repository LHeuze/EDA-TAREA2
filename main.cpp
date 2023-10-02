#include <iostream>
#include "maze.hpp"

using namespace std;
int main(){
	maze::Maze laberinto(21,21);
	laberinto.print();
	cout << "Solucion con cola: "<< endl;
	laberinto.solve_queue(0,0,20,10);
	cout << "Solucion con pila: "<< endl;
	laberinto.solve_stack(0,0,20,10);
	return 0;
}