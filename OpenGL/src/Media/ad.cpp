//
//  audo.cpp
//  openGLTest
//
//  Created by xt on 17/8/26.
//  Copyright © 2017年 xt. All rights reserved.
//

#include "../../include/Media/ad.hpp"

#include <fmod_studio.hpp>
#include <fmod_errors.h>
Audo::Audo()
{
}

bool Audo::InitAudo()
{
    return false;
}

bool Audo::Update()
{
    return true;
}

bool Audo::ShutDown()
{
    return true;
}


class FMAudo :public Audo
{
public:
    FMAudo(){}

    virtual bool InitAudo()
    {
        FMOD_RESULT result;

        result = FMOD::Studio::System::create(&system); // Create the Studio System object.
        if (result != FMOD_OK)
        {
            printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        }

        // Initialize FMOD Studio, which will also initialize FMOD Low Level
        result = system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
        if (result != FMOD_OK)
        {
            printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        }

        return  true;
    }

    virtual bool ShutDown()
    {
        system->release();
        return  true;
    }

private:
    FMOD::Studio::System* system;
};

Audo *   g_Audo;

extern bool InitAudo()
{
    g_Audo = new FMAudo();

    //return  g_Audo->InitAudo();

    return false;
}