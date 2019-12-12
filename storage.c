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
static int systemSize[2] = {4, 6};  		//row/column of the delivery system
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
	
	int num; 										//n'th password number (for example, password 1234 :  1st password number = 1)
	for(x=0;x<systemSize[0];x++)
	{
		for(y=0;y<systemSize[0];y++)				    	 //set all the member variable as an initial value
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
	
	if (deliverySystem[x][y].passwd[PASSWD_LEN+1] == password)			//deliverySystem[x][y]'s password = when input the password (match!)
	{
		return 0;	
	}
	else 														     	//deliverySystem[x][y]'s password and input the password are different.
	{
		return -1;	
	}
		
}


// ------- API function for main.c file ---------------

//backup the delivery system context to the file system
//char* filepath : filepath and name to write
//return : 0 - backup was successfully done, -1 - failed to backup
int str_backupSystem(char* filepath) {
	
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
	
		
	
	int row, column;							//storage's row (row of ROW 4) and storage's column (column of COLUMN 6)
	int input_r, input_c;						// input_r : input row, input_c: input column
	
	FILE *fp = NULL;							//point file structure & make file null
	fp = fopen(filepath, "r");					//file open : read mode

	if (fp = NULL)
	{
		return -1;							//failed to create the systerm -> return -1;
	}
	
	fscanf(fp,"%d %d %s", &systemSize[0],&systemSize[1], masterPassword);

	//memory allocate about structure and free : double pointer	
	deliverySystem = (storage_t**)malloc(systemSize[0]*sizeof (storage_t*));
	for(row=0;row<systemSize[0];row++)
	{
		deliverySystem[row] = (storage_t*)malloc(systemSize[1]*sizeof(storage_t));
	}
	
	//memory allocate (use of malloc), context
	for(row=0;row<systemSize[0];row++)
	{
		for(column=0; column<systemSize[1]; column++)
		{
			deliverySystem[row][column].context = (char *)malloc(100*sizeof(char));
		}
	}
	
	while(fscanf(fp, "%d %d", &input_r, &input_c) ==2)
	{
		fscanf(fp,"%d %d %s %s",deliverySystem[input_r][input_c].building,deliverySystem[input_r][input_c].room,
								deliverySystem[input_r][input_c].passwd,deliverySystem[input_r][input_c].context);
		printf("%d %d %s %d %d %d %d %s", systemSize[0], systemSize[1], masterPassword, input_r, input_c,
										deliverySystem[input_r][input_c].building,deliverySystem[input_r][input_c].room,
										deliverySystem[input_r][input_c].passwd,deliverySystem[input_r][input_c].context);
	}
	
	
	fclose(fp);
	
	return 0;
	
}


//free the memory of the deliverySystem 
void str_freeSystem(void) {
	
	int row;
	for (row=0;row<systemSize[0];row++)
	free(deliverySystem[row]);
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
	if (x < 0 || x >= systemSize[0])		//it y is inadequate row number(0,1,2,3)
	{
		return -1;
	}
	
	if (y < 0 || y >= systemSize[1])		//if y is inadequate column number(0,1,2,3,4,5)
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
	fp = fopen("storage.txt", "w");
	fscanf(fp,"%d %d %100s %4s",x,y,nBuilding,nRoom, msg, passwd);			//file open and input a storage information
	fclose(fp);
	
	if ((x < 0 || x >= systemSize[0]) && 								// x = storage's row , y = storage's column, nBuilding and nRoom are valid
		(y < 0 || y >= systemSize[1]) && 
		(buildingValidityCheck(nBuilding, nRoom)==0))
	{
		return 0;
	}
	else
	{
		return -1;
	}
}


//extract the package context with password checking
//after password checking, then put the msg string on the screen and re-initialize the storage
//int x, int y : coordinate of the cell to extract
//return : 0 - successfully extracted, -1 = failed to extract
int str_extractStorage(int x, int y) {
	
	inputPasswd(x, y);							// input a password function 
	
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
	
	// input Building number = deliverySystem's building number , input roomnumber =  deliverySystem's room number
	if((nBuilding == deliverySystem[systemSize[0]][systemSize[1]].building)&&(nRoom ==deliverySystem[systemSize[0]][systemSize[1]].room))
	{
		printf("-----------------------> Found a package in (%d, %d)", nBuilding, nRoom);
	}
	else
	{
		return -1;
	}
	return 0;
}

