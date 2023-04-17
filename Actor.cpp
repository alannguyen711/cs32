#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void Actor::changeHealth(int change)
{
    // function changes the health of CAWA
    if (change + m_health >= 100 && change > 0) // maximum of 100 hit points
    {
        m_health = 100;
        return;
    }
    
    m_health += change;
    
    
    if (m_health <= 0)
    {
        if (isZombieCab() && change == -1) // dead by holy water projectiles
        {
            if (randInt(1, 5) == 1)
            {
                // 1/5 chance for an oil slick to be generated
                OilSlick* os = new OilSlick(getX(), getY(), getSW());
                getSW()->pushActor(os);
            }
            setDead();
            getSW()->playSound(SOUND_VEHICLE_DIE); // play appropriate sounds
            getSW()->increaseScore(200); // score goes up
            return;
        }
        
        if (isZombie() && change == -1) // dead by holy water projectiles
        {
            if (randInt(1, 5) == 1)
            {
                HealingGoodie* hg = new HealingGoodie(getX(), getY(), getSW());
                getSW()->pushActor(hg);
            }
            setDead();
            getSW()->playSound(SOUND_PED_DIE); // play appropriate sounds
            getSW()->increaseScore(150); // score goes up
            return;
        }
    }
    
    if (isZombieCab() && change == -1) // if hit by holy water projectile
        getSW()->playSound(SOUND_VEHICLE_HURT);
    if (isZombie() && change == -1)
        getSW()->playSound(SOUND_PED_HURT);
}

bool Actor::overlapGR()
{
    // if the ghostracer overlaps with whatever actor
    double delta_x = getSW()->getGhost()->getX() - getX();
    double delta_y = getSW()->getGhost()->getY() - getY();
    if (delta_x < 0)
        delta_x = delta_x * -1;
    if (delta_y < 0)
        delta_y = delta_y * -1;
    double radius_sum = getRadius() + getSW()->getGhost()->getRadius();
    if (delta_x < (radius_sum * .25) && delta_y < (radius_sum*.6))
        return true;
    return false;
    // this algorithm is specified in the spec
}

bool Actor::overlapOtherActor(Actor* otherActor)
{
    // takes another actor as a parameter
    double delta_x = otherActor->getX() - getX();
    double delta_y = otherActor->getY() - getY();
    if (delta_x < 0)
        delta_x = delta_x * -1;
    if (delta_y < 0)
        delta_y = delta_y * -1;
    double radius_sum = getRadius() + otherActor->getRadius();
    if (delta_x < (radius_sum * .25) && delta_y < (radius_sum*.6))
        return true;
    return false;
    // this algorithm is specified in the spec
}

void Actor::generalMove()
{
    // Actors use this algorithm from the spec to move at the correct speed
    // called within the other Actor doSomething
    double vert_speed = getVSpeed() - getSW()->getGhost()->getVSpeed();
    double horiz_speed = getHSpeed();
    double new_y = getY() + vert_speed;
    double new_x = getX() + horiz_speed;
    moveTo(new_x, new_y);
    
    // if actor is no longer on the screen
    if (getX() < 0 || getX() > VIEW_WIDTH || getY() < 0 || getY() > VIEW_HEIGHT)
        setDead();
}

int Actor::getLane()
{
    int LEFT_EDGE = (ROAD_CENTER - ROAD_WIDTH/2);
    int RIGHT_EDGE = (ROAD_CENTER + ROAD_WIDTH/2);
    if (getX() > LEFT_EDGE && getX() < (LEFT_EDGE + ROAD_WIDTH/3))
        return 1; // leftmost lane
    if (getX() > (LEFT_EDGE + ROAD_WIDTH/3) && getX() < (RIGHT_EDGE - ROAD_WIDTH/3))
        return 2;// middle lane
    if (getX() > (RIGHT_EDGE - ROAD_WIDTH/3) && getX() < RIGHT_EDGE)
        return 3; // right lane
    return -1;
}


void GhostRacer::doSomething()
{
    if (!isAlive()) // HIT POINTS LESS THAN 0
        return;
    if (getHealth() <= 0)
        return;
    
    // check to be sure GR is on the road
    if (getX() <= (ROAD_CENTER - ROAD_WIDTH/2))
    {
        if (getDirection() > 90)
            changeHealth(-10);
        setDirection(82);
        getSW()->playSound(SOUND_VEHICLE_CRASH);
    }
    else if (getX() >= (ROAD_CENTER + ROAD_WIDTH/2))
    {
        if (getDirection() < 90)
        changeHealth(-10);
        setDirection(98);
        getSW()->playSound(SOUND_VEHICLE_CRASH);
    }
    
    
    // if the user has pressed a key
    int ch;
    if (getSW()->getKey(ch))
    {
        if (ch == KEY_PRESS_SPACE)
        {
            if (getSW()->getGhost()->getHolyWater() > 0)
            {
                // add new HWP in front of ghost racer
                double xCoord = getSW()->getGhost()->getX() + cos(getDirection()*(M_PI/180))*SPRITE_HEIGHT;
                double yCoord = getSW()->getGhost()->getY() + sin(getDirection()*(M_PI/180))*SPRITE_HEIGHT;
                HolyWaterProjectile* HWP = new HolyWaterProjectile(xCoord, yCoord, getDirection(), getSW());
                getSW()->pushActor(HWP);
                getSW()->playSound(SOUND_PLAYER_SPRAY); // play sound
                changeHW(-1); // decrement holy water shots
            }
        }
        else if (ch == KEY_PRESS_LEFT && getDirection() < 114)
            setDirection(getDirection()+8);
        else if (ch == KEY_PRESS_RIGHT && getDirection() > 66)
            setDirection(getDirection()-8);
        else if (ch == KEY_PRESS_UP && getVSpeed() < 5)
            setVSpeed(getVSpeed()+1);
        else if (ch == KEY_PRESS_DOWN && getVSpeed() > -1)
            setVSpeed(getVSpeed()-1);
    }
    
    double max_shift_per_tick = 4.0;
    int direction = getDirection();
    double delta_x = cos(direction*(M_PI/180)) * max_shift_per_tick;
    double cur_x = getX();
    double cur_y = getY();
    moveTo(cur_x + delta_x, cur_y);
    // uses the moveTo function to move appropriately
}


void BorderLine::doSomething()
{
    // only moves down the screen
    generalMove();
    if (!isAlive())
        return;
}

void Pedestrian::finishMovePed()
{
    // use movement plan distance as specified in the spec
    decMPDistance();
    if (getMPDistance() > 0)
        return;
    
    // pick a new movement plan for the human pedestrian
    int newHSpeed = randInt(-2, 3);
    if (newHSpeed <= 0)
        newHSpeed--;
    setHSpeed(newHSpeed);
    changeMPDistance(randInt(4, 32)); // change MPDDistance
    if (getHSpeed() < 0)
        setDirection(180);
    else
    setDirection(0);
}

void Pedestrian::doSomething()
{
    if (!isAlive()) // HIT POINTS LESS THAN 0
        return;
    if (getHealth() <= 0)
    {
        setDead();
        return;
    }
    
    // If the human pedestrian overlaps with the Ghost Racer, then the player loses a life and the level ends (you must communicate this somehow to your StudentWorld).
    if (overlapGR())
    {
        collideGR();
        return;
    }
    
    zombieChange(); // specific to Zombie's movements

    generalMove();
    if (!isAlive())
        return;
    finishMovePed();
    
}

void HumanPedestrian::collideGR()
{
    // what to do when the human collides with GhostRacer
    setDead();
    getSW()->decLives();
    getSW()->getGhost()->setDead();
    return;
}

void ZombiePedestrian::collideGR()
{
    // what to do when the zombie collides with GhostRacer
    getSW()->getGhost()->changeHealth(-5);
    changeHealth(-2);
    setDead();
}

void ZombiePedestrian::zombieChange()
{
    // specific to Zombie's movements
    int newHSpeed = 0;
    // zombie is < 30 pix to the left of GR
    if (getSW()->getGhost()->getX() - getX() < 30 && getSW()->getGhost()->getX() - getX() > 0)
        newHSpeed = 1;
    // zombie is < 30 pix to the right of GR
    else if (getX() - getSW()->getGhost()->getX() < 30 && getX() - getSW()->getGhost()->getX() > 0)
        newHSpeed = -1;
    // same x coordinate
    else if (getX() == getSW()->getGhost()->getX())
        newHSpeed = 0;
    // if not within 30 pix left or right
    else return;
    
    if (getY() > getSW()->getGhost()->getY())
    {
        setDirection(270);
        setHSpeed(newHSpeed);
        decTicks();
        if (ticksNextGrunt() <= 0)
        {
            getSW()->playSound(SOUND_ZOMBIE_ATTACK);
            resetTicks();
        }
    }
    
}


void ZombieCab::doSomething()
{
    if (!isAlive() || getHealth() <= 0)
    {
        setDead();
        return;
    }
    
    if (overlapGR())
    {
        if (!hasDamagedGR())
        {
            getSW()->playSound(SOUND_VEHICLE_CRASH);
            getSW()->getGhost()->changeHealth(-20);
            
            // the zombie cab is to the left or has the same X coordinate as Ghost Racer
            if (getX() <= getSW()->getGhost()->getX())
            {
                setHSpeed(-5);
                setDirection(120+randInt(0, 19));
            }
            //  right of the Ghost Racer
            if (getX() > getSW()->getGhost()->getX())
            {
                setHSpeed(5);
                setDirection(60-randInt(0, 19));
            }
            // must remember that it has now damaged Ghost Racer
            damageGR();
        }
    }
    
    // move zombie cab
    generalMove();
    
    if (getVSpeed() > getSW()->getGhost()->getVSpeed() && getSW()->CAWAInFront(this))
    {
        if (getSW()->closestActorFront(this)->getY() - getY() < 96)
        {
            setVSpeed(getVSpeed()-0.5);
            return;
        }
    }
    
    if (getVSpeed() <= getSW()->getGhost()->getVSpeed() && getSW()->CAWAInBack(this))
    {
        if (getY() - getSW()->closestActorBack(this)->getY() < 96)
            setVSpeed(getVSpeed()+0.5);
            return;
    }
    decMPDistance();
    if (m_MPDistance > 0)
        return;
    else
    {
        changeMPDistance(randInt(4, 32));
        setVSpeed(getVSpeed()+randInt(-2, 2));
    }
    
        
}

void OilSlick::doSomething()
{
    generalMove();
    if (!isAlive())
        return;
    
    if (overlapGR())
    {
        getSW()->playSound(SOUND_OIL_SLICK);
        spinGR(); // spin the GhostRacer if overlap with oil slick
    }
    
}

void OilSlick::spinGR()
{
    // spin the GhostRacer if overlap with oil slick
    int changeDirection = randInt(5, 20);
    if (randInt(1, 2) == 1) // counterclockwise
    {
        changeDirection *= -1;
    }
    
    if (changeDirection + getSW()->getGhost()->getDirection() > 120 || changeDirection + getSW()->getGhost()->getDirection() < 60)
        getSW()->getGhost()->setDirection(getSW()->getGhost()->getDirection() - changeDirection);
    else
        getSW()->getGhost()->setDirection(getSW()->getGhost()->getDirection() + changeDirection);
}

void Goodie::doSomething()
{
    generalMove();
    goodieCollideGR(); // different for each goodie, see below functions
    moveSoul();
}

void HealingGoodie::goodieCollideGR()
{
    // goodie adds to health
    if (overlapGR())
    {
        getSW()->getGhost()->changeHealth(10);
        setDead();
        getSW()->playSound(SOUND_GOT_GOODIE);
        getSW()->increaseScore(250);
    }
}



void HolyWaterGoodie::goodieCollideGR()
{
    // goodie adds to HW charge
    if (overlapGR())
    {
        getSW()->getGhost()->changeHW(10);
        setDead();
        getSW()->playSound(SOUND_GOT_GOODIE);
        getSW()->increaseScore(50);
    }
}


void SoulGoodie::goodieCollideGR()
{
    if (overlapGR())
    {
        getSW()->getGhost()->saveSoul(); // increase the number of lost souls
        setDead();
        getSW()->playSound(SOUND_GOT_SOUL);
        getSW()->increaseScore(100);
    }
}

void HolyWaterProjectile::doSomething()
{
    if (!isAlive()) // if not alive return immediately
        return;
    
    // check to see if activated
    Actor* activated = getSW()->findOverlappingActor(this);
    if (activated != nullptr)
    {
        if (activated->affectedByHW())
        {
            if (activated->isHuman())
            {
                activated->setHSpeed(activated->getHSpeed() * -1);
                if (activated->getDirection() == 180)
                    activated->setDirection(0);
                else
                    activated->setDirection(180);
                getSW()->playSound(SOUND_PED_HURT);
                return;
            }
            // if goodie then set dead
            if (activated->goodieAffectedByHW())
            {
                activated->setDead();
            }
            activated->changeHealth(-1);
            setDead();
            return;
        }
    }
    
    // move projectile
    for (int i = 0; i < SPRITE_HEIGHT; i++)
        moveForward();
    movePixels(SPRITE_HEIGHT);
    if (getX() < 0 || getX() > VIEW_WIDTH || getY() < 0 || getY() > VIEW_HEIGHT)
    {
        setDead();
        return;
    }
    if (pixelsLeft() <= 0)
        setDead();
}
