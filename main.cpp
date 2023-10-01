#include <iostream>
#include "maze.hpp"

using namespace std;
int main(){
	maze::Maze laberinto(21,21);
	laberinto.print();
	if(!laberinto.solve_queue(0,0,20,10)){
		cout << "No se pudo resolver el laberinto.";
	}
	else{
		cout << "Else";
	}
	return 0;
}