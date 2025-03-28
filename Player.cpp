#include "Player.hpp"
#include <math.h>
#include <iostream>
#include "utils.hpp"
#include <cmath>

int map2[]=           //the map array. Edit to change level but keep the outer walls
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,1,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,1,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,	
};




Player::Player()
{
    m_player.h = 10;
    m_player.w = 10;
    m_player.x = 150;
    m_player.y = 400;
    m_playerDeltas.angle = 90;
    m_playerDeltas.deltaX = cos(degToRad(m_playerDeltas.angle));
    m_playerDeltas.deltaY = -sin(degToRad(m_playerDeltas.angle));
}

Player::~Player()
{}

void Player::movePlayer(Directions direction)
{
    switch (direction)
    {
        case Directions::LEFT:
            m_playerDeltas.angle += 5;
            m_playerDeltas.radians = degToRad(fixAngle((m_playerDeltas.angle)));
            m_playerDeltas.deltaX = cos(m_playerDeltas.radians);
            m_playerDeltas.deltaY = -sin(m_playerDeltas.radians);
            break;
        case Directions::RIGHT:
            m_playerDeltas.angle -= 5;
            m_playerDeltas.radians = degToRad(fixAngle((m_playerDeltas.angle)));
            m_playerDeltas.deltaX = cos(m_playerDeltas.radians);
            m_playerDeltas.deltaY = -sin(m_playerDeltas.radians);
            break;
        case Directions::UP:
            m_player.x += m_playerDeltas.deltaX * 5.0f;
            m_player.y += m_playerDeltas.deltaY * 5.0f;
            break;
        case Directions::DOWN:
            m_player.x -= m_playerDeltas.deltaX * 5.0f;
            m_player.y -= m_playerDeltas.deltaY * 5.0f;
            break;
        default:
            break;
    }
}

void Player::calculateRays(SDL_Renderer * renderer)
{
    int r, mx, my, mp, dof;
    float rayX = 0, rayY = 0, xOffset = 0, yOffset = 0, rayAngle = 0, vx = 0, vy = 0;
    float disV, disH;
    rayAngle = fixAngle(m_playerDeltas.angle + 30);
    for(r = 0; r < 60; r++)
    {
        float playerRadians = degToRad(rayAngle);
        dof=0; disV=100000;
        float playerTan = tan(playerRadians);
        //verical lines
        if(cos(playerRadians) > 0.0001)
        {
            rayX = (((int)m_player.x>>6)<<6) + 64;
            rayY = (m_player.x-rayX) * playerTan+m_player.y;
            xOffset = 64;
            yOffset = -xOffset*playerTan;
        }
        else if(cos(playerRadians) < -0.0001)
        {
            rayX = (((int)m_player.x>>6)<<6) - 0.0001;
            rayY = (m_player.x-rayX) * playerTan+m_player.y;
            xOffset = -64;
            yOffset = -xOffset*playerTan;
        }
        else
        {
            rayX = m_player.x;
            rayY = m_player.y;
            dof = 8;
        }
        while(dof < 8)
        {
            mx = rayX/64;
            my = rayY/64;
            mp = my*8+mx; 
            if(mp > 0 && mp < 64 && map2[mp] == 1) 
            {
                dof = 8;
                disV=cos(playerRadians)*(rayX-m_player.x)-sin(playerRadians)*(rayY-m_player.y);
            }
            else
            {   
                rayX += xOffset;
                rayY += yOffset;
                dof += 1;
            }
        }
        vx = rayX; 
        vy = rayY;
        //horizontal line
        dof=0; disH=100000;
        playerTan=1.0/playerTan; 

        if(sin(playerRadians) > 0.0001)
        { 
            rayY = (((int)m_player.y>>6)<<6) -0.0001; 
            rayX = (m_player.y-rayY)*playerTan+m_player.x; 
            yOffset = -64; 
            xOffset = -yOffset*playerTan;
        }//looking up 
        else if(sin(playerRadians) < -0.0001)
        { 
            rayY = (((int)m_player.y>>6)<<6)+64;      
            rayX = (m_player.y-rayY)*playerTan+m_player.x; 
            yOffset = 64; 
            xOffset = -yOffset*playerTan;
        }//looking down
        else{ 
            rayX=m_player.x; 
            rayY=m_player.y; 
            dof=8;
        }                                                   //looking straight left or right
       
        while(dof<8) 
        { 
            mx = rayX/64;
            my = rayY/64;
            mp=my*8+mx;                          
            if(mp>0 && mp<64 && map2[mp]==1)
            { 
                dof=8; 
                disH=cos(playerRadians)*(rayX-m_player.x)-sin(playerRadians)*(rayY-m_player.y);
            }//hit         
            else
            { 
                rayX +=xOffset; 
                rayY +=yOffset;  
                dof += 1;
            }                                               //check next horizontal
        }
        SDL_SetRenderDrawColor(renderer, 255,255,255, SDL_ALPHA_OPAQUE);
        if(disV<disH)
        { 
            rayX=vx; rayY=vy; disH=disV; 
            SDL_SetRenderDrawColor(renderer, 200,200,200, SDL_ALPHA_OPAQUE);
        }                  //horizontal hit first
        int ca=fixAngle(m_playerDeltas.angle-rayAngle); 

        disH=disH*cos(degToRad(ca));
        int lineH = (64*512)/(disH); 
        if(lineH>512)
        { 
            lineH=512;
        }                     //line height and limit
        int lineOff = 256 - lineH/2;                         

        SDL_Rect wall;
        wall.h = lineH;
        wall.w = 10;
        wall.x = r*10;
        wall.y = lineOff;
        SDL_RenderFillRect(renderer, &wall);

        rayAngle = fixAngle(rayAngle - 1);
    }
}

void Player::renderPlayer(SDL_Renderer* renderer)
{
    calculateRays(renderer);
}

