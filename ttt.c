#include <stdio.h>
#include <stdlib.h>

void print_board(int size, char** board);

int main(){
  int size, i, j, row, col, win;
  char outputPlay;
  char** board;
  printf("Board Size (3..N):\n");
  scanf("%d", &size);
  if(size < 3){
    printf("Inappropriate value. Goodbye.\n");
    return 0;
  }
  board = (char**) malloc(size * sizeof(char*));
  for(i = 0; i < size; i++){
    board[i] = (char*) malloc(size * sizeof(char));
  }
  for(i = 0; i < size; i++){//filling out the board with spaces to start
    for(j = 0; j < size; j++){
      board [i][j] = ' ';
    }
  }
  //board[0][0] = 'O';
  //board[1][1] = 'O';
  //board[2][2] = 'O';
  //board[2][1] = 'X';
  //board[0][1] = 'X';
  //win = check_win(size, board);
  //printf("%d\n", win);
  printf("Output Play (y/n):\n");
  scanf(" %c", &outputPlay);
  int a;
  while ( (a = getchar()) != '\n' && a != EOF ) { }
  if((outputPlay != 'y') && (outputPlay != 'n')){
    printf("Inappropriate value. Goodbye.\n");
    return 0;
  }
  printf("You entered %d %c.\nStarting game with %d x %d board.\nEach player should enter\na row and col num (eg: 2 0).\nPlayer 1:\n", size, outputPlay, size, size);
  int correct = 0;
  while(correct == 0){
    scanf("%d %d", &row, &col);
    int b;
    while ( (b = getchar()) != '\n' && b != EOF ) { }
    if((row <= size) && (col <= size)){
      correct = 1;
    }
    else{
      printf("Incorrect value, try again.\nPlayer 1:\n");
    }
  }
  board[row][col] = 'O';
  while((row != -1) && (col != -1)){
    printf("Player 1 entered %d %d.\n", row, col);
    if(outputPlay == 'y'){
      print_board(size, board);
      win = check_win(size, board);
      //printf("%d", win);
    }
    if((check_win(size, board)) == 1){
      printf("Player 1 is the winner.\n");
      break;
    }
    else if(check_win(size, board) == -1){
      printf("Who wins?? Nobody!\n");
      break;
    }
    printf("Player 2:\n");
    correct = 0;
    while(correct == 0){
      scanf("%d %d", &row, &col);
      int c;
      while ( (c = getchar()) != '\n' && c != EOF ) { }
      if((row <= size) && (col <= size) && (board[row][col] == ' ')){
        correct = 1;
      }
      else{
          printf("Incorrect value, try again.\nPlayer 2:\n");
      }
    }
    board[row][col] = 'X';
    printf("Player 2 entered %d %d.\n", row, col);
    if(outputPlay == 'y'){
      print_board(size, board);
      win = check_win(size, board);
      //printf("%d", win);
    }
    if((check_win(size, board)) == 1){
      printf("Player 2 is the winner.\n");
      break;
    }
    else if(check_win(size, board) == -1){
      printf("Who wins?? Nobody!\n");
      break;
    }
    printf("Player 1:\n");
    correct = 0;
    while(correct == 0){
      scanf("%d %d", &row, &col);
      //printf("row: %d col: %d", row, col);
      int d;
      while ( (d = getchar()) != '\n' && d != EOF ) { }
      if((row <= size) && (col <= size) && (board[row][col] == ' ')){
        correct = 1;
      }
      else{
          printf("Incorrect value, try again.\nPlayer 1:\n");
      }
    }
    board[row][col] = 'O';
  }
  print_board(size, board);
  return 0;
}

void print_board(int size, char** board){
  int i, j;
  for(i = 0; i < size; i++){
    printf("-");
    for(j = 0; j < size; j++){
      printf("----");
    }
    printf("\n");
    for(j = 0; j < size; j++){
      printf("| %c ", board[i][j]);
    }
    printf("|\n");
  }
  printf("-");
  for(i = 0; i < size; i++){
    printf("----");
  }
  printf("\n");
}

int check_win(int size, char** board){
  int i, j, a, b;
  int result = 0;
  char current, next;

  //check horizontal
  for(i = 0; i < size; i++){
    if(result == 0){
      j = 2;
      current = board[i][0];
      next = board[i][1];
      while((current != ' ') && (j < size)){
        //printf("current: %c next: %c\n", current, next);
        if(current == next){
          current = next;
          next = board[i][j];
          if((j == (size - 1)) && (current == next)){
            //printf("test\n");
            result = 1;
            break;
          }
          j++;
        }
        else{
          result = 0;
          break;
        }
      }
    }
  }

  // check vertical
  if(result == 0){
    //printf("vertical check\n");
    for(i = 0; i < size; i++){
      if(result == 0){
        j = 2;
        current = board[0][i];
        next = board[1][i];
        while((current != ' ') && (j < size)){
          //printf("current: %c next: %c\n", current, next);
          if(current == next){
            current = next;
            next = board[j][i];
            if((j == (size - 1)) && (current == next)){
              //printf("test\n");
              result = 1;
              break;
            }
            j++;
          }
          else{
            result = 0;
            break;
          }
        }
      }
    }
    //printf("result: %d\n", result);
  }

  //check diagonal
  if(result == 0){
    //printf("diagonal 1 check\n");
    a = 0;
    b = 0;
    while((a < (size - 1)) && (b < (size - 1))){
      if((board[a][b] != ' ') && board[a][b] == board[a+1][b+1]){
        a++;
        b++;
        result = 1;
      }
      else{
        result = 0;
        break;
      }
    }
    //printf("diagonal 1 result: %d\n", result);
  }

  if(result == 0){
    //printf("diagonal 2 check\n");
    a = 0;
    while((size - 2 - a) >= 0){
      if((board[size - 1 - a][a] != ' ') && board[size - 1 - a][a] == board[size - 2 - a][a + 1]){
        a++;
        result = 1;
      }
      else{
        result = 0;
        break;
      }
    }
    //printf("diagonal 2 result: %d\n", result);
  }

  if(result == 0){
    result = -1;
    for(i = 0; i < size; i++){
      for(j = 0; j < size; j++){
        if(board[i][j] == ' '){
          result = 0;
        }
      }
    }
  }
  return result;
}
