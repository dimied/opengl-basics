#ifndef __SCENE_RENDERER__
#define __SCENE_RENDERER__

class SceneRenderer
{
public:
    virtual void init() = 0;
    
    virtual void draw() = 0;
};

#endif