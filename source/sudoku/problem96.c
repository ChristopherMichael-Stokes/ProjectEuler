#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define GRID_SIZE 9
#define BOX_LENGTH 3
#define INPUTS 50

void solveSudoku(int **grid);
int **readGrid(FILE * sudokuGrids);
void freeGrid(int **grid);
void printGrid(int **grid);

int main(void)
{
	int sum = 0, i;

	FILE *sudokuGrids;
	if ((sudokuGrids = fopen("problem96_input.txt", "r")) == NULL) {
		perror("problem96_input.txt");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < INPUTS; i++) {
	//	fseek(sudokuGrids, 0, SEEK_SET);	
		int **grid = readGrid(sudokuGrids);
		//printGrid(grid);
		solveSudoku(grid);
		//printGrid(grid);
		sum += grid[0][0] * 100 + grid[1][0] * 10 + grid[2][0];
		freeGrid(grid);
	}

	printf("sum %d\n",sum);
	fclose(sudokuGrids);
	return 0;
}

void printGrid(int **grid)
{
	int x, y;	
	printf("\n");
	for (y = 0; y < GRID_SIZE; y++) {
		for (x = 0; x < GRID_SIZE; x++) {
			printf("%d ", grid[x][y]);
		}
		printf("\n");
	}


}

bool isValid(int **grid, int x, int y)
{
	int i, j, val = grid[x][y], boundingX[2], boundingY[2];
	if (0 == val || val > 9) {
		return false;
	}

	for (i = 0; i < GRID_SIZE; i++) 
		if (x != i && grid[i][y] == val)
			return false;	
	

	for (i = 0; i < GRID_SIZE; i++) 
		if (y != i && grid[x][i] == val)	
			return false;

	boundingX[0] = x - (x % (BOX_LENGTH));
	boundingX[1] = boundingX[0] + BOX_LENGTH - 1;
	boundingY[0] = y - (y % (BOX_LENGTH));
	boundingY[1] = boundingY[0] + BOX_LENGTH - 1;

	for (i = boundingX[0]; i <= boundingX[1]; i++) { 
		for (j = boundingY[0]; j <= boundingY[1]; j++) {
			if (!(x == i && y == j) && val == grid[i][j]) {
				return false;
			}
		}	
	}	
	

	return true;
}
/*
bool isValid(int **grid, int x, int y)
{
	int i, j, val;
	if (0 == grid[x][y] || grid[x][y] > 9)
		return false;

	for (i = 0; i < GRID_SIZE; i += BOX_LENGTH) {
		for (j = 0; j < GRID_SIZE; j += BOX_LENGTH) {
			val = grid[i][j];
			if (val > 9)
				return false;	
			
		}	
	}
}
*/
struct list {
	struct list_elem *header;
	struct list_elem *footer;
};

struct list_elem {
	int x;
	int y;
	struct list_elem *prev;
	struct list_elem *next;
};

struct list_elem *list_alloc_elem(void);
void list_free_elem(struct list_elem *elem);
void list_init(struct list *l);
typedef struct list_elem *list_iter;
list_iter list_begin(struct list *l);
list_iter list_end(struct list *l);
void list_insert(struct list *l, list_iter iter, int x, int y);
list_iter list_iter_next(list_iter iter);
list_iter list_iter_prev(list_iter iter);
int list_iter_x(list_iter iter);
int list_iter_y(list_iter iter);
void list_insert_front(struct list *l, int x, int y);
void list_insert_back(struct list *l, int x, int y);
void list_destroy(struct list *l);

void solveSudoku(int **grid)
{
	int x, y;
	struct list modifiedIndices;
	list_init(&modifiedIndices);
	list_iter iter;

	/* find first occurence of 0 */

	for (y = 0; y < GRID_SIZE; y++) {
		for (x = 0; x < GRID_SIZE; x++) {
			if (grid[x][y] == 0) {
				list_insert_back(&modifiedIndices, x, y);	
			}
		}
	}


	for (iter = list_begin(&modifiedIndices);
			iter != list_end(&modifiedIndices);
			iter = list_iter_next(iter)) {
	
		x = list_iter_x(iter);
		y = list_iter_y(iter);

		while(!isValid(grid, x, y)) {
			if (grid[x][y] >= 9) {
				grid[x][y] = 0;
				iter = list_iter_prev(iter); 	
				x = list_iter_x(iter);
				y = list_iter_y(iter);
				grid[x][y]++;
			} else {
				grid[x][y]++;
			}	
		}

	}

}

int **readGrid(FILE * sudokuGrids)
{
	int **grid, i = 0, j = 0, swap;
	char temp = '0';

	grid = (int **)calloc(GRID_SIZE, sizeof(int *));
	if (!grid) {
		perror("Failed to initialize grid\n");
		exit(EXIT_FAILURE);
	}

	grid[0] = (int *)calloc(GRID_SIZE, GRID_SIZE * sizeof(int));
	if (!grid[0]) {
		perror("Failed to initialize grid\n");
		exit(EXIT_FAILURE);
	}

	for (i = 1; i < GRID_SIZE; i++) {
		grid[i] = grid[i - 1] + GRID_SIZE;
	}

	while(fscanf(sudokuGrids, "%c", &temp)) {
		if (temp == '\n') {
			break;	
		}	
	}

	i = 0;

	do {
		if (i > GRID_SIZE - 1) {
			if (j > GRID_SIZE - 1) {
				printf("exit early\n");
				break;
			} else {
				i = 0;
				j++;
			}
		}
		

		if (!fscanf(sudokuGrids, "%c", &temp)) {
			perror("Error reading input");
			exit(EXIT_FAILURE);
		}
		swap = temp - '0';

		if (swap >= 0 && swap <= GRID_SIZE) {
			grid[i][j] = swap;
			i++;
		}

		if (GRID_SIZE == i && GRID_SIZE -1 == j) {
			break;
		}
		
	}
	while (!feof(sudokuGrids));

	while(fscanf(sudokuGrids, "%c", &temp)) {
		if (temp == '\n') {
			break;	
		}	
	}


	return grid;
}

void freeGrid(int **grid)
{
	free(grid[0]);
	free(grid);
}

struct list_elem *list_alloc_elem(void)
{
	struct list_elem *elem = malloc(sizeof(struct list_elem));
	if (elem == NULL) {
		perror("list_alloc_elem");
		exit(EXIT_FAILURE);
	}

	return elem;
}

void list_free_elem(struct list_elem *elem)
{
	free(elem);
}

void list_init(struct list *l)
{
	l->header = list_alloc_elem();
	l->footer = list_alloc_elem();
	l->header->prev = NULL;
	l->footer->next = NULL;
	l->header->next = l->footer;
	l->footer->prev = l->header;
}

list_iter list_begin(struct list *l)
{
	return l->header->next;
}

list_iter list_end(struct list * l)
{
	return l->footer;
}

void list_insert(struct list *l, list_iter iter, int x, int y)
{
	struct list_elem *new_elem = list_alloc_elem();
	new_elem->x = x;
	new_elem->y = y;

	new_elem->prev = iter->prev;
	new_elem->next = iter;

	iter->prev->next = new_elem;
	iter->prev = new_elem;
}

list_iter list_iter_next(list_iter iter)
{
	return iter->next;
}

list_iter list_iter_prev(list_iter iter)
{
	return iter->prev;
}

int list_is_internal(list_iter iter)
{
	return iter->prev != NULL && iter->next != NULL;
}

int list_iter_x(list_iter iter)
{
	assert(list_is_internal(iter));
	return iter->x;
}

int list_iter_y(list_iter iter)
{
	assert(list_is_internal(iter));
	return iter->y;
}

void list_insert_front(struct list *l, int x, int y)
{
	list_insert(l, list_begin(l), x, y);
}

void list_insert_back(struct list *l, int x, int y)
{
	list_insert(l, list_end(l), x, y);
}

void list_destroy(struct list *l)
{
	struct list_elem *elem = l->header;
	while (elem != NULL) {
		struct list_elem *next = elem->next;
		list_free_elem(elem);
		elem = next;
	}
}
