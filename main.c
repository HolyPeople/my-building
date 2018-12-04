#include <stdio.h>
#include <stdlib.h>

#define Room Person*

typedef struct _person {
	char name[10];
	int age;
	char phone_number[20];
}Person;

int show_menu();
void init_room(Room*); //initialization Room and dynamic alloc Person array
void asign_room(Room*); //asign Person data to Room
void delete_room(Room); //retrun Person array
void print_room(Room); //print room_data

int main(void) {

	Room my_room = NULL;
	int menu = 0;
	
	while (1) {
		menu = show_menu();
		if (!menu) break;
		switch (menu)
		{
		case 1: init_room(&my_room); break;
		case 2: asign_room(&my_room); break;
		case 3: print_room(my_room); break;
		}
		system("pause");
		system("cls");
	}
	
	delete_room(my_room);

	return 0;
}

int show_menu() {

	char ch;

	printf("0. 종료 1. 방 만들기 2.방에 입주 3. 방 정보 출력\n");
	printf("입력 : ");

	scanf_s("%c", &ch, sizeof(ch));
	while (getchar() != '\n');
	if ('0' <= ch && ch <= '3') {
		return ch - '0';
	}
	
	printf("잘못된 입력입니다. 다시 입력해 주세요\n");
	printf("pause");
	system("cls");

	return show_menu();

}

//initialization Room and dynamic alloc Person array
void init_room(Room* room_p) {

	int size;

	if (*room_p) return;

	printf("방에 몇명의 거주자가 있나요? : ");
	scanf_s("%d", &size);

	if (size <= 0 || size > 2) {
		printf("잘못된 입력입니다. 다시 입력해 주세요\n");
		init_room(room_p);
		return;
	}
	*room_p = (Room)malloc(sizeof(Person) * size);
}

//asign Person data to Room
void asign_room(Room* room_p) {

	int i;

	if (!(*room_p)) return;

	for (i = 0; i < _msize(*room_p) / sizeof(Person); i++) {
		printf("%d번 거주자의 이름 : ", i+1);
		scanf_s("%s", room_p[i]->name, sizeof(room_p[i]->name));
		printf("%d번 거주자의 나이 : ", i+1);
		scanf_s("%d", &(room_p[i]->age));
		printf("%d번 거주자의 전화번호 : ", i+1);
		scanf_s("%s", room_p[i]->phone_number, sizeof(room_p[i]->phone_number));
	}
}

//retrun Person array
void delete_room(Room room) {

	if (!room) return;
	free(room);
}

//print room_data
void print_room(Room room) {

	int i;

	if (!room) return;

	for (i = 0; i < _msize(room) / sizeof(Person); i++) {
		printf("%d번 거주자의 이름 : %s\n", i+1,room[i].name);
		printf("%d번 거주자의 나이 : %d\n", i+1,room[i].age);
		printf("%d번 거주자의 전화번호 : %s\n", i+1,room[i].phone_number);
	}
}
