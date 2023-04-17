#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    GameWorld* getStudentWorld()
    {
        return this;
    }
    Actor* getGhost()
    {
        return actors[0];
    }
    void pushActor(Actor* toPush)
    {
        actors.push_back(toPush);
    }
    Actor* findOverlappingActor(Actor* HW)
    {
        for (int i = 0; i < actors.size(); i++)
        {
            if (HW->overlapOtherActor(actors[i]))
                return actors[i];
        }
        return nullptr;
    }
    bool CAWAInFront(Actor* zc);
    bool CAWAInBack(Actor* zc);
    Actor* closestActorFront(Actor* zc);
    Actor* closestActorBack(Actor* zc);
    Actor* closestToBottom(int lane);
    Actor* closestToTop(int lane);
    
private:
    std::vector<Actor*> actors;
    double lastWBL;
};

#endif // STUDENTWORLD_H_
