//
//  Callback.h
//  openGLTest
//
//  Created by xt on 17/8/29.
//  Copyright © 2017年 xt. All rights reserved.
//

#ifndef OPENGL_CALLBACK_H
#define OPENGL_CALLBACK_H

template<class PARAM>
struct ICallback
{
    virtual void execute(PARAM) = 0;
};



#endif /* Header_h */
