#include <ncurses.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double posX, posY;
double dirX, dirY;
double planeX, planeY;

double newTime;
double oldTime;
double frameTime;

void drawMiniMap() {
	for(int x=0; x<mapWidth; x++) {
		for(int y=0; y<mapHeight; y++) {
			if(worldMap[x][y]>0) {
				attrset(COLOR_PAIR(worldMap[x][y]));
				mvprintw(y+2,x+2, "@");
			}
		}
	}
	attrset(COLOR_PAIR(5));
	mvprintw(posY+2,posX+2, "P");
}

int main(int argc, char *argv[]) {

	posX = 22; posY = 12;
	dirX = -1; dirY = 0;
	planeX = 0; planeY = 0.66;

	newTime = 0;
	oldTime = 0;
	frameTime = 0;

	WINDOW *pwin = 0;

	initscr();
  	noecho();
	cbreak();
	keypad(stdscr, TRUE);
  	curs_set(FALSE);

  	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);

	//pwin = newwin(LINES, COLS, 0, 0);

  	while(1) {

    		clear();

		for(int x=0; x<COLS; x++) {

			double cameraX = 2 * x / (double)COLS-1;
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;

			int mapX = (int)posX;
			int mapY = (int)posY;

			double sideDistX;
			double sideDistY;

			double deltaDistX = abs(1 / rayDirX);
			double deltaDistY = abs(1 / rayDirY);
			double perpWallDist;

			int stepX;
			int stepY;

			int hit = 0;
			int side;

			if(rayDirX<0) {
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else {
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}

			if(rayDirY<0) {
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else {
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}

			while(hit==0) {
				if(sideDistX<sideDistY) {
					sideDistX+=deltaDistX;
					mapX+=stepX;
					side=0;
				}
				else {
					sideDistY+=deltaDistY;
					mapY+=stepY;
					side=1;
				}
				if(worldMap[mapX][mapY] > 0) hit = 1;
			}

			if(side==0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

			int lineHeight = (int)(LINES / perpWallDist);

			int drawStart = -lineHeight / 2 + LINES / 2;
			if(drawStart<0) drawStart=0;
			int drawEnd = lineHeight / 2 + LINES / 2;
			if(drawEnd >= LINES) drawEnd = LINES - 1;

			switch(worldMap[mapX][mapY]) {
				case 1:
					if(side==1)
						init_color(COLOR_RED, 500, 0, 0);
					else
						init_color(COLOR_RED, 1000, 0, 0);
				break;

				case 2:
					if(side==1)
						init_color(COLOR_GREEN, 0, 500, 0);
					else
						init_color(COLOR_GREEN, 0, 1000, 0);
				break;

				case 3:
					if(side==1)
						init_color(COLOR_BLUE, 0, 0, 500);
					else
						init_color(COLOR_BLUE, 0, 0, 1000);
				break;

				case 4:
					if(side==1)
						init_color(COLOR_YELLOW, 500, 0, 500);
					else
						init_color(COLOR_YELLOW, 1000, 0, 1000);
				break;

				case 5:
					if(side==1)
						init_color(COLOR_WHITE, 500, 500, 500);
					else
						init_color(COLOR_WHITE, 1000, 1000, 1000);
				break;

				default:
				break;
			}

			if(worldMap[mapX][mapY]>0)
				attrset(COLOR_PAIR(worldMap[mapX][mapY]));

      			//give x and y sides different brightness
      			//if (side == 1) {color = color / 2;}

			mvvline(drawStart, x, '#', drawEnd-drawStart);

			attrset(COLOR_PAIR(5));
			oldTime = newTime;
			newTime = clock();
			frameTime = (newTime - oldTime) / 1000.0;
			mvprintw(1, 1, "FPS: %d", (1.0/frameTime));
			drawMiniMap();
			refresh();
		}

		double moveSpeed = frameTime * 5.0;
		double rotSpeed = 90.0; // frameTime * 3.0;

		int c;
		double oldDirX, oldPlaneX;
		if((c=getch())==ERR) {
			continue;
		}
		switch(c) {
			case KEY_UP:
				/*
				if(worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == false) posX += dirX * moveSpeed;
      				if(worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
				*/
				if(worldMap[(int)(posX + dirX)][(int)posY] == false) posX += dirX;
				if(worldMap[(int)posX][(int)(posY + dirY)] == false) posY += dirY;
			break;
			case KEY_DOWN:
				/*
				if(worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == false) posX -= dirX * moveSpeed;
      				if(worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
				*/
				if(worldMap[(int)(posX - dirX)][(int)posY] == false) posX -= dirX;
				if(worldMap[(int)posX][(int)(posY - dirY)] == false) posY -= dirY;
			break;
			case KEY_LEFT:
				oldDirX = dirX;
      				dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      				dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      				oldPlaneX = planeX;
     				planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      				planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
			break;
			case KEY_RIGHT:
				oldDirX = dirX;
      				dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      				dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      				oldPlaneX = planeX;
      				planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      				planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
			break;
			default:
			break;
		}

		//drawMiniMap();
    		//refresh();
  	}

  	endwin();

  	return 0;
}
