#pragma once
#include "units.h"
#include "creatures.h"

#include <iostream>

const int H_TM = 20;
const int W_TM = 66;

char TileMap0[H_TM][W_TM] = {
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

char TileMap1[H_TM][W_TM] = {
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

char TileMap2[H_TM][W_TM] = {
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



// карта - хранилище. Констукторы - для заполнения массивов
class Map {
public:

	Map(int H_, int W_, int c_E) : H(H_), W(W_), count_Enemy(c_E) { 
		allocateCharArr(backgroundAndSolid);
		allocateCharArr(solidObjects);
		unicObjects = new Unit[c_E];
        std::cout << backgroundAndSolid << "\n";
        std::cout << solidObjects << "\n";
	}

	// заполнение из динамических массивов
	Map(char** bgAS, char** sO, char** uO, int H_, int W_, int c_E) :
		H(H_), W(W_), count_Enemy(c_E) { 
		writeIntoCharArr(bgAS, backgroundAndSolid);
		writeIntoCharArr(sO, solidObjects);
		writeIntoUnitArr(uO, unicObjects);
	}

	// заполнение из тестового файла
	Map(char const* fN_bgAS, char const* fN_sO, char const* fN_uO) { }

	// деструктор
	~Map() {
		delete[] unicObjects;
	}

    // Map1 костыль
    void Map1(){
        for (size_t i = 0; i < H; ++i) {
            for (size_t j = 0; j < W; ++j) {
                backgroundAndSolid[i][j] = TileMap0[i][j];
                solidObjects[i][j] = TileMap1[i][j];
                // // // // // // // // // // // // //
                std::cout << "Ok " << i << " " << j << "\n";
            }
        }

    }

	// вывод всей карты на экран (вместе с существами)
	void update(sf::RenderWindow &window, Plumber &p) {
        sf::RectangleShape rectangle(sf::Vector2f(tile, tile)); // костыль

        window.clear(sf::Color::White); // цвет зависит от карты

        for (size_t i = 0; i < H; ++i) {
            for (size_t j = 0; j < W; ++j) {
                if (solidObjects[i][j] == 'B') rectangle.setFillColor(sf::Color::Red);
                if (solidObjects[i][j] == '0') { rectangle.setFillColor(sf::Color::Yellow); }
                if (solidObjects[i][j] == ' ') continue;
                rectangle.setPosition(j * tile - p.getOffsetX(), i * tile - p.getOffsetY());
                window.draw(rectangle);
            }
        }    
    }

	int H = 0; // размеры 
	int W = 0; // массива
    int tile = 32;
	int count_Enemy = 0; // количество врагов
	int player_x, player_y; //в каких координатах должен появиться персонаж
	char color = 0; // 0 - Black, 1 - Blue
	char** backgroundAndSolid = nullptr; // backgroung и solid (pipe, tap); неизменяемый
	char** solidObjects = nullptr; // coin, destructible; изменяемый (динамический)
	Unit* unicObjects = nullptr;  //moving, boilingWater, raft, jet, valve, teleport, Creature, triggers

private:

	Map() {} // приватный конструктор по умолчанию, чтобы нельзя было вызвать извне

	// заполнение двумерных массивов карты
	void writeIntoCharArr(char** arr_out, char** arr_in) {
		arr_in = new char* [H];
		for (size_t i = 0; i < H; ++i) {
			arr_in[i] = new char[W];
			for (size_t j = 0; j < W; ++j) {
				arr_in[i][j] = arr_out[i][j];
			}
		}
	}

	// заполнение списка существ (внутри каждого объекта его координаты)
	void writeIntoUnitArr(char ** arr_out, Unit* arr_in) {
		arr_in = new Unit [count_Enemy];
		for (size_t i = 0; i < H; ++i) {
			for (size_t j = 0; j < W; ++j) {
				switch (arr_out[i][j]) {
				case ' ': break;
				}
			}
		}
	}

	// выделение памяти для двумерных массивов карты
	void allocateCharArr(char ** &arr) {
		char** arr_tmp = new char* [H];
		for (size_t i = 0; i < H; ++i) {
			arr_tmp[i] = new char[W];
		}
        arr = arr_tmp;
	}

};