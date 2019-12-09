#include <stdio.h>
#include <stdlib.h>
#include "storage.h"

#define N_BUILDING				10
#define N_FLOOR					10
#define N_ROOM					10

#define STORAGE_FILEPATH 		"storage.txt"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


//get an integer value from keyboard
int getIntegerInput(void)
{
	int input = -1;
	scanf("%d", &input);
	fflush(stdin);
	
	return input;
}



//check whether building/room number is valid or not
int buildingValidityCheck(int nBuilding, int nRoom)
{
	if (nBuilding <= 0 || nBuilding > N_BUILDING)
	{
		return -1;
	}
	
	if (nRoom/100 <= 0 || nRoom/100 > N_FLOOR)
	{
		return -1;
	}
	
	if (nRoom%100 <= 0 || nRoom%100 > N_ROOM)
	{
		return -1;
	}
	
	return 0;
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	return 0;
}
