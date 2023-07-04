#pragma once

#include <SFML/Graphics.hpp>

class Unit {
public:
	Unit() {};
	virtual ~Unit() {};
protected:
	
	int x;
	int y;
	int textureX;
	int textureY;
private:
	// file .png with all texture pictures, global for heirs // ���� .png �� ����� ����������, ���������� ��� �����������
	static sf::Texture generalTexture; 
};
