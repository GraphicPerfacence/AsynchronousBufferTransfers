//
//  Subdivision.hpp
//  openGLTest
//
//  Created by xt on 17/12/9.
//  Copyright © 2017年 xt. All rights reserved.
//

#ifndef Subdivision_hpp
#define Subdivision_hpp

#include <vector>
#include "base/defType.hpp"

namespace Util
{
    class Subdivision
    {
        public:
            static void subdivisionSphere(std::vector<V3f>&,std::vector<unsigned int> &,
                                          std::vector<V3f>&,short level = 3);
    };
}

#endif /* Subdivision_hpp */
