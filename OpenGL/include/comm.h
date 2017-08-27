//
//  comm.h
//  OpenGL
//
//  Created by xt on 15/7/24.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__comm__
#define __OpenGL__comm__


#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>

static bool isGlewInit = false;

///////////////////////////////////////////////////////////////////
// common helper fun
///////////////////////////////////////////////////////////////////
unsigned int	stringToUint(const std::string &source);
int				stringToInt(const std::string &source);
float			stringToFloat(const std::string &source);


template<class T>
inline std::string toString(const T& input) {
    std::ostringstream converter;
    converter << input;
    return converter.str();
}
///////////////////////////////////////////////////////////////////	
//test
///////////////////////////////////////////////////////////////////
void			testOpenGl();

///////////////////////////////////////////////////////////////////
//          INIT GLEW GLFW

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool			initGlew();

bool            initGlfw(bool flag = true);

#endif /* defined(__OpenGL__comm__) */
