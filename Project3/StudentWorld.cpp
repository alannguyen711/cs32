#include "StudentWorld.h"
#include "GameConstants.h"

#include <iostream> // defines the overloads of the << operator
#include <sstream>
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    GhostRacer* GR = new GhostRacer(this);
    actors.push_back(GR);
    
    // add N yellow border line objects where N is equal to VIEW_HEIGHT / SPRITE_HEIGHT
    int N = VIEW_HEIGHT / SPRITE_HEIGHT;
    int LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
    int RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;
    for (int j = 0; j < N; j++)
    {
        BorderLine* YBLLeft = new BorderLine(IID_YELLOW_BORDER_LINE, LEFT_EDGE, j*SPRITE_HEIGHT, this);
        BorderLine* YBLRight = new BorderLine(IID_YELLOW_BORDER_LINE, RIGHT_EDGE, j*SPRITE_HEIGHT, this);
        actors.push_back(YBLLeft);
        actors.push_back(YBLRight);
    }
    
    // Add M white border line objects
    int M = VIEW_HEIGHT / (4*SPRITE_HEIGHT);
    for (int j = 0; j < M; j++)
    {
        BorderLine* WBLLeft = new BorderLine(IID_WHITE_BORDER_LINE, LEFT_EDGE + ROAD_WIDTH/3, j * (4*SPRITE_HEIGHT), this);
        BorderLine* WBLRight = new BorderLine(IID_WHITE_BORDER_LINE, RIGHT_EDGE - ROAD_WIDTH/3, j * (4*SPRITE_HEIGHT), this);
        actors.push_back(WBLLeft);
        actors.push_back(WBLRight);
        lastWBL = j * (4*SPRITE_HEIGHT);
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    for (int i = 0; i < actors.size(); i++)
    {
        if (actors[i]->isAlive())
            actors[i]->doSomething();
        if (!getGhost()->isAlive() || getGhost()->getHealth() <= 0)
        {
            getGhost()->setDead();
            return GWSTATUS_PLAYER_DIED;
        }
        
        if ((2 * getLevel() + 5) - getGhost()->soulsSaved() <= 0)
            return GWSTATUS_FINISHED_LEVEL;
    }
    
    // delete dead actors
    vector<Actor*>:: iterator it;
    it = actors.begin();
    while (it != actors.end())
    {
        if (!((*it)->isAlive()))
        {
            delete *it;
            it = actors.erase(it);
        }
        else
            it++;
    }
    
    // update y coordinate
    it = actors.begin();
    while (it != actors.end())
    {
        if ((*it)->isBorderLine())
        {
            lastWBL += (*it)->getVSpeed() - getGhost()->getVSpeed();
            break;
        }
        else
            it++;
    }
     
    // add new actors
    
    // add new borderlines
    int new_border_y = (VIEW_HEIGHT - SPRITE_HEIGHT);
    int delta_y = new_border_y - lastWBL;
    if (delta_y >= SPRITE_HEIGHT)
    {
        BorderLine* YBLLeft = new BorderLine(IID_YELLOW_BORDER_LINE, ROAD_CENTER - ROAD_WIDTH/2, new_border_y, this);
        BorderLine* YBLRight = new BorderLine(IID_YELLOW_BORDER_LINE, ROAD_CENTER + ROAD_WIDTH/2, new_border_y, this);
        actors.push_back(YBLLeft);
        actors.push_back(YBLRight);
    }
    if (delta_y >= 4*SPRITE_HEIGHT)
    {
        BorderLine* WBLLeft = new BorderLine(IID_WHITE_BORDER_LINE, ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH/3, new_border_y, this);
        BorderLine* WBLRight = new BorderLine(IID_WHITE_BORDER_LINE, ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH/3, new_border_y, this);
        actors.push_back(WBLLeft);
        actors.push_back(WBLRight);
        lastWBL = new_border_y;
    }
    
    // add human pedestrians
    int ChanceHumanPed = max(200 - getStudentWorld()->getLevel() * 10, 30);
    int chanceHuman = randInt(0, ChanceHumanPed-1);
    if (chanceHuman == 0)
    {
        HumanPedestrian* human = new HumanPedestrian(randInt(1, VIEW_WIDTH-1), VIEW_HEIGHT, this);
        actors.push_back(human);
    }
    
    int ChanceZombiePed = max(100 - getStudentWorld()->getLevel() * 10, 20);
    int chanceZombie = randInt(0, ChanceZombiePed-1);
    if (chanceZombie == 0)
    {
        ZombiePedestrian* zombie = new ZombiePedestrian(randInt(1, VIEW_WIDTH-1), VIEW_HEIGHT, this);
        actors.push_back(zombie);
    }
    
    // add oil slicks
    int ChanceOilSlick = max(150 - getStudentWorld()->getLevel() * 10, 40);
    int chanceOil = randInt(0, ChanceOilSlick-1);
    if (chanceOil == 0)
    {
        int LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
        int RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;
        OilSlick* oil = new OilSlick(randInt(LEFT_EDGE, RIGHT_EDGE), VIEW_HEIGHT, this);
        actors.push_back(oil);
    }
    
    
    // add appropriate goodies
    int ChanceOfHolyWater = 100 + 10 * getStudentWorld()->getLevel();
    int chanceHW = randInt(0, ChanceOfHolyWater-1);
    if (chanceHW == 0)
    {
        int LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
        int RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;
        HolyWaterGoodie* holy = new HolyWaterGoodie(randInt(LEFT_EDGE, RIGHT_EDGE), VIEW_HEIGHT, this);
        actors.push_back(holy);
    } 
    
    
    int chanceLostSoul = randInt(0, 100-1);
    if (chanceLostSoul == 0)
    {
        int LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
        int RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;
        SoulGoodie* soul = new SoulGoodie(randInt(LEFT_EDGE, RIGHT_EDGE), VIEW_HEIGHT, this);
        actors.push_back(soul);
    }
    
    // add zombie cabs
    int ChanceVehicle = max(100 - getStudentWorld()->getLevel() * 10, 20);
    int chanceZC = randInt(0, ChanceVehicle-1);
    if (chanceZC == 0)
    {
        int cur_lane = randInt(1,3);
        double zcY = -1; double zcSpeed = -1;
        for (int lanesChecked = 0; lanesChecked < 3; lanesChecked++)
        {
            if (closestToBottom(cur_lane) == nullptr || closestToBottom(cur_lane)->getY() > (VIEW_HEIGHT/3))
            {
                zcY = SPRITE_HEIGHT/2;
                zcSpeed = getGhost()->getVSpeed() + randInt(2, 4);
                break;
            }
            else if (closestToTop(cur_lane) == nullptr || closestToTop(cur_lane)->getY() < (VIEW_HEIGHT * 2/3))
            {
                zcY = VIEW_HEIGHT - SPRITE_HEIGHT/2;
                zcSpeed = getGhost()->getVSpeed() - randInt(2, 4);
                break;
            }
            else
            {}
            // to check all the lanes
            if (cur_lane == 3)
                cur_lane = 1;
            else
                cur_lane++;
        }
        if (zcY != -1 && zcSpeed != -1) // if there is a zombie cab to add
        {
            double zcX;
            if (cur_lane == 1)
                zcX = ROAD_CENTER - ROAD_WIDTH/3;
            else if (cur_lane == 2)
                zcX = ROAD_CENTER;
            else
                zcX = ROAD_CENTER + ROAD_WIDTH/3;
            ZombieCab* ZC = new ZombieCab(zcX, zcY, this, zcSpeed);
            actors.push_back(ZC);
        }
    }
    
    // game text on top of screen
    ostringstream gameText;
    gameText << "Score: " << getScore() << "  Lvl: " << getLevel() << "  Souls2Save: " << (2 * getLevel() + 5) - getGhost()->soulsSaved() << "  Lives: " << getLives() << "  Health: " << getGhost()->getHealth() << "  Sprays: " << getGhost()->getHolyWater() << " Bonus: " << getScore();
    string text = gameText.str();
    setGameStatText(text);
    
    if (!(getGhost()->isAlive()))
        return GWSTATUS_PLAYER_DIED;
    
    return GWSTATUS_CONTINUE_GAME;
    
}

void StudentWorld::cleanUp()
{
    vector<Actor*>:: iterator it;
    it = actors.begin();
    while (it != actors.end())
    {
        delete *it;
        it = actors.erase(it);
    }
}


bool StudentWorld::CAWAInFront(Actor* zc)
{
    // find closest CAWA in the front
    for (int i = 0; i < actors.size(); i++)
    {
        if (zc->getLane() != actors[i]->getLane())
            continue;
        if (actors[i]->isHuman() || actors[i]->isZombie() || actors[i]->isZombieCab() || i == 0)
        {
            if (actors[i]->getY() > zc->getY())
                return true; // return true if so
        }
    }
    return false;
}

bool StudentWorld::CAWAInBack(Actor* zc)
{
    // find closest CAWA in the back
    for (int i = 0; i < actors.size(); i++)
    {
        if (zc->getLane() != actors[i]->getLane())
            continue;
        if (actors[i]->isHuman() || actors[i]->isZombie() || actors[i]->isZombieCab() || i == 0)
        {
            if (zc->getY() > actors[i]->getY())
                return true; // return true if so
        }
    }
    return false;
}

Actor* StudentWorld::closestActorFront(Actor* zc)
{
    int closestIndex = -1;
    double distanceInFront = 9999; // always greater than the distance
    for (int i = 0; i < actors.size(); i++)
    {
        if (zc->getLane() != actors[i]->getLane())
            continue;
        if (actors[i]->isHuman() || actors[i]->isZombie() || actors[i]->isZombieCab() || i == 0)
        {
            if ((actors[i]->getY() - zc->getY()) < distanceInFront && (actors[i]->getY() - zc->getY()) > 0)
            {
                distanceInFront = (actors[i]->getY() - zc->getY());
                closestIndex = i;
            }
        }
    }
    if (closestIndex != -1)
        return actors[closestIndex]; // return appropriate actor
    else
        return nullptr;
}

Actor* StudentWorld::closestActorBack(Actor* zc)
{
    int closestIndex = -1;
    double distanceBehind = 9999;  // always greater than the distance
    for (int i = 0; i < actors.size(); i++)
    {
        if (zc->getLane() != actors[i]->getLane())
            continue;
        if (actors[i]->isHuman() || actors[i]->isZombie() || actors[i]->isZombieCab() || i == 0)
        {
            if ((zc->getY() - actors[i]->getY()) < distanceBehind && (zc->getY() - actors[i]->getY()) > 0)
            {
                distanceBehind = (zc->getY() - actors[i]->getY());
                closestIndex = i;
            }
        }
    }
    if (closestIndex != -1)
        return actors[closestIndex]; // return appropriate actor
    else
        return nullptr;
}

Actor* StudentWorld::closestToBottom(int lane)
{
    // find actor that's the closest to the bottom in the same lane that is CAW
    double closest = 9999;
    int closestIndex = -1;
    for (int i = 0; i < actors.size(); i++)
    {
        if (lane == actors[i]->getLane())
        {
            if (actors[i]->CAWA() && actors[i]->getY() < closest)
            {
                closest = actors[i]->getY();
                closestIndex = i;
            }
        }
    }
    if (closestIndex == -1)
        return nullptr;
    else return actors[closestIndex];
}
Actor* StudentWorld::closestToTop(int lane)
{
     // find actor that's the closest to the top in the same lane that is CAW
    double closest = 9999;
    int closestIndex = -1;
    for (int i = 0; i < actors.size(); i++)
    {
        if (lane == actors[i]->getLane())
        {
            if (actors[i]->CAWA() && VIEW_HEIGHT - actors[i]->getY() < closest)
            {
                closest = VIEW_HEIGHT - actors[i]->getY();
                closestIndex = i;
            }
        }
    }
    if (closestIndex == -1)
        return nullptr;
    else return actors[closestIndex];
}
