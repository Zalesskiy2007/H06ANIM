/* FILE NAME   : texture.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               texture's and texture's manager handle module.
 */

#ifndef __texture_h_
#define __texture_h_

#include "def.h"

#include "res_manager.h"

#include <iostream>

/* Project namespace */
namespace mzgl
{
  /* texture representation type */
  class texture
  {
    friend class render;
  public:
    std::string Name;          // texture name
    INT W, H;
    UINT TexId;
    BOOL IsCubeMap;
    /* texture default constructor */
    texture( VOID )
    {
    } /* End of 'texture' function */

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
    texture & AddImg( std::string Name, INT W, INT H, INT C, VOID *ptr );

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
    texture & AddFmt( std::string Name, INT W, INT H, INT GLType );

    /* Texture add cube map function.
     * ARGUMENTS:
     *   - File name:
     *       const CHAR *FileName;
     *   - Name:
     *       std::string Name;
     * RETURNS:
     *   (texture &) self reference.
     */
    texture & AddCubeMap( const CHAR * FileName, std::string Name );

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
    texture & AddFromFile( const CHAR *FileName, std::string Name, BOOL IsCube );

        
    /* Free texture function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

  }; /* End of 'texture' class */
  
  /* texture manager representation type */
  class texture_manager : public resource_manager<texture, std::string>
  {
  public:
    /* Texture load function.
     * ARGUMENTS:
     *   - File name:
     *       const CHAR *FileName;
     *   - Name:
     *       std::string Name;
     *   - Is cube:
     *       BOOL IsC;
     * RETURNS:
     *   (texture *) pointer to texture.
     */
    texture * TxtLoad( const CHAR *FileName, std::string Name, BOOL IsC )
    {
      return resource_manager::Add(texture().AddFromFile(FileName, Name, IsC));
    } /* End of 'TxtLoad' function */

    /* Texture load img function.
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
     *   (texture *) pointer to texture.
     */
    texture * TxtLoadImg( std::string Name, INT W, INT H, INT C, VOID *ptr )
    {
      return resource_manager::Add(texture().AddImg(Name, W, H, C, ptr));
    } /* End of 'TxtLoadImg' function */

    /* Texture load fmt function.
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
     *   (texture *) pointer to texture.
     */
    texture * TxtLoadFmt( std::string Name, INT W, INT H, INT GLType )
    {
      return resource_manager::Add(texture().AddFmt(Name, W, H, GLType));
    } /* End of 'TxtLoadFmt' function */

    /* Free texture function.
     * ARGUMENTS:
     *   - texture pointer:
     *       texture *Mtl;
     * RETURNS: None.
     */
    VOID TxtFree( texture *Txt )
    {
      resource_manager::Delete(Txt);
    } /* End of 'TxtFree' function */
  }; /* End of 'texture_manager' class */

} /* end of 'mzgl' namespace */

#endif /* __texture_h_ */

/* END OF 'texture.h' FILE */