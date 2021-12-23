/* FILE NAME: RNDBASE.C
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: Animation system
 *          Rendering system
 *          Base shaders function
 */

#include <stdio.h>

#include "rnd.h"

#define SK3_MAX_SHADERS 30

/* Shader resource table and size */
SK3SHADER SK3_RndShaders[SK3_RESOURCE_TABLE_SIZE];
INT SK3_RndShadersSize;

/* Save text to log file function.
 * ARGUMENTS:
 *   - shader file name:
 *       CHAR *FileName;
 *   - text 1 to save:
 *       CHAR *Stage;
 *   - text 2 to save:
 *       CHAR *Text;
 * RETURNS: None.
 */
static VOID SK3_RndShaderLog( CHAR *FileName, CHAR *Stage, CHAR *Text )
{
  FILE *F;

  if ((F = fopen("SK3{SHAD}30.LOG", "a")) != NULL)
  {
    fprintf(F, "%s\n  %s: %s\n", FileName, Stage, Text);
    fclose(F);
  }
} /* End of 'SK3_RndShaderLog' function */

/* Text file load to memory function.
 * ARGUMENTS:
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) load text or NULL if error is occured.
 */
static CHAR * SK3_RndShaderLoadTextFile( CHAR *FileName )
{
  FILE *F;
  INT flen;
  CHAR *text;

  if ((F = fopen(FileName, "r")) == NULL)
    return NULL;

  /* Obtain file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);

  /* Allocate memory */
  if ((text = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }
  memset(text, 0, flen + 1);

  /* Read text */
  fseek(F, 0, SEEK_SET);
  fread(text, 1, flen, F);

  fclose(F);
  return text;
} /* End of 'SK3_RndShaderLoadTextFile' function */

/* Load shader program function.
 * ARGUMENTS:
 *   - shader files prefix (directory):
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (UINT) shader program index or 0 if error is occured.
 */
UINT SK3_RndShaderLoad( CHAR *FileNamePrefix )
{
  INT
    i, res,
    shd_type[] =
    {
      GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER,
      GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER
    };
  CHAR *suff[] = {"VERT", "CTRL", "EVAL", "GEOM", "FRAG"};
  INT NS = sizeof(suff) / sizeof(suff[0]);
  UINT prg = 0, shd[sizeof(suff) / sizeof(suff[0])] = {0};
  BOOL isok = TRUE;
  CHAR *txt;
  static CHAR buf[500];

  /* Load shaders */
  for (i = 0; isok && i < NS; i++)
  {
    /* Load text file */
    sprintf(buf, "%s\\%s.GLSL", FileNamePrefix, suff[i]);
    if ((txt = SK3_RndShaderLoadTextFile(buf)) == NULL)
      continue;
    /* Create shader */
    if ((shd[i] = glCreateShader(shd_type[i])) == 0)
    {
      free(txt);
      SK3_RndShaderLog(FileNamePrefix, suff[i], "Error create shader");
      isok = FALSE;
      break;
    }
    /* Attach text to shader  */
    glShaderSource(shd[i], 1, &txt, NULL);
    free(txt);

    /* Compile shader */
    glCompileShader(shd[i]);
    glGetShaderiv(shd[i], GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shd[i], sizeof(buf), &res, buf);
      SK3_RndShaderLog(FileNamePrefix, suff[i], buf);
      isok = FALSE;
      break;
    }
  }

  /* Create program */
  if (isok)
    if ((prg = glCreateProgram()) == 0)
      isok = FALSE;
    else
    {
      /* Attach shaders to program */
      for (i = 0; i < NS; i++)
        if (shd[i] != 0)
          glAttachShader(prg, shd[i]);

      /* Link program */
      glLinkProgram(prg);
      glGetProgramiv(shd[i], GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(prg, sizeof(buf), &res, buf);
        SK3_RndShaderLog(FileNamePrefix, "LINK", buf);
        isok = FALSE;
      }
    }

  /* Error handle */
  if (!isok)
  {
    for (i = 0; i < NS; i++)
      if (shd[i] != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shd[i]);
        glDeleteShader(shd[i]);
      }
    if (prg != 0)
      glDeleteProgram(prg);
    return 0;
  }
  return prg;
} /* End of 'SK3_RndShaderLoad' function */

/* Shader program free function.
 * ARGUMENTS:
 *   - shader program Id:
 *       UINT Prg;
 * RETURNS: None.
 */
VOID SK3_RndShaderFree( UINT Prg )
{
  UINT i, n = SK3_MAX_SHADERS, shds[5];

  if (Prg == 0)
    return;
  /* Obtain program shaders count */
  glGetAttachedShaders(Prg, 5, &n, shds);
  for (i = 0; i < n; i++)
  {
    glDetachShader(Prg, shds[i]);
    glDeleteShader(shds[i]);
  }
  glDeleteProgram(Prg);
} /* End of 'SK3_RndShaderFree' function */

/* Add shader program from file function.
 * ARGUMENTS:
 *   - shader files prefix (directory):
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) shader table index or -1 if error is occured.
 */
INT SK3_RndShaderAdd( CHAR *FileNamePrefix )
{
  INT i;
  static CHAR Buf[1000];

  /* Look for exists shader */
  for (i = 0; i < SK3_RndShadersSize; i++)
    if (strcmp(SK3_RndShaders[i].Name, FileNamePrefix) == 0)
      return i;

  if (i >= SK3_RESOURCE_TABLE_SIZE)
    return -1;

  sprintf(Buf, "BIN/SHADERS/%s", FileNamePrefix);
  SK3_RndShaders[SK3_RndShadersSize].PrgNo = SK3_RndShaderLoad(Buf);
  strncpy(SK3_RndShaders[SK3_RndShadersSize].Name, FileNamePrefix, SK3_MATERIAL_NAME_SIZE - 1);
  return SK3_RndShadersSize++;
} /* End of 'SK3_RndShaderAdd' function */

/* Update all shaders from store table function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID SK3_RndShadersUpdate( VOID )
{
  INT i;
  static CHAR Buf[1000];

  for (i = 0; i < SK3_RndShadersSize; i++)
  {
    SK3_RndShaderFree(SK3_RndShaders[i].PrgNo);
    sprintf(Buf, "BIN/SHADERS/%s", SK3_RndShaders[i].Name);
    SK3_RndShaders[i].PrgNo = SK3_RndShaderLoad(Buf);
  }
} /* End of 'SK3_RndShadersUpdate' function */

/* Remove shader program from resource table function.
 * ARGUMENTS:
 *   - shader table index:
 *       INT ShdNo;
 * RETURNS: None.
 */
VOID SK3_RndShaderDelete( INT ShdNo )
{
  if (ShdNo < 0 || ShdNo >= SK3_RndShadersSize)
    return;
  SK3_RndShaderFree(SK3_RndShaders[ShdNo].PrgNo);
  memset(&SK3_RndShaders[ShdNo], 0, sizeof(SK3SHADER));
} /* End of 'SK3_RndShaderDelete' function */

/* END OF 'RNDSHD.C' FILE */
