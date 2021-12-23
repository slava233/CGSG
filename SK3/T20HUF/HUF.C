#include <string.h>
#include <stdio.h>

#include "HUF.H"

void Stat( char *FileName )
{
  FILE *F;
  int i, j, total = 0, unpack;
  double ratio;
  if ((F = fopen(FileName, "rb")) == NULL)
  {
    printf("File '%s' is not found\n", FileName);
    return;
  }
  CountFreq(F);
  for (i = 0; i < 256; i++)
    if (Freq[i] > 0)
      PlaceNode(i, Freq[i], NULL, NULL);
  while (NumOfNodes > 1)
  {
    TREE *Last = Nodes[--NumOfNodes], *PreLast = Nodes[--NumOfNodes];
    PlaceNode(' ', Last->Freq + PreLast->Freq, PreLast, Last);
  }
  /*DrawTree(Nodes[0], 0);*/
  CurCode.Len = 0;
  BuildCodes(Nodes[0]);
  for (i = 0; i < 256; i++)
    total += NewCodes[i].Len * Freq[i];
  unpack = Nodes[0]->Freq * 8;
  ratio = (double)unpack / total;
  printf("%f\n", ratio);
  printf("\n\n\n");
  for (i = 0; i < 256; i++)
    if (Freq[i] > 0)
    {
      printf("%c (%3d) [0x%02X] <%5ld> :", i < ' ' ? '.' : i, i, i, Freq[i]);
      for (j = 0; j < NewCodes[i].Len; j++)
        printf("%i", NewCodes[i].Code[j]);
      printf("\n");
    }
  printf("\n\n\n");
  fclose(F);
}

void DrawTree( TREE *T, int Level )
{
  if (T != NULL)
  {
    DrawTree(T->Left, Level + 1);
    printf("\n%*c%d\n", Level * 5, ' ', T->Freq);
    DrawTree(T->Right, Level + 1);
  }
}

void CountFreq( FILE *F )
{
  int i;
  memset(Freq, 0, sizeof Freq);
  while ((i = fgetc(F)) != EOF)
    Freq[i]++;
}

void PlaceNode( char Ch, long Freq, TREE *L, TREE *R )
{
  int i;
  TREE *T;
  if ((T = malloc(sizeof(TREE))) == NULL)
    return;
  T->Ch = Ch;
  T->Freq = Freq;
  T->Left = L;
  T->Right = R;
  i = NumOfNodes - 1;
  while (i >= 0 && T->Freq > Nodes[i]->Freq)
    Nodes[i + 1] = Nodes[i], i--;
  Nodes[i + 1] = T;
  NumOfNodes++;
}

void BuildCodes( TREE *T )
{
  if (T != NULL)
  {
    CurCode.Code[CurCode.Len] = 0;
    CurCode.Len++;
    BuildCodes(T->Left);
    CurCode.Len--;
    CurCode.Code[CurCode.Len] = 1;
    CurCode.Len++;
    BuildCodes(T->Right);
    CurCode.Len--;
    if (T->Left == NULL && T->Right == NULL)
      NewCodes[(unsigned char)T->Ch] = CurCode;
    return;
  }
}




