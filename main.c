
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Room Person*
#define Floor Room*
#define Building Floor*

typedef struct _person {
	char name[10];
	int age;
	char phone_number[20];
}Person;

int show_menu();
void init_room(Building*); //initialize Room and dynamic alloc Person array
void asign_room(Building*); //asign Person data to Room
void delete_room(Room); //retrun Person array
void print_room(Building); //print building_memory
void make_floor(Building*); // make floor and dynamic alloc Person 2D array
void delete_floor(Floor); //return floor_memory
void init_building(Building*); //make building and dynamic alloc Person 3D array
void delete_building(Building); ////return building_memory

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
	}
	
	delete_building(my_building);

	return 0;
}

int show_menu() {

	char ch;

	printf("0. 종료\n1. 방 만들기 2.방에 입주 3. 방 정보 출력\n");
	printf("4. 층 만들기\n");
	printf("5. 건물 만들기\n");
	printf("입력 : ");

	scanf_s(" %c", &ch, sizeof(ch));
	while (getchar() != '\n');

	if ('0' <= ch && ch <= '5') {
		return ch - '0';
	}
	
	printf("잘못된 입력입니다. 다시 입력해 주세요\n");
	printf("pause");
	system("cls");

	return show_menu();

}

//initialization Room and dynamic alloc Person array
void init_room(Building* building_p) {

	int size;
	int i, j, k;
	int room, floor;

	if (!(*building_p)) return;
	if (!(**building_p)) return;

	floor = _msize(*building_p) / sizeof(Floor);
	room = _msize(**building_p) / sizeof(Room);

	for (i = 0; i < floor; i++) {
		printf("[%d층]\n", i+1);

		for (j = 0; j < room; j++) {
			printf("%d0%d호에는 몇명의 거주자가 있나요? : ", i+1 , j + 1);
			scanf_s("%d", &size);

			if (size <= 0 || size > 2) {
				printf("잘못된 입력입니다. 다시 입력해 주세요\n");
				j--;
				continue;
			}
			*(*(*building_p + i) + j) = (Room)malloc(sizeof(Person) * size);
			for (k = 0; k < size; k++) {

				strcpy((*(*(*building_p + i) + j) + k)->name, "");
				(*(*(*building_p + i) + j) + k)->age = 0;
				strcpy((*(*(*building_p + i) + j) + k)->phone_number, "");
			}
		}
	}
}

//asign Person data to Room
void asign_room(Building* building_p){

	int i, j, k;
	int floor, room, person;

	if (!(*building_p)) return;
	if (!(**building_p)) return;

	floor = _msize(*building_p) / sizeof(Floor);
	room = _msize(**building_p) / sizeof(Room);
	person = _msize(***building_p) / sizeof(Person);


	for (i = 0; i < floor; i++) {
		printf("[%d층]\n", i + 1);
		for (j = 0; j < room; j++) {
			printf("%3d호 정보 입력\n", j + 100*(i+1) +1 );
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

	floor = _msize(building) / sizeof(Floor);
	room = _msize(*building) / sizeof(Room);
	person = _msize(**building) / sizeof(Person);

	for (i = 0; i < floor; i++) {
		printf("[%d층]\n", i + 1);
		for (j = 0; j < room; j++) {
			printf("[%3d호]\n", j + 100 * (i + 1) + 1);
			for (k = 0; k < person; k++) {
				printf("%d번 거주자의 이름 : %s\n", i + 1, building[i][j][k].name);
				printf("%d번 거주자의 나이 : %d\n", i + 1, building[i][j][k].age);
				printf("%d번 거주자의 전화번호 : %s\n", i + 1, building[i][j][k].phone_number);
			}

		}
	}

}

// make Room and dynamic alloc Person 2D array
//TODO : 2018-12-05 12:39 make_floor Building으로 변경
void make_floor(Building* building_p) {
	int size;
	int i;
	int floor;
	
	if (!(*building_p)) return;
	if (**building_p) return;

	floor = _msize(*building_p) / sizeof(Floor);

	for (i = 0; i < floor; i++) {
		printf("%d층에 몇개의 방이 있나요 : ", i+1);
		scanf_s("%d", &size);

		if (size <= 0 || size > 4) {
			printf("잘못된 입력입니다.\n");
			i--;
			return;
		}

		(*building_p)[i] = (Floor)malloc(sizeof(Room) * size);
	}
	
}

//return floor_memory
void delete_floor(Floor floor) {

	int i;
	int room;

	if (!floor) return;

	room = _msize(floor) / sizeof(Room);

	for (i = 0; i < room; i++) {
		delete_room(*floor + i);
	}
	free(floor);
}

void init_building(Building * building_p) {

	int size;
	int i;

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

void delete_building(Building building) {

	int i, floor;
	
	if (!building) return;

	floor = _msize(building) / sizeof(Floor);

	for (i = 0; i < floor; i++) {
		delete_floor(*building + i);
	}

	free(building);
}
