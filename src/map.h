#pragma once
#include "units.h"
#include "creatures.h"

#include <iostream>

const int H_TM = 20;
const int W_TM = 66;

char TileMap0[H_TM][W_TM] = {
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",// 0
    "B                                                        B",// 1
    "B   BBB   B     BB   BB  BBB                             B",// 2
    "B   B  B  B    B  B B  B B  B                            B",// 3
    "B   BBB   B    B  B B  B B  B                            B",// 4
    "B   B  B  B    B  B B  B B  B                            B",// 5
    "B   BBB   BBBB  BB   BB  BBB               0             B",// 6
    "B                                                        B",// 7
    "B                0000                          B         B",// 8
    "B                                        B               B",// 9
    "B                                                        B",// 10
    "B             BB        0       0                        B",// 11
    "B         BBBBBBBBB             0                        B",// 12
    "B         B       B             0                        B",// 13
    "B     BBBBB                BB                            B",// 14
    "B     B                    BB                            B",// 15
    "BBBBBBBBBBBBBBBBB   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",// 16
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",// 17
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",// 18
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",// 19
};

char TileMap1[H_TM][W_TM] = {
    "                                                          ",// 0
    "                                                          ",// 1
    "                                                          ",// 2
    "                                                          ",// 3
    "                                                          ",// 4
    "                                                          ",// 5
    "                                                          ",// 6
    "                                                          ",// 7
    "                                                          ",// 8
    "                                                          ",// 9
    "                                                          ",// 10
    "                                                          ",// 11
    "                                                          ",// 12
    "                                                          ",// 13
    "                                                          ",// 14
    "                                                          ",// 15
    "                                                          ",// 16
    "                                                          ",// 17
    "                                                          ",// 18
    "                                                          ",// 19
};
/*//////////////////////////////////////////!!!!!!!
����� ������ ����� ���������� ��������� � ��������� �����. (� ��� ������ 5 ����)
������ ��� ����� ����� ���������� � ������ ������ �����, ������ ���������
������ � ����� ����� - �������� ������ ��������� �� ����� ����������� (Teleport)
���� ������ ���������� � ������� ������ Teleport. � �� ����� �����, ������� ���������� ����� ���������
1 ������� ������
2 ��������� 
3 ����������

��� � ������� (������, �����, �����������) �������� � ������� char
�������� � ������� �������, ������� ��������� ��� ����� ������ - � ������� Unit*, � ���� ������ (��� ����������� ������ ����� ���������)

���� ������ Map �������� ������ Creature � ��� ����������� ��� ������������� � �������: Collision
*///////////////////////////////////////////!!!!!!!!


// ����� - ���������. ����������� - ��� ���������� ��������
class Map {
public:

	Map(int H_, int W_) : H(H_), W(W_) { 
		allocateCharArr(backgroundAndObjects);
		//unicObjects = new Unit[c_E];
		unicObjects = new Unit[0]; // !!!!! �������� !!!!!
        std::cout << "Map() " << backgroundAndObjects << "\n";
	}

	// ���������� �� ������������ ��������
	Map(char** bgAO, char** uO, int H_, int W_) :
		H(H_), W(W_) { 
		writeIntoCharArr(bgAO, backgroundAndObjects);
		writeIntoUnitArr(uO, unicObjects);
	}

	// ���������� �� ��������� �����
	Map(char const* fN_bgAO, char const* fN_uO) { }

    Map(Map &a){}

	// ����������
	~Map() {
        if (unicObjects != nullptr) delete[] unicObjects;
        // std::cout << "~Map() start" << backgroundAndObjects << "\n\n";
        for (size_t i = 0; backgroundAndObjects != nullptr && i < H; ++i) {
            // std::cout << "~Map() " << i << " " << &backgroundAndObjects[i] << "\n";
            delete[] this->backgroundAndObjects[i];
            this->backgroundAndObjects[i] = nullptr;
        }
        delete[] this->backgroundAndObjects;
        // std::cout << "\n" << "~Map() " << backgroundAndObjects << "\n";
        this->backgroundAndObjects = nullptr;
	}

    // Map1 �������
    void Map1(){
        for (size_t i = 0; i < H; ++i) {
            for (size_t j = 0; j < W; ++j) {
                backgroundAndObjects[i][j] = TileMap0[i][j];
                // // // // // // // // // // // // //
                //std::cout << "Ok " << i << " " << j << "\n";
            }
        }

    }

    // ������� ������ ��� ����� �����
    void nextMap() {
        //delete[] unicObjects;
        for (size_t i = 0; i < H; ++i) {
            delete[] backgroundAndObjects[i];
        }
        delete[] backgroundAndObjects;
    }

	// ����� ���� ����� �� ����� (������ � ����������)
	void update(sf::RenderWindow &window, Plumber &p) {
        sf::RectangleShape rectangle(sf::Vector2f(tile, tile)); // �������

        window.clear(sf::Color::White); // ���� ������� �� �����

        for (size_t i = 0; i < H; ++i) {
            for (size_t j = 0; j < W; ++j) {
                if (backgroundAndObjects[i][j] == 'B') rectangle.setFillColor(sf::Color::Red);
                if (backgroundAndObjects[i][j] == '0') { rectangle.setFillColor(sf::Color::Yellow); }
                if (backgroundAndObjects[i][j] == ' ') continue;
                rectangle.setPosition(j * tile - p.getOffsetX(), i * tile - p.getOffsetY());
                window.draw(rectangle);
            }
        }    
    }

	int H = 0; // ������� 
	int W = 0; // �������
    int tile = 32;
	int player_x, player_y; //� ����� ����������� ������ ��������� ��������
	char color = 0; // 0 - Black, 1 - Blue
	char** backgroundAndObjects = nullptr; // backgroung � solid (pipe, tap); coin, destructible;
	Unit* unicObjects = nullptr;  //moving, boilingWater, raft, jet, valve, teleport, Creature, triggers

private:

	Map() {} // ��������� ����������� �� ���������, ����� ������ ���� ������� �����

	// ���������� ��������� �������� �����
	void writeIntoCharArr(char** arr_out, char** arr_in) {
		arr_in = new char* [H];
		for (size_t i = 0; i < H; ++i) {
			arr_in[i] = new char[W];
			for (size_t j = 0; j < W; ++j) {
				arr_in[i][j] = arr_out[i][j];
			}
		}
	}

	// ���������� ������ ������� (������ ������� ������� ��� ����������)
	void writeIntoUnitArr(char ** arr_out, Unit* arr_in) {
		arr_in = new Unit [0]; // !!!! �������� !!!!!
		for (size_t i = 0; i < H; ++i) {
			for (size_t j = 0; j < W; ++j) {
				switch (arr_out[i][j]) {
				case ' ': break;
				}
			}
		}
	}

	// ��������� ������ ��� ��������� �������� �����
	void allocateCharArr(char ** &arr) {
		char** arr_tmp = new char* [H];
		for (size_t i = 0; i < H; ++i) {
			arr_tmp[i] = new char[W];
		}
        arr = arr_tmp;
	}

};