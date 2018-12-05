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