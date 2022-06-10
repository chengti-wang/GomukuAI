#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
#define ROW 19
#define COL 19
int cb[ROW][COL];
char turn = 1;
int count = 0;
int height = 0;
int bestX;
int bestY;
int x[8][5] = {
  {0, 0, 0, 0, 0},
  {1, 2, 3, 4, 5},
  {1, 2, 3, 4, 5},
  {1, 2, 3, 4, 5},
  {0, 0, 0, 0, 0},  
  {-1, -2, -3, -4, -5},
  {-1, -2, -3, -4, -5},
  {-1, -2, -3, -4, -5},
};
int y[8][5] = {
  {-1, -2, -3, -4, -5},
  {-1, -2, -3, -4, -5},
  {0, 0, 0, 0, 0},
  {1, 2, 3, 4, 5},
  {1, 2, 3, 4, 5},
  {1, 2, 3, 4, 5},
  {0, 0, 0, 0, 0},
  {-1, -2, -3, -4, -5},
};
int pattern[243] = {
  /* ----- */ 0,
  /* ----X */ 0,
  /* ----O */ 0,
  /* ---X- */ 0,
  /* ---XX */ 0,
  /* ---XO */ 0,
  /* ---O- */ 0,
  /* ---OX */ 0,
  /* ---OO */ 0,
  /* --X-- */ 0,
  /* --X-X */ 0,
  /* --X-O */ 0,
  /* --XX- */ 0,
  /* --XXX */ 0,
  /* --XXO */ 0,
  /* --XO- */ 0,
  /* --XOX */ 0,
  /* --XOO */ 0,
  /* --O-- */ 0,
  /* --O-X */ 0,
  /* --O-O */ 0,
  /* --OX- */ 0,
  /* --OXX */ 0,
  /* --OXO */ 0,
  /* --OO- */ 0,
  /* --OOX */ 0,
  /* --OOO */ 0,
  /* -X--- */ 0,
  /* -X--X */ 0,
  /* -X--O */ 0,
  /* -X-X- */ 0,
  /* -X-XX */ 0,
  /* -X-XO */ 0,
  /* -X-O- */ 0,
  /* -X-OX */ 0,
  /* -X-OO */ 0,
  /* -XX-- */ 0,
  /* -XX-X */ 0,
  /* -XX-O */ 0,
  /* -XXX- */ 0,
  /* -XXXX */ 0,
  /* -XXXO */ 0,
  /* -XXO- */ 0,
  /* -XXOX */ 0,
  /* -XXOO */ 0,
  /* -XO-- */ 0,
  /* -XO-X */ 0,
  /* -XO-O */ 0,
  /* -XOX- */ 0,
  /* -XOXX */ 0,
  /* -XOXO */ 0,
  /* -XOO- */ 0,
  /* -XOOX */ 0,
  /* -XOOO */ 0,
  /* -O--- */ 0,
  /* -O--X */ 0,
  /* -O--O */ 0,
  /* -O-X- */ 0,
  /* -O-XX */ 0,
  /* -O-XO */ 0,
  /* -O-O- */ 0,
  /* -O-OX */ 0,
  /* -O-OO */ 0,
  /* -OX-- */ 0,
  /* -OX-X */ 0,
  /* -OX-O */ 0,
  /* -OXX- */ 1,
  /* -OXXX */ 2,
  /* -OXXO */ 0,
  /* -OXO- */ 2,
  /* -OXOX */ 0,
  /* -OXOO */ -2,
  /* -OO-- */ -3,
  /* -OO-X */ -2,
  /* -OO-O */ -4,
  /* -OOX- */ 1,
  /* -OOXX */ 0,
  /* -OOXO */ -2,
  /* -OOO- */ -4,
  /* -OOOX */ 0,
  /* -OOOO */ 0,
  /* X---- */ 1, 
  /* X---X */ 1,  
  /* X---O */ 1, 
  /* X--X- */ 1, 
  /* X--XX */ 1, 
  /* X--XO */ 1, 
  /* X--O- */ 1, 
  /* X--OX */ 1, 
  /* X--OO */ 1, 
  /* X-X-- */ 1,  
  /* X-X-X */ 1,  
  /* X-X-O */ 1, 
  /* X-XX- */ 1,  
  /* X-XXX */ 1,  
  /* X-XXO */ 1, 
  /* X-XO- */ 0, 
  /* X-XOX */ 0, 
  /* X-XOO */ 0, 
  /* X-O-- */ 0, 
  /* X-O-X */ 0, 
  /* X-O-O */ 0, 
  /* X-OX- */ 0, 
  /* X-OXX */ 0, 
  /* X-OXO */ 0, 
  /* X-OO- */ 0, 
  /* X-OOX */ 0, 
  /* X-OOO */ 0, 
  /* XX--- */ 6, 
  /* XX--X */ 6, 
  /* XX--O */ 6, 
  /* XX-X- */ 6, 
  /* XX-XX */ 6, 
  /* XX-XO */ 6, 
  /* XX-O- */ 6, 
  /* XX-OX */ 6, 
  /* XX-OO */ 6, 
  /* XXX-- */ 8, 
  /* XXX-X */ 8, 
  /* XXX-O */ 8, 
  /* XXXX- */ 20, 
  /* XXXXX */ 10,// WIN 121 
  /* XXXXO */ 20,   
  /* XXXO- */ 7, 
  /* XXXOX */ 7, 
  /* XXXOO */ 7, 
  /* XXO-- */ 0, 
  /* XXO-X */ 0, 
  /* XXO-O */ 0, 
  /* XXOX- */ 0, 
  /* XXOXX */ 0, 
  /* XXOXO */ 0, 
  /* XXOO- */ 0, 
  /* XXOOX */ 0, 
  /* XXOOO */ 0, 
  /* XO--- */ 0, 
  /* XO--X */ 0, 
  /* XO--O */ 0, 
  /* XO-X- */ 0, 
  /* XO-XX */ 0, 
  /* XO-XO */ 0, 
  /* XO-O- */ 0, 
  /* XO-OX */ 0, 
  /* XO-OO */ 0, 
  /* XOX-- */ 0, 
  /* XOX-X */ 0, 
  /* XOX-O */ 0, 
  /* XOXX- */ 0, 
  /* XOXXX */ 0, 
  /* XOXXO */ 0, 
  /* XOXO- */ 0, 
  /* XOXOX */ 0, 
  /* XOXOO */ 0, 
  /* XOO-- */ 0, 
  /* XOO-X */ 0, 
  /* XOO-O */ 0, 
  /* XOOX- */ 0, 
  /* XOOXX */ 0, 
  /* XOOXO */ 0, 
  /* XOOO- */ 0, 
  /* XOOOX */ 0, 
  /* XOOOO */ 0, 
  /* O---X */ -1,
  /* O---- */ -1,
  /* O---O */ -1,
  /* O--X- */ -1,
  /* O--XX */ -1,
  /* O--XO */ -1,
  /* O--O- */ -1,
  /* O--OX */ -1,
  /* O--OO */ -1,
  /* O-X-- */ -1,
  /* O-X-X */ -1,
  /* O-X-O */ -1,
  /* O-XX- */ -1,
  /* O-XXX */ -1,
  /* O-XXO */ -1,
  /* O-XO- */ -1,
  /* O-XOX */ -1,
  /* O-XOO */ -1,
  /* O-O-- */ -1,
  /* O-O-X */ -1,
  /* O-O-O */ -1,
  /* O-OX- */ -1,
  /* O-OXX */ -1,
  /* O-OXO */ -1,
  /* O-OO- */ -1,
  /* O-OOX */ -1,
  /* O-OOO */ -1,
  /* OX--- */ 0,
  /* OX--X */ 0,
  /* OX--O */ 0,
  /* OX-X- */ 0,
  /* OX-XX */ 0,
  /* OX-XO */ 0,
  /* OX-O- */ 0,
  /* OX-OX */ 0,
  /* OX-OO */ 0,
  /* OXX-- */ 0,
  /* OXX-X */ 0,
  /* OXX-O */ 0,
  /* OXXX- */ 0,
  /* OXXXX */ 0,
  /* OXXXO */ 0,
  /* OXXO- */ 0,
  /* OXXOX */ 0,
  /* OXXOO */ 0,
  /* OXO-- */ 0,
  /* OXO-X */ 0,
  /* OXO-O */ 0,
  /* OXOX- */ 0,
  /* OXOXX */ 0,
  /* OXOXO */ 0,
  /* OXOO- */ 0,
  /* OXOOX */ 0,
  /* OXOOO */ 0,
  /* OO--- */ -6,
  /* OO--X */ -6,
  /* OO--O */ -6,
  /* OO-X- */ -6,
  /* OO-XX */ -6,
  /* OO-XO */ -6,
  /* OO-O- */ -6,
  /* OO-OX */ -6,
  /* OO-OO */ -6,
  /* OOX-- */ -6,
  /* OOX-X */ -6,
  /* OOX-O */ -6,
  /* OOXX- */ -6,
  /* OOXXX */ -6,
  /* OOXXO */ -6,
  /* OOXO- */ -6,
  /* OOXOX */ -6,
  /* OOXOO */ -6,
  /* OOO-- */ -8,
  /* OOO-X */ -8,
  /* OOO-O */ -8,
  /* OOOX- */ -7,
  /* OOOXX */ -7,
  /* OOOXO */ -7,
  /* OOOO- */ -20,
  /* OOOOX */ -20,
  /* OOOOO */ -10, // WIN
};

typedef struct _NODE
{
  int x;
  int y;
  int height;
  int sumscore;
  int decision;
}NODE;

vector<NODE> node;

int move(int *r, int *c);
void printTable(int, int);

int recursive()
{
  if(count == 0)
  {
    bestX = ROW/2;
    bestY = COL/2;
    return 0;
  }
  else if(height == 5)
  {
    move(&bestX, &bestY);
  }
  else
  {
    vector<NODE> good_moves;
    int decided = 0;

    if(count == 0)
    {
      bestX = ROW/2;
      bestY = COL/2;
      return 0;
    }
    int largest = 0;
    for(int i=0; i<ROW; i++)
    {
      for(int j=0; j<COL; j++)
      {
        if(cb[i][j] == 1) cb[i][j] = 2;
        else if(cb[i][j] == 2) cb[i][j] = 1;
      }
    }
    for(int i=0; i<ROW; i++)
    {
      for(int j=0; j<COL; j++)
      {
        if(cb[i][j] == 0)
        {
          // make temperary NODE
          NODE t;

          int sumScore = 0;
          int dir_index[8];
          for(int dir=0; dir<8; dir++)
          {
            int index = 0;
            for(int grid=0; grid<5; grid++)
            {
              int search_y = i+y[dir][grid];
              int search_x = j+x[dir][grid];
              if((search_y >= 0 && search_y < COL) && (search_x >= 0 && search_x < ROW))
              {
                index += cb[search_y][search_x] * pow(3, 4-grid);
              }
            }
            dir_index[dir] = index;
            int score = abs(pattern[index]);
            if(score > 0)
            {
              //printf("%d %d %d %d\n", score, i, j, dir);
            }
            if(score >= 9)
            {
              score *= 3;
              t.decision = 3;
            }
            sumScore += score;
          }
          int atk = 0;
          int def = 0;
          for(int cross=0; cross<4; cross++)
          {
            int acrossScore1 = pattern[dir_index[cross]];
            int acrossScore2 = pattern[dir_index[cross+4]];
            

            // X[]XXX
            if(((dir_index[cross] >= 81 && dir_index[cross] <= 161) && acrossScore2 >= 7) || ((dir_index[cross+4] >= 81 && dir_index[cross+4] <= 161) && acrossScore1 >= 7))
            {
              sumScore += 20;
              if(t.decision < 3)
                t.decision = 3;
            }
            //XX[]XX
            if(acrossScore1 >= 5 && acrossScore2 >= 5)
            {
              sumScore += 20;
              if(t.decision < 3)
                t.decision = 3;
            }
            // -[]XXX-
            if(((dir_index[cross] >= 0 && dir_index[cross] < 81) && (dir_index[cross+4] >= 117 && dir_index[cross+4] <= 119)) || ((dir_index[cross+4] >= 0 && dir_index[cross+4] < 81) && (dir_index[cross] >= 117 && dir_index[cross] <= 119)))
            {
              sumScore += 13;
              if(t.decision < 2)
                t.decision = 2;
            }
            // -X[]XX-
            if(((dir_index[cross] >= 81 && dir_index[cross] <= 107) && (dir_index[cross+4] >= 108 && dir_index[cross+4] <= 116)) || ((dir_index[cross+4] >= 81 && dir_index[cross+4] <= 107) && (dir_index[cross] >= 108 && dir_index[cross] <= 116)))
            {
              sumScore += 13;
              if(t.decision < 2)
                t.decision = 2;
            }
            // -X[]X--
            if(((dir_index[cross] >= 81 && dir_index[cross] <= 107) && (dir_index[cross+4] >= 81 && dir_index[cross+4] <= 89)) || ((dir_index[cross+4] >= 81 && dir_index[cross+4] <= 107) && (dir_index[cross] >= 81 && dir_index[cross] <= 89)))
            {
              sumScore += 5; 
              atk++;
            }
            // --[]XX-
            else if(((dir_index[cross] >= 0 && dir_index[cross] <= 26) && (dir_index[cross+4] >= 108 && dir_index[cross+4] <= 116)) || ((dir_index[cross+4] >= 0 && dir_index[cross+4] <= 26) && (dir_index[cross] >= 108 && dir_index[cross] <= 116)))
            {
              sumScore += 5; 
              atk++;
            }
            // -[]XX--
            else if(((dir_index[cross] >= 0 && dir_index[cross] <= 80) && (dir_index[cross+4] >= 108 && dir_index[cross+4] <= 110)) || ((dir_index[cross+4] >= 0 && dir_index[cross+4] <= 80) && (dir_index[cross] >= 108 && dir_index[cross] <= 110)))
            {
              sumScore += 5; 
              atk++;
            }
            if(((dir_index[cross] >= 108 && dir_index[cross] <= 134) && (dir_index[cross+4] >= 81 && dir_index[cross+4] <= 107)) || ((dir_index[cross+4] >= 108 && dir_index[cross+4] <= 134) && (dir_index[cross] >= 81 && dir_index[cross] <= 107)))
            {
              sumScore += 5; 
              atk++;
            }
            else if(((dir_index[cross] >= 81 && dir_index[cross] <= 161) && (dir_index[cross+4] >= 90 && dir_index[cross+4] <= 98)) || ((dir_index[cross+4] >= 81 && dir_index[cross+4] <= 161) && (dir_index[cross] >= 90 && dir_index[cross] <= 98)))
            {
              sumScore += 5; 
              atk++;
            }
            else if(((dir_index[cross] >= 108 && dir_index[cross] <= 134) && (dir_index[cross+4] >= 27 && dir_index[cross+4] <= 53)) || ((dir_index[cross+4] >= 108 && dir_index[cross+4] <= 134) && (dir_index[cross] >= 27 && dir_index[cross] <= 53)))
            {
              sumScore += 5; 
              atk++;
            }
            else if(((dir_index[cross] >= 81 && dir_index[cross] <= 161) && (dir_index[cross+4] >= 36 && dir_index[cross+4] <= 44)) || ((dir_index[cross+4] >= 81 && dir_index[cross+4] <= 161) && (dir_index[cross] >= 36 && dir_index[cross] <= 44)))
            {
              sumScore += 5; 
              atk++;
            }
            else if(((dir_index[cross] >= 0 && dir_index[cross] <= 80) && (dir_index[cross+4] >= 108 && dir_index[cross+4] <= 110)) || ((dir_index[cross+4] >= 0 && dir_index[cross+4] <= 80) && (dir_index[cross] >= 108 && dir_index[cross] <= 110)))
            {
              sumScore += 5; 
              atk++;
            }
            // []XXX-O
            else if(dir_index[cross] == 119)
            {
              sumScore += 5; 
              atk++;
            }
            // []-XXX
            else if(dir_index[cross] == 41)
            {
              sumScore += 5; 
              atk++;
            }
            // []X-XX
            else if(dir_index[cross] == 95)
            {
              sumScore += 5; 
              atk++;
            }
            // []XX-X
            else if(dir_index[cross] == 113)
            {
              sumScore += 5; 
              atk++;
            }

            //circle
            // O[]OOO 
            if(((dir_index[cross] >= 162 && dir_index[cross] <= 242) && (dir_index[cross+4] >= 234 && dir_index[cross+4] <= 242)) || ((dir_index[cross+4] >= 162 && dir_index[cross+4] <= 242) && (dir_index[cross] >= 234 && dir_index[cross] <= 242)))
            {
              sumScore += 20;
              if(t.decision>-3 && t.decision<3)
                t.decision = -3;
            }
            // OO[]OO
            if(acrossScore1 <= -5 && acrossScore2 <= -5)
            {
              sumScore += 20;
              if(t.decision>-3 && t.decision<3)
                t.decision = -3;
            }
            // -OOO[]-
            if(((dir_index[cross] >= 0 && dir_index[cross] < 81) && (dir_index[cross+4] >= 234 && dir_index[cross+4] <= 236)) || ((dir_index[cross+4] >= 0 && dir_index[cross+4] < 81) && (dir_index[cross] >= 234 && dir_index[cross] <= 236)))
            {
              sumScore += 13;
              if(t.decision>-2 && t.decision<2)
                t.decision = -2;
            }
            // -OO[]O-
            if(((dir_index[cross] >= 216 && dir_index[cross] < 225) && (dir_index[cross+4] >= 162 && dir_index[cross+4] <= 189)) || ((dir_index[cross+4] >= 216 && dir_index[cross+4] < 225) && (dir_index[cross] >= 162 && dir_index[cross] <= 189)))
            {
              sumScore += 13;
              if(t.decision>-2 && t.decision<2)
                t.decision = -2;
            }
            // -O[]O--
            if(((dir_index[cross] >= 162 && dir_index[cross] <= 188) && (dir_index[cross+4] >= 162 && dir_index[cross+4] <= 170)) || ((dir_index[cross+4] >= 162 && dir_index[cross+4] <= 188) && (dir_index[cross] >= 162 && dir_index[cross] <= 170)))
            {
              sumScore += 5; 
              def++;
            }
            // --[]OO-
            else if(((dir_index[cross] >= 0 && dir_index[cross] <= 26) && (dir_index[cross+4] >= 216 && dir_index[cross+4] <= 224)) || ((dir_index[cross+4] >= 0 && dir_index[cross+4] <= 26) && (dir_index[cross] >= 216 && dir_index[cross] <= 224)))
            {
              sumScore += 5; 
              def++;
            }
            // -[]OO-
            else if(((dir_index[cross] >= 0 && dir_index[cross] <= 80) && (dir_index[cross+4] >= 216 && dir_index[cross+4] <= 224)) || ((dir_index[cross+4] >= 0 && dir_index[cross+4] <= 80) && (dir_index[cross] >= 216 && dir_index[cross] <= 224)))
            {
              sumScore += 5; 
              def++;
            }
            // OO[]O-
            if(((dir_index[cross] >= 216 && dir_index[cross] <= 242) && (dir_index[cross+4] >= 162 && dir_index[cross+4] <= 188)) || ((dir_index[cross+4] >= 216 && dir_index[cross+4] <= 242) && (dir_index[cross] >= 162 && dir_index[cross] <= 188)))
            {
              sumScore += 5; 
              def++;
            }
            // O[]O-O
            else if(((dir_index[cross] >= 162 && dir_index[cross] <= 242) && (dir_index[cross+4] >= 180 && dir_index[cross+4] <= 188)) || ((dir_index[cross+4] >= 162 && dir_index[cross+4] <= 242) && (dir_index[cross] >= 180 && dir_index[cross] <= 188)))
            {
              sumScore += 5; 
              def++;
            }
            // XX[]-X
            else if(((dir_index[cross] >= 216 && dir_index[cross] <= 242) && (dir_index[cross+4] >= 54 && dir_index[cross+4] <= 80)) || ((dir_index[cross+4] >= 216 && dir_index[cross+4] <= 242) && (dir_index[cross] >= 54 && dir_index[cross] <= 80)))
            {
              sumScore += 5; 
              def++;
            }
            // -[]OO-
            else if(((dir_index[cross] >= 162 && dir_index[cross] <= 242) && (dir_index[cross+4] >= 72 && dir_index[cross+4] <= 80)) || ((dir_index[cross+4] >= 162 && dir_index[cross+4] <= 242) && (dir_index[cross] >= 72 && dir_index[cross] <= 80)))
            {
              sumScore += 5; 
              def++;
            }
            else if(dir_index[cross] == 235)
            {
              sumScore += 5; 
              def++;
            }
            else if(dir_index[cross] == 79)
            {
              sumScore += 5; 
              def++;
            }
            else if(dir_index[cross] == 187)
            {
              sumScore += 5; 
              def++;
            }

            if(atk > 1 && t.decision == 0)
            {
              t.decision = 1;
            }
            if(def > 1 && t.decision == 0)
            {
              t.decision = -1;
            }
          }
          
          if(sumScore > largest)
          {
            largest = sumScore;
            bestX = i;
            bestY = j;
            //printf("%d %d %d", largest, i, j);
          }
          
          // no good moves --> no more recursive
          if(t.decision != 0)
          {
            decided = 1;
          }

          //collect the good moves for recursive
          if(sumScore > 15)
          {
            t.x = i; 
            t.y = j;
            t.sumscore = sumScore;
            t.height = height;
            good_moves.push_back(t);
          }
        }
      }
    }
    for(int i=0; i<ROW; i++)
    {
      for(int j=0; j<COL; j++)
      {
        if(cb[i][j] == 1) cb[i][j] = 2;
        else if(cb[i][j] == 2) cb[i][j] = 1;
      }
    }

    // No key decision and layer depth less than 5 --> RUN recursive
    if(decided == 0 || height < 5)
    {
      vector<NODE>::iterator p;
      for(p=good_moves.begin(); p!=good_moves.end(); p++)
      {
        //play the imaginary move
        cb[p->y][p->x] = turn;
        printTable(p->x, p->y);
        printf("**********************************************************************");
        //switch moves
        if(turn==1) turn = 2;
        else turn = 1;

        height++;
        //call recursive
        recursive();
        
        height--;
        if(turn==1) turn = 2;
        else turn = 1;
        cb[p->y][p->x] = 0;
        printf("i: %d j: %d\n", p->x + 1, p->y + 1);
      }
    }

    if(decided == 1 && height == 1)
    {
      
    }
    for(int i=0; i<good_moves.size(); i++)
    {
      printf("i: %d  j: %d\n", good_moves[i].x+1, good_moves[i].y+1);
    }
    good_moves.clear();
  }
  if(height == 1)
  {
    
  }
  return 0;
}
void printTable(int r, int c)
{
  for(int y=-3; y<=ROW; y++)
  {
    if(y<0 || y == ROW) printf("    ");
    for(int x=0; x<COL; x++)
    {
      if( y == -3)
      {
        printf("%d ", (x+1)/10);
      }
      else if(y == -2)
      {
        printf("%d ", (x+1) % 10);
      }
      else if(y == -1 || y == ROW)
      {
        printf("--");
      }
      else
      {
        if(x==0)
        {
          printf("%02d|", y+1);
        }
      }
      if(x >= 0 && y>=0 && y<ROW)
      {
        if(x==c && y == r)
        {
          switch(cb[y][x])
          {
            case 0: printf("[:"); break;
            case 1: printf("[X"); break;
            case 2: printf("[O"); break;
          }
        }
        else if(x==c+1 && y == r)
        {
          switch(cb[y][x])
          {
            case 0: printf("]:"); break;
            case 1: printf("]X"); break;
            case 2: printf("]O"); break;
          }
        }
        else
        {
          switch(cb[y][x])
          {
            case 0: printf(" :"); break;
            case 1: printf(" X"); break;
            case 2: printf(" O"); break;
          }
        }
      }
    }
    if(y >= 0 && y<ROW)
    {
      printf(" |\n");
    }
    else
    {
      printf("\n");
    }
  }
}

int checkWin()
{
  for(int i=0; i<ROW; i++)
  {
    for(int j=0; j<COL; j++)
    {
      for(int dir=0; dir<8; dir++)
      {
        int index = 0;
        for(int grid=0; grid<5; grid++)
        {
          int search_y = i+y[dir][grid];
          int search_x = j+x[dir][grid];
          if((search_y >= 0 && search_y < COL) && (search_x >= 0 && search_x < ROW))
          {
            index += cb[search_y][search_x] * pow(3, 4-grid);
          }
        }
        if(index == 121)
          return 1;
        else if(index == 242)
          return 2;
      }
    }
  }
  return 0;
}

int move(int *r, int *c)
{
  if(count == 0)
  {
    *r = ROW/2;
    *c = COL/2;
    return 0;
  }
  int largest = 0;

  for(int i=0; i<ROW; i++)
  {
    for(int j=0; j<COL; j++)
    {
      if(cb[i][j] == 0)
      {
        int sumScore = 0;
        int dir_index[8];
        for(int dir=0; dir<8; dir++)
        {
          int index = 0;
          for(int grid=0; grid<5; grid++)
          {
            int search_y = i+y[dir][grid];
            int search_x = j+x[dir][grid];
            if((search_y >= 0 && search_y < COL) && (search_x >= 0 && search_x < ROW))
            {
              index += cb[search_y][search_x] * pow(3, 4-grid);
            }
          }
          dir_index[dir] = index;
          int score = abs(pattern[index]);
          if(score > 0)
          {
            //printf("%d %d %d %d\n", score, i, j, dir);
          }
          if(score >= 9)
          {
            score *= 3;
          }
          sumScore += score;
          
        }
        for(int cross=0; cross<4; cross++)
        {
          int acrossScore1 = pattern[dir_index[cross]];
          int acrossScore2 = pattern[dir_index[cross+4]];
          // X[]XXX
          if(((dir_index[cross] >= 81 && dir_index[cross] <= 161) && acrossScore2 >= 7) || ((dir_index[cross+4] >= 81 && dir_index[cross+4] <= 161) && acrossScore1 >= 7))
          {
            sumScore += 20;
          }
          //XX[]XX
          if(acrossScore1 >= 5 && acrossScore2 >= 5)
          {
            sumScore += 20;
          }
          // -[]XXX-
          if(((dir_index[cross] >= 0 && dir_index[cross] < 81) && (dir_index[cross+4] >= 117 && dir_index[cross+4] <= 119)) || ((dir_index[cross+4] >= 0 && dir_index[cross+4] < 81) && (dir_index[cross] >= 117 && dir_index[cross] <= 119)))
          {
            sumScore += 13;
          }
          // -X[]XX-
          if(((dir_index[cross] >= 81 && dir_index[cross] <= 107) && (dir_index[cross+4] >= 108 && dir_index[cross+4] <= 116)) || ((dir_index[cross+4] >= 81 && dir_index[cross+4] <= 107) && (dir_index[cross] >= 108 && dir_index[cross] <= 116)))
          {
            sumScore += 13;
          }
          // -X[]X--
          if(((dir_index[cross] >= 81 && dir_index[cross] <= 107) && (dir_index[cross+4] >= 81 && dir_index[cross+4] <= 89)) || ((dir_index[cross+4] >= 81 && dir_index[cross+4] <= 107) && (dir_index[cross] >= 81 && dir_index[cross] <= 89)))
          {
            sumScore += 5; 
          }
          // --[]XX-
          else if(((dir_index[cross] >= 0 && dir_index[cross] <= 26) && (dir_index[cross+4] >= 108 && dir_index[cross+4] <= 116)) || ((dir_index[cross+4] >= 0 && dir_index[cross+4] <= 26) && (dir_index[cross] >= 108 && dir_index[cross] <= 116)))
          {
            sumScore += 5; 
          }
          // -[]XX--
          else if(((dir_index[cross] >= 0 && dir_index[cross] <= 80) && (dir_index[cross+4] >= 108 && dir_index[cross+4] <= 110)) || ((dir_index[cross+4] >= 0 && dir_index[cross+4] <= 80) && (dir_index[cross] >= 108 && dir_index[cross] <= 110)))
          {
            sumScore += 5; 
          }
          //circle
          // O[]OOO 
          if(((dir_index[cross] >= 162 && dir_index[cross] <= 242) && (dir_index[cross+4] >= 234 && dir_index[cross+4] <= 242)) || ((dir_index[cross+4] >= 162 && dir_index[cross+4] <= 242) && (dir_index[cross] >= 234 && dir_index[cross] <= 242)))
          {
            sumScore += 20; 
          }
          // OO[]OO
          if(acrossScore1 <= -5 && acrossScore2 <= -5)
          {
            sumScore += 20;
          }
          // -OOO[]-
          if(((dir_index[cross] >= 0 && dir_index[cross] < 81) && (dir_index[cross+4] >= 234 && dir_index[cross+4] <= 236)) || ((dir_index[cross+4] >= 0 && dir_index[cross+4] < 81) && (dir_index[cross] >= 234 && dir_index[cross] <= 236)))
          {
            sumScore += 13;
          }
          // -OO[]O-
          if(((dir_index[cross] >= 216 && dir_index[cross] < 225) && (dir_index[cross+4] >= 162 && dir_index[cross+4] <= 189)) || ((dir_index[cross+4] >= 216 && dir_index[cross+4] < 225) && (dir_index[cross] >= 162 && dir_index[cross] <= 189)))
          {
            sumScore += 13;
          }
          // -O[]O--
          if(((dir_index[cross] >= 162 && dir_index[cross] <= 188) && (dir_index[cross+4] >= 162 && dir_index[cross+4] <= 170)) || ((dir_index[cross+4] >= 162 && dir_index[cross+4] <= 188) && (dir_index[cross] >= 162 && dir_index[cross] <= 170)))
          {
            sumScore += 5; 
          }
          // --[]OO-
          else if(((dir_index[cross] >= 0 && dir_index[cross] <= 26) && (dir_index[cross+4] >= 216 && dir_index[cross+4] <= 224)) || ((dir_index[cross+4] >= 0 && dir_index[cross+4] <= 26) && (dir_index[cross] >= 216 && dir_index[cross] <= 224)))
          {
            sumScore += 5; 
          }
          // -[]OO-
          else if(((dir_index[cross] >= 0 && dir_index[cross] <= 80) && (dir_index[cross+4] >= 216 && dir_index[cross+4] <= 224)) || ((dir_index[cross+4] >= 0 && dir_index[cross+4] <= 80) && (dir_index[cross] >= 216 && dir_index[cross] <= 224)))
          {
            sumScore += 5; 
          }
        }
        if(sumScore > largest)
        {
          largest = sumScore;
          *r = i;
          *c = j;
          //printf("%d %d %d", largest, i, j);
        }
        
      }
    }
  }
  
  return 0;
}

int main() {

  while(1)
  {
    int r, c;
    if(turn == 2)
    {
      printf("Enter Your Move (R/C): ");
      scanf("%d %d", &r, &c);
      r--; c--;
    }
    else
    {
      height = 1;
      recursive();
      r = bestX;
      c = bestY;
    } 
    cb[r][c] = turn; count++;

    if(turn == 1) turn = 2;
    else turn = 1;

    printTable(r, c);
    printf("%d Move: (%d, %d)\n", turn, r+1, c+1);
    int win = checkWin();
    if(win == 1)
    {
      printf("YOU ARE SUCH A LOSER, U LOST TO RETARDED BOT \"ALEX\", U R FOREVER CANCELED!!!");
      break;
    }
    else if(win == 2)
    {
      printf("YOU WIN!!!!!");
      break;
    }
  }
  
}