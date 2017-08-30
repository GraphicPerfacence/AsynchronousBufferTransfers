
//
//  Action
//  openGLTest
//
//  Created by xt on 17/8/29.
//  Copyright © 2017年 xt. All rights reserved.
//

#include "../base.hpp"
#include "../Callback.h"
#include "../RefPointer.hpp"

#ifndef OPENGL_Action_H
#define OPENGL_Action_H

class Action:public Base
{

    typedef Action&PARAM;
    typedef ICallback<PARAM>*CB;

    CB                          _callback;

    const std::string           _name;
    const std::string           _helpText;

public:
    Action(const std::string&name,const std::string&lt,CB pc = 0):
                        _name(name),
                        _helpText(lt),
                        _callback(pc){}
    virtual  ~Action()
    {
        if(0 != _callback)
        {
            delete _callback;
            _callback = 0;
        }
    }

    void            ExecuteCallback()
    {
        if(0 != _callback)
        {
            _callback->execute(*this);
        }
    }

    virtual void        Execute()
    {
            ExecuteCallback();
    }

    virtual std::string GetDataString()const = 0;

};

typedef RefPointer<Action> RefAction;



#endif /* Header_h */
