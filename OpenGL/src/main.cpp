    //GLUT
    //#include <glut/glut.h>

#include "../include/GLFWManager.h"
#include "../include/GLApplication.h"
#include "../include/camera.h"


int main(void)
{
    Camera *pCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    GLFWManager *pWindowManager = new GLFWManager(pCamera);

    GLApplication application;
    application.SetWindowManager(pWindowManager);

    pWindowManager->GetInputManager()->SetCamera(pCamera);
    
    return application.GLMain();
    
}