/* FILE NAME   : model.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               model unit.
 */

#include "mzgl.h"

/* model_unit unit representation type */
class model_unit : public mzgl::unit
{
public:
  mzgl::prim *pr;
  /* model_unit constructor */
  model_unit(mzgl::anim *MyAnim)
  {
    mzgl::material_pattern *MtlP = MyAnim->MtlPatCreate("MtlPM", 16, "default");
    mzgl::material *Mtl = MyAnim->MtlCreate("MtlM", mzgl::vec3(0.3, 0, 0), 
                                                                    mzgl::vec3(0.2, 0.2, 0.2), mzgl::vec3(1, 1, 1),
                                                                    32, 1, MtlP);

    pr = MyAnim->LoadModel("bin/models/cow.obj", Mtl);
  } /* End of 'model_unit' constructor */

  /* Virtual render function.
   * ARGUMENTS:
   *   - animation context:
   *       anim *Ani;
   * RETURNS: None.
   */
  VOID Render(mzgl::anim* Ani) override
  {
    Ani->Draw(pr, mzgl::matr().Scale(mzgl::vec3(0.2, 0.2, 0.2)) * mzgl::matr().RotateY(sin(Ani->Time * 2) * 300));
  } /* End of 'Render' function */

  /* Virtual response function.
   * ARGUMENTS:
   *   - animation context:
   *       anim *Ani;
   * RETURNS: None.
   */
  VOID Response(mzgl::anim* Ani) override
  {
  } /* End of 'Response' function */
}; /* End of 'model_unit' class */

static mzgl::anim::unit_register<model_unit> _("Model unit");

/* END OF 'model.cpp' FILE */