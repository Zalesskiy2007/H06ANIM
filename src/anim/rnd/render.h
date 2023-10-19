/* FILE NAME   : render.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 31.07.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Render system module.
 *               Render handle module.
 */

#ifndef __render_h_
#define __render_h_

#include "def.h"

#include "anim/rnd/res/shader.h"
#include "anim/rnd/res/mtl_pattern.h"
#include "anim/rnd/res/material.h"
#include "anim/rnd/res/primitives.h"
#include "anim/rnd/res/font.h"
#include "anim/rnd/res/target.h"
#include "anim/rnd/res/light.h"

 /* Project namespace */
namespace mzgl
{
   /* Primitive data representation type */
  struct prim_data
  {
    matr MatrWVP;
    matr MatrW;
    matr MatrWInvTrans;
  }; /* End of 'prim_data' class */

  /* Render representation type */
  class render : 
    public shader_manager, public material_pattern_manager,
    public material_manager, public primitive_manager, public texture_manager, public font_manager,
    public target_manager, public light_manager
  {
  private:
    HWND& hWnd;     // Render reference to window handle
    HDC hDC;        // Render window device context
    HGLRC hGLRC;    // Render OpenGL context handle

  public:
    camera Camera;   // Camera type
    prim_data Prim_data;  // Primitive data 
    target *Trg;
    light *Lgh;

    /* Render default constructor */
    render(HWND& hNewWnd) : hWnd(hNewWnd)
    {
    }
    /* Render default destructor */
    ~render(VOID)
    {
    }

    BOOL IsInit;  // Flag for initialization render

    /* Render system initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init(VOID);

    /* Render system close (deinitialization) function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close(VOID);

    /* Render system resize function.
     * ARGUMENTS:
     *   - window new size:
     *       INT W, INT H;
     * RETURNS: None.
     */
    VOID Resize(INT NewW, INT NewH);

    /* Start render frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameStart(VOID);

    /* Finish render frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameEnd(VOID);

    /* Primitive draw function.
     * ARGUMENTS:
     *   - primitive pointer:
     *       prim *Pr;
     *   - transformation matrix:
     *       const matr &World;
     * RETURNS: None.
     */
    VOID Draw(const prim* Pr, const matr& World = matr().Identity());

    /* Primitive load function.
     * ARGUMENTS:
     *   - Filename:
     *       const CHAR *Fn;
     *   - Material:
     *       material *Mat;
     * RETURNS:
     *   (prim *) created primitive;
     */
    prim * LoadModel( const CHAR *Fn, material *Mat );

  }; /* End of 'render' class */

} /* end of 'mzgl' namespace */

#endif /* __render_h_ */

/* END OF 'render.h' FILE */