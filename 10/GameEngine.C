#include "GameEngine.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h> 
#include <termios.h> 
#include <fcntl.h>
#include <algorithm> 
#include <sstream> 


#include "Shell.h"
#include "Torpedo.h"
#include "Missile.h"
#include "GunBoat.h"
#include "Destroyer.h"
#include "Cruiser.h"
#include "Bomber.h"

using namespace std;


int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}


GameEngine::GameEngine() : isRunning(true), gameTick(0), currentLevel(1), targetCoins(WIN_COIN_BASE) {
    srand(time(0));
   
    player = new Player(MAP_HEIGHT - 2, MAP_WIDTH / 2);
}

GameEngine::~GameEngine() {
    delete player;
    for (auto e : enemies) delete e;
    for (auto p : projectiles) delete p;
    for (auto i : items) delete i;
    for (auto o : obstacles) delete o;
}


bool GameEngine::isBlocked(int r, int c) {
    if (r < 0 || r >= MAP_HEIGHT || c < 0 || c >= MAP_WIDTH) return true; 
    for (auto o : obstacles) {
        if (o->getPos().r == r && o->getPos().c == c) return true;
    }
    return false;
}


bool GameEngine::isFootprintBlocked(GameObject* obj, int r, int c) {
  
    if (isBlocked(r, c)) return true;


    
    Player* p = dynamic_cast<Player*>(obj);
    if (p) {
        if (p->getVertical()) {
          
            if (isBlocked(r-1, c)) return true;
            if (isBlocked(r+1, c)) return true;
        } else {
        
            if (isBlocked(r, c-1)) return true;
            if (isBlocked(r, c+1)) return true;
        }
        return false;
    }


    Bomber* b = dynamic_cast<Bomber*>(obj);
    if (b) {
    
        if (isBlocked(r-1, c)) return true;
        if (isBlocked(r+1, c)) return true;

        if (isBlocked(r, c+1)) return true;
        return false;
    }

    Cruiser* cr = dynamic_cast<Cruiser*>(obj);
    if (cr) {
        if (isBlocked(r, c-1)) return true;
        return false;
    }

  
    return false;
}


void GameEngine::loadLevel() {
  
    for (auto o : obstacles) { delete o; } obstacles.clear();
    for (auto e : enemies) { delete e; } enemies.clear();
    for (auto p : projectiles) { delete p; } projectiles.clear();
    for (auto i : items) { delete i; } items.clear();

   
    string filename = "map.txt"; 
    ifstream infile(filename);

    if (infile.is_open()) {
        string line;
        int r = 0;
        while (getline(infile, line) && r < MAP_HEIGHT) {
            for (int c = 0; c < (int)line.length() && c < MAP_WIDTH; c++) {
                if (line[c] == '#') {
                    obstacles.push_back(new Obstacle(r, c));
                }
            }
            r++;
        }
        infile.close();
    } else {

        int obsCount = 20 + (currentLevel * 5); 
        for(int i=0; i<obsCount; i++) {
            int r = rand() % (MAP_HEIGHT - 5);
            int c = rand() % MAP_WIDTH;
            if (!isBlocked(r, c)) {
                obstacles.push_back(new Obstacle(r, c));
            }
        }
    }
}


void GameEngine::spawnEnemies() {
    int chance;
    if (currentLevel == 1) chance = 100; 
    else if (currentLevel == 2) chance = 35;
    else chance = max(10, 30 - (currentLevel - 2) * 5); 

    if (rand() % chance == 0) {
        int type = rand() % 3;
        int r = rand() % (MAP_HEIGHT / 2);
        int c = rand() % MAP_WIDTH;
        
   
        if (!isBlocked(r, c)) { 
            if (type == 0) enemies.push_back(new GunBoat(r, c));
            else if (type == 1) enemies.push_back(new Destroyer(r, c));
            else enemies.push_back(new Cruiser(r, c));
        }
    }
   
    if (rand() % (chance * 2) == 0) {
        enemies.push_back(new Bomber(rand() % (MAP_HEIGHT/2), 0));
    }
}


void GameEngine::spawnItems() {
    if (rand() % 150 == 0) {
        int r = rand() % (MAP_HEIGHT - 5);
        int c = rand() % MAP_WIDTH;
        if (!isBlocked(r, c)) {
            ItemType type = (rand() % 2 == 0) ? MEDICAL_PACK : WEAPON_PACK;
            items.push_back(new Item(r, c, type));
        }
    }
}


void GameEngine::handleInput() {
    if (kbhit()) {
        char c = getchar();
        Point pPos = player->getPos();
        Point next = pPos;

        if (c == '\033') { 
            getchar(); char dir = getchar(); 
            if (dir == 'A') { next.r--; player->setVertical(true); } 
            if (dir == 'B') { next.r++; player->setVertical(true); } 
            if (dir == 'D') { next.c--; player->setVertical(false); } 
            if (dir == 'C') { next.c++; player->setVertical(false); } 
            
           
            if (!isFootprintBlocked(player, next.r, next.c)) {
                player->setPos(next.r, next.c);
            }
        }
        else {
            if (c == 'q') isRunning = false;
            
        
            
       
            if (c == ' ' && player->useShells(1)) {
                projectiles.push_back(new Shell(pPos.r-1, pPos.c, UP, true));
            }
            
       
            if (c == 'a' && player->useShells(3)) {
                if (player->getVertical()) {
                    int spawnCol = pPos.c - 1;
                    projectiles.push_back(new Shell(pPos.r, spawnCol, LEFT, true));
                    projectiles.push_back(new Shell(pPos.r-1, spawnCol, LEFT, true));
                    projectiles.push_back(new Shell(pPos.r+1, spawnCol, LEFT, true));
                } else {
                    int spawnRow = pPos.r - 1;
                    projectiles.push_back(new Shell(spawnRow, pPos.c, UP, true));
                    projectiles.push_back(new Shell(spawnRow, pPos.c-1, UP, true));
                    projectiles.push_back(new Shell(spawnRow, pPos.c+1, UP, true));
                }
            }

  
            if (c == 'd' && player->useShells(3)) {
                if (player->getVertical()) {
                    int spawnCol = pPos.c + 1;
                    projectiles.push_back(new Shell(pPos.r, spawnCol, RIGHT, true));
                    projectiles.push_back(new Shell(pPos.r-1, spawnCol, RIGHT, true));
                    projectiles.push_back(new Shell(pPos.r+1, spawnCol, RIGHT, true));
                } else {
                    int spawnRow = pPos.r + 1;
                    projectiles.push_back(new Shell(spawnRow, pPos.c, DOWN, true));
                    projectiles.push_back(new Shell(spawnRow, pPos.c-1, DOWN, true));
                    projectiles.push_back(new Shell(spawnRow, pPos.c+1, DOWN, true));
                }
            }

 
            if (c == 'u' && player->useMissiles(1)) {
                GameObject* target = nullptr;
      
                if (!enemies.empty()) target = enemies[0]; 
                projectiles.push_back(new Missile(pPos.r-1, pPos.c, UP, true, target));
            }
        }
    }
}


void GameEngine::checkCollisions() {
    Point pPos = player->getPos();

 
    for (auto p : projectiles) {
        if (!p->isActive()) continue;
        Point pp = p->getPos();
        
       
        if (isBlocked(pp.r, pp.c)) { 
            p->deactivate(); 
            continue; 
        }

        if (p->isFriendly()) {
            for (auto e : enemies) {
                bool hit = false;
         
                Bomber* bomber = dynamic_cast<Bomber*>(e);
                if (bomber && bomber->isActive()) {
                    Point ep = e->getPos();
                    if (abs(pp.r - ep.r) <= 1 && abs(pp.c - ep.c) <= 1) hit = true;
                } else {
               
                    if (e->getPos() == pp && e->isActive()) hit = true;
                }

                if (hit) {
                    Missile* missile = dynamic_cast<Missile*>(p);
             
                    if (missile && bomber) continue; 
                    
                    Enemy* ship = dynamic_cast<Enemy*>(e);
                    if (ship) {
                        ship->takeDamage(p->getDamage());
                        p->deactivate(); 
                        if (ship->isDestroyed()) player->addCoins(ship->getCoinValue());
                    } else if (bomber) {
                     
                        p->deactivate(); 
                    }
                }
            }
        } else {
         
            bool hit = false;
            if (player->getVertical()) {
                 if (pp.c == pPos.c && abs(pp.r - pPos.r) <= 1) hit = true;
            } else {
                 if (pp.r == pPos.r && abs(pp.c - pPos.c) <= 1) hit = true;
            }
            if (hit) {
                player->takeDamage(p->getDamage());
                p->deactivate();
            }
        }
    }
    

    for (auto it = items.begin(); it != items.end(); ) {
        if ((*it)->canPickUp(pPos)) {
            if ((*it)->getType() == MEDICAL_PACK) player->heal(100);
            else player->addAmmo(20, 1);
            (*it)->deactivate();
        }
        if (!(*it)->isActive()) { delete *it; it = items.erase(it); } else ++it;
    }
    
  
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        if (!(*it)->isActive()) { delete *it; it = projectiles.erase(it); } else ++it;
    }
    
 
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if (!(*it)->isActive()) {
            GameObject* dyingEnemy = *it;
            for (auto p : projectiles) {
                Missile* m = dynamic_cast<Missile*>(p);
                if (m && m->getTarget() == dyingEnemy) m->clearTarget();
            }
            delete *it; it = enemies.erase(it); 
        } else ++it;
    }
}

void GameEngine::render() {
    for(int i=0; i<MAP_HEIGHT; i++) {
        for(int j=0; j<MAP_WIDTH; j++) {
            map[i][j] = ' '; 
            colorMap[i][j] = RESET;
        }
    }
    for (auto o : obstacles) o->draw(map, colorMap);
    for (auto i : items) i->draw(map, colorMap);
    for (auto e : enemies) e->draw(map, colorMap);
    for (auto p : projectiles) p->draw(map, colorMap);
    player->draw(map, colorMap);

    stringstream ss;
    ss << "\033[H"; 
    ss << YELLOW << "LEVEL " << currentLevel << RESET 
       << " | HP: " << GREEN << player->getHealth() << RESET 
       << " | Shells: " << player->getNumShells() 
       << " | Missiles: " << player->getNumMissiles()
       << " | Coins: " << YELLOW << player->getCoins() << "/" << targetCoins << RESET << endl;
    ss << "--------------------------------------------------------------------------------" << endl;
    for(int i=0; i<MAP_HEIGHT; i++) {
        for(int j=0; j<MAP_WIDTH; j++) {
            ss << colorMap[i][j] << map[i][j] << RESET;
        }
        ss << endl;
    }
    cout << ss.str() << flush;
}


void GameEngine::run() {
    cout << "\033[2J\033[H"; 
    cout << "\033[?25l";
    while (isRunning && player->getHealth() > 0) {
        loadLevel(); 
        cout << "\033[2J\033[H";
        cout << "Entering Level " << currentLevel << "..." << endl;
        sleep(1);
        cout << "\033[2J\033[H";
        while (isRunning && player->getHealth() > 0 && player->getCoins() < targetCoins) {
            handleInput();
            spawnEnemies();
            spawnItems();
            player->update();
            
      
            for (auto e : enemies) { 
                Point oldPos = e->getPos(); 
                e->update();                
                
               
                if (isFootprintBlocked(e, e->getPos().r, e->getPos().c)) {
                    
                    e->setPos(oldPos.r, oldPos.c);
                    
               
                    Bomber* bomber = dynamic_cast<Bomber*>(e);
                    if (bomber) {
                        bomber->reverseDirection();
                    }
                }

               
                vector<Projectile*> newShots = e->attack(player);
                for (auto s : newShots) projectiles.push_back(s);
            }
            
            for (auto p : projectiles) p->update();
            for (auto i : items) i->update();
            checkCollisions();
            render();
            usleep(50000); 
            gameTick++;
        }
        if (player->getCoins() >= targetCoins) {
            currentLevel++;
            targetCoins += 1000;
            player->heal(300); 
        }
    }
    cout << "\033[?25h";
    cout << "\n" << (player->getHealth() > 0 ? GREEN "YOU QUIT!" : RED "GAME OVER!") << RESET << endl;
}