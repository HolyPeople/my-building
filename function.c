#include "function.h"
#include "cursor_control.h"

//printf_menu
int show_menu() {

	gotoxy(0, 0);
	printf("0. 종료\n1. 방 만들기 2.방에 입주 3. 방 정보 출력\n");
	printf("4. 층 만들기\n");
	printf("5. 건물 만들기\n");
	return get_only_n2m_number_1(0, 5);
}

//initialization Room and dynamic alloc Person array
void init_room(Building* building_p) {

	int size;
	int i, j, k, l;
	int room, floor;

	if (!(*building_p)) return;
	if (!(**building_p)) return;
	if (***building_p) return;

	floor = _msize(*building_p) / sizeof(Floor);

	for (i = 0; i < floor; i++) {
		printf("[%d층]\n", i + 1);
		room = _msize(*(*building_p + i)) / sizeof(Room);
		for (j = 0; j < room; j++) {
			printf("%d0%d호에는 몇명의 거주자가 있나요? : ", i + 1, j + 1);
			scanf_s("%d", &size);

			if (size <= 0 || size > 2) {
				printf("잘못된 입력입니다. 다시 입력해 주세요\n");
				j--;
				continue;
			}
			*(*(*building_p + i) + j) = (Room)malloc(sizeof(Person) * size);
			for (k = 0; k < size; k++) {
				for (l = 0; l < 10; l++) {
					(*(*(*building_p + i) + j) + k)->name[l] = '\0';
				}
				(*(*(*building_p + i) + j) + k)->age = 0;
				for (l = 0; l < 20; l++) {
					(*(*(*building_p + i) + j) + k)->phone_number[l] = '\0';
				}
			}
		}
	}
}

//asign Person data to Room
void asign_room(Building* building_p) {

	int i, j, k;
	int floor, room, person;

	if (!(*building_p)) return;
	if (!(**building_p)) return;
	if (!(***building_p)) return;
	if ((***building_p)->name[0] != 0) return;

	floor = _msize(*building_p) / sizeof(Floor);

	for (i = 0; i < floor; i++) {
		printf("[%d층]\n", i + 1);
		room = _msize(*(*building_p + i)) / sizeof(Room);
		for (j = 0; j < room; j++) {
			person = _msize(*(*(*building_p + i) + j)) / sizeof(Person);
			printf("%3d호 정보 입력\n", j + 100 * (i + 1) + 1);
			for (k = 0; k < person; k++) {
				printf("%d번 거주자의 이름 : ", k + 1);
				scanf_s("%s", (*(*(*building_p + i) + j) + k)->name, sizeof((*(*(*building_p + i) + j) + k)->name));
				printf("%d번 거주자의 나이 : ", k + 1);
				scanf_s("%d", &(*(*(*building_p + i) + j) + k)->age);
				printf("%d번 거주자의 전화번호 : ", k + 1);
				scanf_s("%s", (*(*(*building_p + i) + j) + k)->phone_number, sizeof((*(*(*building_p + i) + j) + k)->phone_number));
			}

		}
	}

}

//retrun Person array
void delete_room(Room room) {

	if (!room) return;
	free(room);
}

//print room_data
void print_room(Building building) {

	int i, j, k;
	int floor, room, person;

	if (!building) return;
	if (!(*building)) return;
	if (!(**building)) return;
	if ((***building).name[0] == 0) return;

	floor = _msize(building) / sizeof(Floor);
	
	for (i = 0; i < floor; i++) {
		room = _msize(building[i]) / sizeof(Room);
		printf("[%d층]\n", i + 1);
		for (j = 0; j < room; j++) {
			person = _msize(building[i][j]) / sizeof(Person);
			printf("[%3d호]\n", j + 100 * (i + 1) + 1);
			for (k = 0; k < person; k++) {
				printf("%d번 거주자의 이름 : %s\n", i + 1, building[i][j][k].name);
				printf("%d번 거주자의 나이 : %d\n", i + 1, building[i][j][k].age);
				printf("%d번 거주자의 전화번호 : %s\n", i + 1, building[i][j][k].phone_number);
			}

		}
	}

}

//make Room and dynamic alloc Person 2D array
void make_floor(Building* building_p) {
	int size;
	int i, j;
	int floor;

	if (!(*building_p)) return;
	if (**building_p) return;

	floor = _msize(*building_p) / sizeof(Floor);

	for (i = 0; i < floor; i++) {
		printf("%d층에 몇개의 방이 있나요 : ", i + 1);
		scanf_s("%d", &size);

		if (size <= 0 || size > 4) {
			printf("잘못된 입력입니다.\n");
			i--;
			return;
		}

		(*building_p)[i] = (Floor)malloc(sizeof(Room) * size);
		for (j = 0; j < size; j++) {
			(*building_p)[i][j] = NULL;
		}
	}

}

//return floor_memory
void delete_floor(Floor floor) {

	int i;
	int room;

	if (!floor) return;

	room = _msize(floor) / sizeof(Room);

	for (i = 0; i < room; i++) {
		delete_room(floor[i]);
		printf("Delete Room[%d]\n", i + 1);
	}
	free(floor);
}

//initialization Room and dynamic alloc Person 3D array
void init_building(Building * building_p) {

	int size;
	int i;

	if (*building_p) return;

	printf("건물에 몇개의 층이 있나요 : ");
	scanf_s("%d", &size);

	if (size <= 0 || size > 7) {
		printf("잘못된 입력입니다.");
		init_building(building_p);
		return;
	}

	*building_p = (Building)malloc(sizeof(Floor) * size);

	for (i = 0; i < size; i++) {
		(*building_p)[i] = NULL;
	}
	if (*building_p) return;

}

//return building memory
void delete_building(Building building) {

	int i, floor;

	if (!building) return;

	floor = _msize(building) / sizeof(Floor);

	for (i = 0; i < floor; i++) {
		delete_floor(building[i]);
		printf("Delete floor[%d]\n", i + 1);
	}

	free(building);
	printf("Delete building\n");
}

void print_building(Building building) {
	int room, floor;
	int i, j;
	if (!building) return;

	floor = _msize(building) / sizeof(Floor);
	for (i = 0; i < floor; i++) {
		room = 0;
		gotoxy(70, 7 - i);
		printf("[%d 층] ", i+1);
		
		if (building[i]) room = _msize(building[i]) / sizeof(Room);
		for (j = 0; j < room; j++) {
			printf("[%d0%d호] ", i+1, j+1);
		}
	}
	
}

int get_only_n2m_number_1(int n, int m) {
	char ch;

	printf("입력 : ");

	scanf_s(" %c", &ch, sizeof(ch));
	while (getchar() != '\n');

	if ('0' + n <= ch && ch <= '0' + m) {
		return ch - '0';
	}

	printf("잘못된 입력입니다. 다시 입력해 주세요\n");
	printf("pause");

	return get_only_n2m_number_1(n , m);
}
