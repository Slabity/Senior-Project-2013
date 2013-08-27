#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <vector>

class SceneObject {
public:
    SceneObject();
    ~SceneObject();

    //Update, check collision, and draw functions.
    virtual void update();
    virtual void checkCollision(std::vector<SceneObject*>);
    virtual void draw();
};

#endif
