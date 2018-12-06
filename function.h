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

extern int show_menu();
extern void init_room(Building*); //initialize Room and dynamic alloc Person array
extern void asign_room(Building*); //asign Person data to Room
extern void delete_room(Room); //retrun Person array
extern void print_room(Building); //print building_memory
extern void make_floor(Building*); // make floor and dynamic alloc Person 2D array
extern void delete_floor(Floor); //return floor_memory
extern void init_building(Building*); //make building and dynamic alloc Person 3D array
extern void delete_building(Building); ////return building_memory
extern void remodeling_building(Building*);
void print_building(Building);
int get_only_n2m_number_1(int, int);