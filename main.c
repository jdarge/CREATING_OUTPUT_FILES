#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(void) {

    char* outputName = (char*) malloc(sizeof(char) * 14); //output###.txt\0    
    struct dirent **namelist;
    int n = scandir(".", &namelist, NULL, alphasort);// get a list of files in the CWD and store the file count in 'n'

    if(n<0) {// error getting directory information
        return 1;
    }

    int number = -1;// used to store the highest number, for making the directory name
    char val[4];// used to store the highest number, for making the directory name
    for(int i = 2; i < n; i++) {// i = 2, to ignore . and ..
    	if(strlen(namelist[i]->d_name) >= 9) {// check to see if the file can be output### (for out of bounds assurance)
    		memcpy(outputName, &namelist[i]->d_name, 6);//get the first 6 letters of the string in namelist

    		if (strcmp(outputName, "output") == 0) {// we found an existing output file
    			char tmpv[4]; tmpv[3] = '\0'; 
    			memcpy(tmpv, &namelist[i]->d_name[6],3);// copy the ### number (i.e. >>001<<)
    			
    			if(tmpv[0] < '0' || tmpv[0] > '9') continue;// there is an ouputfile that doesnt follow our format (i.e. output.txt)

    			int tempi = atoi(tmpv);
    			if(tempi > number) {// we found the next highest value (i.e. 001 -> 002)

    				if(number != -1 && tempi-number != 1) break;// we found a gap (i.e. 001 -> 004)    				
    				
    				number = tempi;
    				strcpy(val, tmpv);
    			}
    		}
    	}
    }
    
    number++; // this is the new number we will use

    if(number >= 1000) return -1; // if the new number is too large. 

    if(number) {// check to see if we ever actually found an output###.txt file

    	sprintf(val, "%d", number);// convert the number into string format
    	int len = strlen(val);// see how many leading zero's are required

    	switch(len) {// generate leading zero('s) and add the digit(s)
    		case 1: {
    			outputName[6] = '0';
    			outputName[7] = '0';
    			strcat(outputName, val);
    			break;
    		}
    		case 2: {
    			outputName[6] = '0';
    			strcat(outputName, val);
    			break;
    		} 
    		default: {
    			strcat(outputName, val);
    			break;
    		}
    	}

    	strcat(outputName, ".txt\0");// finalize the documents name
    } else {// there was no output###.txt file found. create the first one.
    	strcpy(outputName, "output000.txt\0");
    }

    printf("%s%s%s\n", "\033[1m\033[32m", outputName, "\033[0m");// color coded print of the new files name.

    FILE* outputFile = fopen(outputName, "w");// create the file
    fprintf(outputFile, "");
    fclose(outputFile);
}// DONE
