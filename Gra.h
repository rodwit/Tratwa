#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <algorithm>
#include <list>
class Gra
{
private:
	float _szerokoscOkna;
	float _wysokoscOkna;
	float _szeroksocWody;
	float _szerokoscBrzegu;
	sf::RenderWindow* _okno;
	sf::View* _kamera;
	float _szybkosc;
	sf::Clock _licznikPrzeszkoda;
	float _czasDoPrzeszkody;
	sf::Clock _licznikPoziomu;
	float _czasDoKoncaPoziomu;


	//t³o
	sf::Texture _textureBrzegL;
	sf::Texture _textureBrzegP;
	sf::Texture _textureWoda;
	sf::Sprite _brzegL;
	sf::Sprite _brzegP;
	sf::Sprite _brzegL2;
	sf::Sprite _brzegP2;
	sf::Sprite _woda;
	
	//przeszkody
	sf::Texture _texturePrzeszkody[5];
	std::list<sf::Sprite*> _przeszkody;

	//gui
	sf::Texture _textureStart;
	sf::Sprite _start;

	sf::Texture _textureKoniecGry;
	sf::Sprite _koniecGry;

	sf::Texture _textureKolejny;
	sf::Sprite _kolejny;

	sf::Texture _textureBrawo;
	sf::Sprite _brawo;

	//meta
	sf::Texture _textureMeta;
	sf::Sprite _meta;
	float _ruchMeta;

	//gracz
	sf::Texture _textureGracz;
	sf::Sprite _gracz;
	float _ruchGracza;

	void rysujTlo();
	void generujPrzeszkode();
	void petlaGry();
	void sterowanie(sf::Event event);
	void kolizje();
	void meta();
	void nowyPoziom();
public:
	Gra();
	virtual ~Gra();
	void start();
};