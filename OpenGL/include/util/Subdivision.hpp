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
#include "geometry/Ellipsoid.h"

namespace Util
{
    class Subdivision
    {

        public:
            enum    TYPE
            {
                TETRAHEDRON,
                CUBMAP,
                GEOGRAPHICGRID

            };
        public:			

        static void subdivisionSphere(TYPE,
                                          std::vector<V3f>*,
                                          std::vector<unsigned int> &,
                                          std::vector<V3f>*,
                                          std::vector<V2f>*,short level = 3);

        static void subdivisionElliposid(Ellipsoid<float> *,TYPE,
                                  std::vector<V3f>*,
                                  std::vector<unsigned int> &,
                                  std::vector<V3f>*,
                                  std::vector<V2f>*,short level = 3);


        static V2f computeTextureCoordinate(const V3f&);

        static short numberOfSlicePartitions;
        static short numberOfStackPartitions;

    };
}

#endif /* Subdivision_hpp */
