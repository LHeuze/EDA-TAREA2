#include "maze.hpp"
#include "queue.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>


namespace maze{

const unsigned char Maze::WALL  = '@';
const unsigned char Maze::EMPTY = '-';
const int Maze::NORTH= 0;
const int Maze::SOUTH= 1;
const int Maze::EAST= 2;
const int Maze::WEST= 3;
Maze::Maze(int h, int w):
		height(h),
		width(w),
		grid(nullptr){
	dir[0] = NORTH;
	dir[1] = SOUTH;
	dir[2] = EAST;
	dir[3] = WEST;
	std::srand(time(0));
	generate_maze(h, w);

}

void Maze::reset_maze(int h, int w){
	delete_maze();
	height = h;
	width= w;
	grid = new int*[height];
	for (int i = 0; i < height; i++){
		grid[i] = new int[width];
		for (int j = 0; j < width; j++){
			grid[i][j] = 1;
		}
	}
}

void Maze::generate_maze(int h, int w){
	reset_maze(h, w);
	visit(0,0);
}

void Maze::delete_maze(){
	if (grid != nullptr){
		for (int i = 0; i < height; i++){
			delete[] grid[i];
		}
		delete[] grid;
	}
}

void Maze::shuffle_dir(){
	for (int i = 0; i < 4; i++){
		int r = std::rand() & 3;
		int aux = dir[r];
		dir[r] = dir[i];
		dir[i] = aux;
	 }
}
bool Maze::inRange(int i, int j){
	return ((i >= 0) && (i< height) && (j >= 0) && (j< width));
}

void Maze::visit(int i, int j){

	int dx  = 0;
	int dy = 0;
	int i_next = 0;
	int j_next = 0;
	grid[i][j] = 0;
	shuffle_dir();
	//std::cout << dir[0] << " " << dir[1] << " " << dir[2] << " "<< dir[3] << std::endl;
	for(int k = 0; k <  4; k++){
		//std::cout << dir[k] << std::endl;
		if (dir[k] == NORTH){
			dy = -1;
			dx = 0;
		}
		else if (dir[k] == SOUTH){
			dy = 1;
			dx = 0;
		}
		else if (dir[k] == EAST){
			dy = 0;
			dx = 1;
		}
		else if (dir[k] == WEST){
			dy = 0;
			dx = -1;
		}
		i_next = i + (dy<<1);
		j_next = j + (dx<<1);
		if (inRange(i_next, j_next) && grid[i_next][j_next] == 1){
			grid[i_next - dy][j_next - dx] = 0;
			visit(i_next, j_next);

		}
	}
}

void Maze::print(){
	char LIMIT = '=';
	std::cout << " Maze ( "<< height << " x " << width << " ) " << std::endl;
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
	for (int i = 0; i < height; i++){
		std::cout << "|";
		for (int j = 0; j < width; j++){
			if (grid[i][j] == 0) {
				std::cout << EMPTY;
			}
			else {
				std::cout << WALL;
			}
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
}

void Maze::printMarked(int** mat){
	char VISITED = 'x';
	char LIMIT = '=';
	std::cout << " Maze ( "<< height << " x " << width << " ) " << std::endl;
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
	for (int i = 0; i < height; i++){
		std::cout << "|";
		for (int j = 0; j < width; j++){
			if (mat[i][j] == 0) {
				std::cout << EMPTY;
		    }
			else if(mat[i][j] == 2){
			std::cout << VISITED;
			} else if(mat[i][j] == 1){
			std::cout << WALL;
			}
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
}


bool Maze::solve_queue(int f1, int c1, int f2, int c2){
	eda::Queue queue;
	int ** marked = new int*[height];
	for (int i = 0; i < height; i++) {
    	marked[i] = new int[width];
    	for (int j = 0; j < width; j++) {
			if(grid[i][j] == 0){
        		marked[i][j] = 0;
			} else{
				marked[i][j] = 1;
			}
    	}
	}	
	if(!inRange(f1,c1) || !inRange(f2,c2)){
		std::cout << "Posición de inicio o termino invalida, esta fuera de alcance."<< std::endl;
		return false;
	}
	if (grid[f1][c1] == 1){
		std::cout << "Posición de inicio invalida, es un muro."<< std::endl;
		return false;
	}
	if (grid[f2][c2] == 1){
		std::cout << "Posición de termino invalida, es un muro." << std::endl;
		return false;
	}
	if(f1 != 0){
		std::cout << "Posicion de inicio invalida, el inicio debe ser en la primera fila"<< std::endl;
		return false;
	}
	
	if(f2 != height-1){
		std::cout << "Posicion de termino invalida, el destino debe ser en la ultima fila"<< std::endl;
		return false;
	}
	
	std::string pos = std::to_string(f1) + "," + std::to_string(c1);
	queue.push(pos);
	int iter = 0;
	while (!queue.isEmpty() && (pos[0]-'0' != f2 || pos[1]-'0' != c2)) {
		pos = queue.top()->getData();
		queue.pop();
		int i = 0;
    	int j = 0;
    	size_t commaPos = pos.find(',');
    	if (commaPos != std::string::npos) {
        	i = std::stoi(pos.substr(0, commaPos));
        	j = std::stoi(pos.substr(commaPos + 1));
    	}
		if(marked[i][j] != 2){
			//int i = int(pos[0]-'0');
			//int j = int(pos[1]-'0');
			int dx;
			int dy;
			shuffle_dir();
			for(int k = 0; k <  4; k++){
				if (dir[k] == NORTH){
					dy = -1;
					dx = 0;
				}
				else if (dir[k] == SOUTH){
					dy = 1;
					dx = 0;
				}
				else if (dir[k] == EAST){
					dy = 0;
					dx = 1;
				}
				else if (dir[k] == WEST){
					dy = 0;
					dx = -1;
				}
				int i_next = i + dy;
				int j_next = j + dx;
				std::cout << iter<<" next pos: "<< i <<" + "<< dy<<" , "<< j << " + "<< dx <<  std::endl;
				marked[i][j] = 2;
				if (inRange(i_next, j_next) && (grid[i_next][j_next] == 0)){
							
					if(i_next == f2 && j_next == c2){
						marked[i_next][j_next] = 2;							
						printMarked(marked);
						for (int i = 0; i < height; i++) {
    						delete[] marked[i];
						}
						delete[] marked;
						std::cout << iter<< std::endl;
						return true;
					}
					
					if(marked[i_next][j_next] != 2){
						queue.push(std::to_string(i_next) + "," + std::to_string(j_next));
					}

				}
			}
		}
		iter++;
	}
	printMarked(marked);
	for (int i = 0; i < height; i++) {
    	delete[] marked[i];
	}
	delete[] marked;
	
	return false;

}
}