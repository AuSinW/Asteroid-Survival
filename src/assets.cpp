#include <ClinetGFX.h>
#include "assets.h"
#include <time.h>
#include <stdlib.h>



double GetSlope(Pixel p1, Pixel p2){
    double dY = p1.y - p2.y;
    double dX = p1.x - p2.x;
    return dY/dX;
}

void MoveAsteroid(Asteroid& asteroid){
    MovePoly(asteroid.asteroid, asteroid.movementX, asteroid.movementY);
    RotatePoly(asteroid.asteroid, 0.0025, Pixel {GetMidpointPoly(asteroid.asteroid).first, GetMidpointPoly(asteroid.asteroid).second});
}



PolygonShape CreatePlayer(Framebuffer& fb, Pixel spawnLocation){
     
    Pixel p1{spawnLocation.x + 20, spawnLocation.y};
    Pixel p2{spawnLocation.x - 20, spawnLocation.y};
    Pixel p3{spawnLocation.x, spawnLocation.y+10};
    Pixel p4{spawnLocation.x, spawnLocation.y+40};
    LineSegment l1(p1, p3, 0x0000FF00);
    LineSegment l2(p3, p2);
    LineSegment l3(p2, p4);
    LineSegment l4(p4, p1);
    std::vector<LineSegment> x = {l1,l2,l3,l4};
    PolygonShape player(x);
    return player;
    
}



PolygonShape CreateAsteroid(Framebuffer& fb, int windowWidth, int windowHeight, double& moveX, double& moveY){
    srand(time(NULL));
    int numOfSides = (rand() % 5)+6;
    double radius = (rand()%25)+20;
    int x = rand() % 2;
    // moveX = 0.5;
    // moveY = 0.5;
    Pixel spawn;
    if(x){// Spawn on either the top or bottom
        int k = rand() % 2;
        Pixel x {(double)(rand() % windowWidth), k == 0 ? (double)-100 : (double)(windowHeight + 100)};
        if(k == 1){ //Spawn on the bottom screen
            moveY = -0.4;
        }else{
            moveY = 0.4;
        }
        int dest = rand() % (windowWidth/2) + (windowWidth/4);
        moveX = (dest-x.x)/2000;
        spawn = x;
    }else{
        int k = rand() % 2;
        Pixel x {k == 0 ? (double)-100 : (double)(windowWidth + 100), (double)(rand() % windowHeight)};
        if(k == 1) {
            moveX = -0.4;
        }else{
            moveX = 0.4;
        }
        int dest = rand() % (windowHeight/2) + (windowHeight/4);
        moveY = (dest-x.x)/2000;
        spawn = x;
    } 
    PolygonShape asteroid(numOfSides, 0xFFFFFFFF, radius, spawn, 0.707);
    return asteroid;
}