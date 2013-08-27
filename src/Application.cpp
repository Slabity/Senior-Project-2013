#include "Application.h"
#include <SDL/SDL_opengl.h>
#include <stdio.h>
#include <stdlib.h>

#include "PrototypeScene.h"

//Resolution constants.
const unsigned int WIDTH  = 2560;
const unsigned int HEIGHT = 1080;
const unsigned int FPS    = 60;

//Initialize both static variables to NULL.
SDL_Surface* Application::s_Screen = NULL;
Uint8* Application::s_Keyboard = NULL;
Mouse Application::s_Mouse;
SDL_Joystick* Application::s_Joystick = NULL;

//Initialize SDL and the window.
void Application::initialize()
{
    //Initialize the SDL library.
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Unable to load SDL\n");
        exit(1);
    }

    //Set the video mode.
    Application::s_Screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL | SDL_FULLSCREEN);
    if(Application::s_Screen == NULL) {
        fprintf(stderr, "Unable to create window\n");
        exit(2);
    }

    //Load the projection and modelview matrices.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIDTH*1.5, HEIGHT*1.5, 0.0, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    //Set the clear color.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //Check for OpenGL errors.
    GLenum error = glGetError();
    if(error != GL_NO_ERROR) {
        fprintf(stderr, "Unable to load OpenGL\n");
        exit(3);
    }

    //Set the window caption
    SDL_WM_SetCaption("Senior Project 2013", NULL);

    //Set the timer to the current SDL time.
    m_Timer = SDL_GetTicks();

    //Create the first scene.
    m_CurrentScene = new PrototypeScene();
    if(m_CurrentScene == NULL) {
        fprintf(stderr, "Unable to create the scene\n");
        exit(4);
    }

    if(SDL_NumJoysticks() > 0) {
        Application::s_Joystick = SDL_JoystickOpen(0);
        if(Application::s_Joystick == NULL) {
            fprintf(stderr, "Unable to load the joystick\n");
        }
    }
}

//Main execute loop.
void Application::execute()
{
    //While we are not quitting.
    while(!m_Quit) {

        //Continue from the start of the loop if the timer has not activated.
        if(SDL_GetTicks() < m_Timer) {
            continue;
        }
        
        //Update the timer.
        m_Timer += 1000 / FPS;

        //Call the update functions.
        updateEvents();
        updateScene();
        updateScreen();
    }
}

//Shut SDL down on exit.
void Application::quit()
{
    SDL_Quit();
}

//Update the event handler.
void Application::updateEvents()
{
    s_Keyboard = SDL_GetKeyState(NULL);
    while(SDL_PollEvent(&m_Event)) {
        m_Quit = (m_Event.type == SDL_QUIT) || Application::s_Keyboard[SDLK_ESCAPE];
        s_Mouse.pressed = (m_Event.type == SDL_MOUSEBUTTONDOWN);
    }
    
    //Update s_Mouse position.
    int x, y;
    SDL_GetMouseState(&x, &y);
    s_Mouse.position = Vector2d((float)x, (float)y);

    m_CurrentScene->sceneEvents();
}

//Update the scene.
void Application::updateScene()
{
    m_CurrentScene->sceneUpdate();
}

//Update the window.
void Application::updateScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    m_CurrentScene->sceneRender();

    SDL_GL_SwapBuffers();
}
