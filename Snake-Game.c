#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
const int width=20,height=20;
int snakex,snakey,foodx,foody,obstaclex[10],obstacley[10],score,gameover,countdown;
enum eDirection{STOP=0,LEFT,RIGHT,UP,DOWN};
enum eDirection dir;
time_t starttime;
void instructions()
{	
	printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\tSNAKE GAME!");
	printf("\n\n\t\t\t\t\t\t\tMembers:\n\t\t\t\t\t\t\t\t1.SUFYAN\n\t\t\t\t\t\t\t\t2.HAMZA\n\t\t\t\t\t\t\t\t3.SHAYAN");
	getch();
	system("cls");
	printf("\n\n\t\t  ------ Instructions---\n\n\n\nUSE  A   D   W   S keys to move your snake left, right, up, down\n");
	printf("\n\n\nO is the snake, X is hurdle and F is the snake's food\n\n");
	printf("\n\nBeware of the Hurdles revolving around...\n\n");
	printf("\n\n\n\t\tLET'S BEGIN NOW...press any key to continue...");
	getch();
}
void setup() 
{
	int i;
    gameover=0;
    dir=STOP;
    snakex=width/2;
    snakey=height/2;
    srand(time(NULL));
    foodx=rand()%width;
    foody=rand()%height;
    score=0;
    for(i=0;i<10;i++) 
	{
        obstaclex[i]=rand()%width;
        obstacley[i]=rand()%height;
    }
    starttime=time(NULL);
    countdown=60;
}
void draw()
{
	int i,j,k;
    system("cls");
    for(i=0;i<width+2;i++)
        printf("-");
    printf("\n");
    for(i=0;i<height;i++) 
	{
        for(j=0;j<width;j++) 
		{
            if(j==0)
                printf("|");
            if(i==snakey&&j==snakex)
                printf("O");
            else if(i==foody&&j==foodx)
                printf("F");
            else 
			{
                int printed=0;
                for(k=0;k<10;k++) 
				{
                    if(obstaclex[k]==j&&obstacley[k]==i) 
					{
                        printf("X");
                        printed=1;
                    }
                }
                if(!printed)
                    printf(" ");
            }
            if(j==width-1)
                printf("|");
        }
        printf("\n");
    }
    for(i=0;i<width+2;i++)
        printf("-");
    printf("\n");
    printf("Score: %d\n", score);
    printf("Time: %d seconds\n", countdown);
    if(gameover)
        printf("Game over! Your score: %d\nYou hit the wall!\n");
}
void input() 
{
    if(_kbhit()) 
	{
        switch(_getch()) 
		{
        case'a':
            dir=(dir!=RIGHT)?LEFT:dir;
            break;
        case'd':
            dir=(dir!=LEFT)?RIGHT:dir;
            break;
        case'w':
            dir=(dir!=DOWN)?UP:dir;
            break;
        case's':
            dir=(dir!=UP)?DOWN:dir;
            break;
        }
    }
}
void logic() 
{
    switch(dir) 
	{
    case LEFT:
        snakex--;
        break;
    case RIGHT:
        snakex++;
        break;
    case UP:
        snakey--;
        break;
    case DOWN:
        snakey++;
        break;
    default:
        break;
    }
    int i=0;
    if(snakex<0||snakex>=width||snakey<0||snakey>=height) 
	{
        gameover=1;
    }
    for(i;i<10;i++) 
	{
        if(snakex==obstaclex[i]&&snakey==obstacley[i])
            gameover=1;
    }
    if(snakex==foodx&&snakey==foody) 
	{
        score++;
        foodx=rand()%width;
        foody=rand()%height;
        for(i=0;i<10;i++) 
		{
            while(foodx==obstaclex[i]&&foody==obstacley[i]) 
			{
                foodx=rand()%width;
                foody=rand()%height;
            }
        }
    }
    if(countdown<=0) 
	{
        gameover=1;
    } else 
	{
        countdown=60-(int)(time(NULL)-starttime);
    }
}
int main()
{
	instructions();
    setup();
    while(!gameover) 
	{
        draw();
        input();
        logic();
        Sleep(100); 
    }
    return 0;
}
