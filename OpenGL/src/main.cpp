    //GLUT
    //#include <glut/glut.h>

#include "../include/GLFWManager.h"
#include "../include/GLApplication.h"
#include "../include/camera.h"


#include "../include/base/Geometry.h"
#include "../include/base/engine/KDTree.h"

int main(void)
{
    Camera *pCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    GLFWManager *pWindowManager = new GLFWManager(pCamera);

    GLApplication application;
    application.SetWindowManager(pWindowManager);

    pWindowManager->GetInputManager()->SetCamera(pCamera);
    
    return application.GLMain();

    
   
}