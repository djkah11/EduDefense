#ifndef GAMEOBJECTCREATOR_H
#define GAMEOBJECTCREATOR_H

#include "gameobject.h"
#include "mapobject.h"
#include <string>
#include <vector>
//базовый класс для карт
class MapObjects {
  public:
    std::vector<MapObject> freeAreas;
    std::vector<MapObject> roads;
};

//обычная карта с камнями
class UsualMap : public MapObjects {
  public:
    std::vector<MapObject> stones;
};

//Чтение из файла и создание игровых объектов - Абстрактный класс
class ObjectsCreator {
  public:
    ObjectsCreator(std::string filename) : file(filename) {}
    int getFreeAreasCount() { return freeAreasCount; }
    int getNumRoads() { return roadsCount; }

  protected:
    int freeAreasCount;
    int roadsCount;
    virtual void readfile() = 0;
    virtual Area getAreaByChar(char c) = 0;
    std::string file;
    int stonesCount;
    const int texture_size = 60; //размер текстурки
    std::string mapStates;
};

class UsualMapCreator : public ObjectsCreator {
  public:
    UsualMap usualmap;
    UsualMapCreator(std::string filename);
    int getStonesCount() { return stonesCount; }
    virtual void readfile();

  protected:
    virtual Area getAreaByChar(char c);
};

#endif // GAMEOBJECTCREATOR_H
