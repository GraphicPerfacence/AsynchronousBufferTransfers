//GLUT
//#include <glut/glut.h>

#include "../include/GLFWManager.h"
#include "../include/GLApplication.h"


#if 1
int main(void)
{
	// First create our desired WindowManager implementation so we can set it below
	GLFWManager *pWindowManager = new GLFWManager();
	
	Camera *pCamera = new Camera();
	
	GLApplication application;
	application.SetWindowManager(pWindowManager);
	

	application.SetCamera(pCamera);
	pWindowManager->GetInputManager()->SetCamera(pCamera);
	
	return application.GLMain();
	
}
#endif