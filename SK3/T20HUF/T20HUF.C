#include <conio.h>
#include <stdio.h>

#include "HUF.H"

void main()
{
  Stat("MY.TXT");
  Stat("X:\\TXT\\ORWELL.TXT");
  Stat("X:\\TXT\\CHEHOV.TXT");
  _getch();
}

/*int main( int argc, char *argv[] )
{
  char ch;
  if (argc == 1)
  {
    printf("c - compress"
           "d - decompress"
           "s - state");
    scanf("%c", &ch);
    argv[1][0] = ch;
  }
  else
    if (argv[1][0] == 'c')
      Compress(argv[3], argv[2]);
    else if (argv[1][0] == 'd')
      Decompress(argv[3], argv[2]);
    else if (argv[1][0] == 's')
      Stat(argv[2]);
    else
      printf("Unrecognized switch\n");
  return 0;
}*/
