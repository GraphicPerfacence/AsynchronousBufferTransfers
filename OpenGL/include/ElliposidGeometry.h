    //
    //  ElliposidGeometry.h
    //  openGLTest
    //
    //  Created by xt on 17/12/30.
    //  Copyright © 2017年 xt. All rights reserved.
    //

#ifndef ElliposidGeometry_h
#define ElliposidGeometry_h

namespace Util {


    class ElliposidGeometry
    {
    public:
    ElliposidGeometry();

    void    DrawElliposid();
    //private:

    void create();

    unsigned int _vertex_buffer;

    int         _subType;

    int         _indicesNum;
    };

}

#endif /* ElliposidGeometry_h */
