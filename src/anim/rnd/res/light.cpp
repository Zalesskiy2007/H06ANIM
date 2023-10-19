/* FILE NAME   : light.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               light module.
 */

#include "mzgl.h"

/* Light init function.
 * ARGUMENTS:
 *   - Name:
 *       std::string Name;
 * RETURNS:
 *   (light &) self reference.
 */
mzgl::light & mzgl::light::LightInit( std::string Name )
{
  this->Name = Name;
  LightDir = vec3(-5, 8, -5).Normalize();
  LightColor = vec3(1, 1, 1);

  glGenFramebuffers(1, &ShadowFBO);
  glBindFramebuffer(GL_FRAMEBUFFER, ShadowFBO);

  ShadowTex = mzgl::anim::Get()->TxtLoadFmt(Name + "Shadow Map", SHADOW_MAP_SIZE, SHADOW_MAP_SIZE, GL_DEPTH_COMPONENT24);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ShadowTex->TexId, 0);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glActiveTexture(GL_TEXTURE0 + 8);
  glBindTexture(GL_TEXTURE_2D, ShadowTex->TexId);

  return *this;
} /* End of 'LightInit' function */

/* Light shadow function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::light::LightShadow( VOID )
{
  FLT size = 100, far_dist = 300, clear_depth = 1;
  mzgl::anim *Ani = mzgl::anim::Get();
  vec3 sclc = Ani->Camera.Loc, scat = Ani->Camera.At, scup = Ani->Camera.Up;
  matr scp = Ani->Camera.MatrProj;

  Ani->Camera.MatrProj = matr().Ortho(-size, size, -size, size, -size * 8, far_dist);
  Ani->Camera.CamSet(Ani->Camera.At, Ani->Camera.At - LightDir, vec3(0, 1, 0));
  ShadowMatr = Ani->Camera.MatrVP;

  glBindFramebuffer(GL_FRAMEBUFFER, ShadowFBO);

  glClearBufferfv(GL_DEPTH, 0, &clear_depth);
  glViewport(0, 0, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(4, 4);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  Ani->IsShading = TRUE;
  Ani->Units.Walk([Ani](unit* Uni)
    {
      Uni->Render(Ani);
    });
  Ani->IsShading = FALSE;
  glDisable(GL_CULL_FACE);
  glDisable(GL_POLYGON_OFFSET_FILL);
  glFinish();

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  Ani->Camera.MatrProj = scp;
  Ani->Camera.CamSet(sclc, scat, scup);
} /* End of 'LightShadow' function */

/* Free light function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::light::Free( VOID )
{
  glBindFramebuffer(GL_FRAMEBUFFER, ShadowFBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDeleteFramebuffers(1, &ShadowFBO);
} /* End of 'mzgl::light::Free' function */

/* END OF 'light.cpp' FILE */