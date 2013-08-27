#include "SceneObject.h"

SceneObject::SceneObject() {}
SceneObject::~SceneObject() {}

//Virtual functions.
void SceneObject::update() {}
void SceneObject::checkCollision(std::vector<SceneObject*>) {}
void SceneObject::draw() {}
