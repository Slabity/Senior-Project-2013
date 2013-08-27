#include "PrototypeScene.h"
#include <SDL/SDL_opengl.h>
#include "Application.h"
#include "Vector2d.h"
#include <fstream>
#include <stdlib.h>
#include <string>
#include <streambuf>

//Set the variables of the camera.
PrototypeScene::PrototypeScene() : Scene(),
                                   m_Camera(Vector2d(0.0, 0.0)),
                                   m_Player(Vector2d(256.0, 256.0), &m_UpdateObjects)
{
    m_Paused = false;
    m_PauseLatch = false;

    std::ifstream levelStream("bin/data/ProtoLevel.lvl");
    std::string levelData;

    levelStream.seekg(0, std::ios::end); 
    levelData.reserve(levelStream.tellg());
    levelStream.seekg(0, std::ios::beg);

    levelData.assign((std::istreambuf_iterator<char>(levelStream)),
                      std::istreambuf_iterator<char>());
 
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 100; j++) {
            int tile = levelData.at(j + i * 100) - '0';

            if(tile == 9) {
                continue;
            }

            Polygon *platform = new Polygon;
            switch(tile) {
                case 1:
                    platform->add(Vector2d(0.0, 0.0));
                    platform->add(Vector2d(64.0, 0.0));
                    platform->add(Vector2d(64.0, 64.0));
                    platform->add(Vector2d(0.0, 64.0));
                    break;

                case 2:
                    platform->add(Vector2d(64.0, 0.0));
                    platform->add(Vector2d(64.0, 64.0));
                    platform->add(Vector2d(0.0, 64.0));
                    break;

                case 3:
                    platform->add(Vector2d(0.0, 0.0));
                    platform->add(Vector2d(64.0, 64.0));
                    platform->add(Vector2d(0.0, 64.0));
                    break;

                case 4:
                    platform->add(Vector2d(0.0, 0.0));
                    platform->add(Vector2d(64.0, 0.0));
                    platform->add(Vector2d(0.0, 64.0));
                    break;

                case 5:
                    platform->add(Vector2d(0.0, 0.0));
                    platform->add(Vector2d(64.0, 0.0));
                    platform->add(Vector2d(64.0, 64.0));
                    break;

                case 6:
                    platform->add(Vector2d(0.0, 32.0));
                    platform->add(Vector2d(64.0, 32.0));
                    platform->add(Vector2d(64.0, 64.0));
                    platform->add(Vector2d(0.0, 64.0));
                    break;

                case 7:
                    platform->add(Vector2d(64.0, 32.0));
                    platform->add(Vector2d(64.0, 64.0));
                    platform->add(Vector2d(0.0, 64.0));
                    break;

                case 8:
                    platform->add(Vector2d(0.0, 32.0));
                    platform->add(Vector2d(64.0, 64.0));
                    platform->add(Vector2d(0.0, 64.0));
                    break;
            }

            Vector2d position = Vector2d(j*64.0, i*64.0);
            platform->setPosition(position);

            m_UpdateObjects.push_back(platform);
        }
    }
}

PrototypeScene::~PrototypeScene() {}

//Pause the game if escape is pressed.
void PrototypeScene::sceneEvents()
{
    if(Application::s_Keyboard[SDLK_ESCAPE]) {
        if(!m_PauseLatch) {
            m_Paused = !m_Paused;
            m_PauseLatch = true;
        }
    } else {
        m_PauseLatch = false;
    }

    if(m_Paused) {
        return;
    }

    if(Application::s_Keyboard[SDLK_e] || SDL_JoystickGetButton(Application::s_Joystick, 3)) {
        m_Player.setPosition(Vector2d(256.0, 256.0));
    }
    m_Player.control();
}

//Update all objects in the scene.
void PrototypeScene::sceneUpdate()
{
    //Do not update if the game is paused.
    if(m_Paused) {
        return;
    }

    //Update the player's everything.
    m_Player.update();

    if(m_Player.getPosition().y > 1500.0) {
        m_Player.setPosition(Vector2d(256.0, 256.0));
    }

    m_Camera.setHeading(m_Player.getPosition());
    m_Camera.update();
}

//Draw all objects in the scene.
void PrototypeScene::sceneRender()
{
    //Translate the OpenGL camera to the correct point.
    glTranslatef(Application::s_Screen->w / 1.33 - m_Camera.getPosition().x,
                 Application::s_Screen->h / 1.33 - m_Camera.getPosition().y, 0.0f);


    m_Player.render();

    for(int i = 0; i < m_UpdateObjects.size(); i++) {
        m_UpdateObjects[i]->render();
    }
}
