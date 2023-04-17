#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor: public GraphObject
{
public:
    Actor(int imageID, double startX, double startY, int dir, double size, unsigned int depth, double vSpeed, double hSpeed, StudentWorld* sw, int health):
    GraphObject(imageID, startX, startY, dir, size, depth), m_vSpeed(vSpeed), m_hSpeed(hSpeed), m_isAlive(true), m_sw(sw), m_health(health), m_holyWaterCharge(10)
    { m_isAlive = true; }
    virtual void doSomething() = 0;
    virtual bool isBorderLine() { return false; }
    double getVSpeed() { return m_vSpeed; }
    double getHSpeed() { return m_hSpeed; }
    bool isAlive() { return m_isAlive; }
    void setDead() { m_isAlive = false; }
    StudentWorld* getSW() { return m_sw; }
    void setVSpeed(double newSpeed) { m_vSpeed = newSpeed; }
    void setHSpeed(double newSpeed) { m_hSpeed = newSpeed; }
    int getHealth() { return m_health; }
    void changeHealth(int change);
    bool overlapGR();
    bool overlapOtherActor(Actor* otherActor);
    void generalMove();
    virtual bool CAWA() { return false; }
    int getLane();
    int getHolyWater() { return m_holyWaterCharge; } // virtual?
    void changeHW(int change) { m_holyWaterCharge += change; }
    virtual void saveSoul() { return; }
    virtual int soulsSaved() { return 0; }
    virtual bool affectedByHW() { return false; }
    virtual bool goodieAffectedByHW() { return false; }
    virtual bool isHuman() { return false; }
    virtual bool isZombie() { return false; }
    virtual bool isZombieCab() { return false; }
private:
    double m_vSpeed;
    double m_hSpeed;
    bool m_isAlive;
    StudentWorld* m_sw;
    int m_health;
    int m_holyWaterCharge;
};


class GhostRacer: public Actor
{
public:
    GhostRacer(StudentWorld* sw):
    Actor(IID_GHOST_RACER, 128, 32, 90, 4.0, 0, 0, 0, sw, 100), m_soulsSaved(0)
    {}
    virtual void doSomething();
    virtual bool CAWA() { return true; }
    virtual void saveSoul() { m_soulsSaved++; }
    virtual int soulsSaved() { return m_soulsSaved; }
private:
    int m_soulsSaved;
};

class BorderLine: public Actor
{
    public:
        BorderLine(int imageID, double startX, double startY, StudentWorld* sw):
    Actor(imageID, startX, startY, 0, 2.0, 1, -4, 0, sw, 0)
        {}
    virtual void doSomething();
    virtual bool isBorderLine() { return true; }
    private:
};

class Pedestrian: public Actor
{
    public:
    Pedestrian(int imageID, double startX, double startY, int size, StudentWorld* sw):
        Actor(imageID, startX, startY, 0, size, 0, -4, 0, sw, 2), m_MPDistance(0)
        {}
        virtual void doSomething();
        void finishMovePed();
        int getMPDistance() { return m_MPDistance; }
        void decMPDistance() { m_MPDistance--; }
        void changeMPDistance(int changeTo) { m_MPDistance = changeTo; }
        virtual bool CAWA() { return true; }
        virtual void collideGR() = 0;
        virtual void zombieChange() { return; }
        virtual int ticksNextGrunt() { return 0; }
        virtual void decTicks() { return; }
        virtual void resetTicks() { return; }
        virtual bool affectedByHW() { return true; }
    private:
        int m_MPDistance;
};

class HumanPedestrian: public Pedestrian
{
public:
    HumanPedestrian(double startX, double startY, StudentWorld* sw):
    Pedestrian(IID_HUMAN_PED, startX, startY, 2.0, sw)
    {}
    virtual void collideGR();
    virtual bool isHuman() { return true; }
private:
};

class ZombiePedestrian: public Pedestrian
{
public:
    ZombiePedestrian(double startX, double startY, StudentWorld* sw):
    Pedestrian(IID_ZOMBIE_PED, startX, startY, 3.0, sw), m_ticksNextGrunt(0)
    {}
    virtual void collideGR();
    virtual void zombieChange();
    virtual int ticksNextGrunt() { return m_ticksNextGrunt; }
    virtual void decTicks() { m_ticksNextGrunt--; }
    virtual void resetTicks() { m_ticksNextGrunt = 20; }
    virtual bool isZombie() { return true; }
private:
    int m_ticksNextGrunt;
};


class ZombieCab: public Actor
{
public:
    ZombieCab(double startX, double startY, StudentWorld* sw, double vSpeed):
    Actor(IID_ZOMBIE_CAB, startX, startY, 90, 4.0, 0, vSpeed, 0, sw, 3), m_hasDamagedGR(false)
    {}
    virtual void doSomething();
    bool hasDamagedGR() { return m_hasDamagedGR; }
    void damageGR() { m_hasDamagedGR = true; }
    int getMPDistance() { return m_MPDistance; }
    void decMPDistance() { m_MPDistance--; }
    void changeMPDistance(int changeTo) { m_MPDistance = changeTo; }
    virtual bool CAWA() { return true; }
    virtual bool affectedByHW() { return true; }
    virtual bool isZombieCab() { return true; }
private:
    bool m_hasDamagedGR;
    int m_MPDistance;
};

class OilSlick: public Actor
{
public:
    OilSlick(double startX, double startY, StudentWorld* sw):
    Actor(IID_OIL_SLICK, startX, startY, 0, randInt(2, 5), 1, -4, 0, sw, 0) // vertical speed?
    {}
    virtual void doSomething();
    void spinGR();
private:
};

class Goodie: public Actor
{
public:
    Goodie(int imageID, double startX, double startY, int dir, int size, StudentWorld* sw):
    Actor(imageID, startX, startY, dir, size, 2, -4, 0, sw, 1)
    {}
    virtual void doSomething();
    virtual void goodieCollideGR() = 0;
    virtual void moveSoul() { return; }
    virtual bool affectedByHW() { return true; }
    virtual bool goodieAffectedByHW() { return true; }
};

class HealingGoodie: public Goodie
{
public:
    HealingGoodie(double startX, double startY, StudentWorld* sw):
    Goodie(IID_HEAL_GOODIE, startX, startY, 0, 1.0, sw)
    {}
    virtual void goodieCollideGR();
};

class HolyWaterGoodie: public Goodie
{
public:
    HolyWaterGoodie(double startX, double startY, StudentWorld* sw):
    Goodie(IID_HOLY_WATER_GOODIE, startX, startY, 90, 2.0, sw)
    {}
    virtual void goodieCollideGR();
};

class SoulGoodie: public Goodie
{
public:
    SoulGoodie(double startX, double startY, StudentWorld* sw):
    Goodie(IID_SOUL_GOODIE, startX, startY, 0, 4.0, sw)
    {}
    virtual void goodieCollideGR();
    virtual void moveSoul() { setDirection(getDirection() - 10); }
    virtual bool affectedByHW() { return false; }
    virtual bool goodieAffectedByHW() { return false; }
};

class HolyWaterProjectile: public Actor
{
public:
    HolyWaterProjectile(double startX, double startY, int dir, StudentWorld* sw):
    Actor(IID_HOLY_WATER_PROJECTILE, startX, startY, dir, 1.0, 1, 0, 0, sw, 0), m_pixelsLeft(160)
    {}
    virtual void doSomething();
    void movePixels(int move) { m_pixelsLeft -= move; }
private:
    int pixelsLeft() { return m_pixelsLeft; }
    int m_pixelsLeft;
};

#endif // ACTOR_H_
