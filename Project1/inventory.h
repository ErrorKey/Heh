#include <vector>
 class Inventory
{
public:
	const int i = 10;
	int cell_posx[10];
	int cell_posy[10];
	std::vector <std::vector <int> > cell_pos;
	
	Inventory(int X, int Y) {

		cell_posx[i] = X;
		cell_posy[i] = Y;
		cell_posx[0] = 125;
		cell_posx[2] = 149;
		cell_posx[3] = 172;
		cell_posx[4] = 125;
		cell_posx[5] = 149;
		cell_posx[6] = 172;
		cell_posx[7] = 125;
		cell_posx[8] = 149;
		cell_posx[9] = 172;

		cell_posy[0] = 11;
		cell_posy[2] = 11;
		cell_posy[3] = 11;
		cell_posy[4] = 34;
		cell_posy[5] = 34;
		cell_posy[6] = 34;
		cell_posy[7] = 56;
		cell_posy[8] = 56;
		cell_posy[9] = 56;
	}
};
