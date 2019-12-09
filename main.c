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
	
	int cmd;							//command number 1. put a package 2. get my package 3. check the storage status 4. find my package
	int x, y, nBuilding, nRoom;			// storage row, column, building number, room number
	char msg[MAX_MSG_SIZE+1];			//my input message
	char passwd[PASSWD_LEN+1];			//my input password
	
	//1. initialize the delivery system
	if (str_createSystem(STORAGE_FILEPATH) != 0)
	{
		printf("failed to open storage config file! (%s)\n", STORAGE_FILEPATH);
		return -1;
	}
	
	printf("------- Unmanned Delivery Storage System START -------\n");
	
	do
	{
        //2. menu printing
		printf("\n\n");
		printf("----------------------------------------------\n");
		printf("1. put a package\n");
		printf("2. get my package\n");
		printf("3. check the storage status\n");
		printf("4. find my package\n");
		printf("0. exit\n");
		printf("----------------------------------------------\n");
		printf("command : ");
		
        //3. getting user command
		cmd = getIntegerInput();	
	return 0;
}
