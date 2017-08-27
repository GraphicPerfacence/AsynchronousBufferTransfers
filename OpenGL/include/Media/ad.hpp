//
//  audo.hpp
//  openGLTest
//
//  Created by xt on 17/8/26.
//  Copyright © 2017年 xt. All rights reserved.
//

#ifndef __OpenGL__Audo_hpp
#define __OpenGL__Audo_hpp

#include <stdio.h>


class Audo
{
public:
    Audo();

   virtual bool                InitAudo();

   virtual bool                Update();
    
   virtual bool                ShutDown();

};

extern bool         InitAudo();

extern Audo *                         g_Audo;
#endif /* audo_hpp */
