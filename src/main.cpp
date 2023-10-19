/* FILE NAME   : main.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Main project file.
 */

#include "mzgl.h"

 /* The main program function.
  * ARGUMENTS:
  *   - handle of application instance:
  *       HINSTANCE hInstance;
  *   - dummy handle of previous application instance (not used):
  *       HINSTANCE hPrevInstance;
  *   - command line string:
  *       CHAR *CmdLine;
  *   - show window command parameter (see SW_***):
  *       INT CmdShow;
  * RETURNS:
  *   (INT) Error level for operation system (0 for success).
  */
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  CHAR* CmdLine, INT ShowCmd)
{                                        
  SetDbgMemHooks();

  mzgl::anim *MyAnim = mzgl::anim::Get();

  *MyAnim << "Skybox unit";
  *MyAnim << "Control unit";

  //*MyAnim << "Test unit";
  *MyAnim << "Model unit";
  *MyAnim << "Floor unit";
  MyAnim->Run();
} /* End of 'WinMain' function */

/* END OF 'main.cpp' FILE */