#include <stdio.h>

#include <math.h>

#include <string.h>

#include <ctype.h>

#include <conio.h>

#include <windows.h>

struct Node{
	
	int i;
	
	int j;
	
	float F;
	
	int G;
	
	struct Node *parent;
	
	struct Node *stack;
};

typedef struct Node node;

typedef node * pnode;

pnode openlist=NULL, closelist=NULL, *X, first;
			   
int access[1000][2], counter,final[2] ,start[2], Count=0, a, b;

void check_map();
int check_is(int i, int j);
int is_in(pnode NODE, int i, int j);
void insert(pnode*parent ,pnode *top, int i, int j);
void Remove(pnode *NODE, pnode *head);

void gotoxy( int x, int y) 
{ 
COORD coord; 
coord.X= x; 
coord.Y= y; 
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
SetConsoleCursorPosition( handle, coord); 
}

void Display();
void Move();

char map[50][50], *MOVE, move, pacman=175, food=241,trash=220, place=176;

int x, y,prex, prey, h, v, flag, FLAG, point_place[10000][2], count, END, total, flagp=0;

FILE *ptf;

void Map()

{
	
	ptf=fopen("testcase01.txt", "r");
	
	if(ptf==NULL)
	
	{
		
		printf("NO map exist!");
	}
	
	else
	
	{

		
		for( h=0; !feof(ptf); h++)
		
		{
			
			fscanf(ptf,"%s",map[h]);
			
		}
		
		v=strlen(map[0]);		
		
		for(int i=0; i<h; i++)
		
		{
			
			for(int j=0; j<v; j++)
			
			{

				if(map[i][j]!='#')
				
				{
					
				access[counter][0]=i;
				
				access[counter][1]=j;
				
				counter++;
				
				}				
				
				if(map[i][j]=='*')
				
				{
					
					point_place[count][0]=i;
					
					point_place[count][1]=j;
					
				    count++;
				    
				    map[i][j]=food;
				
				}
				
				if(map[i][j]=='1')
				
				{
					
					map[i][j]=place;
				}				
				
				if(map[i][j]=='#')
				
				{
					
					map[i][j]=trash;
				}
			
			}
			
			
		}
		
		system("color 64");
		
		for(int i=0; i<h; i++)
		
		{
			
			gotoxy(54,i+10);
			
			puts(map[i]);
		}
		
	}
}

void key()

{
	
	while(END==0)
	
	{
	
	move=getch();
	
	switch(move)
	
	{
	
	case 75:
	
	{
		
		move='a';
		
		break;
	}

	case 72:
	
	{
		
		move='w';
		
		break;
	}
	
	case 77:
	
	{
		
		move='d';
		
		break;
	}
	
	case 80:
	
	{
		
		move='s';
	}
	
}
	
	Move();
	
    }
}

void Move()

{
	
	move=tolower(move);
	
	prex=x;
	
	prey=y;
	
	switch(move)
	
	{
		
		case 'w':
			
			{
				
				y--;
				
				
				if(y<0||(map[y][x]==trash))
				
				{
					
					if(map[y][x]==trash)
					
					{
						
						FLAG=1;
						
						MOVE="up";
						
						gotoxy(1,10);
						
						printf("pacman cant go %s there is an abstract", MOVE);
						
					}
					
					y++;
					
					printf("\a");
				}
				
				
				break;
			}
			
		case 's':
			
			{
				
				y++;
				
				
	            if(y>=h||(map[y][x]==trash))
	            
	            {
	            	
	            	if(map[y][x]==trash)
					
					{
						
						FLAG=1;
						
						MOVE="down";
						
						gotoxy(1,10);
						
                        printf("pacman cant go %s there is an abstract", MOVE);
					}
					
	            	
	            	y--;
	            	
	            	printf("\a");
	            	
	            }
				
				
				break;
			}
			
		case 'a':
			
			{
				
				if(flagp==0)
				{
				
				pacman--;
				
				flagp++;
				
			    }
			    
				x--;
				
				if(x<0||(map[y][x]==trash))
				
				{
					if(map[y][x]==trash)
					
					{
						
						FLAG=1;
						
						MOVE="left";
						
						gotoxy(1,10);
						
					    printf("pacman cant go %s there is an abstract", MOVE);
					}
					
					x++;
					
					printf("\a");
					
					
				}
				
				break;
			}
			
		case 'd':
			
			{
				
				if(flagp)
				{
				
				pacman++;
	
				flagp--;
				
				}
				x++;
				
				if(x>=v||(map[y][x]==trash))
				
				{
					
					if(map[y][x]==trash)
					
					{
						
						FLAG=1;
						
						MOVE="right";
						
						gotoxy(1,10);
						
                        printf("pacman cant go %s there is an abstract", MOVE);						
					}
					
					
					x--;
					
					printf("\a");
				}
				
				break;
				
			}
			
	}
	
	if(map[y][x]==food)
	
	{
		
		flag=1;
		
		map[y][x]=place;
	}

	
	Display();
	
    
}

void Display()

{
    
    gotoxy(prex+54,prey+10);
    
    printf("%c", place);
	
    gotoxy(x+54,y+10);
	
	printf("%c", pacman);
	
	if(flag)
	
	{
		Beep(1000,100);
						
		total++;
		
		flag=0;
	}
	
	gotoxy(1,8);
	
	printf("point:%d", total);
	
	if(total==count)
	
	{
		
		gotoxy(1,10);
		
		printf("packman finished eating                          ");
		
		for(int i=0; i<1000; i++)
		
		{
			
			Beep(800,400);
			
			system("color 01");
			
			Beep(8000,200);
			
			system("color 12");
			
			Beep(2000,200);
			
			system("color 23");
			
			Beep(8000,200);
			
			system("color 34");
			
			Beep(400,500);
			
			system("color 45");
			
			Beep(8000,200);
			
			system("color 56");
			
			Beep(800,400);
			
			system("color 67");
			
			Beep(8000,200);
			
			system("color 78");
			
			Beep(3000,200);
			
			system("color 89");
			
			Beep(8000,000);
			
			system("color 9A");
			
			Beep(400,500);
			
			system("color AB");
			
			Beep(8000,200);
			
			system("color BC");
			
			Beep(800,400);
			
			system("color CD");
			
			Beep(8000,200);
			
			system("color DE");
			
			Beep(1000,200);
			
			system("color EF");
			
			Beep(8000,200);
			
			system("color 01");
			
			Beep(400,500);
			
			system("color 10");
			
			Beep(8000,200);
			
			system("color 02");
			
			Beep(800,400);
			
			system("color 20");
			
			Beep(8000,200);
			
			
		}
		
		END=1;
		
}
	
		
}

int check_is(int i, int j)

{
	
	for(int I=0; I<counter; I++)
	
	{
		
		if(i==access[I][0]&&j==access[I][1])
		
		{
			
			return 1;
		}
		
	}
	
	return 0;
}

int is_in(pnode NODE, int i, int j)

{
	pnode x;
	
	for( x=NODE; x!=NULL; x=x->stack)
	
	{
		
		if(x->i==i&&x->j==j)
		
		{
			
			return 1;
		}
	}
	
	return 0;
}

void insert(pnode *parent,pnode *top, int i, int j)

{
	
	pnode newp=(pnode)malloc(sizeof(node));	
	
	newp->i=i;
	
	newp->j=j;
	
	if(*top==NULL)
	
	{
		newp->G=0;
		
	}
	
	else
	
	{
	    newp->G=(*parent)->G+1;
	    
	}
	
	newp->F=sqrt((i-final[0])*(i-final[0])+(j-final[1])*(j-final[1]))+newp->G;
	
	if(parent==NULL)
	
	{
		
		newp->parent=NULL;
	}
	
	else
	
	{
	
	newp->parent=*parent;
	
    }
	
	newp->stack=*top;
	
	*top=newp;

}

void Remove(pnode *NODE, pnode *head)

{
	
	pnode temp=*NODE;
	
	if(*head==*NODE)
	
	{
		
		*head=(*head)->stack;
		
	}
	
	else
	
	{
		pnode x;
		
		for(x=*head; x->stack!=temp; x=x->stack);
		
		x->stack=temp->stack;
	}
}

pnode search(pnode head, int i, int j)
{
	
	for(pnode x=head; x!=NULL; x=x->stack)
	
	{
		
		if(i==x->i&&j==x->j)
		
		{
		
			
			return x;
		}
	}
}

void A_star()

{
		
	do{
	
	pnode S=NULL;
	
	for(pnode x=openlist; x!=NULL; x=x->stack)
	
	{
		
		if(S==NULL||x->F<S->F)
		
		{
			
			S=x;
			
		}
    }
    
    insert(&S->parent,&closelist, S->i, S->j);
    
    if(S->parent==NULL)
    
    {
    	
    	first=closelist;
	}
    
    Remove(&S, &openlist);
    
    if(S->i==final[0]&&S->j==final[1])
    
    {
    	
    	break;
	}
    
    int i, j;

    i=S->i-1, j=S->j;

    if(!is_in(closelist, i, j))
    {
	
    if(check_is(i, j))
    
    {
	
    if(!is_in(openlist, i, j))
    
    {
    	
    	insert(&S,&openlist, i, j);
	}
	
	else
	
	{
		
		pnode T=search(openlist, i, j);
		
		float f=S->G+1+sqrt((i-final[0])*(i-final[0])+(j-final[1])*(j-final[1]));
		
		if(f<T->F)
		
		{
			
			T->G=S->G+1;
			
			T->parent=S;
			
			T->F=f;
}
}}}

    i=S->i, j=S->j-1;

    if(!is_in(closelist, i, j))
    
    {
	
    if(check_is(i, j))
    {
	
    if(!is_in(openlist, i, j))
    
    {
    	
    	insert(&S,&openlist, i, j);
	}
	
    else
	
	{
		
		pnode T=search(openlist, i, j);
		
		float f=S->G+1+sqrt((i-final[0])*(i-final[0])+(j-final[1])*(j-final[1]));
		if(f<T->F)
		
		{
			
			T->G=S->G+1;
			
			T->parent=S;
			
			T->F=f;
		}
	} 
    
}}

    i=S->i+1, j=S->j;
    
    if(!is_in(closelist, i, j))
    {
	
    if(check_is(i, j))
    {
	
    if(!is_in(openlist, i, j))
    
    {
    	
    	insert(&S,&openlist, i, j);
    	
	}
	
    	else
	
	{
		
		pnode T=search(openlist, i, j);
		
		float f=S->G+1+sqrt((i-final[0])*(i-final[0])+(j-final[1])*(j-final[1]));
		
		if(f<T->F)
		
		{
			
			T->G=S->G+1;
			
			T->parent=S;
			
			T->F=f;
		}
	} 
    
}}

    i=S->i, j=S->j+1;

    if(!is_in(closelist, i, j))
	{
		        
    if(check_is(i, j))
    {
	
    if(!is_in(openlist, i, j))
    
    {
    	
    	insert(&S,&openlist, i, j);
	}	  
    
    	else
	
	{
		
		pnode T=search(openlist, i, j);
		
		float f=S->G+1+sqrt((i-final[0])*(i-final[0])+(j-final[1])*(j-final[1]));
		
		if(f<T->F)
		
		{
			
			T->G=S->G+1;
			
			T->parent=S;
			
			T->F=f;
		}
	}
}}

	}while(closelist->i!=final[0]||closelist->j!=final[1]);
	

}

int main()

{
	int A=56,B=0;
	
	system("color F4");
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t-play computer\n\t\t\t\t\t\t\t-play player\n\t\t\t\t\t\t\t-exit");
	
	gotoxy(A,12);
	
	char Key;
	
	Key=13;
	
	if(Key==72)
	
	{
		
		Key='w';
	}
	
	if(Key==80)
	
	{
		
		Key='s';
	}
	
	while(Key!=13)
	
	{
	
	if(Key=='w')
	
	{
		B--;
		
		if(B>2)
		
		{
			
			B=0;
		}
		
		if(B<0)
		
		{
			
			B=2;
		}
		
		gotoxy(A,B+12);
		
	
	}
	
	if(Key=='s')
	
	{
		B++;
		
		if(B>2)
		
		{
			
			B=0;
		}
		
		if(B<0)
		
		{
			
			B=2;
		}		
		
		gotoxy(A,B+12);
	
	}
	
	    if(B==0)
		
		{
			
			system("color F4");
	    }
	    
	    if(B==1)
		
		{
			
			system("color F3");
	    }
	    
	    if(B==2)
		
		{
			
			system("color F1");
	    }
	
	Key=getch();
	
	if(Key==72)
	
	{
		
		Key='w';
		
	}
	
	if(Key==80)
	
	{
		
		Key='s';
		
	}
	
    }
	
	if(B!=2)
	
	{

	for(int i=0; i<1; i++)
	
	{
		
		system("cls");
		
		printf("please wait");
		
		for(int i=0; i<3; i++)
		
		{
			
			sleep(1);
			
			printf(".");
		}
	
	}
	
	sleep(1);
	
    }
	
	system("cls");
	
	switch(B)
	
	{
		
	case 1:
	
	{
		
	Map();
	
    Display();
			
	key();
	
	break;
	
    }

    case 0:
    	
    {
	                                                 
	Map();
	
    Display();	
	
	start[0]=0;
    
    start[1]=0;	   
    
    for(int p=0; p<count; p++)
    
    {
    	
    
	if(point_place[p][0]!=-1&&point_place[p][1]!=-1)

    {	
    	
    final[0]=point_place[p][0];
    
    final[1]=point_place[p][1];
    
    insert(NULL,&openlist,start[0],start[1]);
    
    A_star();
    
    while(first!=closelist)
	
	{
		
	sleep(1);
	
	pnode i;
	
	for(i=closelist; i->parent->i!=first->i||i->parent->j!=first->j; i=i->parent);
	
	first->parent=i;
	
	first=i;
	
	for(int z=0; z<count; z++)
	
	{
		
		if(first->i==point_place[z][0]&&first->j==point_place[z][1])
		
		{
			
			point_place[z][0]=point_place[z][1]=-1;
		}
	}
	
	if(first->i-y==1)
	
	{
		
		move='s';
		
		Move();
	
	}
	
	if(first->i-y==-1)
	
	{
		
		move='w';
		
		Move();
	}
	
	if(first->j-x==1)
	
	{
		
		move='d';
		
		Move();
	
	}
	
	if(first->j-x==-1)
	
	{
		
		move='a';
		
		Move();
		
	}
	
    }
    
    start[0]=final[0];
	
	start[1]=final[1];
	
	while(closelist!=NULL)
	
	{
		pnode temp=closelist;
		
		Remove(&closelist,&closelist);
		
		temp=NULL;
		
		free(temp);
	}
	
	free(closelist);
	
	closelist=NULL;
	
	while(openlist!=NULL)
	
	{
		pnode temp=openlist;
		
		Remove(&openlist,&openlist);
		
		temp=NULL;
		
		free(temp);
	}	
	
	free(openlist);
	
	openlist=NULL;
		
	}
	
	}

    }
    
    case  2:
    	
    	{
    		
    		exit(0);
		}
    
    }
    
	
	fclose(ptf);
}
