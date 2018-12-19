//Or Hadad, 308101591, Beer Sheva

#include <stdlib.h>
#include <stdio.h>
#define length 14
#define width 15

//stack implementation, I wasnt present in the class so I might have implemented it differently
struct node {
	int x;
	int y;
	struct node *next;
}*top = NULL;

//print the stack
void printstack(struct node* top) {
	if (top == NULL)
		printf("Stack is empty\n");
	else {
		int i = 0;
		struct node *ptr = top;
		printf("List of previous locations-\n");
		while (ptr->next != NULL) {
			printf("\nNode number %d\nLocation (%d, %d)", i, ptr->x, ptr->y);
			ptr = ptr->next;
			i++;
		}
	}
}

//push a new node onto the stack (with given values)
//uncomment to follow insertions
struct node* push(struct node* top, int newx, int newy) {
	struct node *newnode;
	newnode = (struct node*)malloc(sizeof(struct node));
	newnode->x = newx;
	newnode->y = newy;
	if (top == NULL) 
		newnode->next = NULL;
	else newnode->next = top;
	top = newnode;
	//printf("(%d, %d) was pushed\n", top->x, top->y);
	return top;
}

//popping a node off of the stack
//uncomment to follow the extractions
struct node* pop(struct node* top) {
	if (top == NULL) {
		printf("Stack is empty\n");
		return top;
	}
	//printf("(%d, %d) was popped\n", top->x, top->y);
	top = top->next;
	return top;
}

//print the maze
void printmaze(int maze[length][width]) {
	printf("\n\n");
	printf("LEGEND:\n4-mouse, 3 - visited more than once (no terrain), 2 - visited once (no terrain), 1-no terrain, 0-terrain\n");
	for (int i = 0; i < length; i++) {
		printf("\n");
		for (int j = 0; j < width; j++) {
			printf("%d", maze[i][j]);
		}
	}
	printf("\n\n");
}

//the movment proccess prioritizes going right, then down, left and up, then backwards
//prints the current state of the mouse's block and remembers it to restore it in the next step
//declares the next step each time
//backtracking works with a stack - pushing the previous steps and popping them if backtracking is performed
//uncomment to see the final stack
void movement(int maze[length][width], struct node *stack) {
	int mem = 2;
	int x = 0;
	int y = 0;
	while (maze[length-1][width-1] != 4) {
		if (maze[x][y + 1] != 0 && maze[x][y + 1] != 2 && maze[x][y + 1] != 3 && y + 1 < 15) {
			printf("Mouse is in (%d, %d) - the color of this block is YELLOW and the mouse is going RIGHT to (%d, %d)\n", x, y, x, y + 1);
			maze[x][y + 1] = 4;
			stack = push(stack, x, y);
			y++;
			maze[stack->x][stack->y] = mem;
		}
		else if (maze[x + 1][y] != 0 && maze[x + 1][y] != 2 && maze[x + 1][y] != 3 && x + 1 < 14) {
			printf("Mouse is in (%d, %d) - the color of this block is YELLOW and the mouse is going DOWN to (%d, %d)\n", x, y, x + 1, y);
			maze[x + 1][y] = 4;
			stack = push(stack, x, y);
			x++;
			maze[stack->x][stack->y] = mem;
		}
		else if (maze[x][y - 1] != 0 && maze[x][y - 1] != 2 && maze[x][y - 1] != 3 && y - 1 > -1) {
			printf("Mouse is in (%d, %d) - the color of this block is YELLOW and the mouse is going LEFT to (%d, %d)\n", x, y, x, y - 1);
			maze[x][y - 1] = 4;
			stack = push(stack, x, y);
			y--;
			maze[stack->x][stack->y] = mem;
		}
		else if (maze[x - 1][y] != 0 && maze[x - 1][y] != 2 && maze[x - 1][y] != 3 && x - 1 > -1) {
			printf("Mouse is in (%d, %d) - the color of this block is YELLOW and the mouse is going UP to (%d, %d)\n", x, y, x - 1, y);
			maze[x - 1][y] = 4;
			stack = push(stack, x, y);
			x--;
			maze[stack->x][stack->y] = mem;
		}
		else {
			printf("Mouse is in (%d, %d) - the color of this block is RED and the mouse is going BACK to (%d, %d)\n", x, y, x + 1, y);
			maze[x][y] = 3;
			x = stack->x;
			y = stack->y;
			maze[stack->x][stack->y] = 4;
			stack = pop(stack);
		}
	}
	//printstack(stack);
}

//initializing stuff and printing the results.
int main() {
	int maze[length][width] = {
		{ 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1 ,1 },
		{ 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 },
		{ 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0 },
		{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
	};
	struct node *stack = NULL;
	movement(maze, stack);
	printmaze(maze);
	system("PAUSE");
}
