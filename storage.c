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
	
	if (deliverySystem[x][y].passwd[PASSWD_LEN+1] == password);			//deliverySystem[x][y]'s password = when input the password (match!)
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

//free the memory of the deliverySystem 
void str_freeSystem(void) {
	
	free(deliverySystem);
	
	return;
	
}


//print the current state of the whole delivery system (which cells are occupied and the destination of the each occupied cells)
void str_printStorageStatus(void) {
	int i, j;
	printf("----------------------------- Delivery Storage System Status (%i occupied out of %i )-----------------------------\n\n", storedCnt, systemSize[0]*systemSize[1]);
	
	printf("\t");
	for (j=0;j<systemSize[1];j++)
	{
		printf(" %i\t\t",j);
	}
	printf("\n-----------------------------------------------------------------------------------------------------------------\n");
	
	for (i=0;i<systemSize[0];i++)
	{
		printf("%i|\t",i);
		for (j=0;j<systemSize[1];j++)
		{
			if (deliverySystem[i][j].cnt > 0)
			{
				printf("%i,%i\t|\t", deliverySystem[i][j].building, deliverySystem[i][j].room);
			}
			else
			{
				printf(" -  \t|\t");
			}
		}
		printf("\n");
	}
	printf("--------------------------------------- Delivery Storage System Status --------------------------------------------\n\n");
}


//check if the input cell (x,y) is valid and whether it is occupied or not
int str_checkStorage(int x, int y) {
	if (x < 0 || x >= systemSize[0])
	{
		return -1;
	}
	
	if (y < 0 || y >= systemSize[1])
	{
		return -1;
	}
	
	return deliverySystem[x][y].cnt;	
}


//put a package (msg) to the cell
//input parameters
//int x, int y : coordinate of the cell to put the package
//int nBuilding, int nRoom : building and room numbers of the destination
//char msg[] : package context (message string)
//char passwd[] : password string (4 characters)
//return : 0 - successfully put the package, -1 - failed to put
int str_pushToStorage(int x, int y, int nBuilding, int nRoom, char msg[MAX_MSG_SIZE+1], char passwd[PASSWD_LEN+1]) {
	
	FILE *fp;
	fp = open("storage.txt¡±, "w");
	fscanf(fp,"%d %d %s %s",x,y,nBuilding,nRoom, msg[MAX_MSG_SIZE+1], passwd[PASSWD_LEN+1]);			//file open and input a storage information
	fclose(f);

	if ((x < 0 || x >= systemSize[0]) && 
		(y < 0 || y >= systemSize[1]) && 
		(buildingValidityCheck(nBuilding, nRoom)==0) && 
		(strlen(msg[MAX_MSG_SIZE+1])<100) &&
		(strlen(passwd[PASSWD_LEN+1])==4))
	{
		return 0;
	}
	else
		return -1;
}


//extract the package context with password checking
//after password checking, then put the msg string on the screen and re-initialize the storage
//int x, int y : coordinate of the cell to extract
//return : 0 - successfully extracted, -1 = failed to extract
int str_extractStorage(int x, int y) {
	
	inputPasswd(x, y);			
	
	if(inputPasswd(x, y)==0)					// deliverySystem[x][y]'s password = when input the password 
	{
		printStorageInside(x, y); 				//print storage's message
	}
	else
	{
		return -1;
	}
	
	return 0;
}

//find my package from the storage
//print all the cells (x,y) which has my package
//int nBuilding, int nRoom : my building/room numbers
//return : number of packages that the storage system has
int str_findStorage(int nBuilding, int nRoom) {
	
	if((nBuilding == deliverySystem[i][j].building)&& (nRoom ==deliverySystem[i][j].room))
	{
		printf("-----------------------> Found a package in (%d, %d)", nBuilding, nRoom);
		return 0;
	}
	else
	{
		return -1;
	}
	
	return cnt;
}

