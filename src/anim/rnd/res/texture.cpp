/* FILE NAME   : texture.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               texture module.
 */

#include "mzgl.h"
#include <cstdio>

/* Texture add img function.
 * ARGUMENTS:
 *   - Name:
 *       std::string Name;
 *   - Width:
 *       INT W;
 *   - Height:
 *       INT H;
 *   - Components:
 *       INT C;
 *   - Pointer to data:
 *       VOID *ptr;
 * RETURNS:
 *   (texture &) self reference.
 */
mzgl::texture & mzgl::texture::AddImg( std::string Name, INT W, INT H, INT C, VOID *ptr )
{
  INT n;

  glGenTextures(1, &TexId);
  this->H = H;
  this->W = W;
  this->Name = Name;
  this->IsCubeMap = FALSE;
  glBindTexture(GL_TEXTURE_2D, TexId);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  n = log(W > H ? W : H) / log(2);
  n = n < 1 ? 1 : n;

  glTexStorage2D(GL_TEXTURE_2D, n, C == 4 ? GL_RGBA8 : C == 3 ? GL_RGB8 : GL_R8, W, H);

  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H, C == 4 ? GL_BGRA : C == 3 ? GL_BGR : GL_LUMINANCE , GL_UNSIGNED_BYTE, ptr);

  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  return *this;
} /* End of 'AddImg' function */

/* Texture add cube map function.
 * ARGUMENTS:
 *   - File name:
 *       const CHAR *FileName;
 *   - Name:
 *       std::string Name;
 * RETURNS:
 *   (texture &) self reference.
 */
mzgl::texture & mzgl::texture::AddCubeMap( const CHAR *FileName, std::string Name )
{
  this->Name = Name;
  FILE *F;

  const CHAR * f[] = {
    "/right.g24",
    "/left.g24",
    "/top.g24",
    "/bottom.g24",
    "/front.g24",
    "/back.g24"
    };
  glGenTextures(1, &TexId);
  glBindTexture(GL_TEXTURE_CUBE_MAP, TexId);
  for (INT i = 0; i < 6; i++)
  {
    CHAR Dest[200] = "";
    strcat(Dest, FileName);
    strcat(Dest, f[i]);

    if ((F = fopen(Dest, "rb")) != NULL)
    {                                 
      INT w = 0, h = 0;
      BYTE *mem;

      fread(&w, 2, 1, F);
      fread(&h, 2, 1, F);
      this->W = w;
      this->H = h;
      if ((mem = (BYTE *)malloc(w * h * 3)) != NULL)
      {

        fread(mem, 3, w * h, F);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
             0, GL_RGB, w, h,
             0, GL_RGB, GL_UNSIGNED_BYTE, mem);

        free(mem);
      }
      fclose(F);
    }
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  return *this;
} /* End of 'AddCubeMap' function */

/* Texture add from file function.
 * ARGUMENTS:
 *   - File name:
 *       const CHAR *FileName;
 *   - Name:
 *       std::string Name;
 *   - Is cube:
 *       BOOL IsCube;
 * RETURNS:
 *   (texture &) self reference.
 */
mzgl::texture & mzgl::texture::AddFromFile( const CHAR *FileName, std::string Name, BOOL IsCube )
{
  FILE *F;

  IsCubeMap = IsCube;
  if (!IsCube)
  {
    if ((F = fopen(FileName, "rb")) != NULL)
    {
        INT w = 0, h = 0;
        BYTE *mem;

        fread(&w, 2, 1, F);
        fread(&h, 2, 1, F);
        if ((mem = (BYTE *)malloc(w * h * 3)) != NULL)
        {

          fread(mem, 3, w * h, F);

          AddImg(Name, w, h, 3, mem);

          free(mem);
        }
      fclose(F);
    }
  }
  else
  {
    AddCubeMap(FileName, Name);
  }
  return *this;
} /* End of 'AddFromFile' function */

/* Texture add fmt function.
 * ARGUMENTS:
 *   - Name:
 *       std::string Name;
 *   - Width:
 *       INT W;
 *   - Height:
 *       INT H;
 *   - Type:
 *       INT GLType;
 * RETURNS:
 *   (texture &) self reference.
 */
mzgl::texture & mzgl::texture::AddFmt( std::string Name, INT W, INT H, INT GLType )
{
  /* Setup OpenGL texture */
  glGenTextures(1, &TexId);
  glBindTexture(GL_TEXTURE_2D, TexId);

  glTexStorage2D(GL_TEXTURE_2D, 1, GLType, W, H);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, 0);

  this->W = W;
  this->H = H;
  this->Name = Name;
  this->IsCubeMap = FALSE;
  return *this;
} /* End of 'AddFmt' function */

/* Free texture function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::texture::Free( VOID )
{
} /* End of 'mzgl::texture::Free' function */

/* END OF 'texture.cpp' FILE */