#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(void) {

    char* outputName = (char*) malloc(sizeof(char) * 14); //output###.txt\0    
    struct dirent **namelist;
    int n = scandir(".", &namelist, NULL, alphasort);

    if(n<0) {
        return 1;
    }

    int number = -1;
    char val[4];
    for(int i = 2; i < n; i++) {// i = 2, to ignore . and ..
    	if(strlen(namelist[i]->d_name) >= 9) {
    		memcpy(outputName, &namelist[i]->d_name, 6);//get the first 6 letters of the string in namelist
    		//outputName[7] = '\0';

    		if (strcmp(outputName, "output") == 0) {// we found an existing output file
    			char tmpv[4]; tmpv[3] = '\0'; 
    			memcpy(tmpv, &namelist[i]->d_name[6],3);
    			
    			if(tmpv[0] < '0' || tmpv[0] > '9') continue;

    			int tempi = atoi(tmpv);
    			if(tempi > number) {

    				if(number != -1 && tempi-number != 1) break;    				
    				
    				number = tempi;
    				strcpy(val, tmpv);
    			}
    		}
    	}
    }

    if(number >= 1000) return -1;

    if(number++ != -1) {

    	sprintf(val, "%d", number);
    	int len = strlen(val);

    	switch(len) {
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

    	strcat(outputName, ".txt\0");
    } else {
    	strcpy(outputName, "output000.txt\0");
    }

    printf("%s%s%s\n", "\033[1m\033[32m", outputName, "\033[0m");

    FILE* outputFile = fopen(outputName, "w");
    fprintf(outputFile, "");
    fclose(outputFile);
}
