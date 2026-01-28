#pragma once
#include <ClinetGFX.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
double GetSlope(Pixel p1, Pixel p2);


struct Asteroid{
    PolygonShape asteroid;
    // int numOfSides {};
    // double radius {};
    // uint32_t color {};
    // double locationX {};
    // double locationY {};
    int value;
    double movementX {};
    double movementY {};

    Asteroid(double width, double height){
        //srand(time(NULL));

        double absSpeed = 0.4;
        double locationX {}, locationY{};
        int boolean1 = rand() % 2, boolean2 = rand() % 2;
        double radius = (rand() % 25) + 25;
        if(boolean1){// Spawn location is either TOP or BOTTOM
            locationX = (rand() % (int)width);
            locationY = boolean2 == 0 ? 0 - radius : height + radius;
        }else{// Spawn location is either LEFT or RIGHT
            locationX = boolean2 == 0 ? 0 - radius : width + radius;  
            locationY = (rand() % (int)height);          
        }
        // locationX = width/4;
        // locationY = height/4;
        double k = 0;
        Pixel destination = {width/2, height/2};

        double dX = destination.x - locationX;
        double dY = destination.y - locationY;
        k = pow(absSpeed*absSpeed/(dX*dX + dY*dY), 0.5);
        //double slope = GetSlope({locationX, locationY}, destination);
        this->movementX = dX*k;
        this->movementY = dY*k;
        // if(locationX >= 0){
        //     this->movementX *= -1;
        // }
        // if(locationY >= 0){
        //     this->movementY *= -1;
        // }

        // this->movementX = 0.05;
        // this->movementY = 0.05;
        this->value = 50+radius;
        this->asteroid = PolygonShape((rand() % 8) + 7, 0xFFFFFFF, radius, {locationX, locationY}, 0.99);


    }
};

struct Asteroids{
    std::vector<Asteroid> asteroids;

    Asteroids() = default;

    void add(Asteroid& a){
        asteroids.emplace_back(a);
    }
    void addNew(const Asteroid& a){
        asteroids.push_back(a);
    }    

    void clear(){
        asteroids.clear();
    }
    void removeFast(size_t index) {
        this->asteroids[index] = asteroids.back();
        this->asteroids.pop_back();
    }
};



void MoveAsteroid(Asteroid& asteroid);

PolygonShape CreatePlayer(Framebuffer& fb, Pixel spawnLocation);

// PolygonShape CreateAsteroid(Framebuffer& fb, int windowHeight, int windowWidth, double& moveX, double& moveY);
