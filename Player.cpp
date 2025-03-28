#include <iostream>
#include <cmath>
#include "player.hpp"
#include "utils.hpp"

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
    player_.h = 10;
    player_.w = 10;
    player_.x = 150;
    player_.y = 400;
    player_deltas_.angle = 90;
    player_deltas_.deltaX = cos(DegToRad(player_deltas_.angle));
    player_deltas_.deltaY = -sin(DegToRad(player_deltas_.angle));
}

Player::~Player()
{}

void Player::MovePlayer(Directions direction)
{
    switch (direction)
    {
        case Directions::LEFT:
            player_deltas_.angle += 5;
            player_deltas_.radians = DegToRad(FixAngle((player_deltas_.angle)));
            player_deltas_.deltaX = cos(player_deltas_.radians);
            player_deltas_.deltaY = -sin(player_deltas_.radians);
            break;
        case Directions::RIGHT:
            player_deltas_.angle -= 5;
            player_deltas_.radians = DegToRad(FixAngle((player_deltas_.angle)));
            player_deltas_.deltaX = cos(player_deltas_.radians);
            player_deltas_.deltaY = -sin(player_deltas_.radians);
            break;
        case Directions::UP:
            player_.x += player_deltas_.deltaX * 5.0f;
            player_.y += player_deltas_.deltaY * 5.0f;
            break;
        case Directions::DOWN:
            player_.x -= player_deltas_.deltaX * 5.0f;
            player_.y -= player_deltas_.deltaY * 5.0f;
            break;
        default:
            break;
    }
}

void Player::CalculateRays(SDL_Renderer * renderer)
{
    int r, mx, my, mp, dof;
    float rayX = 0, rayY = 0, xOffset = 0, yOffset = 0, rayAngle = 0, vx = 0, vy = 0;
    float disV, disH;
    rayAngle = FixAngle(player_deltas_.angle + 30);
    for(r = 0; r < 60; r++)
    {
        float playerRadians = DegToRad(rayAngle);
        dof=0; disV=100000;
        float playerTan = tan(playerRadians);
        //verical lines
        if(cos(playerRadians) > 0.0001)
        {
            rayX = (((int)player_.x>>6)<<6) + 64;
            rayY = (player_.x-rayX) * playerTan+player_.y;
            xOffset = 64;
            yOffset = -xOffset*playerTan;
        }
        else if(cos(playerRadians) < -0.0001)
        {
            rayX = (((int)player_.x>>6)<<6) - 0.0001;
            rayY = (player_.x-rayX) * playerTan+player_.y;
            xOffset = -64;
            yOffset = -xOffset*playerTan;
        }
        else
        {
            rayX = player_.x;
            rayY = player_.y;
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
                disV=cos(playerRadians)*(rayX-player_.x)-sin(playerRadians)*(rayY-player_.y);
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
            rayY = (((int)player_.y>>6)<<6) -0.0001; 
            rayX = (player_.y-rayY)*playerTan+player_.x; 
            yOffset = -64; 
            xOffset = -yOffset*playerTan;
        }//looking up 
        else if(sin(playerRadians) < -0.0001)
        { 
            rayY = (((int)player_.y>>6)<<6)+64;      
            rayX = (player_.y-rayY)*playerTan+player_.x; 
            yOffset = 64; 
            xOffset = -yOffset*playerTan;
        }//looking down
        else{ 
            rayX=player_.x; 
            rayY=player_.y; 
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
                disH=cos(playerRadians)*(rayX-player_.x)-sin(playerRadians)*(rayY-player_.y);
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
        int ca=FixAngle(player_deltas_.angle-rayAngle); 

        disH=disH*cos(DegToRad(ca));
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

        rayAngle = FixAngle(rayAngle - 1);
    }
}

void Player::RenderPlayer(SDL_Renderer* renderer)
{
    CalculateRays(renderer);
}

