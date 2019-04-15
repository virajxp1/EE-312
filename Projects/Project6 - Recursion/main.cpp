#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "MazeParams.h"
#include "Recursion.h"


int maze[MATRIX_SIZE][MATRIX_SIZE];
#define WALL (1 << 30)
#define MARK (1 << 29)
#define MASK (((-1) ^ WALL) ^ MARK)
int start_col; // the starting column for the maze;

void printMaze(void) {
	unsigned r, c;
	for (r = 0; r < MATRIX_SIZE; r += 1) {
		printf("%d",r%10);
		for (c = 0; c < MATRIX_SIZE; c += 1) {
			switch (maze[r][c] ) {
			case 0:
				putchar(' ');
				break;
			case 1:	
				putchar('#');
				break;
			case 2: // bread crumb
				putchar('o');
				break;
			default: // error!
				putchar('@');
				break;			
			}
		}
		putchar('\n');
	}
}
 	
void printCodedMaze(void) {
	unsigned r, c;
	for (r = 0; r < MATRIX_SIZE; r += 1) {
		for (c = 0; c < MATRIX_SIZE; c += 1) {
			switch(maze[r][c] & WALL) {
			case WALL: 
				putchar('#');
				break;
			case 0:
				putchar(' ');
				break;
			}
		}
		putchar('\n');
	}
}

enum Directions {
	UP,
	DOWN, 
	LEFT,
	RIGHT
};

void interpretDir(int* prow, int* pcol, int dir) {
	switch (dir) {
		case UP: *prow = *prow - 1; break;
		case DOWN: *prow = *prow + 1; break;
		case LEFT: *pcol = *pcol - 1; break;
		case RIGHT: *pcol = *pcol + 1; break;
	}
}

void clearWall(int row, int col, int dir) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	interpretDir(&r, &c, dir);
	maze[r][c] &= ~WALL;
}

void markCell(int row, int col) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	
	maze[r][c] |= MARK;
}

int isMarked(int row, int col) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	
	return (maze[r][c] & MARK);
}


/*
 * return an integer that uniquely identifies each cell
 */
int cellID(int row, int col) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	return r * MATRIX_SIZE + c;
}

/*
 * reverse the cellID to compute the row and col numbers
 */
void findCell(int cell, int* prow, int* pcol) {
	int r = cell / MATRIX_SIZE;
	int c = cell % MATRIX_SIZE;
	*prow = r / 2;
	*pcol = c / 2;
}
char *randstring(size_t length) {

	static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
	char *randomString = NULL;

	if (length) {
		randomString = (char*)malloc(sizeof(char) * (length +1));

		if (randomString) {
			for (int n = 0;n < length;n++) {
				int key = rand() % (int)(sizeof(charset) -1);
				randomString[n] = charset[key];
			}

			randomString[length] = '\0';
		}
	}

	return randomString;
}
/*
 * store some annotation information in a cell 
 * (the annotation must be an int less than 25 bits (i.e., smaller than 32 million)
 */
void annotateCell(int row, int col, int annotation) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	
	maze[r][c] &= ~MASK;
	maze[r][c] |= annotation;
}

int annotation(int row, int col) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	
	return maze[r][c] & MASK;
}

void clearCellMark(int row, int col) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	
	maze[r][c] &= ~MARK;
}

void clearCell(int row, int col) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	
	maze[r][c] = 0;
}

void makeAllWalls(void) {
	unsigned r, c;
	unsigned row, col;
	for (r = 0; r < MATRIX_SIZE; r += 1) {
		for (c = 0; c < MATRIX_SIZE; c += 1) {
			maze[r][c] = WALL;
		}
	}
	for (row = 0; row < MAZE_SIZE; row += 1) {
		for (col = 0; col < MAZE_SIZE; col += 1) {
			clearCell(row, col);
		}
	}
}

/*
 * this function makes a random maze with exactly one path between
 * any two points in the maze
 *
 * If you're curious about the algorithm, come talk to me.  It's not very
 * complicated (although the code might be confusing)
 */
void makeMaze() {
	int num_visited = 1;
	int first;
	int finish_col;
	makeAllWalls();
	markCell(0, 0);  // mark the first cell as visited
	
	/* add the first cell (row 0, col 0) to the linked list of visited cells */
	first = cellID(0, 0);
	annotateCell(0, 0, 0);
	
	while(num_visited < MAZE_SIZE * MAZE_SIZE) {
		int visit = rand() % num_visited;
		int cell = first; 
		int row, col;
		int d;
		int nrow, ncol;

		findCell(cell, &row, &col);
		while (visit > 0) {
			cell = annotation(row, col);
			findCell(cell, &row, &col);
			visit -= 1;
		}
		d = rand() % 4;
		nrow = row; // row of neighbor cell
		ncol = col; // col of neighbor cell
		interpretDir(&nrow, &ncol, d);
		if (nrow >= 0 && nrow < MAZE_SIZE
			&& ncol >= 0 && ncol < MAZE_SIZE
			&& !isMarked(nrow, ncol)) {
			clearWall(row, col, d);
			num_visited += 1;
			markCell(nrow, ncol);
			annotateCell(nrow, ncol, first);
			first = cellID(nrow, ncol);	
		}
	}
	
	start_col = rand() % MAZE_SIZE;
	start_col = 2 * start_col + 1;
	maze[0][start_col] &= ~WALL;
	finish_col = rand() % MAZE_SIZE;
	maze[MATRIX_SIZE - 1][2 * finish_col + 1] &= ~WALL;
}


/*
 * recode the maze so that all walls are exactly 1 and all 
 * other cells are exactly zero
 */
void recodeMaze(void) {
	int r, c;
	for (r = 0; r < MATRIX_SIZE; r += 1) {
		for (c = 0; c < MATRIX_SIZE; c += 1) {
			maze[r][c] = ((maze[r][c] & WALL) == WALL);
		}
	}
}
	

int main(void) {
	const int magic_number = 13017;

	/* test min */
//	int a[] = { 8, 2, 8, 4, -7, 66, 97, 8, 9, 10 };
//	//printf("the smallest of the first 10 natural numbers is: %d\n", minIt(a, 10));
//	printf("the smallest of the first 10 natural numbers is: %d\n", minRec1(a, 1));
//	printf("the smallest of the first 10 natural numbers is: %d\n", minRec2(a, 1));
//	a[0] = -1;
//	//printf("now the smallest is %d\n", minIt(a, 10));
//	printf("now the smallest is %d\n", minRec1(a, 1));
//	printf("now the smallest is %d\n", minRec2(a, 1));
	
	/* test sqrt */
	for (int i = 0; i < 101; i++){
		double yeet = 1.00;
		printf("%d %g \n", i,  sqrtRec(i*yeet, 0, i*yeet) - sqrt(i*yeet));
	}

	/* test strCompare */

	char* s1; char* s2;

	s1 = "apple"; s2 = "apricot";
	if (strCompare(s1, s2) < 0) { 
		printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
	}
			
	s1 = "Apple"; s2 = "apple";
	if (strCompare(s1, s2) < 0) { 
		printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
	}

	s1 = "baby boy"; s2 = "banana";
	if (strCompare(s1, s2) < 0) { 
		printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
	}

	s1 = "a rather silly string"; s2 = "a rather silly string";
	if (strCompare(s1, s2) == 0) { 
		printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
	}

	s1 = "12345"; s2 = "12345";
	if (strCompare(s1, s2) == 0) { 
		printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
	}

	s1 = "Numbers: 12345"; s2 = "12345";
	if (strCompare(s1, s2) > 0) { 
		printf("\"%s\" is greater than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be greater than \"%s\"\n", s1, s2);
	}

	s1 = "Texas"; s2 = "California";
	if (strCompare(s1, s2) > 0) { 
		printf("\"%s\" is greater than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be greater than \"%s\"\n", s1, s2);
	}




/* test strCompare2 */

	s1 = "apple"; s2 = "Apricot";
	if (strCompare2(s1, s2) < 0) { 
		printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
	}

	s1 = "Batman!!!!!a"; s2 = "bat man";
	if (strCompare2(s1, s2) == 1) {
		printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
	}

	s1 = "OMG, WTF?"; s2 = "oh my goodness, what the heck?";
	if (strCompare2(s1, s2) > 0) { 
		printf("\"%s\" is greater than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be greater than \"%s\"\n", s1, s2);
	}
////
	s1 = "apple"; s2 = "apricot";
	if (strCompare2(s1, s2) < 0) {
		printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
	}

	s1 = "Apple"; s2 = "apple";
	if (strCompare2(s1, s2) == 0) {
		printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
	}

	s1 = "baby boy"; s2 = "banana";
	if (strCompare2(s1, s2) < 0) {
		printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
	}

	s1 = "a rather silly string"; s2 = "arathersillystring!";
	if (strCompare2(s1, s2) == 0) {
		printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
	}

	s1 = "123a"; s2 = "123";
	if (strCompare2(s1, s2) == 1) {
		printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
	}

	s1 = "Numbers: 12345"; s2 = "12345";
	if (strCompare2(s1, s2) > 0) {
		printf("\"%s\" is greater than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be greater than \"%s\"\n", s1, s2);
	}

	s1 = "ZZZ"; s2 = "aaa ";
	if (strCompare2(s1, s2) > 0) {
		printf("\"%s\" is greater than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be greater than \"%s\"\n", s1, s2);
	}


	for(int i = 0;i<100;i++){
		srand(100+i);
		int length1 = rand() % 15 +1;
		int length2 = rand() % 15 +1;
		int j,k;
		char st1[length1];
		char st2[length2];
		for(j =0;j<length1;j++){
			st1[j] =rand() %80 + 30;
		}
		for(k =0;k<length2;k++){
			st2[k] =rand() %80 + 30;
		}
		st1[length1] = 0;
		st2[length2] = 0;

		if(strcmp(st1,st2)>0 && strCompare(st1,st2) != 1) {
			printf("%d failed should be %d\n", i, strcmp(st1,st2));
		}
		else if(strcmp(st1,st2)<0 && strCompare(st1,st2) != -1) {
			printf("%d failed should be %d\n", i, strcmp(st1,st2));
		}
	}

	for(int i = 0;i<5;i++){
		srand(100+i);
		int length1 = rand() % 15 +1;
		int length2 = rand() % 15 +1;
		int j,k;
		char* st1 = randstring(length1);
		char* st2 = randstring(length2);
		printf("returns: %d for 1:%s and 2:%s\n",strCompare2(st1,st2),st1,st2);
	}


	/* test maze */
	for(int i = 0;i<1;i++) {
        srand(magic_number+i);
        makeMaze();
        recodeMaze();
        printf("recursive solution to the maze\n");
        printMaze();
        solveMazeRec(0, start_col);
        printMaze();
        printf("\n\n\n");
    }
	
	/*printf("iterative solution to the maze\n");
	srand(magic_number);
	makeMaze();
	recodeMaze();
	solveMazeIt(0, start_col);
	printMaze(); */

Martian change1;
	for (int i = 1; i < 10; i++){
		change1 = change(i);
		printf("change 1 is: %dd %dn %dp for %d\n", change1.dodeks, change1.nicks, change1.pennies,i);
	}
}
