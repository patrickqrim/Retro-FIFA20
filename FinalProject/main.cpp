#include<SFML\Graphics.hpp>
#include<SFML\Graphics\Rect.hpp>
#include<string>
#include<iostream>
#include<vector>
#include<random>
#include<SFML\Audio.hpp>
using namespace std;

//create window
sf::RenderWindow window(sf::VideoMode(1211, 852), "FIFA2020");

//music
sf::Music music;

//goal and winning sound fx
sf::Sound celebration;
sf::SoundBuffer celebrationbuffer;

enum GameState {
	MENU,
	SELECT,
	GAMEPLAY,
	INSTRUCTIONS
};

//current gamestate
GameState currentState = MENU;

//MENU SCREEN
void menu() {

	//design stuff
	sf::Sprite background;
	sf::Texture field;
	field.loadFromFile("Textures/MENU.png");
	background.setTexture(field);
	background.setScale(1.15, 1.15);

	window.clear();

	window.draw(background);

	window.display();

}

//SELECT TEAMS MENU
void select() {

	//design stuff
	sf::Sprite background;
	sf::Texture field;
	field.loadFromFile("Textures/menus.png");
	background.setTexture(field);
	background.setScale(1.15, 1.15);

	window.clear();

	window.draw(background);

	window.display();
}

//INSTRUCTIONS
void instructions() {

	//design stuff
	sf::Sprite background;
	sf::Texture field;
	field.loadFromFile("Textures/instructions.png");
	background.setTexture(field);
	background.setScale(1.15, 1.15);

	window.clear();

	window.draw(background);

	window.display();
}

void game(int a, int b){

	//initialize sound fx
	celebrationbuffer.loadFromFile("Textures/cheer.wav");
	celebration.setBuffer(celebrationbuffer);
	celebration.setVolume(100);

	//gameover or not
	bool gameOver = false;
	bool breakit = false;

	//create background
	sf::Sprite background;
	sf::Texture field;
	field.loadFromFile("Textures/soccer.png");
	background.setTexture(field);
	background.setScale(1.5, 1.5);

	//PLAYER and marker POINTERS
	sf::Sprite* homePlayer;
	sf::Sprite* awayPlayer;
	sf::Sprite* homeMarker;
	sf::Sprite* awayMarker;

	//PLAYERS
	sf::Sprite player1;
	sf::Sprite player2;
	sf::Sprite player3;
	sf::Sprite player4;
	sf::Sprite player5;
	sf::Sprite player6;

	//CURRENT PLAYER MARKERS
	sf::Texture homemarker;
	sf::Texture awaymarker;
	homemarker.loadFromFile("Textures/home.png");
	awaymarker.loadFromFile("Textures/away.png");

	sf::Sprite player1m;
	sf::Sprite player2m;
	sf::Sprite player3m;
	sf::Sprite player4m;
	sf::Sprite player5m;
	sf::Sprite player6m;

	player1m.setTexture(homemarker);
	player2m.setTexture(homemarker);
	player3m.setTexture(homemarker);
	player4m.setTexture(awaymarker);
	player5m.setTexture(awaymarker);
	player6m.setTexture(awaymarker);

	player1m.setScale(0.12, 0.12);
	player2m.setScale(0.05, 0.05);
	player3m.setScale(0.05, 0.05);
	player4m.setScale(0.12, 0.12);
	player5m.setScale(0.05, 0.05);
	player6m.setScale(0.05, 0.05);

	player3m.setPosition(964, 270);
	player1m.setPosition(784, 70);
	player2m.setPosition(784, 470);
	player6m.setPosition(179, 270);
	player4m.setPosition(359, 70);
	player5m.setPosition(359, 470);

	//ball
	sf::Sprite ball;
	sf::Texture balltexture;

	float velocity1 = 0;
	float velocity2 = 0;
	float velocity3 = 0;
	float velocity4 = 0;
	float velocity5 = 0;
	float velocity6 = 0;
	const float gravity = 0.01f;

	float xdiff1;
	float ydiff1;
	float xdiff2;
	float ydiff2;
	float xdiff3;
	float ydiff3;
	float xdiff4;
	float ydiff4;
	float xdiff5;
	float ydiff5;
	float xdiff6;
	float ydiff6;
	
	balltexture.loadFromFile("Textures/ball.png");
	ball.setTexture(balltexture);
	ball.setScale(0.015, 0.015);
	ball.setOrigin(11, 11);
	ball.setPosition(595, 410);

	//TEXT
	sf::Text GOAL;
	sf::Text OWNGOAL;
	sf::Text n;

	sf::Font myFont;
	myFont.loadFromFile("Textures/Candal.ttf");

	GOAL.setFont(myFont);
	GOAL.setString("HOME GOAL");
	GOAL.setCharacterSize(100);
	GOAL.setPosition(280, 720);
	GOAL.setFillColor(sf::Color::Red);
	GOAL.setScale(0, 0);

	OWNGOAL.setFont(myFont);
	OWNGOAL.setString("AWAY GOAL");
	OWNGOAL.setCharacterSize(100);
	OWNGOAL.setPosition(280, 720);
	OWNGOAL.setFillColor(sf::Color::Blue);
	OWNGOAL.setScale(0, 0);

	n.setFont(myFont);
	n.setString("Press N to Continue");
	n.setCharacterSize(24);
	n.setPosition(470, 820);
	n.setFillColor(sf::Color::White);
	n.setScale(0, 0);

	sf::Text HOMEWINS;
	sf::Text AWAYWINS;

	HOMEWINS.setFont(myFont);
	HOMEWINS.setString("HOME TEAM WINS");
	HOMEWINS.setCharacterSize(100);
	HOMEWINS.setPosition(125, 350);
	HOMEWINS.setFillColor(sf::Color::Red);
	HOMEWINS.setScale(0, 0);

	AWAYWINS.setFont(myFont);
	AWAYWINS.setString("AWAY TEAM WINS");
	AWAYWINS.setCharacterSize(100);
	AWAYWINS.setPosition(140, 350);
	AWAYWINS.setFillColor(sf::Color::Blue);
	AWAYWINS.setScale(0, 0);

	//goal boolean + score counter
	int homegoals = 0;
	int awaygoals = 0;
	bool crossedhome = false;
	bool crossedaway = false;
	bool reset = false;

	//SCOREBOARD
	sf::Sprite korea;
	sf::Texture koreat;
	koreat.loadFromFile("Textures/korea.png");
	korea.setTexture(koreat);
	korea.setPosition(607, 25);

	sf::Sprite usa;
	sf::Texture usat;
	usat.loadFromFile("Textures/usa.png");
	usa.setTexture(usat);
	usa.setPosition(186, 25);

	sf::Sprite france;
	sf::Texture francet;
	francet.loadFromFile("Textures/france.png");
	france.setTexture(francet);
	france.setPosition(186, 25);

	sf::Sprite spain;
	sf::Texture spaint;
	spaint.loadFromFile("Textures/spain.png");
	spain.setTexture(spaint);
	spain.setPosition(607, 25);

	sf::Sprite pubg;
	sf::Texture pubgt;
	pubgt.loadFromFile("Textures/pubg.png");
	pubg.setTexture(pubgt);
	pubg.setPosition(607, 25);

	sf::Sprite fortnite;
	sf::Texture fortnitet;
	fortnitet.loadFromFile("Textures/fortnite.png");
	fortnite.setTexture(fortnitet);
	fortnite.setPosition(186, 25);

	//SCORE
	sf::Text homescore;
	sf::Text awayscore;
	homescore.setFont(myFont);
	awayscore.setFont(myFont);

	int actualhomegoals = 0;
	int actualawaygoals = 0;

	homescore.setString("0");
	homescore.setCharacterSize(75);
	homescore.setPosition(1032, 5);
	homescore.setFillColor(sf::Color::White);

	awayscore.setString("0");
	awayscore.setCharacterSize(75);
	awayscore.setPosition(125, 5);
	awayscore.setFillColor(sf::Color::White);

	//STOP BUTTON
	sf::Sprite pause;
	sf::Texture pauset;
	pauset.loadFromFile("Textures/stop.png");
	pause.setTexture(pauset);
	pause.setScale(0.05, 0.05);
	pause.setPosition(1130, 20);


	//set pointers to default
	homePlayer = &player1;
	awayPlayer = &player4;
	homeMarker = &player1m;
	awayMarker = &player4m;

	//animations (COMPLETED)

	sf::Texture myTexture;
	sf::IntRect right[4];
	sf::IntRect left[4];
	right[0] = sf::IntRect(20, 145, 23, 47);  //originally 96 (2nd param)
	right[1] = sf::IntRect(84, 145, 23, 47);
	right[2] = sf::IntRect(148, 145, 23, 47);
	right[3] = sf::IntRect(212, 145, 23, 47);
	left[0] = sf::IntRect(20, 241, 25, 44);
	left[1] = sf::IntRect(84, 241, 25, 44);
	left[2] = sf::IntRect(148, 241, 25, 44);
	left[3] = sf::IntRect(212, 241, 25, 44);
	
	myTexture.loadFromFile("Textures/freakybabies.png");

	//spawn players
	player1.setTexture(myTexture);
	player1.setTextureRect(right[0]);
	player1.setOrigin(11, 24);
	player1.setScale(1.5, 1.5);

	player2.setTexture(myTexture);
	player2.setTextureRect(right[0]);
	player2.setOrigin(11, 24);
	player2.setScale(1.5, 1.5);

	player3.setTexture(myTexture);
	player3.setTextureRect(right[0]);
	player3.setOrigin(11, 24);
	player3.setScale(1.5, 1.5);

	player4.setTexture(myTexture);
	player4.setTextureRect(left[0]);
	player4.setOrigin(11, 24);
	player4.setScale(1.5, 1.5);

	player5.setTexture(myTexture);
	player5.setTextureRect(left[0]);
	player5.setOrigin(11, 24);
	player5.setScale(1.5, 1.5);

	player6.setTexture(myTexture);
	player6.setTextureRect(left[0]);
	player6.setOrigin(11, 24);
	player6.setScale(1.5, 1.5);

	//set locations (diff for each)
	player3.setPosition(1000, 350);
	player1.setPosition(820, 150);
	player2.setPosition(820, 550);
	player6.setPosition(210, 350);
	player4.setPosition(390, 150);
	player5.setPosition(390, 550);


	//clock for animation
	sf::Clock clock;
	int imgCount = 0;
	float timer = 0;

	//movement booleans
	bool p1movingUp = false;
	bool p1movingDown = false;
	bool p1movingLeft = false;
	bool p1movingRight = false;

	bool p2movingUp = false;
	bool p2movingDown = false;
	bool p2movingLeft = false;
	bool p2movingRight = false;

	//MAIN GAME ***LLLOOOOOOPPPP***
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			/*if (event.type == sf::Event::MouseButtonPressed) {
				cout << sf::Mouse::getPosition(window).x << ", " << sf::Mouse::getPosition(window).y << endl;
			}*/

			if (event.type == sf::Event::Closed)
				window.close();

			if (!gameOver) {
				//PLAYER 1 MOVEMENT
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Up) {
						p1movingUp = true;
					}
					if (event.key.code == sf::Keyboard::Down)
					{
						p1movingDown = true;
					}
					if (event.key.code == sf::Keyboard::Left)
					{
						p1movingLeft = true;
					}
					if (event.key.code == sf::Keyboard::Right)
					{
						p1movingRight = true;
					}
					if (event.key.code == sf::Keyboard::N)
					{
						player3m.setPosition(968, 270);
						player1m.setPosition(788, 70);
						player2m.setPosition(788, 470);
						player6m.setPosition(184, 270);
						player4m.setPosition(364, 70);
						player5m.setPosition(364, 470);
						player3.setPosition(1000, 350);
						player1.setPosition(820, 150);
						player2.setPosition(820, 550);
						player6.setPosition(210, 350);
						player4.setPosition(390, 150);
						player5.setPosition(390, 550);
						ball.setPosition(595, 410);
						GOAL.setScale(0, 0);
						OWNGOAL.setScale(0, 0);
						n.setScale(0, 0);
						reset = true;
						//music.play();
					}
					if (event.key.code == sf::Keyboard::U)
					{
						awaygoals++;
					}
					if (event.key.code == sf::Keyboard::I)
					{
						homegoals++;
					}
					if (event.key.code == sf::Keyboard::O)
					{
						awaygoals--;
					}
					if (event.key.code == sf::Keyboard::P)
					{
						homegoals--;
					}
				}
				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Up)
					{
						p1movingUp = false;
					}
					if (event.key.code == sf::Keyboard::Down)
					{
						p1movingDown = false;
					}
					if (event.key.code == sf::Keyboard::Left)
					{
						p1movingLeft = false;
					}
					if (event.key.code == sf::Keyboard::Right)
					{
						p1movingRight = false;
					}
				}

				//PLAYER 2 MOVEMENT
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::W) {
						p2movingUp = true;
					}
					if (event.key.code == sf::Keyboard::S)
					{
						p2movingDown = true;
					}
					if (event.key.code == sf::Keyboard::A)
					{
						p2movingLeft = true;
					}
					if (event.key.code == sf::Keyboard::D)
					{
						p2movingRight = true;
					}
				}
				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::W)
					{
						p2movingUp = false;
					}
					if (event.key.code == sf::Keyboard::S)
					{
						p2movingDown = false;
					}
					if (event.key.code == sf::Keyboard::A)
					{
						p2movingLeft = false;
					}
					if (event.key.code == sf::Keyboard::D)
					{

						p2movingRight = false;
					}
				}
				//CHANGE PLAYERS
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::RShift) {
						if (homePlayer == &player1) {
							homePlayer = &player2;
							homeMarker = &player2m;
							player1m.setScale(0.05, 0.05);
							player2m.setScale(0.12, 0.12);
						}
						else if (homePlayer == &player2) {
							homePlayer = &player3;
							homeMarker = &player3m;
							player2m.setScale(0.05, 0.05);
							player3m.setScale(0.12, 0.12);
						}
						else if (homePlayer == &player3) {
							homePlayer = &player1;
							homeMarker = &player1m;
							player3m.setScale(0.05, 0.05);
							player1m.setScale(0.12, 0.12);
						}
					}
					if (event.key.code == sf::Keyboard::C)
					{
						if (awayPlayer == &player4) {
							awayPlayer = &player5;
							awayMarker = &player5m;
							player4m.setScale(0.05, 0.05);
							player5m.setScale(0.12, 0.12);
						}
						else if (awayPlayer == &player5) {
							awayPlayer = &player6;
							awayMarker = &player6m;
							player5m.setScale(0.05, 0.05);
							player6m.setScale(0.12, 0.12);
						}
						else if (awayPlayer == &player6) {
							awayPlayer = &player4;
							awayMarker = &player4m;
							player6m.setScale(0.05, 0.05);
							player4m.setScale(0.12, 0.12);
						}
					}

					

				}
			}

			//SWITCHING TO MENU

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState == GAMEPLAY) {
				if (sf::Mouse::getPosition(window).x > 1122 && sf::Mouse::getPosition(window).x < 1177 && sf::Mouse::getPosition(window).y > 18 && sf::Mouse::getPosition(window).y < 73)
				{
					breakit = true;
					break;
				}
			}
		}

		//ANIMATION CLOCK
		timer = clock.getElapsedTime().asSeconds();
		if (timer > 0.1f) {
			if (imgCount < 3) {
				imgCount++;
			}
			else {
				imgCount = 0;
			}
			clock.restart();
		}

		//P1 VECTOR
		sf::Vector2f p1movement(0, 0);

		if (p1movingUp)
			//check if they are in bounds
			if (homePlayer->getPosition().y > 80)
				p1movement.y -= 0.3f;
		if (p1movingDown)
			if (homePlayer->getPosition().y < 730)
				p1movement.y += 0.3f;
		if (p1movingRight)
			if (homePlayer->getPosition().x < 1120)
				p1movement.x += 0.3f;
		if (p1movingLeft)
			if (homePlayer->getPosition().x > 110)
				p1movement.x -= 0.3f;

		//P2 VECTOR
		sf::Vector2f p2movement(0, 0);
		
		if (p2movingUp)
			//check if they are in bounds
			if (awayPlayer->getPosition().y > 80)
				p2movement.y -= 0.5f;
		if (p2movingDown)
			if (awayPlayer->getPosition().y < 730)
				p2movement.y += 0.5f;
		if (p2movingRight)
			if (awayPlayer->getPosition().x < 1120)
				p2movement.x += 0.5f;
		if (p2movingLeft)
			if (awayPlayer->getPosition().x > 110)
				p2movement.x -= 0.5f;

		//SET VECTORS FOR CURRENT PLAYER
		homePlayer -> move(p1movement);
		awayPlayer -> move(p2movement);
		homeMarker->move(p1movement);
		awayMarker->move(p2movement); 

		//ENACT RANDOM MOVEMENT (4 diff ones)
		sf::Vector2f homerandom(0 , 0);
		random_device homerd;
		
		int x = homerd() % 88;

		if (x >= 0 && x <= 22)
			if (player1.getPosition().y > 100 && player2.getPosition().y > 100 && player3.getPosition().y > 100)
				homerandom.y -= 0.7f;
		if (x >= 44 && x <= 66)
			if (player1.getPosition().y < 710 && player2.getPosition().y < 710 && player3.getPosition().y < 710)
				homerandom.y += 0.7f;
		if (x >= 22 && x <= 44)
			if (player1.getPosition().x < 1100 && player2.getPosition().x < 1100 && player3.getPosition().x < 1100)
				homerandom.x += 0.7f;
		if (x >= 66 || x == 0)
			if (player1.getPosition().x > 130 && player2.getPosition().x > 130 && player3.getPosition().x > 130)
				homerandom.x -= 0.7f;

		sf::Vector2f homerandom2(0, 0);
		random_device homerd2;

		int x2 = homerd() % 88;

		if (x2 >= 0 && x2 <= 22)
			if (player1.getPosition().y > 100 && player2.getPosition().y > 100 && player3.getPosition().y > 100)
				homerandom2.y -= 0.5f;
		if (x2 >= 44 && x2 <= 66)
			if (player1.getPosition().y < 710 && player2.getPosition().y < 710 && player3.getPosition().y < 710)
				homerandom2.y += 0.5f;
		if (x2 >= 22 && x2 <= 44)
			if (player1.getPosition().x < 1100 && player2.getPosition().x < 1100 && player3.getPosition().x < 1100)
			homerandom2.x += 0.5f;
		if (x2 >= 66 || x2 == 0)
			if (player1.getPosition().x > 130 && player2.getPosition().x > 130 && player3.getPosition().x > 130)
			homerandom2.x -= 0.5f;

		sf::Vector2f awayrandom(0, 0);
		random_device awayrd;

		int y = awayrd() % 88;

		if (y >= 0 && y <= 22)
			if (player4.getPosition().y > 100 && player5.getPosition().y > 100 && player6.getPosition().y > 100)
				awayrandom.y -= 0.7f;
		if (y >= 44 && y <= 66)
			if (player4.getPosition().y < 710 && player5.getPosition().y < 710 && player6.getPosition().y < 710)
			awayrandom.y += 0.7f;
		if (y >= 22 && y <= 44)
			if (player4.getPosition().x > 130 && player5.getPosition().x > 130 && player6.getPosition().x > 130)
			awayrandom.x -= 0.7f;
		if (y >= 66 || y == 0)
			if (player4.getPosition().x < 1100 && player5.getPosition().x < 1100 && player6.getPosition().x < 1100)
			awayrandom.x += 0.7f;

		sf::Vector2f awayrandom2(0, 0);
		random_device awayrd2;

		int y2 = awayrd2() % 88;

		if (y2 >= 0 && y2 <= 22)
			if (player4.getPosition().y > 100 && player5.getPosition().y > 100 && player6.getPosition().y > 100)
				awayrandom2.y -= 0.5f;
		if (y2 >= 44 && y2 <= 66)
			if (player4.getPosition().y < 710 && player5.getPosition().y < 710 && player6.getPosition().y < 710)
			awayrandom2.y += 0.5f;
		if (y2 >= 22 && y2 <= 44)
			if (player4.getPosition().x > 130 && player5.getPosition().x > 130 && player6.getPosition().x > 130)
				awayrandom2.x -= 0.5f;
		if (y2 >= 66 || y2 == 0)
			if (player4.getPosition().x < 1100 && player5.getPosition().x < 1100 && player6.getPosition().x < 1100)
				awayrandom2.x += 0.5f;

		//GOALKEEPER VECTOR
		sf::Vector2f homekeeper(0, 0);
		random_device homerand;

		int hgk = homerand() % 88;

		if (!(player1.getPosition().x > 930 || player2.getPosition().x > 930 || player3.getPosition().x > 930)) {
			if (hgk >= 0 && hgk <= 15)
				if (player1.getPosition().y > 100 && player2.getPosition().y > 100 && player3.getPosition().y > 100)
					homekeeper.y -= 0.7f;
			if (hgk >= 30 && hgk <= 45)
				if (player1.getPosition().y < 710 && player2.getPosition().y < 710 && player3.getPosition().y < 710)
					homekeeper.y += 0.7f;
			if (hgk >= 15 && hgk <= 30)
				if (player1.getPosition().x > 130 && player2.getPosition().x > 130 && player3.getPosition().x > 130)
					homekeeper.x -= 0.7f;
			if (hgk >= 45 || hgk == 0)
				if (player1.getPosition().x < 1100 && player2.getPosition().x < 1100 && player3.getPosition().x < 1100)
					homekeeper.x += 2.0f;
		}
		else {
			if (hgk >= 0 && hgk <= 22)
				if (player1.getPosition().y > 100 && player2.getPosition().y > 100 && player3.getPosition().y > 100)
					homekeeper.y -= 0.7f;
			if (hgk >= 44 && hgk <= 66)
				if (player1.getPosition().y < 710 && player2.getPosition().y < 710 && player3.getPosition().y < 710)
					homekeeper.y += 0.7f;
			if (hgk >= 22 && hgk <= 44)
				if (player1.getPosition().x < 1100 && player2.getPosition().x < 1100 && player3.getPosition().x < 1100)
					homekeeper.x += 0.7f;
			if (hgk >= 66 || hgk == 0)
				if (player1.getPosition().x > 130 && player2.getPosition().x > 130 && player3.getPosition().x > 130)
					homekeeper.x -= 0.7f;
		}


		sf::Vector2f awaykeeper(0, 0);
		random_device awayrand;

		int agk = awayrand() % 88;

		if (!(player4.getPosition().x < 230 || player5.getPosition().x < 230 || player6.getPosition().x < 230)) {
			if (agk >= 0 && agk <= 15)
				if (player4.getPosition().y > 100 && player5.getPosition().y > 100 && player6.getPosition().y > 100)
					awaykeeper.y -= 0.7f;
			if (agk >= 30 && agk <= 45)
				if (player4.getPosition().y < 710 && player5.getPosition().y < 710 && player6.getPosition().y < 710)
					awaykeeper.y += 0.7f;
			if (agk >= 15 && agk <= 30)
				if (player4.getPosition().x < 1100 && player5.getPosition().x < 1100 && player6.getPosition().x < 1100)
					awaykeeper.x += 0.7f;
			if (agk >= 45 || agk == 0)
				if (player4.getPosition().x > 130 && player5.getPosition().x > 130 && player6.getPosition().x > 130)
					awaykeeper.x -= 2.0f;
		}
		else {
			if (agk >= 0 && agk <= 22)
				if (player4.getPosition().y > 100 && player5.getPosition().y > 100 && player6.getPosition().y > 100)
					awaykeeper.y -= 0.7f;
			if (agk >= 44 && agk <= 66)
				if (player4.getPosition().y < 710 && player5.getPosition().y < 710 && player6.getPosition().y < 710)
					awaykeeper.y += 0.7f;
			if (agk >= 22 && agk <= 44)
				if (player4.getPosition().x > 130 && player5.getPosition().x > 130 && player6.getPosition().x > 130)
					awaykeeper.x -= 0.7f;
			if (agk >= 66 || agk == 0)
				if (player4.getPosition().x < 1100 && player5.getPosition().x < 1100 && player6.getPosition().x < 1100)
					awaykeeper.x += 0.7f;
		}


		//SET RANDOM/GOALKEEPER VECTORS
		if (homePlayer == &player1) {
			player2.move(homerandom);
			player2m.move(homerandom);
			player3.move(homekeeper);
			player3m.move(homekeeper);
		}
		else if (homePlayer == &player2) {
			player3.move(homekeeper);
			player3m.move(homekeeper);
			player1.move(homerandom2);
			player1m.move(homerandom2);
		}
		else if (homePlayer == &player3) {
			player1.move(homerandom);
			player1m.move(homerandom);
			player2.move(homekeeper);
			player2m.move(homekeeper);
		}

		if (awayPlayer == &player4) {
			player5.move(awayrandom);
			player5m.move(awayrandom);
			player6.move(awaykeeper);
			player6m.move(awaykeeper);
		}
		else if (awayPlayer == &player5) {
			player4.move(awayrandom2);
			player4m.move(awayrandom2);
			player6.move(awaykeeper);
			player6m.move(awaykeeper);
		}
		else if (awayPlayer == &player6) {
			player4.move(awayrandom);
			player4m.move(awayrandom);
			player5.move(awaykeeper);
			player5m.move(awaykeeper);
		}
		
		//GOAL LINES W/ VECTORS
		sf::ConvexShape homeline;
		homeline.setPointCount(4);
		homeline.setPoint(0, sf::Vector2f(1200, 300));
		homeline.setPoint(1, sf::Vector2f(1200, 560));
		homeline.setPoint(2, sf::Vector2f(1055, 560));
		homeline.setPoint(3, sf::Vector2f(1055, 300));
		homeline.setFillColor(sf::Color::Black);

		sf::ConvexShape awayline;
		awayline.setPointCount(4);
		awayline.setPoint(0, sf::Vector2f(150, 300));
		awayline.setPoint(1, sf::Vector2f(150, 560));
		awayline.setPoint(2, sf::Vector2f(0, 560));
		awayline.setPoint(3, sf::Vector2f(0, 300));
		awayline.setFillColor(sf::Color::Black);


		//PHYSICS (TAKE 1)

		if (player1.getGlobalBounds().intersects(ball.getGlobalBounds())) {
			velocity1 = 0.2;
			xdiff1 = ball.getPosition().x - player1.getPosition().x;
			ydiff1 = ball.getPosition().y - player1.getPosition().y;
		}
		if (velocity1 > 0) {
			
			velocity1 -= gravity;
			
			if (ball.getPosition().x >= 1096 || ball.getPosition().x <= 130)
				ball.move(sf::Vector2f(velocity1 * xdiff1 * -1.0, velocity1 * ydiff1));
			else if ((ball.getPosition().y >= 710 || ball.getPosition().y <= 100) && (player1.getPosition().y >= 100 && player1.getPosition().y <= 710))
				ball.move(sf::Vector2f(velocity1 * xdiff1, velocity1 * ydiff1 * -1.0));
			else if ((ball.getPosition().x >= 1050 || ball.getPosition().x <= 200) && ball.getPosition().y >= 650) {
				ball.setPosition(350, 650);
			}
			else if ((ball.getPosition().x >= 1050 || ball.getPosition().x <= 200) && ball.getPosition().y <= 200) {
				ball.setPosition(950, 150);
			}
			else
				ball.move(sf::Vector2f(velocity1 * xdiff1, velocity1 * ydiff1));
		
		}

		if (player2.getGlobalBounds().intersects(ball.getGlobalBounds())) {
			velocity2 = 0.2;
			xdiff2 = ball.getPosition().x - player2.getPosition().x;
			ydiff2 = ball.getPosition().y - player2.getPosition().y;
		}
		if (velocity2 > 0) {

			velocity2 -= gravity;
			
			if (ball.getPosition().x >= 1096 || ball.getPosition().x <= 130)
				ball.move(sf::Vector2f(velocity2* xdiff2* -1.0, velocity2* ydiff2));
			else if ((ball.getPosition().y >= 710 || ball.getPosition().y <= 100) && (player2.getPosition().y >= 100 && player2.getPosition().y <= 710))
				ball.move(sf::Vector2f(velocity2* xdiff2, velocity2* ydiff2* -1.0));
			else if ((ball.getPosition().x >= 1050 || ball.getPosition().x <= 200) && ball.getPosition().y >= 650) {
				ball.setPosition(650, 550);
			}
			else if ((ball.getPosition().x >= 1050 || ball.getPosition().x <= 200) && ball.getPosition().y <= 200) {
				ball.setPosition(650, 260);
			}
			else
				ball.move(sf::Vector2f(velocity2* xdiff2, velocity2* ydiff2));

		}

		if (player3.getGlobalBounds().intersects(ball.getGlobalBounds())) {
			velocity3 = 0.2;
			xdiff3 = ball.getPosition().x - player3.getPosition().x;
			ydiff3 = ball.getPosition().y - player3.getPosition().y;
		}
		if (velocity3 > 0) {

			velocity3 -= gravity;
			
			if (ball.getPosition().x >= 1096 || ball.getPosition().x <= 130)
				ball.move(sf::Vector2f(velocity3 * xdiff3 * -1.0, velocity3 * ydiff3));
			else if ((ball.getPosition().y >= 710 || ball.getPosition().y <= 100) && (player3.getPosition().y >= 100 && player3.getPosition().y <= 710))
				ball.move(sf::Vector2f(velocity3 * xdiff3, velocity3 * ydiff3 * -1.0));
			else if ((ball.getPosition().x >= 1050 || ball.getPosition().x <= 200) && ball.getPosition().y >= 650) {
				ball.setPosition(650, 550);
			}
			else if ((ball.getPosition().x >= 1050 || ball.getPosition().x <= 200) && ball.getPosition().y <= 200) {
				ball.setPosition(650, 260);
			}
			else
				ball.move(sf::Vector2f(velocity3 * xdiff3, velocity3 * ydiff3));

		}

		if (player4.getGlobalBounds().intersects(ball.getGlobalBounds())) {
			velocity4 = 0.26;
			xdiff4 = ball.getPosition().x - player4.getPosition().x;
			ydiff4 = ball.getPosition().y - player4.getPosition().y;
		}
		if (velocity4 > 0) {

			velocity4 -= gravity;
			
			
			if (ball.getPosition().x >= 1096 || ball.getPosition().x <= 130)
				ball.move(sf::Vector2f(velocity4 * xdiff4 * -1.0, velocity4 * ydiff4));
			else if ((ball.getPosition().y >= 710 || ball.getPosition().y <= 100) && (player4.getPosition().y >= 100 && player4.getPosition().y <= 710))
				ball.move(sf::Vector2f(velocity4 * xdiff4, velocity4 * ydiff4 * -1.0));
			else if ((ball.getPosition().x >= 1050 || ball.getPosition().x <= 200) && ball.getPosition().y >= 650) {
				ball.setPosition(650, 550);
			}
			else if ((ball.getPosition().x >= 1050 || ball.getPosition().x <= 200) && ball.getPosition().y <= 200) {
				ball.setPosition(650, 260);
			}
			else
				ball.move(sf::Vector2f(velocity4 * xdiff4, velocity4 * ydiff4));

		}

		if (player5.getGlobalBounds().intersects(ball.getGlobalBounds())) {
			velocity5 = 0.26;
			xdiff5 = ball.getPosition().x - player5.getPosition().x;
			ydiff5 = ball.getPosition().y - player5.getPosition().y;

		}
		if (velocity5 > 0) {

			velocity5 -= gravity;
			
			if (ball.getPosition().x >= 1096 || ball.getPosition().x <= 130)
				ball.move(sf::Vector2f(velocity5 * xdiff5 * -1.0, velocity5 * ydiff5));
			else if ((ball.getPosition().y >= 710 || ball.getPosition().y <= 100) && (player5.getPosition().y >= 100 && player5.getPosition().y <= 710))
				ball.move(sf::Vector2f(velocity5 * xdiff5, velocity5 * ydiff5 * -1.0));
			else if ((ball.getPosition().x >= 1050 || ball.getPosition().x <= 200) && ball.getPosition().y >= 650) {
				ball.setPosition(650, 550);
			}
			else if ((ball.getPosition().x >= 1050 || ball.getPosition().x <= 200) && ball.getPosition().y <= 200) {
				ball.setPosition(650, 260);
			}
			else
				ball.move(sf::Vector2f(velocity5 * xdiff5, velocity5 * ydiff5));

		}

		if (player6.getGlobalBounds().intersects(ball.getGlobalBounds())) {
			velocity6 = 0.26;
			xdiff6 = ball.getPosition().x - player6.getPosition().x;
			ydiff6 = ball.getPosition().y - player6.getPosition().y;

		}

		if (velocity6 > 0) {

			velocity6 -= gravity;
			
			if (ball.getPosition().x >= 1096 || ball.getPosition().x <= 130)
				ball.move(sf::Vector2f(velocity6 * xdiff6 * -1.0, velocity6 * ydiff6));
			else if ((ball.getPosition().y >= 710 || ball.getPosition().y <= 100) && (player6.getPosition().y >= 100 && player6.getPosition().y <= 710))
				ball.move(sf::Vector2f(velocity6 * xdiff6, velocity6 * ydiff6 * -1.0));
			else if ((ball.getPosition().x >= 1050 || ball.getPosition().x <= 180) && ball.getPosition().y >= 650) {
				ball.setPosition(650, 550);
			}
			else if ((ball.getPosition().x >= 1050 || ball.getPosition().x <= 180) && ball.getPosition().y <= 200) {
				ball.setPosition(650, 260);
			}
			else
				ball.move(sf::Vector2f(velocity6 * xdiff6, velocity6 * ydiff6));

		}


		//checks for goals
		if (ball.getGlobalBounds().intersects(homeline.getGlobalBounds())) {
			celebration.setBuffer(celebrationbuffer);
			celebration.setVolume(100);
			celebration.play();
			ball.setPosition(1190, 430);
			OWNGOAL.setScale(1.0, 1.0);
			n.setScale(1.0, 1.0);
			crossedhome = true;
		}
		else if (ball.getGlobalBounds().intersects(awayline.getGlobalBounds())) {
			celebration.setBuffer(celebrationbuffer);
			celebration.setVolume(100);
			celebration.play();
			ball.setPosition(10, 430);
			GOAL.setScale(1.0, 1.0);
			n.setScale(1.0, 1.0);
			crossedaway = true;
		}
		
		
		//scoreboard incrementation
		if (crossedaway && reset) {
			homegoals++;
			//if (homegoals - 1 > 0)	actualhomegoals = homegoals - 1;
			crossedaway = false;
			reset = false;
		}
		if (crossedhome && reset) {
			awaygoals++;
			//if (awaygoals - 1 > 0)	actualawaygoals = awaygoals - 1;
			crossedhome = false;
			reset = false;
		}

		homescore.setString(to_string(homegoals));
		awayscore.setString(to_string(awaygoals));

		if (homegoals >= 3 || awaygoals >= 3) {
			gameOver = true;
			celebration.setBuffer(celebrationbuffer);
			celebration.setVolume(2000);
			celebration.play();
		}

		if (gameOver && homegoals >= 3) {
			HOMEWINS.setScale(1.0, 1.0);
		}
		else if (gameOver) {
			AWAYWINS.setScale(1, 1);
		}

		//SET ANIMATIONS
		player1.setTextureRect(right[imgCount]);
		player2.setTextureRect(right[imgCount]);
		player3.setTextureRect(right[imgCount]);
		player4.setTextureRect(left[imgCount]);
		player5.setTextureRect(left[imgCount]);
		player6.setTextureRect(left[imgCount]);

		window.clear();

		//DRAW ALL SPRITES
		window.draw(homeline);
		window.draw(awayline);
		window.draw(background);
		window.draw(pause);

		if (a == 1)
			window.draw(usa);
		else if (a == 2)
			window.draw(france);
		else
			window.draw(fortnite);

		if(b == 1) 
			window.draw(korea);
		else if (b == 2)
			window.draw(spain);
		else 
			window.draw(pubg);

		window.draw(homescore);
		window.draw(awayscore);

		window.draw(ball);

		window.draw(player1);
		window.draw(player2);
		window.draw(player3);
		window.draw(player4);
		window.draw(player5);
		window.draw(player6);

		window.draw(player1m);
		window.draw(player2m);
		window.draw(player3m);
		window.draw(player4m);
		window.draw(player5m);
		window.draw(player6m);

		window.draw(GOAL);
		window.draw(OWNGOAL);
		window.draw(n);

		window.draw(HOMEWINS);
		window.draw(AWAYWINS);

		window.display();

		if (breakit) {
			break;
		}

	}

	currentState = MENU;
	//menu();

}

//MAIN METHOD
int main()
{
	//music
	music.openFromFile("Textures/flag.wav");
	music.setLoop(true);
	music.setVolume(200);
	music.play(); 

	//select team icon
	sf::Sprite ball;
	sf::Texture balltexture;
	balltexture.loadFromFile("Textures/ball.png");
	ball.setTexture(balltexture);
	ball.setScale(0.015, 0.015);
	ball.setOrigin(11, 11);
	ball.setPosition(570, 400);

	//boolean for click once
	bool once = true;

	//PARAMETERS FOR select --> game
	int a = 1;
	int b = 1;

	while (window.isOpen())
	{
		once = true;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState == MENU && once) {
			if (sf::Mouse::getPosition(window).x > 107 && sf::Mouse::getPosition(window).x < 617 && sf::Mouse::getPosition(window).y > 248 && sf::Mouse::getPosition(window).y < 358)
			{
				currentState = SELECT;
				once = false;
			}
			if (sf::Mouse::getPosition(window).x > 107 && sf::Mouse::getPosition(window).x < 617 && sf::Mouse::getPosition(window).y > 388 && sf::Mouse::getPosition(window).y < 498)
			{
				currentState = INSTRUCTIONS;
				once = false;
			}
		}

		//menu <-- select
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState == SELECT && once) {
			if (sf::Mouse::getPosition(window).x > 37 && sf::Mouse::getPosition(window).x < 357 && sf::Mouse::getPosition(window).y > 778 && sf::Mouse::getPosition(window).y < 828)
			{
				currentState = MENU;
				once = false;
			}
		}

		//menu <-- instructions
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState == INSTRUCTIONS && once) {
			if (sf::Mouse::getPosition(window).x > 37 && sf::Mouse::getPosition(window).x < 357 && sf::Mouse::getPosition(window).y > 778 && sf::Mouse::getPosition(window).y < 828)
			{
				currentState = MENU;
				once = false;
			}
		}

		//select --> game
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState == SELECT) {
			//TEAM1
			if (sf::Mouse::getPosition(window).x > 67 && sf::Mouse::getPosition(window).x < 577 && sf::Mouse::getPosition(window).y > 368 && sf::Mouse::getPosition(window).y < 468)
			{
				a = 1;
				ball.setPosition(570, 400);
				window.draw(ball);
				window.display();
			}
			//TEAM2
			if (sf::Mouse::getPosition(window).x > 67 && sf::Mouse::getPosition(window).x < 577 && sf::Mouse::getPosition(window).y > 498 && sf::Mouse::getPosition(window).y < 598)
			{
				a = 2; 
				ball.setPosition(570, 530);
				window.draw(ball);
				window.display();
			}
			//TEAM3
			if (sf::Mouse::getPosition(window).x > 67 && sf::Mouse::getPosition(window).x < 577 && sf::Mouse::getPosition(window).y > 628 && sf::Mouse::getPosition(window).y < 728)
			{
				a = 3; 
				ball.setPosition(570, 660);
				window.draw(ball);
				window.display();
			}
			//TEAM4
			if (sf::Mouse::getPosition(window).x > 647 && sf::Mouse::getPosition(window).x < 1147 && sf::Mouse::getPosition(window).y > 368 && sf::Mouse::getPosition(window).y < 468)
			{
				b = 1;
				ball.setPosition(1150, 400);
				window.draw(ball);
				window.display();
			}
			//TEAM5
			if (sf::Mouse::getPosition(window).x > 647 && sf::Mouse::getPosition(window).x < 1147 && sf::Mouse::getPosition(window).y > 498 && sf::Mouse::getPosition(window).y < 598)
			{
				b = 2; 
				ball.setPosition(1150, 530);
				window.draw(ball);
				window.display();
			}
			//TEAM6
			if (sf::Mouse::getPosition(window).x > 647 && sf::Mouse::getPosition(window).x < 1147 && sf::Mouse::getPosition(window).y > 628 && sf::Mouse::getPosition(window).y < 728)
			{
				b = 3;
				ball.setPosition(1150, 660);
				window.draw(ball);
				window.display();
			}
			//to the game
			if (sf::Mouse::getPosition(window).x > 867 && sf::Mouse::getPosition(window).x < 1177 && sf::Mouse::getPosition(window).y > 778 && sf::Mouse::getPosition(window).y < 828)
			{
				currentState = GAMEPLAY;
			}
		}

		if (currentState == MENU) {
			menu();
		}
		if (currentState == SELECT) {
			select();
		}
		if (currentState == GAMEPLAY) {
			game(a, b);
		}
		if (currentState == INSTRUCTIONS) {
			instructions();
		}
	}
	
}