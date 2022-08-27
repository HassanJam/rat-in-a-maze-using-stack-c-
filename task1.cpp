#include<fstream>
#include<string>
#include"Stack.h"
#include <iostream>
using namespace std;

//Global variables
const int N = 4;//rows and columns size
int solution_array[N][N] =
{
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 },
};
int n = N;//for rows
int m = N;//for columns
//destination co-ordinates
int x__destinationcordinate = N - 1;
int y__destinationcordinate = N - 1;
//making a block class to take each index of the 2d array as a block which have its x,y co-orinates and direction in which the mouse will move next;
class  block
{
public:
	int x;
	int y;
	int direction;
};
//main function to solve rat in a maze problem
int rat_in_a_maze(int maze[N][N])
{
	Stackclass<block> stack(20);
	int i = 0;
	int j = 0;
	solution_array[i][j] = 0;
	block temp = { i,j,0 };
	stack.push(temp);
	while (!stack.isempty())
	{
		temp = stack.peek();
		i = temp.x;
		j = temp.y;
		int dir = temp.direction;

		temp.direction++;
		stack.pop();
		stack.push(temp);
		// if we are at our destination
		if (i == y__destinationcordinate && j == x__destinationcordinate)
		{
			return 1;
		}
		//checking in upward direction
		if (dir == 0) 
		{
			if (i - 1 >= 0 && maze[i - 1][j] && solution_array[i - 1][j])
			{
				block temp1 = { i - 1, j, 0 };
				solution_array[i - 1][j] = 0;
				stack.push(temp1);
			}
		}
		//checking in left direction
		else if (dir == 1) {
			if (j - 1 >= 0 && maze[i][j - 1] && solution_array[i][j - 1]) {
				block temp1 = { i, j - 1, 0 };
				solution_array[i][j - 1] = 0;
				stack.push(temp1);
			}
		}
		//checking in down direction
		else if (dir == 2) {
			if (i + 1 < n && maze[i + 1][j] && solution_array[i + 1][j]) {
				block temp1 = { i + 1, j, 0 };
				solution_array[i + 1][j] = 0;
				stack.push(temp1);
			}
		}
		//checking in right direction
		else if (dir == 3) {
			if (j + 1 < m && maze[i][j + 1] && solution_array[i][j + 1]) {
				block temp1 = { i, j + 1, 0 };
				solution_array[i][j + 1] = 0;
				stack.push(temp1);
			}
		}
		//assigning all other indexes as 1(that are not the correct path)
		else {
			solution_array[temp.x][temp.y] = 1;
			stack.pop();
		}
	}
	return 0;
}
//utility function to print the solution
void print(int vis[N][N])
{
	cout << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout <<" " << vis[i][j];
		}
		cout << endl;
	}
}

int main()
{
	//all declearations
	string filename = "input.txt";
	ifstream fin;
	ofstream fout;
	//opening file
	fin.open(filename);
	fout.open("output.txt");
	int array[N][N] = { 0 };
	//reading data from file
	if (fin.is_open())
	{
		cout << "Input-File is succesfully opened" << endl;
		while (!fin.eof())
		{
			for (int i = 0; i< N; i++)
			{
				for (int j = 0; j< N; j++)
				{
					fin >> array[i][j];
				}
			}
		}
		fin.close();
	}
	else 
	{
		cout << "File not found.." << endl;
	}
	//displaying the data that is in the input file
	cout << "The input maze is as under==>" << endl;
	cout << endl;
	for (int a = 0; a < N; a++)
	{
		for (int b = 0; b< N; b++)
		{
			cout << array[a][b] << " ";
		}
		cout << endl;
	}
	cout << "::Important points==>" << endl;
	cout << "The Correct path for the mouse in represented as 0`s in the Solution" << endl;
	if (rat_in_a_maze(array))
	{
		cout << "The solution of the given maze is as under==>" << endl;
		cout << endl;
		print(solution_array);
	}
	//writting data to output file
	if (fout.is_open())
	{
		
		fout << endl;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					fout <<" " << solution_array[i][j];
				}
				fout << endl;
			}
			cout << "Solution is succesfully saved in the output file" << endl;
		fout.close();
	}
	else
	{
		cout << "File not found.." << endl;
	}
	return 0;
}