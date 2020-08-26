#include "Gra.h"

#include <iostream>
#include <string>
Gra::Gra()
{
	_szybkosc = 3.0;
	_wysokoscOkna = 900;
	_szerokoscOkna = 1200;
	_szeroksocWody = 0.60 * _szerokoscOkna;
	_szerokoscBrzegu = 0.20 * _szerokoscOkna;
	_czasDoPrzeszkody = 1.5f;
	_czasDoKoncaPoziomu = 15.0f;
	_textureBrzegL.loadFromFile("./Grafika/brzeg_lewy.png");
	_textureBrzegP.loadFromFile("./Grafika/brzeg_prawy.png");
	_textureWoda.loadFromFile("./Grafika/woda.png");
	_textureWoda.setRepeated(true);
	_woda.setTextureRect(sf::IntRect(0, 0, _szerokoscOkna, _wysokoscOkna * 2));
	_brzegL.setTexture(_textureBrzegL);
	_brzegL.setScale(_szerokoscBrzegu / _brzegL.getLocalBounds().width, (_wysokoscOkna + 10) / _brzegL.getLocalBounds().height);
	_brzegL.setPosition(0, _wysokoscOkna);
	_brzegP.setTexture(_textureBrzegP);
	_brzegP.setScale(_szerokoscBrzegu / _brzegP.getLocalBounds().width, (_wysokoscOkna + 10) / _brzegP.getLocalBounds().height);
	_brzegP.setPosition(_szerokoscBrzegu + _szeroksocWody, _wysokoscOkna);

	_brzegL2.setTexture(_textureBrzegL);
	_brzegL2.setScale(_szerokoscBrzegu / _brzegL2.getLocalBounds().width, (_wysokoscOkna + 10) / _brzegL2.getLocalBounds().height);
	_brzegP2.setTexture(_textureBrzegP);
	_brzegP2.setScale(_szerokoscBrzegu / _brzegP2.getLocalBounds().width, (_wysokoscOkna + 10) / _brzegP2.getLocalBounds().height);
	_brzegP2.setPosition(_szerokoscBrzegu + _szeroksocWody, 0);

	_woda.setTexture(_textureWoda);

	_textureGracz.loadFromFile("./Grafika/tratwa.png");
	_gracz.setTexture(_textureGracz);
	_gracz.setScale(0.3, 0.3);
	_gracz.setPosition(_szerokoscOkna / 2, (_wysokoscOkna * 2) - (_textureGracz.getSize().y*0.3));
	_ruchGracza = 0;
	

	_textureStart.loadFromFile("./Grafika/graj.png");
	_textureKoniecGry.loadFromFile("./Grafika/koniec-gry.png");
	_textureKolejny.loadFromFile("./Grafika/kolejny.png");
	_textureBrawo.loadFromFile("./Grafika/poziom-zakonczony.png");

	_start.setTexture(_textureStart);
	_koniecGry.setTexture(_textureKoniecGry);
	_kolejny.setTexture(_textureKolejny);
	_brawo.setTexture(_textureBrawo);

	_textureMeta.loadFromFile("./Grafika/meta_most.png");
	_meta.setTexture(_textureMeta);
	_meta.setScale((_szeroksocWody + 10) / _meta.getGlobalBounds().width, 1);
	_meta.setPosition(_szerokoscBrzegu - 10, _wysokoscOkna - _meta.getGlobalBounds().height);
	_ruchMeta = 0;

	_okno = new sf::RenderWindow(sf::VideoMode(_szerokoscOkna, _wysokoscOkna), "Tratwa");
	_kamera = new sf::View(sf::FloatRect(0, _wysokoscOkna, _szerokoscOkna, _wysokoscOkna));
	_okno->setView(*_kamera);



	//przeszkody
	for (int i = 1; i <= 5; ++i)
	{
		_texturePrzeszkody[i-1].loadFromFile("./Grafika/kamien" + std::to_string(i) + ".png");
		//_przeszkody[i].setTexture(_texturePrzeszkody[i]);
	}
}

void Gra::rysujTlo()
{
	if (_brzegP.getPosition().y < _wysokoscOkna * 2)
		_brzegP.move(0, _szybkosc/2);
	else
		_brzegP.setPosition(_szerokoscBrzegu + _szeroksocWody, 0);

	if (_brzegP2.getPosition().y <= _wysokoscOkna * 2)
		_brzegP2.move(0, _szybkosc/2);
	else
		_brzegP2.setPosition(_szerokoscBrzegu + _szeroksocWody, 0);

	if (_brzegL.getPosition().y < _wysokoscOkna * 2)
		_brzegL.move(0, _szybkosc/2);
	else
		_brzegL.setPosition(0, 0);

	if (_brzegL2.getPosition().y <= _wysokoscOkna * 2)
		_brzegL2.move(0, _szybkosc/2);
	else
		_brzegL2.setPosition(0, 0);




	_okno->draw(_woda);
	_okno->draw(_brzegL);
	_okno->draw(_brzegL2);
	_okno->draw(_brzegP);
	_okno->draw(_brzegP2);
}

Gra::~Gra()
{
	// TODO Auto-generated destructor stub
}

void Gra::start()
{
	std::srand(std::time(nullptr));
	_okno->setFramerateLimit(60);
	petlaGry();
}

void Gra::generujPrzeszkode()
{
	if (_licznikPrzeszkoda.getElapsedTime().asSeconds() > _czasDoPrzeszkody)
	{
		int przeszkodaIndex = std::rand() % 5;
		int max = _szerokoscBrzegu + _szeroksocWody - _texturePrzeszkody[przeszkodaIndex].getSize().x;
		int min = _szerokoscBrzegu;

		float pozycja = (std::rand() % (max - min + 1)) + min;

		sf::Sprite* przeszkoda = new sf::Sprite(_texturePrzeszkody[przeszkodaIndex]);
		przeszkoda->setPosition(pozycja, _wysokoscOkna/2);
		_przeszkody.push_back(przeszkoda);
		_licznikPrzeszkoda.restart();
		_czasDoPrzeszkody = 1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.5f - 1.0f)));
	}
}

void Gra::petlaGry()
{
	sf::Sprite test(_texturePrzeszkody[0]);
	test.setPosition(_szerokoscOkna / 2, _wysokoscOkna + 200);
	while (_okno->isOpen())
	{
		_okno->clear();
		rysujTlo();
		
		//przeszkody
		generujPrzeszkode();
		for (auto ele : _przeszkody)
		{
			ele->move(0, _szybkosc);
			_okno->draw(*ele);
		}
		//czyœæ
		for (auto ele : _przeszkody)
			if (ele->getPosition().y > _wysokoscOkna * 2)
			{
				delete ele;
				_przeszkody.remove(ele);
				break;
			}

		//gracz
		_okno->draw(_gracz);
		_gracz.move(_ruchGracza * _szybkosc, 0);



		sf::Event event;
		while (_okno->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_okno->close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				_okno->close();
			sterowanie(event);
		}

		meta();

		kolizje();


		_okno->display();

	}
}

void Gra::sterowanie(sf::Event event)
{
	if ( (event.type != sf::Event::KeyPressed) && (event.type != sf::Event::KeyReleased))
		return;

	float ruch = (event.type == sf::Event::KeyPressed) ? 1 : 0;
	switch (event.key.code)
	{
	case sf::Keyboard::Left:
		_ruchGracza = -ruch;
		break;
	case sf::Keyboard::Right:
		_ruchGracza = ruch;
		break;
	default:
		break;
	}
}

void Gra::kolizje()
{
	bool test = false;
	sf::FloatRect intersection;
	//brzegi
	test = _gracz.getGlobalBounds().intersects(_brzegL.getGlobalBounds(),intersection);
	if (test)
		_gracz.move(intersection.width * _szybkosc, 0);
	test = _gracz.getGlobalBounds().intersects(_brzegL2.getGlobalBounds(), intersection);
	if (test)
		_gracz.move(intersection.width * _szybkosc, 0);

	test = _gracz.getGlobalBounds().intersects(_brzegP.getGlobalBounds(), intersection);
	if (test)
		_gracz.move(-intersection.width * _szybkosc, 0);
	test = _gracz.getGlobalBounds().intersects(_brzegP2.getGlobalBounds(), intersection);
	if (test)
		_gracz.move(-intersection.width * _szybkosc, 0);



	//przeszkody
	test = false;
	for (auto ele : _przeszkody)
	{
		test = _gracz.getGlobalBounds().intersects(ele->getGlobalBounds());
		if (test)
			exit(0);
	}


	//meta
	test = _gracz.getGlobalBounds().intersects(_meta.getGlobalBounds());
	if (test)
		nowyPoziom();
}

void Gra::meta()
{
	std::cout << "Licznik: " << _licznikPoziomu.getElapsedTime().asSeconds() << std::endl;
	if (_licznikPoziomu.getElapsedTime().asSeconds() > _czasDoKoncaPoziomu)
		_ruchMeta = 1;
	_meta.move(0, _ruchMeta*_szybkosc/2);

	_okno->draw(_meta);
}

void Gra::nowyPoziom()
{
	++_szybkosc;
	_przeszkody.clear();
	_ruchMeta = false;
	_licznikPoziomu.restart();
	_licznikPrzeszkoda.restart();
	_meta.setPosition(_szerokoscBrzegu - 10, 0);
}
