#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

const int RES_X = 64;
const int RES_Y = 24;
//const char[RES_X][RES_Y] fb; 

char charmatrix[RES_X][RES_Y];


void horizontalLine(int y)
{
	for (int x = 0; x < RES_X; x++)
	{
			printf("%c", charmatrix[x][y]);
	}
	printf("\n");

}

//looks like shit
void clearScreen()
{
	for (int i = 0; i < RES_Y; i++)
	{
		printf("\n\n\n\n\n");
	}
}

void drawFrame()
{
	//clearScreen();
	for (int i = 0; i < RES_Y; i++)
	{
		horizontalLine(i);
	}

}

void line(int x0, int y0, int x1, int y1, char c)
{
	bool steep = false;
	if (std::abs(x0-x1) < std::abs(y0-y1))
	{
		int temp = 0;
		temp = x0;
		x0 = y0;
		y0= temp;

		temp = x1;
		x1 = y1;
		y1 = temp;
		steep = true;	
	}

	if (x0 > x1)
	{
		int temp = 0;
		temp = x0;
		x0 = x1;
		x1 = temp;
		
		temp = y0;
		y0 = y1;
		y1 = temp;
	}
	
	//store pixels in line to char matrix framebuffer
	for (int x = 0; x<=x1; x++)
	{
		float t = (x-x0)/(float)(x1-x0);
		int y = y0*(1.-t)+y1*t;
		if (steep)
			charmatrix[y][x] = c;
		else
			charmatrix[x][y] = c;
	}
}

void resetCharMatrix()
{
	for (int x = 0; x < RES_X; x++)
	{
		for (int y = 0; y < RES_Y; y++)
		{
			charmatrix[x][y] = ' ';
		}
	}

}
//useless
/*void setPixel(int x, int y, char c)
{
	charmatrix[x][y] = c;
}*/

int main(int argc, char** argv) {
	int x0 = 1, x1 = 63, y0 = 1, y1 = 4;
	while (true){
		resetCharMatrix();
		line(x0 ,y0 % RES_Y, x1, y1 % RES_Y, '#');
		drawFrame();
		y0++;
		y1++;
		usleep(32);
	}
}

