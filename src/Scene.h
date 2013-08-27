#ifndef SCENE_H
#define SCENE_H

#include "SceneObject.h"

class Scene {
public:
    /*Scene contains purely virtual functions that are called
      by Application. Inherit other scenes from this class and
      add them to Application.*/
    virtual void sceneEvents();
    virtual void sceneUpdate();
    virtual void sceneRender();
};

#endif
