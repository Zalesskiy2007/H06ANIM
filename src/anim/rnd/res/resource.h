/* FILE NAME   : res_manager.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Resources manager handle module.
 */

#ifndef __res_manager_h_
#define __res_manager_h_

#include "def.h"

#include "../render.h"

/* Project namespace */
namespace mzgl
{
  /* Base resource class (should be base class for all resources) */
  class resource
  {
    template<typename entry_type, typename index_type>
      friend class resource_manager;
  protected:
    // Pointer to render
    render *Rnd {};
  }; /* End of 'resource' class */
} /* end of 'mzgl' namespace */  

#endif /* __res_manager_h_ */

/* END OF 'res_manager.h' FILE */
