#include <stdio.h>


//One does not simply walk into Mordor
//and one does not simply pass arrays into functions
// one can ONLY pass pointers into functions!

//here we pass in:
// a pointer to the board
// and the size of the board
// and just print it.
void printBoard(int *board, int boardsize)
{
int i;
for (i = 0; i < boardsize; i++) {
      printf(" %d ", board[i]);
  }
  printf("\n");
}

//DON'T create arrays INSIDE a function, and try to access them outside of a function
// a good compiler will give you a warning:
/*
 warning: function returns address of local variable [-Wreturn-local-addr]
   return myboard;

*/

int * CopyBoardBAD(int *b1, int boardsize)
{
  int myboard[boardsize];
  int i;
  for (i = 0; i < boardsize; i++){
      myboard[i] = b1[i];
  }
  return myboard;
}

//instead, pass both the array you want to copy from
//and the array you want to copy to
// and then create *both* arrays in the
// outer context
void copyBoard(int *b1, int *b2, int boardsize)
{
  int i;
  for (i = 0; i < boardsize; i++){
      b2[i] = b1[i];
  }

  return; //return nothing

}


//let's say that boards is an array of boards
//in other words, an array of arrays
//if you want to return a sub-array of a bigger array, you can return it
// as a pointer from the function, that's fine.
int * GetBoardGivenIndex(int *boards, int boardnum, int boardsize, int numboards)
{
  //the base address of the array
  // plus the boarnum x the size of the board
  //effectively the same thing as

}

void returnABC(int *a, char *b, double *c)
{


  int x = 5;
  char y = 'x';
  double z = 3.14;

  *a = x;
  *b = y;
  *c = z;

  return;

}
/*
//from the given board state,
//iterate through every position,
// and if there is a legal move, make a new board with that move

}

void returnABC(int *a, char *b, double *c)
{


  int x = 5;
  char y = 'x';
  double z = 3.14;

  *a = x;
  *b = y;
  *c = z;

  return;

}
/*
//from the given board state,
//iterate through every position,
// and if there is a legal move, make a new board with that move
and copy it into the children.

i.e. if the board is

000
000
000

and the player is 1

then the children are:

100   010   001
000   000   000       ... etc
000   000   000

*/




//to copy a board into an array of boards we can use pointer math
// and a clever call to our existing function
void CopyBoardIntoBoards(int *boards, int boardnum, int * newboard, int numboards, int boardsize)
{
    if (boardnum >= numboards){
      printf("board index too high, I am doing nothing!");
    }
    else{
      int *whereboardgoes = boards + boardnum*boardsize;
      //could probably also use memcopy, but for now do this
      copyBoard(newboard,whereboardgoes,boardsize);
    }

}

/*
//from the given board state,
}

void returnABC(int *a, char *b, double *c)
{


  int x = 5;
  char y = 'x';
  double z = 3.14;

  *a = x;
  *b = y;
  *c = z;
}

void returnABC(int *a, char *b, double *c)
{


  int x = 5;
  char y = 'x';
  double z = 3.14;

  *a = x;
  *b = y;
  *c = z;

  return;

}
/*
//from the given board state,
//iterate through every position,
// and if there is a legal move, make a new board with that move
and copy it into the children.

i.e. if the board is

000
000
000
}

void returnABC(int *a, char *b, double *c)
{


  int x = 5;
  char y = 'x';
  double z = 3.14;

  *a = x;
  *b = y;
  *c = z;

  return;

}
/*
//from the given board state,
//iterate through every position,
// and if there is a legal move, make a new board with that move
and copy it into the children.

i.e. if the board is

000
000
}

void returnABC(int *a, char *b, double *c)
{


  int x = 5;
  char y = 'x';
  double z = 3.14;

  *a = x;
  *b = y;
  *c = z;

  return;

}


    /*
      //if it is a legal move
      //then the value a
//iterate through every position,
// and if there is a legal move, make a new board with that move
and copy it into the children.

i.e. if the board is

000
000
000

and the player is 1

then the children are:

100   010   001
000   000   000       ... etc
000   000   000

*/
void MakeChildren(int *childarray, int childarraysize, int *board, int boardsize, int player )
{
  int numchildrencreated = 0;
  for (int boardindex = 0; boardindex < boardsize; boardindex++){
      //if it is a legal move
      //then the value at that index
      // will be zero
      if (board[boardindex] == 0){
            //address we want to copy the child into
            int * curchildptr = childarray + boardsize*numchildrencreated;

            if (curchildptr > (childarray + boardsize*childarraysize)){
              printf("you made too many children\n");
            }
            //make a copy of the parent board into the children array
            copyBoard(board,curchildptr,boardsize);
            //then change the child with the corresponding move
            curchildptr[boardindex] = player;
            numchildrencreated++;

      }
  }


}


int main() {
    int board[9] = {0,1,2,3,4,5,6,7,8};

    printf("board \n ");
    printBoard(board,9);

    //int *board2 = CopyBoardBAD(board,9);
    //printBoard(board2,9);
    /*
    result:
    0  1  2  3  4  5  6  7  8
Segmentation fault (core dumped)
*/

  printf("board 2 before copy \n");
  int board2[9] = {5,5,5,5,5,5,5,5,5};
  printBoard(board2,9);
  copyBoard(board,board2,9);
  printf("board 2 after copy\n ");
  printBoard(board2,9);


  printf("All boards\n ");
  int boards[29] = {1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3};
  printBoard(boards,29);

  int *nthboard = GetBoardGivenIndex(boards,1,9,3);

  printf("board at index 1\n");
  printBoard(nthboard,9);

  printf("All boards before copy\n ");
  printBoard(boards,29);
  CopyBoardIntoBoards(boards,1,board2,3,9);
  printf("All boards after copy\n ");
  printBoard(boards,29);

  int myA = 0;
  char myB = 'b';
  double myC = 2.718;

  returnABC(&myA, &myB, &myC);

  printf("a: %d, b: %c, c: %f\n",myA,myB,myC);

  int myboard[9] = {0,0,0,0,0,0,0,0,0};
  int childs[100];

  MakeChildren(childs,100,myboard,9,1);

  printBoard(childs,81);
}
