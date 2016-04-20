#include "gamemanager.h"

#include "defaultenemy.h"

GameManager::GameManager() {

}

Player GameManager::getPlayer() {
    return player;
}

void GameManager::setPlayer(Player player) {
    this->player = player;
}

std::vector<MapObject> GameManager::getStones() {
    return stones;
}

void GameManager::setStones(std::vector<MapObject> stones) {
    this->stones = stones;
}

std::vector<MapObject> GameManager::getFreeAreas() {
    return freeAreas;
}

void GameManager::setFreeAreas(std::vector<MapObject> freeAreas) {
    this->freeAreas = freeAreas;
}

std::vector<MapObject> GameManager::getRoads() {
    return roads;
}

void GameManager::setRoads(std::vector<MapObject> roads) {
    this->roads = roads;
}

std::vector<Tower *> GameManager::getTowers() {
    return towers;
}

std::vector<Enemy *> GameManager::getEnemies() {
    return enemies;
}

std::vector<Missle> GameManager::getMissles() {
    return missles;
}

void GameManager::loop() {
    // тут в enemies должен добавляться следующий монстр из волны, если прошла задержка
    enemies.push_back(new DefaultEnemy(0, 0));
    //---------

    for (std::vector<Enemy *>::iterator it = enemies.begin(); it != enemies.end(); ) {
        if (!(*it)->isAlive()) {
            // удаляем мертвых и начисляем игроку награду
            player.setMoney(player.getMoney() + (*it)->getBounty());
            delete *it;
            it = enemies.erase(it);
        } else {
            (*it)->loop();
            it++;
        }
    }
    for (Tower *tower : towers) {
        // Установка цели башни на враге в зоне досягаемости
        if (tower->getTarget() == NULL) {
            for (Enemy *enemy : enemies) {
                if (tower->distance(enemy) < tower->getRange()) {
                    tower->setTarget(enemy);
                    break;
                }
            }
        }
        if (tower->getTarget() != NULL) {
            // запускаем ракету (скорость пока магическое число)
            Missle missle(tower->getX(), tower->getY(), 0.1, tower->getDamage(),
                          tower->getTarget());
            missles.push_back(missle);
        }
        tower->loop();
    }
    for (std::vector<Missle>::iterator it = missles.begin(); it != missles.end(); ) {
        if (it->isExploded()) {
            it = missles.erase(it);
        } else {
            it->loop();
            it++;
        }
    }
}
