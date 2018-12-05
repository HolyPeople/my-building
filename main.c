
#include <stdio.h>
#include <stdlib.h>

#define Room Person*
#define Floor Room*

typedef struct _person {
	char name[10];
	int age;
	char phone_number[20];
}Person;

int show_menu();
void init_room(Floor*); //initialization Room and dynamic alloc Person array
void asign_room(Floor*); //asign Person data to Room
void delete_room(Room); //retrun Person array
void print_room(Floor); //print room_memory
void init_floor(Floor*); // initialization Room and dynamic alloc Person 2D array
void delete_floor(Floor); //return floor_memory

int main(void) {

	Floor my_floor = NULL;
	int menu = 0;
	
	while (1) {
		menu = show_menu();

		if (!menu) break;
		switch (menu)
		{
		case 1: init_room(&my_floor); break;
		case 2: asign_room(&my_floor); break;
		case 3: print_room(my_floor); break;
		case 4: init_floor(&my_floor); break;
		}
		system("pause");
		system("cls");
	}
	
	delete_floor(my_floor);

	return 0;
}

int show_menu() {

	char ch;

	printf("0. ����\n1. �� ����� 2.�濡 ���� 3. �� ���� ���\n");
	printf("4. �� �����\n");
	printf("�Է� : ");

	scanf_s(" %c", &ch, sizeof(ch));
	while (getchar() != '\n');

	if ('0' <= ch && ch <= '4') {
		return ch - '0';
	}
	
	printf("�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���\n");
	printf("pause");
	system("cls");

	return show_menu();

}

//initialization Room and dynamic alloc Person array
void init_room(Floor* floor_p) {

	int size;
	int i;
	int room = _msize(*floor_p) / sizeof(Room);

	if (!(*floor_p)) return;

	for (i = 0; i < room; i++) {
		printf("10%dȣ���� ����� �����ڰ� �ֳ���? : " , i+1);
		scanf_s("%d", &size);

		if (size <= 0 || size > 2) {
			printf("�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���\n");
			i--;
			continue;
		}
		*(*floor_p + i) = (Room)malloc(sizeof(Person) * size);
	}

	
	
}

//asign Person data to Room
void asign_room(Floor* floor_p) {

	int i,j;
	int room, person;

	if (!(*floor_p)) return;


	room = _msize(*floor_p) / sizeof(Room);
	person = _msize((*floor_p)[0]) / sizeof(Person);

	for (i = 0; i < room; i++) {
		printf("%3dȣ ���� �Է�\n", i + 101);
		for (j = 0; j < person; j++) {
			printf("%d�� �������� �̸� : ", j+ 1);
			scanf_s("%s", floor_p[i][j]->name, sizeof(floor_p[i][j]->name));
			printf("%d�� �������� ���� : ", j + 1);
			scanf_s("%d", &(floor_p[i][j]->age));
			printf("%d�� �������� ��ȭ��ȣ : ", j + 1);
			scanf_s("%s", floor_p[i][j]->phone_number, sizeof(floor_p[i][j]->phone_number));
		}
		
	}
}

//retrun Person array
void delete_room(Room room) {

	if (!room) return;
	free(room);
}

//print room_data
void print_room(Floor floor) {

	int i,j;
	int room, person;

	if (!floor) return;

	room = _msize(floor) / sizeof(Room);
	person = _msize(floor[0]) / sizeof(Person);

	for (i = 0; i < room; i++) {
		printf("[10%d]ȣ\n", i + 1);
		for (j = 0; j < person; j++) {
			printf("%d�� �������� �̸� : %s\n", i + 1, floor[i][j].name);
			printf("%d�� �������� ���� : %d\n", i + 1, floor[i][j].age);
			printf("%d�� �������� ��ȭ��ȣ : %s\n", i + 1, floor[i][j].phone_number);
		}
	}
}

// initialization Room and dynamic alloc Person 2D array
void init_floor(Floor* floor_p) {
	int size;

	if (*floor_p) return;
	
	printf("���� ��� ���� �ֳ��� : ");
	scanf_s("%d", &size);

	if (size <= 0 || size > 4) {
		printf("�߸��� �Է��Դϴ�.");
		init_floor(floor_p);
		return;
	}

	*floor_p = (Floor)malloc(sizeof(Room) * size);
}

//return floor_memory
void delete_floor(Floor floor) {

	int i;
	int room;

	if (!floor) return;

	room = _msize(floor) / sizeof(Room);

	for (i = 0; i < room; i++) {
		delete_room(floor[i]);
	}
	free(floor);
}