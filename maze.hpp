namespace maze {
	typedef unsigned char uchar;


	class Maze{
	private:
		int**  grid;
		int width;
		int height;
		int dir[4];
		void shuffle_dir();
		void delete_maze();
		void visit(int i, int j);
	public:
		static const unsigned char WALL;
		static const unsigned char EMPTY;
		static const int NORTH;
		static const int SOUTH;
		static const int EAST;
		static const int WEST;
		Maze(int h, int  w);
		void generate_maze(int h, int w);
		void reset_maze(int h, int w);
		bool inRange(int i, int j);
		void print();
		bool solve_queue(int,int,int,int);
		bool solve_stack(int,int,int,int);
		void printMarked(int**);

	};
}