#pragma once
#include "SDL.h"
#include <iostream>
#include <map>
#include <functional>
#include "GameManager.h"
//this base class will render just one static sprite
using namespace std;
class SpriteEx
{
protected:
    SDL_Rect spriteSrcRect; //which part of the spritesheet we would like to render
    SDL_Rect spriteDestRect; //the position on the screen we would like to render this sprite at
    SDL_Texture* texture;
    double angle;//the angle to display sprite (in degrees)
    double m_X, //x coord
        m_Y, //Y coord
        m_DX, //the change in x coord
        m_DY, //the change in Y coordinate
        m_dSpeed; //speed in pixels to move per change
    double m_dRadius; //radius of the sprite's circle bounds
    bool isFlipped;
    bool collision;
    bool canAttack;
    double attackRange;
    std::string attack;
    GameManager gm;


public:
    SpriteEx() {}
    SpriteEx(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect dstRect)
    {
        texture = tex;
        spriteSrcRect = srcRect;
        spriteDestRect = dstRect;
    }
    void Render();
    void UpdateDestRect();
    double GetRadius() { return m_dRadius; }
    double GetX() { return m_X; }
    double GetY() { return m_Y; }

    double GetAttackRange() { return attackRange; }
    void SetCollision(bool col) { collision = col; }

    string GetAttack() { return attack; };
    void SetAttack(std::string atk) { attack = atk; };

    void TakeHit(int atkVal) { 
        m_X += 0.8f; 
        gm.TakeDamage(atkVal); 
    };
};


struct AnimStateDefinition {
    short rowIndex;
    short frames;
    short time;
    bool isLoopable = false;
    bool isInterrupt = true;

    std::function<void()> callbackOnComplete;

    void AddCallBackOnComplete(std::function<void()> cb) {
        callbackOnComplete = cb;
    }

    AnimStateDefinition() {};
    AnimStateDefinition(short ri, short f, short t, bool loop = false, bool interrupt = true) :
        rowIndex(ri), frames(f), time(t), isLoopable(loop), isInterrupt(interrupt) {}
};


class SpriteExAnimated : public SpriteEx
{
private:
    void AnimateRange(AnimStateDefinition asd);
    void Animate();
    bool isAnimFinished = false;

    unsigned int _LastTick = SDL_GetTicks();
    unsigned int GetLastTick() { return _LastTick; }
    void UpdateTick() { _LastTick = SDL_GetTicks(); }


protected:
    int
        //    m_iSprite = 0, //which sprite to display for animation
        //    m_iSpriteMax, //how many sprites in total for this animation
        m_iFrame = 0, //which frame we are at now
        m_iFrameMax; //number of frames for this sprite

    //Store Various Animation States For This Spritesheet
    std::map<std::string, AnimStateDefinition> animStates;

    std::string currentState;

public:
    void AddAnimState(std::string stateName, AnimStateDefinition asd);
    void PlayState(std::string stateName);

    SpriteExAnimated(SDL_Texture* tex, double x, double y, double a);
};
