#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define cols 10
#define rows 10
#define bombs 15
void initial(int board[rows][cols])
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			board[i][j] = 0;
}
void initialshown(char board[rows][cols])
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			board[i][j] = '*';
}
void settingbombs(int board[rows][cols])
{
	srand((unsigned int)time(NULL));
	int r, c;
	for (int i = 0; i < bombs; i++)
	{
		do
		{
			r = rand() % 10;
			c = rand() % 10;
		} while (board[r][c]==-1);
		board[r][c] = -1;
	}
}
void showboard(char board[rows][cols],int board2[rows][cols])
{
	printf("||||||||||||||||||||||||||||||||     1.The \"*\" means it is not swept.\n");
	printf("||||||||||Bombsweeper|||||||||||    2.The number means there are some of bombs around it\n");
	printf("||||||||||||||||||||||||||||||||     3.The \" \" means there is no any mine around it\n");
	printf("R|C  0  1  2  3  4  5  6  7  8  9\n");
	printf("~ ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~\n");
	for (int i = 0; i < rows; i++)
	{
		printf("%d",i);
		printf("||");
		for (int j = 0; j < cols; j++)
			printf("%3c", board[i][j]);
		printf("\n");
	}
}
void afterboard(int board[rows][cols],int row,int col)
{
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if(row+i>=0&&col+j>=0&&row+i<rows&&col+j<cols)
				if (board[row + i][col + j] == -1)
					board[row][col] += 1;
}
void reveal(int visited[rows][cols], char board2[rows][cols], int board[rows][cols], int row, int col)
{
	if (board[row][col] == -1)
		printf("you hit the bomb\n");
	else if (board[row][col] == 0)
		board2[row][col] = ' ';
	else
		board2[row][col] = board[row][col] + '0';
	visited[row][col] = 1;
}
int revealaround(int visited[rows][cols],char board2[rows][cols], int board[rows][cols], int row, int col)
{	
	if (board[row][col] == -1)
	{
		reveal(visited, board2, board, row, col);
		return 1;
	}
	else if (board[row][col] == 0)
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
			{
				if (row + i >= 0 && col + j >= 0 && row + i < rows && col + j < cols && board[row + i][col + j] == 0 && visited[row + i][col + j] == 0)
				{
					reveal(visited, board2, board, row + i, col + j);
					revealaround(visited, board2, board, row + i, col + j);
				}
				else if (row + i >= 0 && col + j >= 0 && row + i < rows && col + j < cols && board[row + i][col + j]>0)
					reveal(visited, board2, board, row + i, col + j);
			}
	else
		reveal(visited, board2, board, row, col);
}
int checkwin(int visited[rows][cols])
{
	int number = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (visited[i][j] == 0)
				number++;
	return number;
}
int main()
{
	int board[rows][cols],visited[rows][cols];
	char shownboard[rows][cols];
	initial(board);
	initial(visited);
	initialshown(shownboard);
	settingbombs(board);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			if(board[i][j]!=-1)
				afterboard(board, i, j);
		}
	while (1)
	{
		int row, col;
		showboard(shownboard, board);
		printf("input the row:");
		scanf("%d", &row);
		printf("input the col:");
		scanf("%d", &col);
		if (revealaround(visited, shownboard, board, row, col) == 1)
		{
			printf("game over!");
			break;
		}
		if (checkwin(visited) == bombs)
		{
			printf("You win!!");
			break;
		}
		printf("\033[2J\033[H");
	}
	return 0;
}