#ifndef PROTOSCENE_H
#define PROTOSCENE_H

#include <vector>

#include "Scene.h"
#include "Camera.h"
#include "CollisionController.h"
#include "Polygon.h"
#include "Player.h"

class PrototypeScene : public Scene {
public:
    /*All setup occurs in the constructor when the scene is created. This
      includes loading images and pushing SceneObjects onto their appropriate
      vectors.*/
    PrototypeScene();
    ~PrototypeScene();

    /*The following functions are inherited from the Scene class and are
      called by Application. All logic should go into here.*/
    void sceneEvents();
    void sceneUpdate();
    void sceneRender();
  
private:
    Camera m_Camera;
    bool m_Paused;
    bool m_PauseLatch;

    Player m_Player;
    Polygon m_Platform;
    Polygon m_Mink;

    Vector2d m_PlayerVel; 
    /*The scene updates itself by adding each object onto the appropriate
      vectors. The vectors iterate through each update and call a specific
      function on each SceneObject. Add objects to their appropriate vectors
      in the constructor. New vectors should be used whenever a new type of
      function needs to be called onto certain SceneObjects.*/
    std::vector<Polygon*> m_UpdateObjects;
    //vector<Polygon*> m_RenderObjects;
};

#endif
