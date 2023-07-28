#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
    struct tmpHash* item;
};

// New struct to help organization
struct tmpHash{
    struct RecordType* data;
    struct tmpHash *next;
};

// Compute the hash function
int hash(int x)
{
    return x % 16;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i, tmpID, tmpOrder;
	char tmpName;
    struct HashType *tmp;
    
    
    printf("----------------------------Hash Records----------------------------\n\n\n");
    
	for (i=0;i<hashSz;++i)
	{
	    tmp = pHashArray; // the temp struct array pointer will be shifted to the right index
	    tmp = tmp + i;
	    printf("\tIndex %d:\n", i);
	    if(tmp -> item != NULL){ //checking if there is an item in the index
	        while(tmp -> item != NULL){ // print all the data blocks in the index
	            tmpID = tmp -> item -> data -> id;
	            tmpOrder = tmp -> item -> data -> order;
	            tmpName = tmp -> item -> data -> name;
	            printf("\t\tID: %d\tName: %c\tOrder: %d\t\n", tmpID, tmpName, tmpOrder);
	            tmp -> item = tmp -> item -> next; // traverse to the next data block
	        }
	    }
	    else{
	        printf("\t\t-----------------NULL-----------------\n"); // prints NULL if there in nothing at that index
	    }
	    printf("\n");
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	
	struct HashType *tmphash = NULL;
	struct tmpHash *t = NULL;
	struct HashType *IDs = malloc(sizeof(struct HashType) * 16); //creates a array of structs
	struct RecordType *tmprec = NULL;
	int hashidx;
	
	for(int i = 0; i < 16; i++){
	    IDs[i].item = NULL;// initialize all the item pointers in the array to NULL for future use
	}
	
	for(int i = 0; i < recordSz; i++){
	    tmprec = pRecords;
	    tmprec = tmprec + i // shifts the temp pointer for the pRecords array to the correct index for the iteration
	    hashidx = hash(tmprec -> id);// finds the hash index for a given id in the pRecords data
	    tmphash = IDs;
	    tmphash = tmphash + hashidx;// shifts the tmp pointer for the Hash Array to the hash index just calculated
	    if(tmphash -> item == NULL){// if theres nothing at the index, place the data block there
	        t = malloc(sizeof(struct tmpHash));
	        t -> next = NULL;
	        t -> data = tmprec;
	        tmphash -> item = t;
	    }
	    else{
	        t = malloc(sizeof(struct tmpHash));// if there is an item there, at another one and link them together
	        t -> next = tmphash -> item;
	        t -> data = tmprec;
	        tmphash -> item = t;
	    }
	}
	displayRecordsInHash(IDs, 16);
	
	
	
	
	// Your hash implementation
}