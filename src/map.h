#pragma once
#include "units.h"
#include "creatures.h"

#include <iostream>
#include <fstream>

/*//////////////////////////////////////////!!!!!!!
����� ������ ����� ���������� ��������� � ��������� �����. (� ��� ������ 5 ����)
������ ��� ����� ����� ���������� � ������ ������ �����, ������ ���������
������ � ����� ����� - �������� ������ ��������� �� ����� ����������� (Teleport)
���� ������ ���������� � ������� ������ Teleport. � �� ����� �����, ������� ���������� ����� ���������
1 ������� ������
2 ��������� 
3 ����������

��� �������� � ������� char backgroundObjects
������� - � ��������� ������� Unit inanimateObjects, ��� ��� ����� �� �������������� �� ������ ��� ������������ ��������
�������� - � ������� Unit aliveObjects, � ���� ������ (��� ����������� ������ ����� ���������)
���������� ������ Unit SamplesOfObjects ������ ������� ��������

���� ������ Map �������� ������ Creature � ��� ����������� ��� ������������� � �������: Collision
*///////////////////////////////////////////!!!!!!!!


// ����� - ���������. ����������� - ��� ���������� ��������
class Map {
public:
	/// ���������� �� ��������� �����
	Map(char const fN_bgO[17], char const fN_iO[16], char const fN_aO[16]) {
        std::ifstream fN_bgO_in, fN_iO_in, fN_aO_in;       
        fN_bgO_in.open(fN_bgO);
        fN_iO_in.open(fN_iO);
        fN_aO_in.open(fN_aO);
        // ������ ������� ����������
        // readFromFileBackgroundObjects(&fN_bgO_in, H_bgO, W_bgO, backgroundObjects);
        readFromFileBackgroundObjects(&fN_iO_in, H_bgO, W_bgO, backgroundObjects); //!!! �������� !!!/
        // ��������� ������ ������������� ��������
        //readFromFileInanimateObjects(&fN_iO_in, H_iO, W_iO, inanimateObjects);
        // ��������� ������ ����� ������� (����� ��)
        //!!! ��������                                                               //!
        // readFromFileAliveObjects();
    }

    Map(Map &a){ }

	// ����������
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

    // ������� ������ ��� ����� �����                                                  //!
    void nextMap() {
        //delete[] unicObjects;
        for (size_t i = 0; i < H_bgO; ++i) {
            delete[] backgroundObjects[i];
        }
        delete[] backgroundObjects;
    }

	// ����� ���� ����� �� ����� (������ � ����������)
	void update(sf::RenderWindow &window, Plumber &p, float time) {
        sf::RectangleShape rectangle(sf::Vector2f(tile, tile)); // �������
        window.clear(sf::Color::White); // ���� ������� �� �����

        for (size_t i = 0; i < H_bgO; ++i) {
            for (size_t j = 0; j < W_bgO; ++j) {
                if (backgroundObjects[i][j] == 'P') rectangle.setFillColor(sf::Color::Red);
                if (backgroundObjects[i][j] == 'T') { rectangle.setFillColor(sf::Color::Yellow); }
                if (backgroundObjects[i][j] == 'S') rectangle.setFillColor(sf::Color::Green);
                if (backgroundObjects[i][j] == '`') continue;
                rectangle.setPosition(j * tile - p.getOffsetX(), i * tile - p.getOffsetY());
                window.draw(rectangle);
            }
        }    
        p.update(time, backgroundObjects);
        window.draw(p.getSprite());
    }

    int H_bgO = 0; // ������� ��������� ��������
    int W_bgO = 0;
    int H_iO = 0;
    int W_iO = 0;
    int S_aO = 0; // ���������� ����� �������
    int tile = 32;
	int player_x, player_y; //� ����� ����������� ������ ��������� ��������
	char color = 0; // 0 - Black, 1 - Blue
	char** backgroundObjects = nullptr; // ������ ������� ����
    Unit** inanimateObjects = nullptr; // ������ ������� ������� (��������� ������, ������ ��� �������� �� �����������)
	Unit* aliveObjects = nullptr;  // ������ ����� �������� (���������� ������, ���������� � ��������)
    Unit* SamplesOfObjects = nullptr; // ���������� ������ ���� ����������� �������� ��� background � inanimateObjects
private:

	Map() {} // ��������� ����������� �� ���������, ����� ������ ���� ������� �����

    // ��������� ������ ��� ��������� �������� �������� ��������
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
    // ��������� ������ ��� ��������� �������� �������� ��������

    void allocateCharArr(char**& arr, int _H, int _W) {
        if (_H != 0 && _W != 0) {
            char** arr_tmp = new char * [_H];
            for (size_t i = 0; i < _H; ++i) {
                arr_tmp[i] = new char[_W];
            }
            arr = arr_tmp;
        }
        else arr = nullptr;
    }
    
    void readFromFileBackgroundObjects(std::ifstream *fN_bgO_in, int &_H_bgO, int &_W_bgO, char** &backgroundObjects) {
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
/*
    void readFromFileInanimateObjects(std::ifstream *fN_iO_in, int &H_iO, int &W_iO, Unit** inanimateObjects) {
        *fN_iO_in >> H_iO >> W_iO;
        std::cout << H_iO << " " << W_iO << "\n";
        allocateCharArr(inanimateObjects, H_iO, W_iO);
        char temp;
        for (size_t i = 0; i < H_iO; ++i) {
            for (size_t j = 0; j < W_iO; ++j) {
                *fN_iO_in >> temp;
                std::cout << temp << " ";
                //!!!  ������� � ������������ �� ������� ���� ��������, ����������� ������                   //!
            }
            std::cout << "\n";
        }
    }*/
};