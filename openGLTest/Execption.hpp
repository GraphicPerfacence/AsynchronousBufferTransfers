//
//  Execption.hpp
//  openGLTest
//
//  Created by xt on 17/8/27.
//  Copyright © 2017年 xt. All rights reserved.
//

#ifndef _Opengl_Execption_hpp
#define _Opengl_Execption_hpp

#include <stdio.h>
#include <exception>
#include <string>

class BaseException : public std::exception {
protected:
    std::string msg;
public:
    BaseException() { };
    BaseException(const std::string& vMsg) { msg = vMsg; };
    virtual const char *what() const throw() { return msg.c_str(); }
    const std::string getMsg() const throw() { return msg; }
};

struct ExistException : public BaseException {
    ExistException(const std::string& vMsg): BaseException(vMsg) { };
};

struct SingeltonException : public BaseException {
    SingeltonException(): BaseException("tried to create Invalid Instance") { };
    SingeltonException(const std::string& vMsg): BaseException(vMsg) { };
};

struct GLException: public BaseException
{
    GLException(const std::string&vMsg):BaseException(vMsg) {}
};

#endif /* Execption_hpp */
