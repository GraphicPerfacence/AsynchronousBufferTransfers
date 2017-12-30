    //GLUT
    //#include <glut/glut.h>

#include "../include/GLFWManager.h"
#include "../include/GLApplication.h"


#include "../include/base/Geometry.h"
#include "../include/base/engine/KDTree.h"
#include "camera.h"

#include <stdlib.h>

int main(void)
{

    Camera *pCamera = new Camera();
    
    GLFWManager *pWindowManager = new GLFWManager(pCamera);

    GLApplication application;
    application.SetWindowManager(pWindowManager);

    return application.GLMain();
   
}