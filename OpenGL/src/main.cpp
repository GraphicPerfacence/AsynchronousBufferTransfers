    //GLUT
    //#include <glut/glut.h>

#include "../include/GLFWManager.h"
#include "../include/GLApplication.h"
#include "../include/camera.h"


#include "../include/base/geometry/Object.h"

template <class T>
class Test :public std::vector<T>
{
    typedef typename std::vector<T>::iterator iterator;

    void test()
    {
        for(iterator i = this->begin();i != this->end();i++)
        {

        }
    }
};

int main(void)
{
    Camera *pCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    GLFWManager *pWindowManager = new GLFWManager(pCamera);

    GLApplication application;
    application.SetWindowManager(pWindowManager);

    pWindowManager->GetInputManager()->SetCamera(pCamera);
    
    return application.GLMain();


}