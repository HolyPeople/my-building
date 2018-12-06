#include "function.h"

int main(void) {

	Building my_building = NULL;

	int menu = 0;
	
	while (1) {
		menu = show_menu();

		if (!menu) break;
		switch (menu)
		{
		case 1: init_room(&my_building); break;
		case 2: asign_room(&my_building); break;
		case 3: print_room(my_building); break;
		case 4: make_floor(&my_building); break;
		case 5: init_building(&my_building); break;
		}
		system("pause");
		system("cls");
		print_building(my_building);
	}
	
	delete_building(my_building);

	return 0;
}