#include "Application.h"

int main(int argv, char** argc)
{
    //Create the application.
    Application* SProject2013 = new Application();
    
    //Initialize, execute, and exit the application.
    SProject2013->initialize();
    SProject2013->execute();
    SProject2013->quit();
    
    //Delete the application.
    delete SProject2013;

    return 0;
}
