/*
Sean Higgins
CIS114
2008 - 04 - 21
*/

#include<stdio.h>

char peg[16] = "OIIIIIIIIIIIIII";

int get_pegs();
void reset_pegs();
int check_move(int a,int b);
int check_act(int a,int b);
int find_peg(int a,int b);
int column(int a);
int row(int a);

int main()
{
	  int select = 1;
	  int act = 0;
	  printf("Pegs!\nComplete the game with 1 peg left!");
	  while(select)
	  {
		  act = 0;
		  select = 0;
		  reset_pegs();
		  while(get_pegs() > 1 && select != 16)
		  {
			  printf("\n      1\n    2   3\n   4  5  6\n  7  8  9 10\n11 12 13 14 15\n\n");
			  printf("\n    %c    \n   %c %c   \n  %c %c %c  \n %c %c %c %c \n%c %c %c %c %c\n\n",peg[0],peg[1],peg[2],peg[3],peg[4],peg[5],peg[6],peg[7],peg[8],peg[9],peg[10],peg[11],peg[12],peg[13],peg[14]);
			  select = 0;
			  act = 0;
			  while(!check_move(select - 1,act))
			  {
				  printf("Choose a peg >");
				  scanf("%d",&select);
				  getchar();
				  while((select < 1 || select > 15) || peg[select - 1] == 'O')
				  {
					  printf("...move a peg... not an open space >");
					  scanf("%d",&select);
					  getchar();
				  }
				  printf("What direction >");
				  scanf("%d",&act);
				  getchar();
				  if(!check_move(select - 1,act))
				  {
					  printf("don't select outside the boundaries!\n");
				  }
				  else
				  {
					  if(check_act(select - 1,act) == 1)
					  {
						  printf("Pegs Left: %d\n",get_pegs());
					  }
					  else if(check_act(select - 1,act) == 0)
					  {
						  printf("no peg to jump\n");
						  act = 5;
					  }
					  else if(check_act(select - 1,act) == -1)
					  {
						  printf("no place to land\n");
						  act = 5;
					  }
				  }

			  }
		  }
		  printf("Game Over!");
		  if(get_pegs() == 1)
		  {
			  printf("You win!\n");
			  if(peg[0] == 'I')
			  {
				  printf("PERFECT win!\n");
			  }
		  }
		  printf("Play again? false(0) or true(1)>");
		  scanf("%d",&select);
		  getchar();
	  }
	  getchar();
	  return 0;
}
int get_pegs()
{
	int ret = 0;
	for(int i = 0;i < 15;i++)
	{
		ret += (peg[i] == 'I');
	}
	return ret;
}
void reset_pegs()
{
	peg[0] = 'O';
	for(int i = 1;i < 15;i++)
	{
		peg[i] = 'I';
	}
}
int check_move(int pos,int move)
{
	if(move == 1 || move == 3)
	{
		return (pos < 6);
	}
	else if(move == 9 || move == 6)
	{
		return (pos == 3)||(pos == 6)||(pos == 7)||(pos == 10)||(pos == 11)||(pos == 12);
	}
	else if(move == 7 || move == 4)
	{
		return (column(pos) > 2);
	}
	else
	{
		return 0;
	}
}
int check_act(int pos,int move)
{
	int tmp_col = column(pos);
	int tmp_row = row(pos);
	int tmp_col2 = column(pos);
	int tmp_row2 = row(pos);
	//vertical movement
	if(move == 7 || move == 9)
	{
		tmp_row -= 2;
	}
	else if(move == 1 || move == 3)
	{
		tmp_row += 2;
	}
	//horizontal movement
	if(move == 7 || move == 4)
	{
		tmp_col -= 2;
	}
	else if(move == 3 || move == 6)
	{
		tmp_col += 2;
	}
	//checking
	if(peg[find_peg(tmp_row,tmp_col)] == 'I')
	{
		return -1;
	}
	//vertical movement
	if(move == 7 || move == 9)
	{
		tmp_row2 -= 1;
	}
	else if(move == 1 || move == 3)
	{
		tmp_row2 += 1;
	}
	//horizontal movement
	if(move == 7 || move == 4)
	{
		tmp_col2 -= 1;
	}
	else if(move == 3 || move == 6)
	{
		tmp_col2 += 1;
	}
	if((peg[find_peg(tmp_row2,tmp_col2)] == 'O'))
	{
		return 0;
	}
	peg[pos] = 'O';
	peg[find_peg(tmp_row,tmp_col)] = 'I';
	peg[find_peg(tmp_row2,tmp_col2)] = 'O';
	return 1;
}
int find_peg(int tmp_row,int tmp_col)
{
	if(tmp_row == 1)
	{
		return 0;
	}
	else if(tmp_row == 2)
	{
		return tmp_col;
	}
	else if(tmp_row == 3)
	{
		return 2 + tmp_col;
	}
	else if(tmp_row == 4)
	{
		return 5 + tmp_col;
	}
	else if(tmp_row == 5)
	{
		return 9 + tmp_col;
	}
	else
	{
		return 0;
	}
}
int column(int pos)
{
	if(pos < 1)
	{
		return 1;
	}
	else if(pos < 3)
	{
		return pos;
	}
	else if(pos < 6)
	{
		return pos - 2;
	}
	else if(pos < 10)
	{
		return pos - 5;
	}
	else if(pos < 16)
	{
		return pos - 9;
	}
	else
	{
		return 0;
	}
}
int row(int pos)
{
	if(pos < 1)
	{
		return 1;
	}
	else if(pos < 3)
	{
		return 2;
	}
	else if(pos < 6)
	{
		return 3;
	}
	else if(pos < 10)
	{
		return 4;
	}
	else if(pos < 16)
	{
		return 5;
	}
	else
	{
		return 0;
	}
}
/*
Pegs!
Complete the game with 1 peg left!
      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    O
   I I
  I I I
 I I I I
I I I I I

Choose a peg >4
What direction >9
Pegs Left: 13

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   O I
  O I I
 I I I I
I I I I I

Choose a peg >6
What direction >4
Pegs Left: 12

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   O I
  I O O
 I I I I
I I I I I

Choose a peg >7
What direction >9
Pegs Left: 11

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   I I
  O O O
 O I I I
I I I I I

Choose a peg >13
What direction >7
Pegs Left: 10

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   I I
  I O O
 O O I I
I I O I I

Choose a peg >2
What direction >1
Pegs Left: 9

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   O I
  O O O
 I O I I
I I O I I

Choose a peg >11
What direction >9
Pegs Left: 8

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   O I
  I O O
 O O I I
O I O I I

Choose a peg >14
What direction >7
Pegs Left: 7

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   O I
  I I O
 O O O I
O I O O I

Choose a peg >1
What direction >3
Pegs Left: 6

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    O
   O O
  I I I
 O O O I
O I O O I

Choose a peg >10
What direction >7
Pegs Left: 5

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    O
   O I
  I I O
 O O O O
O I O O I

Choose a peg >3
What direction >1
Pegs Left: 4

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    O
   O O
  I O O
 O I O O
O I O O I

Choose a peg >4
What direction >3
Pegs Left: 3

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    O
   O O
  O O O
 O O O O
O I I O I

Choose a peg >12
What direction >6
Pegs Left: 2

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    O
   O O
  O O O
 O O O O
O O O I I

Choose a peg >15
What direction >4
Pegs Left: 1
Game Over!You win!
Play again? false(0) or true(1)>



  Pegs!
Complete the game with 1 peg left!
      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    O
   I I
  I I I
 I I I I
I I I I I

Choose a peg >6
What direction >4
no place to land
Choose a peg >1
...move a peg... not an open space >3
What direction >7
don't select outside the boundaries!
Choose a peg >3
What direction >6
don't select outside the boundaries!
Choose a peg >6
What direction >7
Pegs Left: 13

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   I O
  I I O
 I I I I
I I I I I

Choose a peg >1
What direction >3
no peg to jump
Choose a peg >4
What direction >6
Pegs Left: 12

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   I O
  O O I
 I I I I
I I I I I

Choose a peg >11
What direction >9
Pegs Left: 11

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   I O
  I O I
 O I I I
O I I I I

Choose a peg >2
What direction >1
Pegs Left: 10

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   O O
  O O I
 I I I I
O I I I I

Choose a peg >13
What direction >4
Pegs Left: 9

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   O O
  O O I
 I I I I
I O O I I

Choose a peg >11
What direction >9
Pegs Left: 8

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   O O
  I O I
 O I I I
O O O I I

Choose a peg >4
What direction >3
Pegs Left: 7

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   O O
  O O I
 O O I I
O O I I I

Choose a peg >10
What direction >4
Pegs Left: 6

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   O O
  O O I
 O I O O
O O I I I

Choose a peg >14
What direction >4
Pegs Left: 5

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   O O
  O O I
 O I O O
O I O O I

Choose a peg >12
What direction >9
Pegs Left: 4

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   O O
  O I I
 O O O O
O O O O I

 Choose a peg >6
What direction >4
Pegs Left: 3

      1
    2   3
   4  5  6
  7  8  9 10
11 12 13 14 15


    I
   O O
  I O O
 O O O O
O O O O I

Choose a peg >

1
What direction >1
no place to land
Choose a peg >1
What direction >3
no peg to jump
Choose a peg >15
What direction >4
no peg to jump
Choose a peg >
*/