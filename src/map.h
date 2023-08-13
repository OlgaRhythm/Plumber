#pragma once
#include "units.h"
#include "creatures.h"
#include "objects.h"

#include <iostream>
#include <fstream>

/*//////////////////////////////////////////!!!!!!!
Карты должны будут изначально храниться в текстовом файле. (в моём случае 5 карт)
Память под новую карту выделяется в начале каждой сцены, старая очищается
Сигнал о смене карты - персонаж сверху наступает на трубу перемещения (Teleport)
Этот сигнал вызывается в объекте класса Teleport. В нём будет метод, который заставляет карту смениться
1 Очистка памяти
2 Выделение 
3 Заполнение

Фон хранится в массиве char backgroundObjects
Объекты - в двумерном массиве Unit inanimateObjects, так как важно их местоположение на экране для отслеживания коллизий
Существа - в массиве Unit aliveObjects, в виде списка (или односвязный список можно применить)

Поля класса Map доступны классу Creature и его наследникам для использования в методах: Collision
*///////////////////////////////////////////!!!!!!!!


// карта - хранилище. Констукторы - для заполнения массивов
class Map {
public:
    /// заполнение из тестового файла
    Map(char const fN_bgO[17], char const fN_iO[16], char const fN_aO[16]) {
        std::ifstream fN_bgO_in, fN_iO_in, fN_aO_in;
        fN_bgO_in.open(fN_bgO);
        fN_iO_in.open(fN_iO);
        fN_aO_in.open(fN_aO);

        // читаем символы бэкграунда
        // readFromFileBackgroundObjects(&fN_bgO_in, H_bgO, W_bgO, backgroundObjects);
        readFromFileBackgroundObjects(&fN_iO_in, H_bgO, W_bgO, backgroundObjects); //!!! Пластырь !!!/
        
        // заполняем массив интерактивных объектов
        readFromFileInanimateObjects(&fN_iO_in, H_iO, W_iO, inanimateObjects);
        
        // заполняем список живых существ (кроме гг)
        //!!! ДОДЕЛАТЬ                                                               //!
        // readFromFileAliveObjects();
    }

    Map(Map& a) { }

    // деструктор
    ~Map() {
        if (aliveObjects != nullptr) delete[] aliveObjects;
        // std::cout << "~Map() start" << backgroundObjects << "\n\n";
        for (size_t i = 0; backgroundObjects != nullptr && i < H_bgO; ++i) {
            // std::cout << "~Map() " << i << " " << &backgroundObjects[i] << "\n";
            delete[] this->backgroundObjects[i];
            this->backgroundObjects[i] = nullptr;
        }
        delete[] this->backgroundObjects;
        // std::cout << "\n" << "~Map() " << backgroundObjects << "\n";
        this->backgroundObjects = nullptr;

        for (size_t i = 0; inanimateObjects != nullptr && i < H_bgO; ++i) {
            // std::cout << "~Map() " << i << " " << &backgroundObjects[i] << "\n";
            delete[] this->inanimateObjects[i];
            this->inanimateObjects[i] = nullptr;
        }
        delete[] this->inanimateObjects;
        // std::cout << "\n" << "~Map() " << backgroundObjects << "\n";
        this->inanimateObjects = nullptr;
    }

    // очистка памяти для новый карты                                                  //!
    void nextMap() {
        //delete[] unicObjects;
        for (size_t i = 0; i < H_bgO; ++i) {
            delete[] backgroundObjects[i];
        }
        delete[] backgroundObjects;
    }

    // вывод всей карты на экран (вместе с существами)
    void update(sf::RenderWindow& window, Plumber& p, float time) {
        window.clear(sf::Color::White); // цвет зависит от карты

        for (size_t i = 0; i < H_bgO; ++i) {
            for (size_t j = 0; j < W_bgO; ++j) {
                backgroundObjectsDisplay(backgroundObjects[i][j], window, i, j, p.getOffsetX(), p.getOffsetY(), time);
                if (i < H_iO && j < W_iO) inanimateObjects[i][j]->display(window, i, j, p.getOffsetX(), p.getOffsetY(), time);
            }
        }

        // for (size_t i = 0; i < S_aO; ++i) { } /// for aliveObjects

        p.update(time, backgroundObjects);
        window.draw(p.getSprite());
    }

    int H_bgO = 0; // размеры двумерных массивов
    int W_bgO = 0;
    int H_iO = 0;
    int W_iO = 0;
    int S_aO = 0; // количество живых существ
    int tile = 32;
    int player_x, player_y; //в каких координатах должен появиться персонаж
    char color = 0; // 0 - Black, 1 - Blue
    char** backgroundObjects = nullptr; // только объекты фона
    //указатель на массив указателей на массивы указателей на объект
    Object*** inanimateObjects = nullptr; // только неживые объекты (двумерный массив, потому что коллизия по координатам)
    Creature** aliveObjects = nullptr;  // только живые существа (одномерный массив, координаты в объектах)

private:

    Map() {} // приватный конструктор по умолчанию, чтобы нельзя было вызвать извне

    // выделение памяти для двумерных массивов заданных размеров
/*    template <class Type>
    void allocateCharArr(Type**& arr, int _H, int _W) {
        if (_H != 0 && _W != 0) {
            Type** arr_tmp = new Type* [_H];
            for (size_t i = 0; i < _H; ++i) {
                arr_tmp[i] = new Type[_W];
            }
            arr = arr_tmp;
        }
        else arr = nullptr;
    }
    */
    // выделение памяти для двумерных массивов заданных размеров

    void allocateCharArr(char**& arr, int _H, int _W) {
        if (_H != 0 && _W != 0) {
            char** arr_tmp = new char* [_H];
            for (size_t i = 0; i < _H; ++i) {
                arr_tmp[i] = new char[_W];
            }
            arr = arr_tmp;
        }
        else arr = nullptr;
    }

    void allocateObjectArr(Object***& arr, int _H, int _W) {
        if (_H != 0 && _W != 0) {
            Object*** arr_tmp = new Object** [_H];
            for (size_t i = 0; i < _H; ++i) {
                arr_tmp[i] = new Object*[_W];
            }
            arr = arr_tmp;
        }
        else arr = nullptr;
    }

    void readFromFileBackgroundObjects(std::ifstream* fN_bgO_in, int& _H_bgO, int& _W_bgO, char**& backgroundObjects) {
        *fN_bgO_in >> _H_bgO >> _W_bgO;
        std::cout << _H_bgO << " " << _W_bgO << "\n";
        allocateCharArr(backgroundObjects, H_bgO, W_bgO);
        for (size_t i = 0; i < _H_bgO; ++i) {
            for (size_t j = 0; j < _W_bgO; ++j) {
                *fN_bgO_in >> backgroundObjects[i][j];
                std::cout << backgroundObjects[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "Map(char const fN_bgO[17], char const fN_uO[16]...) " << backgroundObjects << "\n";
    }
    
        void readFromFileInanimateObjects(std::ifstream *fN_iO_in, int &H_iO, int &W_iO, Object*** inanimateObjects) {
            *fN_iO_in >> H_iO >> W_iO;
            std::cout << H_iO << " " << W_iO << "\n";
            allocateObjectArr(inanimateObjects, H_iO, W_iO);
            char temp;
            for (size_t i = 0; i < H_iO; ++i) {
                for (size_t j = 0; j < W_iO; ++j) {
                    *fN_iO_in >> temp;
                    std::cout << temp << " ";
                    inanimateObjects[i][j]->getObjectFromPointer(matchingCharAndObject(temp));
                    //!!!  СДЕЛАТЬ в соответствии со списком всех объектов, заполняется массив                   //!
                }
                std::cout << "\n";
            }
        }

    void backgroundObjectsDisplay(char item, sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
        sf::RectangleShape rectangle(sf::Vector2f(tile, tile)); // костыль

        if (backgroundObjects[i][j] == 'P') rectangle.setFillColor(sf::Color::Red);
        if (backgroundObjects[i][j] == 'T') { rectangle.setFillColor(sf::Color::Yellow); }
        if (backgroundObjects[i][j] == 'S') rectangle.setFillColor(sf::Color::Green);
        if (backgroundObjects[i][j] == '`') return;
        rectangle.setPosition(j * tile - offsetX, i * tile - offsetY);
        window.draw(rectangle);
    }

    Object* matchingCharAndObject(char symbol) {
        switch (symbol)
        {
        case 'S': {
            Object* temp_obj = new Solid();
            return temp_obj;
            break;
        }
        case 'P': {
            Object* temp_obj = new Pipe();
            return temp_obj;
            break;
        }
        case 'T': {
            Object* temp_obj = new Tap();
            return temp_obj;
            break;
            break;
        }
        default:
            break;
            std::cout << "something wrong with matchingCharAndObjects\n";
        }
    }

};