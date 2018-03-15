#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GRID_SIZE 9
#define BOX_LENGTH 3

bool isValid(int** grid, int x, int y){
	int i, j, val = grid[x][y];
	for (i = 0; i < GRID_SIZE; i++){
		if (i != x) {
			if (grid[i][y] == val) return false;
		}	
	}
	
	for (i = 0; i < GRID_SIZE; i++){
		if (i != y) {
			if (grid[x][i] == val) return false;
		}
	}

	i = 3 - (x % BOX_LENGTH);
	j = 3 - (x % BOX_LENGTH);

	return true;
}

void solveSudoku(int** grid){
	int gridIndex, x=0, y=0, box[BOX_LENGTH][BOX_LENGTH];
	/* find first occurence of 0 */
	for (; y < GRID_SIZE; y++){
		for (; x < GRID_SIZE; x++){
			if (grid[x][y] == 0) break;
		}
	}

	if (x < 3){
	       	if (y < 3) gridIndex = 0;
		else if (y < 6)	gridIndex = 3;
		else gridIndex = 6;
	} else if (x < 6){
		if (y < 3) gridIndex = 1;
		else if (y < 6) gridIndex = 4;
		else gridIndex = 7;
	} else {
		if (y < 3) gridIndex = 2;
		else if (y < 6) gridIndex = 5;
		else gridIndex = 8;
	}	
	
}

int** readGrid(FILE *sudokuGrids){
	int **grid, i=0, j=0, swap;
	char temp = '0';
	
	grid = (int**) malloc(GRID_SIZE*sizeof(int*));
	if (!grid) {
		perror("Failed to initialize grid\n");
		exit(EXIT_FAILURE);
	}
	grid[0] = (int *) malloc(GRID_SIZE*GRID_SIZE*sizeof(int));	
	if (!grid[0]){
		perror("Failed to initialize grid\n");
		exit(EXIT_FAILURE);



	for (i = 1; i < GRID_SIZE; i++){
		grid[i] = grid[i-1] + GRID_SIZE;
	}

	i = 0;

	do {
		if (i > GRID_SIZE - 1){
			if (j > GRID_SIZE - 1) break;
			else {
				i=0;
				j++;
			}
		}

		fscanf(sudokuGrids, "%c", &temp);
		swap = temp - '0';

		if (swap >= 0 && swap <= GRID_SIZE) {
			grid[i][j] = swap;
			/* printf("%d ", grid[i][j]); */
			i++;
		}	
		
	} while (!feof(sudokuGrids));

	printf("\n");
	return grid;
}

void freeGrid(int** grid){
	free(grid[0]);
	free(grid);
}


int main(void){
	int** grid, x, y;

	FILE *sudokuGrids;
	if ((sudokuGrids = fopen("problem96_input.txt", "r")) == NULL) {
		perror("problem96_input.txt");
		exit(EXIT_FAILURE);
	}	
	
	grid = readGrid(sudokuGrids);
	for (y=0; y<GRID_SIZE; y++){
	      	for (x=0; x<GRID_SIZE; x++){
	       		printf("%d ", grid[x][y]);
		}
		printf("\n");
	}		

	solveSudoku(grid);

	freeGrid(grid);	
		
	fclose(sudokuGrids);

	return 0;
}
