#ifndef APP_H
#define APP_H

#include <SDL/SDL.h>
#include "Scene.h"
#include "Vector2d.h"

typedef struct {
    Vector2d position;
    bool pressed;
} Mouse;

class Application {
public:
    //Functions called by int main()
    void initialize();
    void execute();
    void quit();

    /*The following two variables are static to allow other classes
      to access information that they contain. The s_Window variable
      is the surface that is rendered during runtime. The s_Keyboard
      variable is an array of key states that may be accessed using
      SDLKey constants as the index.*/
    static SDL_Surface* s_Screen;
    static Uint8* s_Keyboard;

    //Hold the current mouse position on screen and if it is pressed.
    static Mouse s_Mouse;

    static SDL_Joystick* s_Joystick;

private:
    /*The application will quit properly if this is true. Do not use
      this if an error is caught. Instead use exit(int).*/
    bool m_Quit;

    //Keeps track of when the loop should be executed.
    unsigned long m_Timer;

    //Event to update the event queue.
    SDL_Event m_Event;

    Scene* m_CurrentScene;

    //Main functions being executed in the loop.
    void updateEvents();
    void updateScene();
    void updateScreen();
};

#endif
