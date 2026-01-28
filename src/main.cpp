#include <iostream>
#include "assets.h"
#include "gamelogic.h"
#include <ClinetGFX.h>

int width = 800;
int height = 600;


int main() {

    srand(static_cast<unsigned>(time(nullptr)));
    bool alive = true;
    bool go = false;
    bool makeNew = true;
    double angleToReset = 0;
    Framebuffer fb;
    Win32Platform platform;

    int playerScore {0};
    std::string strScore {};
    
    BitmapFont font{};
    if (!Win32_Init(platform, fb, width, height, "Asteroids"))
        return -1;

    PolygonShape triangle(7, 0x00FF0000, 100, Pixel{(double)width/2, (double)height/2}, 0.707);
    ObjectBuffer objects;

    PolygonShape player = CreatePlayer(fb, Pixel{(double)width/2, (double)height/2});

    Asteroids asteroids;
    Asteroid asteroid(width, height);
    asteroids.add(asteroid);
    //Asteroid asteroid2(width, height);
    objects.add(player);


    std::vector<PolygonShape> pieces;

    // objects.add(asteroid2);
    //asteroids.add(asteroid2);
    // int numberOfAsteroids;
    // double move_X = 0;
    // double move_Y = 0;
    // double speed = 0.5;


    while (platform.running) {
        Input_Update();
        Win32_PumpMessages(platform);
        if(go){

            

            if(alive){ HandlePlayer(platform, fb, player, angleToReset); RotatePoly(player, angleToReset, Pixel {GetMidpointPoly(player).first, GetMidpointPoly(player).second});}


            HandleAsteroids(platform, fb, asteroids, makeNew, playerScore, alive);


            
            if(alive){
                objects.add(player);
  
            }else{
                MovePoly(pieces[0], 0.4, 0.2);
                MovePoly(pieces[1], -0.25, 0.3);
                MovePoly(pieces[2], -0.3, -0.2);
                RotatePoly(pieces[0], -0.01, Pixel {GetMidpointPoly(pieces[0]).first, GetMidpointPoly(pieces[0]).second});
                RotatePoly(pieces[1], 0.05, Pixel {GetMidpointPoly(pieces[1]).first, GetMidpointPoly(pieces[1]).second});
                RotatePoly(pieces[2], 0.02, Pixel {GetMidpointPoly(pieces[2]).first, GetMidpointPoly(pieces[2]).second});
                objects.add(pieces[0]);
                objects.add(pieces[1]);
                objects.add(pieces[2]);
            }
            for(Asteroid& a : asteroids.asteroids){
                    objects.add(a.asteroid);
                    if(alive && WillCollide(player, a.asteroid)){
                        alive = false;
                        player.color = 0x00FF0000;
                        makeNew = false;
                        pieces = DeathAnimation(player);
                        RotatePoly(player, -1*angleToReset, Pixel {GetMidpointPoly(player).first, GetMidpointPoly(player).second});
                        angleToReset = 0;
                    }
                }
            
            // objects.add(asteroid2);

            Render(fb, objects);
        }else{
            if(Input_IsKeyDown(VK_SPACE)) go = true;
            
        }

        Clear(fb, 0x00181818);
        if(!go) {
            PrintToScreen(fb, font, "PRESS SPACE TO START", width/2 - 120, height/2, 0xFFFFFFFF, 2);
        }else if(alive){
            strScore = std::to_string(playerScore);
            PrintToScreen(fb, font, "SCORE: " + strScore, 10, 10, 0xFFFFFFFF, 2);       
        }else{
            PrintToScreen(fb, font, "DEAD.", width/2 - 20, height/2, 0xFFFFFFFF, 2);
            PrintToScreen(fb, font, "FINAL SCORE: " + strScore, width/2 - 60, height/2 + 20, 0xFCD968, 2);
            PrintToScreen(fb, font, "PRESS 'SPACE BAR' TO PLAY AGAIN!", width/2 - 224, height/2 + 40, 0xFFFFFFFF, 2);
            if(Input_IsKeyDown(VK_SPACE)){
                asteroids.clear();
                go = true;
                alive = true;
                player.color = 0x0000FF00;
                asteroids.add(asteroid);
                playerScore = 0;
                
                makeNew = true;
            };
        }

        
        Render(fb, objects);
        Win32_Present(platform, fb);
        objects.clear();
        RotatePoly(player, -1*angleToReset, Pixel {GetMidpointPoly(player).first, GetMidpointPoly(player).second});
  

    }

    Win32_Shutdown(fb);
    return 0;
}
