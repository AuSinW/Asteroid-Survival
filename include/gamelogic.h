#include "assets.h"
#include <ClinetGFX.h>


void HandleAsteroids(const Win32Platform& platform, Framebuffer& fb, Asteroids& asteroids, bool makeNew, int& playerScore, bool isAlive);

void HandlePlayer(const Win32Platform& platform, Framebuffer& fb, PolygonShape& player, double& angleToResetPlayer);

void HandlePlayerDirection(PolygonShape& player, double moveX, double moveY, double& angleToResetPlayer);

std::vector<PolygonShape> DeathAnimation(PolygonShape& player);

