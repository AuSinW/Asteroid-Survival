#include "assets.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

constexpr double SCREEN_WIDTH = 800.0;
constexpr double SCREEN_HEIGHT = 600.0;
constexpr double MARGIN = 50.0;

bool shouldDestroy(const Asteroid& a, double x, double y, int w, int h) {
    if (a.movementX > 0 && x > w + MARGIN) return true;   // moving right
    if (a.movementX < 0 && x < -MARGIN) return true;      // moving left
    if (a.movementY > 0 && y > h + MARGIN) return true;   // moving down
    if (a.movementY < 0 && y < -MARGIN) return true;      // moving up

    return false;
}


void HandlePlayerDirection(PolygonShape& player, double moveX, double moveY, double& angleToResetPlayer){
    int X = moveX*2;
    int Y = moveY*2;
    // auto k = GetMidpointPoly(player);
    // double oX = k.first;
    // double oY = k.second;
    switch(X){
        case 0:
            switch(Y){
                case 0:
                    angleToResetPlayer = 0; //sample breakout
                    break;
                case 1:
                    angleToResetPlayer = 0;
                    break;
                case -1:
                    angleToResetPlayer = M_PI;
                    //RotatePoly(player, angleToResetPlayer, Pixel {oX, oY}); 
                    break;
            }
            break;

        case 1:
            switch(Y){
                case 0:
                    angleToResetPlayer = -M_PI*0.5;
                    break;
                case 1:
                    angleToResetPlayer = -M_PI/4;
                    break;
                case -1:
                    angleToResetPlayer = -3*M_PI/4;
                    //RotatePoly(player, angleToResetPlayer, Pixel {oX, oY});
                    break;
            }
        break;
        case -1:
            switch(Y){
                case 0:
                    angleToResetPlayer = M_PI*0.5;
                    break;
                case 1:
                    angleToResetPlayer = M_PI/4;
                    break;
                case -1:
                    angleToResetPlayer = 3*M_PI/4;
                    //RotatePoly(player, angleToResetPlayer, Pixel {oX, oY}); 
                    break;
            }
        break;
    }

}

void HandleAsteroids(const Win32Platform&, Framebuffer&, Asteroids& asteroids, bool makeNew, int& playerScore, bool isAlive) {

    std::vector<size_t> indexToRemove;

    for (size_t i = 0; i < asteroids.asteroids.size(); i++) {
        Asteroid& a = asteroids.asteroids[i];

        auto [oX, oY] = GetMidpointPoly(a.asteroid);

        MovePoly(a.asteroid, a.movementX, a.movementY);
        RotatePoly(a.asteroid, 0.0025, {oX, oY});

        if (shouldDestroy(a, oX, oY, 800, 600)) {
            indexToRemove.push_back(i);
            if(isAlive) playerScore += a.value;
        }
    }

    for (size_t idx : indexToRemove) {
        asteroids.removeFast(idx);
    }
    if(makeNew){
        for (size_t i = 0; i < indexToRemove.size(); i++) {
            asteroids.addNew(Asteroid(800, 600));
            if(rand() % 100 < 15){
                asteroids.addNew(Asteroid(800, 600));
            }
        }
    }
}


void HandlePlayer(const Win32Platform& platform, Framebuffer& fb, PolygonShape& player, double& angleToResetPlayer){
    double speed = 0.5;
    double move_X = 0;
    double move_Y = 0;
    if(Input_IsKeyDown(VK_UP)) move_Y += -speed;
    if(Input_IsKeyDown(VK_DOWN)) move_Y += speed;
    if(Input_IsKeyDown(VK_LEFT)) move_X += -speed;
    if(Input_IsKeyDown(VK_RIGHT)) move_X += speed;
    MovePoly(player, move_X, move_Y);
    HandlePlayerDirection(player, move_X, move_Y, angleToResetPlayer);
    
};

std::vector<PolygonShape> DeathAnimation(PolygonShape& player){
    std::vector<PolygonShape> pieces;

    // Step 1: extract vertices from lineSegments
    std::vector<Pixel> vertices;
    for (const auto& seg : player.lineSegments) {
        vertices.push_back(seg.p1);
    }

    // Step 2: compute midpoint
    auto midpoint = GetMidpointPoly(player);

    // Step 3: build triangles
    for (size_t i = 0; i < 3; i++) {
        Pixel p1 = vertices[i];
        Pixel p2 = vertices[(i + 1) % 3]; // wrap around

        std::vector<LineSegment> segs;
        segs.push_back(LineSegment{ p1, p2, player.color});
        segs.push_back(LineSegment{ p2, Pixel {midpoint.first, midpoint.second} });
        segs.push_back(LineSegment{ Pixel {midpoint.first, midpoint.second}, p1 });

        pieces.emplace_back(segs);
    }

    return pieces;
}