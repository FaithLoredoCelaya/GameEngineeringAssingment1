#include "Enemy.h"
#include <algorithm> //for min/max functions

Enemy::Enemy(SDL_Texture* tex, double x, double y) : Player(tex, x, y)
{
    spriteSrcRect = { 0,0,70,80 };
    spriteDestRect = { (int)(m_X - 200),(int)(m_Y - 200) ,140,160 };

    m_velX = 0.7f;
    m_velY = 0.5f;

    isFlipped = true;
    m_dRadius = 40;
    collision = false;
    attackRange = 50;
    canAttack = false;

    randDefNum = rand() % 100 + 1;

    AddAnimState("Hadouken", AnimStateDefinition(0, 4, 60));
    AddAnimState("Idle", AnimStateDefinition(1, 4, 110, true, false));
    AddAnimState("Punch", AnimStateDefinition(2, 3, 60));
    AddAnimState("Move", AnimStateDefinition(3, 5, 90));

    AddAnimState("Kick", AnimStateDefinition(6, 5, 90));
    AddAnimState("Roundhouse", AnimStateDefinition(7, 5, 90));
    AddAnimState("Jump", AnimStateDefinition(8, 7, 90, false, true));
    AddAnimState("Crouch", AnimStateDefinition(9, 1, 20));

}

Enemy::~Enemy()
{

}

void Enemy::Render()
{
    this->SpriteExAnimated::Render(); //invoke the base class's Render()
}

void Enemy::Update()
{
    this->UpdateEnemy();
}

void Enemy::UpdateEnemy()
{
    if (collision) {
        this->Defend();
    }
    else if (canAttack) {
        this->Attack();
    }
    else if (!canAttack) {
        randMove = rand() % 1000 + 1;
        this->Move();
    }
    spriteSrcRect.x = spriteSrcRect.w * m_iFrame;
    this->UpdateDestRect();
}

void Enemy::Attack() {
    if (randAttackNum <= 50) {
        attackType = 1;
        PlayState("Punch");
    }
    else if (randAttackNum <= 100) {
        attackType = 2;
        PlayState("Kick");
    }
    else if (randAttackNum <= 150) {
        attackType = 3;
        PlayState("Roundhouse");
    } else if(randAttackNum <=200){
        attackType = 4;
        PlayState("Hadouken");
    }
    else
    {
        PlayState("Idle");
    }
    
}

void Enemy::Defend() {

    if (randDefNum <= 50) {
        PlayState("Crouch");
    }
    else {
        //Take Hit?? 
        this->TakeHit();
    }
}

void Enemy::Move() {
    currentTime = SDL_GetTicks();
    if (currentTime > lastTime + 3000) {
        m_velX += m_DX * m_dSpeed;
        m_velX = min(max(m_velX, -(m_velX * fabs(m_DX))), (m_velMax * fabs(m_DX)));
        if (randMove <= 500) {
            m_X -= m_velX * 30;
        }
        else {
            m_X += m_velX * 30;
        }
        PlayState("Move");
        lastTime = currentTime;
    }
    else {
        PlayState("Idle");
        randAttackNum = rand() % 500 + 1;
        randDefNum = rand() % 100 + 1;
    }
}

void Enemy::TakeHit() {
    if (dmgToReceive == 1)
    {
        health.TakeDamage(5);
    }
    else if (dmgToReceive == 2)
    {
        health.TakeDamage(10);
    }
    else if (dmgToReceive == 3)
    {
        health.TakeDamage(15);
    }
    else if(dmgToReceive == 4)
    {
        health.TakeDamage(30);
    }
    m_X += 0.1f;
    cout << "Enemy Health" << health.GetHP() << "\n";
}