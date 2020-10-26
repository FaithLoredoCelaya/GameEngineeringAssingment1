#include "Player.h"
#include "Game.h"
#include <algorithm> //for min/max functions

Player::Player(SDL_Texture* tex, double x, double y)
    : SpriteExAnimated(tex, x - 80, y - 80, 0)
{

    spriteSrcRect = { 0,0,70,80 };
    spriteDestRect = { (int)(m_X - 300),(int)(m_Y - 200)  ,140,160 };

    m_velX = 0.7f;
    m_velY = 0.5f;

    m_dRadius = 40;
    attackRange = 50;
    m_DX = 0.1f;
    m_DY = 0.5f;
    preJumpYVal = m_Y;
    isFlipped = false;
    collision = false;

    AddAnimState("Hadouken", AnimStateDefinition(0, 4, 60));
    AddAnimState("Idle", AnimStateDefinition(1, 4, 110, true, false));
    AddAnimState("Punch", AnimStateDefinition(2, 3, 60));
    AddAnimState("Move", AnimStateDefinition(3, 5, 90));

    AddAnimState("Kick", AnimStateDefinition(6, 5, 90));
    AddAnimState("Roundhouse", AnimStateDefinition(7, 5, 90));
    AddAnimState("Jump", AnimStateDefinition(8, 7, 90, false, true));
    AddAnimState("Crouch", AnimStateDefinition(9, 1, 20));

    animStates["Jump"].AddCallBackOnComplete(std::bind(&Player::OnJumpAnimComplete, this));
}

Player::~Player()
{

}

void Player::Render()
{
    this->SpriteExAnimated::Render(); //invoke the base class's Render()
}

void Player::Update()
{
    this->UpdatePlayer();
}

void Player::MovePlayer(bool isFwd)
{
    //Update the velocities 
    m_velX += m_DX * m_dSpeed;

    //clamp the velocity
    m_velX = min(max(m_velX, -(m_velX * fabs(m_DX))), (m_velMax * fabs(m_DX)));
    if (isFwd) {
        m_X += m_velX * 2.5; //updates X coord
    }
    else
        m_X -= m_velX * 2.5;

    PlayState("Move");
}

void Player::Jump() {
    m_velY += m_DY;
    m_velY = min(max(m_velY, -(m_velMax * fabs(m_DY))), (m_velMax * fabs(m_DY)));

    if (m_iFrame < 3)
    {
        if (m_Y >= 453) {
            m_Y -= m_velY;
        }
    }
    else if (m_iFrame > 3)
    {
        m_Y += m_velY;
    }
}

void Player::OnJumpAnimComplete() {
    m_Y = preJumpYVal;
}

void Player::UpdatePlayer()
{

    if (Game::Instance()->KeyDown(SDL_SCANCODE_D))
    {
        this->MovePlayer(true); //updates the animation
    }
    else if (Game::Instance()->KeyDown(SDL_SCANCODE_A))
    {
        this->MovePlayer(false);
    }
    else if (Game::Instance()->KeyDown(SDL_SCANCODE_S))
    {
        PlayState("Crouch");
    }
    else if (Game::Instance()->KeyDown(SDL_SCANCODE_SPACE))
    {
        if (currentState != "Jump") {
            PlayState("Jump");
        }
    }
    else if (Game::Instance()->KeyDown(SDL_SCANCODE_P))
    {
        PlayState("Punch");
        this->SetAttack("Punch");
    }
    else if (Game::Instance()->KeyDown(SDL_SCANCODE_K))
    {
        PlayState("Kick");
        this->SetAttack("Kick");
    }
    else if (Game::Instance()->KeyDown(SDL_SCANCODE_R))
    {
        PlayState("Roundhouse");
        this->SetAttack("Roundhouse");
    }
    else if (Game::Instance()->KeyDown(SDL_SCANCODE_H))
    {
        PlayState("Hadouken");
        this->SetAttack("Hadouken");
    }
    else {
        PlayState("Idle");
        cout << this->gm.GetHP() << endl;
    }

    if (currentState == "Jump")
        Jump();

    spriteSrcRect.x = spriteSrcRect.w * m_iFrame;
    this->UpdateDestRect();
}