#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"



// definition of storage cell structure ----------------------------------------------
typedef struct {
	int building; 	 						//building number of the destination
	int room;								//room number of the destination
	int cnt;								//number of packages in the cell
	char passwd[PASSWD_LEN+1];				//password setting (4 characters)
	
	char *context; 							//package context (message string)
} storage_t;

static storage_t** deliverySystem; 			//deliverySystem (building, room, cnt, password, context)
static int storedCnt = 0;					//number of cells occupied
static int systemSize[2] = {0, 0};  		//row/column of the delivery system
static char masterPassword[PASSWD_LEN+1];	//master password




// ------- inner functions ---------------

//print the inside context of a specific cell
//int x, int y : cell to print the context

static void printStorageInside(int x, int y) {
	printf("\n------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n");
	if (deliverySystem[x][y].cnt > 0)
		printf("<<<<<<<<<<<<<<<<<<<<<<<< : %s >>>>>>>>>>>>>>>>>>>>>>>>>>>>\n", deliverySystem[x][y].context);
	else
		printf("<<<<<<<<<<<<<<<<<<<<<<<< empty >>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		
	printf("------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n\n");
}

//initialize the storage
//and allocate memory to the context pointer
//int x, int y : cell coordinate to be initialized

static void initStorage(int x, int y) {
	
	int num; 	//n'th password number (for example, password 1234 :  1st password number = 1)
	for(x=0;x<ROW;x++)
	{
		for(y=0;y<COLUMN;y++)					 //set all the member variable as an initial value
		{	
			deliverySystem[x][y].building = 0;
			deliverySystem[x][y].room = 0;
			deliverySystem[x][y].cnt = 0;
			
			for (num=0; num<PASSWD_LEN; num++)
			{
				deliverySystem[x][y].passwd[num] = "";
			}
			deliverySystem[x][y].context = "";	
			
		}
	
	}
	return 0;
}

//get password input and check if it is correct for the cell (x,y)
//int x, int y : cell for password check
//return : 0 - password is matching, -1 - password is not matching
static int inputPasswd(int x, int y) {
	
	int password;														// input
	printf("- input password for (%d, %d) storage : ", x,y);			// input password for (x, y) storage , x and y = row and column of storage
	password = getIntegerInput();										// input x and y 
	
	if (deliverySystem[x][y].passwd[PASSWD_LEN+1] == password);			//deliverySystem[x][y]'s password = when input the password
	{
		return 0;
		
	}
	else																//deliverySystem[x][y]'s password and input the password are different.
	{	
		return -1;	
	}
		
}


// ------- API function for main.c file ---------------

//backup the delivery system context to the file system
//char* filepath : filepath and name to write
//return : 0 - backup was successfully done, -1 - failed to backup
int str_backupSystem(char* filepath) {
	
	int i;
	FILE *fp;					//point file structure
	fp= fopen(filepath,"r");	//file open : read mode

	if (fp = NULL)	
	{
		return -1;
	}
	
	fclose(fp);				//file close
	
	return 0;
	
}

//create delivery system on the double pointer deliverySystem
//char* filepath : filepath and name to read config parameters (row, column, master password, past contexts of the delivery system
//return : 0 - successfully created, -1 - failed to create the system
int str_createSystem(char* filepath) {	
	
	int row;									//storage's row (row of ROW 4)
	FILE *filepath = NULL;
	filepath = fopen("storage.txt", "r");
	
	//memory allocate about structure : doubler pointer
	
	struct storage_t** deliverySystem; 
	
	deliverySystem = (struct storage_t**)malloc(ROW*sizeof (struct storage_t*));
	for(row=0;row<ROW;row++)
	{
		deliverySystem[row] = (struct storage_t*)malloc(COLUMN*sizeof(struct storage_t));
	}
	
	for (row=0;row<ROW;row++)
	free(deliverySystem[row]);
	free(deliverySystem);
	
	if (fp = NULL)
	{
		return -1;
	}
	
	fclose(fp);
	
	return 0;
	
}
