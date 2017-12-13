    //GLUT
    //#include <glut/glut.h>

#include "../include/GLFWManager.h"
#include "../include/GLApplication.h"
#include "../include/camera.h"


#include "../include/base/Geometry.h"
#include "../include/base/engine/KDTree.h"
#include "../include/base/CameraEx.h"
int main(void)
{

    CameraEx<float> *pCamera = new CameraEx<float>();
    
    GLFWManager *pWindowManager = new GLFWManager(pCamera);

    GLApplication application;
    application.SetWindowManager(pWindowManager);

    InputManager::Instance().SetCamera(pWindowManager->GetCamera());
    
    return application.GLMain();

    
   
}