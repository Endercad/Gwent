#include "Game.h"

Game::Game()
{
	stage_width = WIDTH;
	stage_height=HEIGHT;

	window.create(sf::VideoMode(stage_width,stage_height), L"Gwent");
}
Game::~Game()
{

}
Player::Player()
{
	HP = 2;
	nC_lib = LIBNUM;
	top_lib = 0;
	top_hand = 0;
	top_trash = 0;
	current_card = -1;
	No_line1 = 0;
	No_line2 = 0;
	No_line3 = 0;
	value_line1 = 0;
	value_line2 = 0;
	value_line3 = 0;
	isput = false;
	isskip = false;
	isgiveup = false;
	change_line = 0;
}
void Game::Init()
{
	window.setFramerateLimit(10);

	isBegin = false;
	isGameover = false;
	isGamequit = false;
	BStart_on = false;
	
	player_1.player_id = 1;
	player_2.player_id = 2;
	game_state = playing;
	current_player = P1;
	Fill(&player_1);
	Shuffle(&player_1);
	Fill(&player_2);
	Shuffle(&player_2);
	Deal(&player_1);
	Deal(&player_2);
	LoadMedia();
	BGM.setVolume(50);
	BGM.play();
	BGM.setLoop(true);

}
void Game::Fill(Player* P)
{
	Card c;
	c.code = "A_1_0";
	c.value = 0;
	P->C_Lib[P->top_lib]=c;
	P->top_lib++;
	c.code = "A_1_1";
	c.value = 5;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "A_1_2";
	c.value = 4;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "A0";
	c.value = 15;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "A1";
	c.value = 15;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "A2";
	c.value = 7;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "A3";
	c.value = 6;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "A4";
	c.value = 5;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "A5";
	c.value = 5;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "A6";
	c.value = 5;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "A7";
	c.value = 5;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "B_2_0";
	c.value = 7;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "B0";
	c.value = 6;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "B1";
	c.value = 5;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "B2";
	c.value = 5;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "B3";
	c.value = 4;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "B4";
	c.value = 4;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "C_1_0";
	c.value = 1;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "C_2_0";
	c.value = 5;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "C0";
	c.value = 6;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "C1";
	c.value = 6;
	P->C_Lib[P->top_lib] = c;
	P->top_lib++;
	c.code = "C2";
	c.value = 6;
	P->C_Lib[P->top_lib] = c;
	


	
	
}
void Game::Shuffle(Player* P)
{
	int index_old, index_new;
	srand(P->player_id*int(time(NULL))); 
	for (index_old = 0; index_old < LIBNUM; index_old++)
	{
		index_new = rand() % LIBNUM;
		swap(P->C_Lib[index_old], P->C_Lib[index_new]);
	}
}
void Game::Deal(Player* P)
{
	for (int i = 0; i < ORIGINNUM; i++)
	{
		Card c=P->C_Lib[P->top_lib];
		P->C_Hand[P->top_hand] = c;
		P->top_hand++;
		P->top_lib--;

	}
}
void Game::LoadMedia()
{
	if (!tBeginPaper.loadFromFile("../BeginPaper.jpg"))
		cout << "BeginPaper.jpg not found" << endl;
	if (!tBeginButton.loadFromFile("../BeginButton.png"))
		cout << "BeginButton.png not found" << endl;
	if (!tBG.loadFromFile("../BG.png"))
		cout << "BG.png not found" << endl;
	if (!tButton.loadFromFile("../button.png"))
		cout << "button.png not found" << endl;
	if (!tHP.loadFromFile("../HP.png"))
		cout << "HP.png not found" << endl;
	if (!tGrey.loadFromFile("../GameOver_Grey.png"))
		cout << "Grey.png not found" << endl;
	if (!tWin.loadFromFile("../Win.png"))
		cout << "Win.png not found" << endl;
	if (!tLose.loadFromFile("../Lose.png"))
		cout << "Lose.png not found" << endl;
	if (!BGM.openFromFile("../BGM.ogg"))
		cout << "BGM.ogg not found	" << endl;
}

void Game::Draw()
{
	window.clear();
	if (isBegin)
	{
		Draw_BG();
		Draw_Button();
		Draw_HP();
		Draw_Cards();
		Draw_TCards();
		Draw_TCards2();
		Draw_Value();
		Draw_Value2();
		Draw_CardNum();
		Draw_CardBack();
		if (isGameover)
		{
			Draw_Gameover();
		}
	}
	if (!isBegin)
	{
		Draw_BeginPaper();
		Draw_BeginButton();
	}
	window.display();
}
void Game::Draw_BeginPaper()
{
	sBeginPaper.setTexture(tBeginPaper);
	sBeginPaper.setPosition(0, (HEIGHT - sBeginPaper.getLocalBounds().height)/ 2);
	window.draw(sBeginPaper);
}
void Game::Draw_BeginButton()
{
	
	sBeginButton.setTexture(tBeginButton);
	sBeginButton.setOrigin(sBeginButton.getLocalBounds().width / 2, sBeginButton.getLocalBounds().height / 2);
	sBeginButton.setPosition(WIDTH / 2, HEIGHT / 2);
	B_Satrt.top = HEIGHT/2- sBeginButton.getLocalBounds().height / 2;
	B_Satrt.left = WIDTH/2- sBeginButton.getLocalBounds().width / 2;
	B_Satrt.height = sBeginButton.getLocalBounds().height;
	B_Satrt.width = sBeginButton.getLocalBounds().width;
	if (BStart_on)
	{
		sBeginButton.setColor(sf::Color(255, 255, 255, 255));
		cout << "color:yellow" << endl;
	}
	if (!BStart_on)
		sBeginButton.setColor(sf::Color(0, 0, 0, 255));
	window.draw(sBeginButton);
}
void Game::Draw_BG()
{
	sBG.setTexture(tBG);
	sBG.setPosition(0, 0);
	window.draw(sBG);
	
}
void Game::Draw_Button()
{
	sGiveup_Button.setTexture(tButton);
	sSkip_Button.setTexture(tButton);
	sPut_Button.setTexture(tButton);
	sGiveup_Button.setTextureRect(IntRect(BUTTONWIDTH * 0, 0, BUTTONWIDTH, BUTTONHEIGHT));
	sSkip_Button.setTextureRect(IntRect(BUTTONWIDTH * 1, 0, BUTTONWIDTH, BUTTONHEIGHT));
	sPut_Button.setTextureRect(IntRect(BUTTONWIDTH * 2, 0, BUTTONWIDTH, BUTTONHEIGHT));
	Vector2i leftcorner;
	leftcorner.x =900;
	leftcorner.y = 850;
	int margin = 5;
	sGiveup_Button.setPosition(leftcorner.x, leftcorner.y);
	B_Giveup.top = leftcorner.y;
	B_Giveup.left = leftcorner.x;
	B_Giveup.height = BUTTONHEIGHT;
	B_Giveup.width = BUTTONWIDTH;
	sSkip_Button.setPosition(leftcorner.x+BUTTONWIDTH*1+margin, leftcorner.y);
	B_Skip.top = leftcorner.y;
	B_Skip.left = leftcorner.x + BUTTONWIDTH * 1 + margin;
	B_Skip.height = BUTTONHEIGHT;
	B_Skip.width = BUTTONWIDTH;
	sPut_Button.setPosition(leftcorner.x+BUTTONWIDTH*2+margin*2, leftcorner.y);
	B_Put.top = leftcorner.y;
	B_Put.left = leftcorner.x + BUTTONWIDTH * 2 + margin*2;
	B_Put.height = BUTTONHEIGHT;
	B_Put.width = BUTTONWIDTH;
	window.draw(sGiveup_Button);
	window.draw(sSkip_Button);
	window.draw(sPut_Button);
}
void Game::Draw_Cards()
{
	int Pos_x = 380;
	int Pos_y = 680;
	for (int i = 0; i < player_1.top_hand; i++)
	{
		Texture tCard;
		Sprite sCard;
		stringstream ss;
		ss << "../cards/" << player_1.C_Hand[i].code << ".jpg";
		if (!tCard.loadFromFile(ss.str()))
			cout << ss.str() << " not found" << endl;
		sCard.setTexture(tCard);
		sCard.setScale(0.3, 0.25);
		sCard.setPosition(Pos_x,Pos_y);
		HCard[i].top = Pos_y;
		HCard[i].left = Pos_x;
		HCard[i].height = sCard.getLocalBounds().height;
		HCard[i].width = sCard.getLocalBounds().width;
		Pos_x += 60;
		window.draw(sCard);
		//绘制选中的卡牌
		if (player_1.current_card == i)
		{
			sCard.setPosition(1050, 300);
			sCard.setScale(0.6, 0.6);
			window.draw(sCard);
		}
		
	}
}
void Game::Draw_TCards()
{
	int PosX_l1, PosX_l2, PosX_l3;
	int PosY_l1, PosY_l2, PosY_l3;
	PosX_l1 = PosX_l2 = PosX_l3 = 460;
	PosY_l1 = 410;
	PosY_l2 = 500;
	PosY_l3 = 590;
	for (int i = 0; i < player_1.No_line1; i++)
	{
		Texture tCard;
		Sprite sCard;
		stringstream ss;
		ss << "../cards/" << player_1.C_Table[0][i].code << ".jpg";
		if (!tCard.loadFromFile(ss.str()))
			cout << ss.str() << "Not Found" << endl;
		sCard.setTexture(tCard);
		sCard.setScale(0.2, 0.14);
		sCard.setPosition(PosX_l1, PosY_l1);
		window.draw(sCard);
		PosX_l1 += 60;

	}
	for (int i = 0; i < player_1.No_line2; i++)
	{
		Texture tCard;
		Sprite sCard;
		stringstream ss;
		ss << "../cards/" << player_1.C_Table[1][i].code << ".jpg";
		if (!tCard.loadFromFile(ss.str()))
			cout << ss.str() << "Not Found" << endl;
		sCard.setTexture(tCard);
		sCard.setScale(0.2, 0.14);
		sCard.setPosition(PosX_l2, PosY_l2);
		window.draw(sCard);
		PosX_l2 += 60;

	}
	for (int i = 0; i < player_1.No_line3; i++)
	{
		Texture tCard;
		Sprite sCard;
		stringstream ss;
		ss << "../cards/" << player_1.C_Table[2][i].code << ".jpg";
		if (!tCard.loadFromFile(ss.str()))
			cout << ss.str() << "Not Found" << endl;
		sCard.setTexture(tCard);
		sCard.setScale(0.2, 0.14);
		sCard.setPosition(PosX_l3, PosY_l3);
		window.draw(sCard);
		PosX_l3 += 60;

	}
	
}
void Game::Draw_TCards2()
{
	//绘制机器人桌面的卡牌
	int PosX2_l1, PosX2_l2, PosX2_l3;
	int PosY2_l1, PosY2_l2, PosY2_l3;
	PosX2_l1 = PosX2_l2 = PosX2_l3 = 460;
	PosY2_l1 = 310;
	PosY2_l2 = 220;
	PosY2_l3 = 130;
	for (int i = 0; i < player_2.No_line1; i++)
	{
		Texture tCard2;
		Sprite sCard2;
		stringstream ss2;
		ss2 << "../cards/" << player_2.C_Table[0][i].code << ".jpg";
		if (!tCard2.loadFromFile(ss2.str()))
			cout << ss2.str() << "Not Found" << endl;
		sCard2.setTexture(tCard2);
		sCard2.setScale(0.2, 0.14);
		sCard2.setPosition(PosX2_l1, PosY2_l1);
		window.draw(sCard2);
		PosX2_l1 += 60;

	}
	for (int i = 0; i < player_2.No_line2; i++)
	{
		Texture tCard2;
		Sprite sCard2;
		stringstream ss2;
		ss2 << "../cards/" << player_2.C_Table[1][i].code << ".jpg";
		if (!tCard2.loadFromFile(ss2.str()))
			cout << ss2.str() << "Not Found" << endl;
		sCard2.setTexture(tCard2);
		sCard2.setScale(0.2, 0.14);
		sCard2.setPosition(PosX2_l2, PosY2_l2);
		window.draw(sCard2);
		PosX2_l2 += 60;

	}
	for (int i = 0; i < player_2.No_line3; i++)
	{
		Texture tCard2;
		Sprite sCard2;
		stringstream ss2;
		ss2 << "../cards/" << player_2.C_Table[2][i].code << ".jpg";
		if (!tCard2.loadFromFile(ss2.str()))
			cout << ss2.str() << "Not Found" << endl;
		sCard2.setTexture(tCard2);
		sCard2.setScale(0.2, 0.14);
		sCard2.setPosition(PosX2_l3, PosY2_l3);
		window.draw(sCard2);
		PosX2_l3 += 60;

	}
}
void Game::Draw_CardBack()
{
	Texture tCardBack;
	Sprite sCardBack1,sCardBack2;
	if (!tCardBack.loadFromFile("../CardBack.png"))
		cout << "load CardBack.png failed" << endl;
	sCardBack1.setTexture(tCardBack);
	sCardBack2.setTexture(tCardBack);
	if (player_1.top_trash > 0)
	{
		sCardBack1.setPosition(1023, 652);
		window.draw(sCardBack1);
		cout << "player1:graveyard card num:" << player_1.top_trash << endl;
	}
	if (player_2.top_trash > 0)
	{
		sCardBack2.setPosition(1023, 168);
		window.draw(sCardBack2);
		cout << "player2:graveyard card num:" << player_2.top_trash << endl;
	}
}
void Game::Draw_CardNum()
{
	//Draw HandCard Num
	Text num;
	Font font;
	stringstream ss;
	font.loadFromFile("../font.ttf");
	num.setFont(font);
	int charactersize = 18;
	num.setCharacterSize(charactersize);
	int posX_1, posY_1, posX_2, posY_2;
	posX_1 = 250;
	posY_1 = 620;
	posX_2 = 250;
	posY_2 = 310;
	ss << player_1.top_hand;
	string n = ss.str();
	num.setPosition(posX_1, posY_1);
	num.setString(n);
	window.draw(num);
	ss.str("");
	ss << player_2.top_hand;
	n = ss.str();
	num.setPosition(posX_2, posY_2);
	num.setString(n);
	window.draw(num);
	Texture tCardicon;
	Sprite sCardicon;
	tCardicon.loadFromFile("../cardicon.png");
	sCardicon.setTexture(tCardicon);
	sCardicon.setPosition(posX_1 - 20, posY_1);
	window.draw(sCardicon);
	sCardicon.setPosition(posX_2 - 20, posY_2);
	window.draw(sCardicon);
	//Draw LibCard Num
	ss.str("");
	ss << player_1.top_lib;
	n = ss.str();
	num.setPosition(1180, 770);
	num.setString(n);
	window.draw(num);
	ss.str("");
	ss << player_2.top_lib;
	n = ss.str();
	num.setPosition(1180, 270);
	num.setString(n);
	window.draw(num);
	//Draw current player
	ss.str("");
	if(current_player==P1)
		ss << "current player:P1";
	else
		ss << "current player:P2";
	string currentP;
	currentP = ss.str();
	num.setPosition(100, 850);
	num.setString(currentP);
	window.draw(num);
}	
void Game::Draw_Value()
{
	Text value;
	Font font;
	stringstream ss;
	font.loadFromFile("../font.ttf");
	value.setFont(font);
	int charactersize = 18;
	value.setCharacterSize(charactersize);
	int PosX_1 , PosX_2 , PosX_3 ;
	PosX_1 = PosX_2 = PosX_3 = 350;
	int PosY_1 = 435;
	int PosY_2 = 525;
	int PosY_3 = 615;
	int PosX_Sum = 300;
	int PosY_Sum = 600;
	ss << player_1.value_line1;
	string Value1 = ss.str();
	value.setPosition(PosX_1, PosY_1);
	value.setString(Value1);
	window.draw(value);
	ss.str("");
	ss << player_1.value_line2;
	string Value2 = ss.str();
	value.setPosition(PosX_2, PosY_2);
	value.setString(Value2);
	window.draw(value);
	ss.str("");
	ss << player_1.value_line3;
	string Value3 = ss.str();
	value.setPosition(PosX_3, PosY_3);
	value.setString(Value3);
	window.draw(value);
	ss.str("");
	player_1.value_sum = player_1.value_line1 + player_1.value_line2 + player_1.value_line3;
	ss << player_1.value_sum;
	string ValueSum = ss.str();
	value.setPosition(PosX_Sum, PosY_Sum);
	value.setString(ValueSum);
	window.draw(value);
}
void Game::Draw_Value2()
{
	Text value;
	Font font;
	stringstream ss;
	font.loadFromFile("../font.ttf");
	value.setFont(font);
	int charactersize = 18;
	value.setCharacterSize(charactersize);
	int PosX_1, PosX_2, PosX_3;
	PosX_1 = PosX_2 = PosX_3 = 350;
	int PosY_1 = 335;
	int PosY_2 = 245;
	int PosY_3 = 155;
	int PosX_Sum = 300;
	int PosY_Sum = 330;
	ss << player_2.value_line1;
	string Value1 = ss.str();
	value.setPosition(PosX_1, PosY_1);
	value.setString(Value1);
	window.draw(value);
	ss.str("");
	ss << player_2.value_line2;
	string Value2 = ss.str();
	value.setPosition(PosX_2, PosY_2);
	value.setString(Value2);
	window.draw(value);
	ss.str("");
	ss << player_2.value_line3;
	string Value3 = ss.str();
	value.setPosition(PosX_3, PosY_3);
	value.setString(Value3);
	window.draw(value);
	ss.str("");
	player_2.value_sum = player_2.value_line1 + player_2.value_line2 + player_2.value_line3;
	ss << player_2.value_sum;
	string ValueSum = ss.str();
	value.setPosition(PosX_Sum, PosY_Sum);
	value.setString(ValueSum);
	window.draw(value);
}
void Game::Draw_HP()
{
	sHP_P1.setTexture(tHP);
	sHP_P2.setTexture(tHP);
	int margin = 5;
	Vector2i leftcorner1;
	leftcorner1.x = 170;
	leftcorner1.y = 570;
	Vector2i leftcorner2;
	leftcorner2.x = 170;
	leftcorner2.y = 350;
	switch (player_1.HP)
	{
	case 2:
		sHP_P1.setTextureRect(IntRect(HPWIDTH * 0, 0, HPWIDTH, HPHEIGHT));
		sHP_P1.setPosition(leftcorner1.x, leftcorner1.y);
		window.draw(sHP_P1);
		sHP_P1.setTextureRect(IntRect(HPWIDTH * 0, 0, HPWIDTH, HPHEIGHT));
		sHP_P1.setPosition(leftcorner1.x+HPWIDTH+margin, leftcorner1.y);
		window.draw(sHP_P1);
		break;
	case 1:
		sHP_P1.setTextureRect(IntRect(HPWIDTH * 0, 0, HPWIDTH, HPHEIGHT));
		sHP_P1.setPosition(leftcorner1.x, leftcorner1.y);
		window.draw(sHP_P1);
		sHP_P1.setTextureRect(IntRect(HPWIDTH * 1, 0, HPWIDTH, HPHEIGHT));
		sHP_P1.setPosition(leftcorner1.x + HPWIDTH + margin, leftcorner1.y);
		window.draw(sHP_P1);
		break;
	case 0:
		sHP_P1.setTextureRect(IntRect(HPWIDTH * 1, 0, HPWIDTH, HPHEIGHT));
		sHP_P1.setPosition(leftcorner1.x, leftcorner1.y);
		window.draw(sHP_P1);
		sHP_P1.setTextureRect(IntRect(HPWIDTH * 1, 0, HPWIDTH, HPHEIGHT));
		sHP_P1.setPosition(leftcorner1.x + HPWIDTH + margin, leftcorner1.y);
		window.draw(sHP_P1);
		break;
	}
	switch (player_2.HP)
	{
	case 2:
		sHP_P2.setTextureRect(IntRect(HPWIDTH * 0, 0, HPWIDTH, HPHEIGHT));
		sHP_P2.setPosition(leftcorner2.x, leftcorner2.y);
		window.draw(sHP_P2);
		sHP_P2.setTextureRect(IntRect(HPWIDTH * 0, 0, HPWIDTH, HPHEIGHT));
		sHP_P2.setPosition(leftcorner2.x + HPWIDTH + margin, leftcorner2.y);
		window.draw(sHP_P2);
		break;
	case 1:
		sHP_P2.setTextureRect(IntRect(HPWIDTH * 0, 0, HPWIDTH, HPHEIGHT));
		sHP_P2.setPosition(leftcorner2.x, leftcorner2.y);
		window.draw(sHP_P2);
		sHP_P2.setTextureRect(IntRect(HPWIDTH * 1, 0, HPWIDTH, HPHEIGHT));
		sHP_P2.setPosition(leftcorner2.x + HPWIDTH + margin, leftcorner2.y);
		window.draw(sHP_P2);
		break;
	case 0:
		sHP_P2.setTextureRect(IntRect(HPWIDTH * 1, 0, HPWIDTH, HPHEIGHT));
		sHP_P2.setPosition(leftcorner2.x, leftcorner2.y);
		window.draw(sHP_P1);
		sHP_P2.setTextureRect(IntRect(HPWIDTH * 1, 0, HPWIDTH, HPHEIGHT));
		sHP_P2.setPosition(leftcorner2.x + HPWIDTH + margin, leftcorner2.y);
		window.draw(sHP_P2);
		break;
	}
}
void Game::Draw_Gameover()
{
	sGrey.setTexture(tGrey);
	sGrey.setPosition(0, 0);
	sGrey.setColor(sf::Color(255, 255, 255, 220));
	window.draw(sGrey);
	if (game_state == win)
	{
		sWin.setTexture(tWin);
		sWin.setOrigin(sWin.getLocalBounds().width/2, sWin.getLocalBounds().height / 2);
		sWin.setPosition(WIDTH / 2, HEIGHT / 2);
		window.draw(sWin);
	}
	else
	{
		sLose.setTexture(tLose);
		sLose.setOrigin(sLose.getLocalBounds().width/2, sWin.getLocalBounds().height / 2);
		sLose.setPosition(WIDTH / 2, HEIGHT / 2);
		window.draw(sLose);
	}

}

void Game::Input()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			isGamequit = true;
		}
		if (event.type == sf::Event::EventType::KeyReleased&&event.key.code == sf::Keyboard::Escape)
		{
			window.close();
			isGamequit = true;
		}
		if(isBegin)
		{ 
			if (event.type == sf::Event::EventType::MouseButtonPressed&&event.mouseButton.button ==sf::Mouse::Left)
			{
				cout << "LEFT MOUSE PRESSED " << endl;
				Vector2i mPosition = Mouse::getPosition(window);
				M_Click(mPosition);
			}
		}
		if (!isBegin)
		{
			if (event.type == sf::Event::EventType::MouseButtonPressed&&event.mouseButton.button == sf::Mouse::Left)
			{
				cout << "LEFT MOUSE PRESSED " << endl;
				Vector2i mPosition = Mouse::getPosition(window);
				Start_Click(mPosition);
			}
			if (event.type == sf::Event::EventType::MouseMoved)
			{
				Vector2i mPosition = Mouse::getPosition(window);
				if (B_Satrt.contains(mPosition.x, mPosition.y))
				{
					BStart_on = true;
					//sBeginButton.setColor(sf::Color(255, 255, 0, 255));
					cout << "Mouse Moved on SatrtButton" << endl;
				}
				else
				{
					BStart_on = false;
				}
			}
		}
	}
}
void Game::M_Click(Vector2i mPosition)
{
	if (current_player == P1)
	{
		if (B_Giveup.contains(mPosition.x, mPosition.y))
			Giveup();
		if (B_Skip.contains(mPosition.x, mPosition.y))
			Skip();
		if (B_Put.contains(mPosition.x, mPosition.y))
			Put();
		for (int i = 0; i < player_1.top_hand; i++)
		{
			if (HCard[i].contains(mPosition.x, mPosition.y))
				player_1.current_card = i;
		}
	}
}
void Game::Start_Click(Vector2i mPosition)
{
	if (B_Satrt.contains(mPosition.x, mPosition.y))
	{
		isBegin = true;
		cout << "game begins" << endl;
	}
}


void Game::Logic()
{
	Count(&player_1);
	Auto();
	Count(&player_2);
	sGameOver();
	bGameOver();
}
void Game::Giveup()
{
	if (current_player == P1)
	{
		cout << "You have Given up this small game" << endl;
		player_1.isgiveup = true;
		current_player = P2;
	}

}
void Game::Skip()
{
	if (current_player == P1)
	{
		if (player_1.isskip == true)
			player_1.isgiveup = true;
		cout << "You have Skip this round" << endl;
		player_1.isskip = true;
		current_player = P2;
	}

}
void Game::Put()
{
	if (current_player == P1)
	{
		if (player_1.current_card == -1)
			return;
		cout << "You have put a card " << endl;
		if (player_1.current_card != -1)
		{
			char c_type = player_1.C_Hand[player_1.current_card].code[0];
			switch (c_type)
			{
			case 'A':
			{
				char fun = player_1.C_Hand[player_1.current_card].code[1];
				if (fun != '_')
				{
					player_1.C_Table[0][player_1.No_line1] = player_1.C_Hand[player_1.current_card];
					player_1.No_line1++;
					player_1.change_line = 1;
					break;
				}
				else
				{
					char functype = player_1.C_Hand[player_1.current_card].code[2];
					if (functype == '1')
					{
						player_2.C_Table[0][player_2.No_line1] = player_1.C_Hand[player_1.current_card];
						player_2.No_line1++;
						player_1.change_line = -1;
						for (int i = 0; i < 2; i++)
						{
							player_1.C_Hand[player_1.top_hand] = player_1.C_Lib[player_1.top_lib - 1];
							player_1.top_hand++;
							player_1.top_lib--;
						}
						break;
					}
					if (functype == '2')
					{
						player_1.C_Table[0][player_1.No_line1] = player_1.C_Hand[player_1.current_card];
						player_1.No_line1++;
						player_1.change_line = 1;
						if (player_1.top_trash > 0)
						{
							srand(time(0));
							int num;
							bool flag = false;
							for (int i = 0; i < player_1.top_trash; i++)
							{
								if (player_1.C_Trash[i].code[1] != '_')
								{
									flag = true;
									break;
								}
							}
							while (flag)
							{
								num = rand() % (player_1.top_trash-1);
								if (player_1.C_Trash[num].code[1] != '_')
									break;
							}
							switch (player_1.C_Trash[num].code[0])
							{
							case 'A':
							{
								player_1.C_Table[0][player_1.No_line1++] = player_1.C_Trash[num];
								player_1.value_line1 += player_1.C_Trash[num].value;
								player_1.value_sum += player_1.C_Trash[num].value;
								break;
							}
							case 'B':
							{
								player_1.C_Table[1][player_1.No_line2++] = player_1.C_Trash[num];
								player_1.value_line2 += player_1.C_Trash[num].value;
								player_1.value_sum += player_1.C_Trash[num].value;
								break;
							}
							case 'C':
							{
								player_1.C_Table[2][player_1.No_line3++] = player_1.C_Trash[num];
								player_1.value_line3 += player_1.C_Trash[num].value;
								player_1.value_sum += player_1.C_Trash[num].value;
								break;
							}
							}
							for (int i = num; i < player_1.top_trash; i++)
							{
								player_1.C_Trash[i] = player_1.C_Trash[i + 1];
							}
							player_1.top_trash--;
						}
						break;
					}
				}
			}
			case 'B':
			{
				char fun = player_1.C_Hand[player_1.current_card].code[1];
				if (fun != '_')
				{
					player_1.C_Table[1][player_1.No_line2] = player_1.C_Hand[player_1.current_card];
					player_1.No_line2++;
					player_1.change_line = 2;
					break;
				}
				else
				{
					char functype = player_1.C_Hand[player_1.current_card].code[2];
					if (functype == '1')
					{
						player_2.C_Table[1][player_2.No_line2] = player_1.C_Hand[player_1.current_card];
						player_2.No_line2++;
						player_1.change_line = -2;
						for (int i = 0; i < 2; i++)
						{
							player_1.C_Hand[player_1.top_hand] = player_1.C_Lib[player_1.top_lib - i];
							player_1.top_hand++;
						}
						break;
					}
					if (functype == '2')
					{
						player_1.C_Table[1][player_1.No_line2] = player_1.C_Hand[player_1.current_card];
						player_1.No_line2++;
						player_1.change_line = 2;
						if (player_1.top_trash > 0)
						{
							srand(time(0));
							int num;
							bool flag = false;
							for (int i = 0; i < player_1.top_trash; i++)
							{
								if (player_1.C_Trash[i].code[1] != '_')
								{
									flag = true;
									break;
								}
							}
							while (flag)
							{
								num = rand() % (player_1.top_trash-1) ;
								if (player_1.C_Trash[num].code[1] != '_')
									break;
							}
							switch (player_1.C_Trash[num].code[0])
							{
							case 'A':
							{
								player_1.C_Table[0][player_1.No_line1++] = player_1.C_Trash[num];
								player_1.value_line1 += player_1.C_Trash[num].value;
								player_1.value_sum += player_1.C_Trash[num].value;
								break;
							}
							case 'B':
							{
								player_1.C_Table[1][player_1.No_line2++] = player_1.C_Trash[num];
								player_1.value_line2 += player_1.C_Trash[num].value;
								player_1.value_sum += player_1.C_Trash[num].value;
								break;
							}
							case 'C':
							{
								player_1.C_Table[2][player_1.No_line3++] = player_1.C_Trash[num];
								player_1.value_line3 += player_1.C_Trash[num].value;
								player_1.value_sum += player_1.C_Trash[num].value;
								break;
							}
							}
							for (int i = num; i < player_1.top_trash; i++)
							{
								player_1.C_Trash[i] = player_1.C_Trash[i + 1];
							}
							player_1.top_trash--;
						}
						break;
					}
				}
			}
			case 'C':
			{
				char fun = player_1.C_Hand[player_1.current_card].code[1];
				if (fun != '_')
				{
					player_1.C_Table[2][player_1.No_line3] = player_1.C_Hand[player_1.current_card];
					player_1.No_line3++;
					player_1.change_line = 3;
					break;
				}
				else
				{
					char functype = player_1.C_Hand[player_1.current_card].code[2];
					if (functype == '1')
					{
						player_2.C_Table[2][player_2.No_line3] = player_1.C_Hand[player_1.current_card];
						player_2.No_line3++;
						player_1.change_line = -3;
						for (int i = 0; i < 2; i++)
						{
							player_1.C_Hand[player_1.top_hand] = player_1.C_Lib[player_1.top_lib - i];
							player_1.top_hand++;
						}
						break;
					}
					if (functype == '2')
					{
						player_1.C_Table[2][player_1.No_line3] = player_1.C_Hand[player_1.current_card];
						player_1.No_line3++;
						player_1.change_line = 3;
						if (player_1.top_trash > 0)
						{
							srand(time(0));
							int num;
							bool flag = false;
							for (int i = 0; i < player_1.top_trash; i++)
							{
								if (player_1.C_Trash[i].code[1] != '_')
								{
									flag = true;
									break;
								}
							}
							while (flag)
							{
								num = rand() % player_1.top_trash - 1;
								if (player_1.C_Trash[num].code[1] != '_')
									break;
							}
							if (flag)
							{
								switch (player_1.C_Trash[num].code[0])
								{
								case 'A':
								{
									player_1.C_Table[0][player_1.No_line1++] = player_1.C_Trash[num];
									player_1.value_line1 += player_1.C_Trash[num].value;
									player_1.value_sum += player_1.C_Trash[num].value;
									break;
								}
								case 'B':
								{
									player_1.C_Table[1][player_1.No_line2++] = player_1.C_Trash[num];
									player_1.value_line2 += player_1.C_Trash[num].value;
									player_1.value_sum += player_1.C_Trash[num].value;
									break;
								}
								case 'C':
								{
									player_1.C_Table[2][player_1.No_line3++] = player_1.C_Trash[num];
									player_1.value_line3 += player_1.C_Trash[num].value;
									player_1.value_sum += player_1.C_Trash[num].value;
									break;
								}
								}
								for (int i = num; i < player_1.top_trash; i++)
								{
									player_1.C_Trash[i] = player_1.C_Trash[i + 1];
								}
								player_1.top_trash--;
							}
						}
						break;
					}
				}
			}
			}                                                                                                                                                                                                                       
			for (int i = player_1.current_card; i < player_1.top_hand; i++)
			{
				player_1.C_Hand[i] = player_1.C_Hand[i + 1];
			}
			player_1.top_hand -= 1;
			player_1.current_card = -1;
			player_1.isput = true;
		}
		if (player_1.isskip == true)
			player_1.isskip = false;
		if(player_2.isgiveup==false)
			current_player = P2;
	}

}
void Game::P2_Put()
{
	if (current_player == P2)
	{
		player_2.current_card = player_2.top_hand - 1;
		char type = player_2.C_Hand[player_2.current_card].code[0];
		switch (type)
		{
		case 'A':
		{
			char fun = player_2.C_Hand[player_2.current_card].code[1];
			if (fun != '_')
			{
				player_2.C_Table[0][player_2.No_line1] = player_2.C_Hand[player_2.current_card];
				player_2.No_line1++;
				player_2.change_line = 1;
				break;
			}
			else
			{
				char functype = player_2.C_Hand[player_2.current_card].code[2];
				if (functype == '1')
				{
					player_1.C_Table[0][player_1.No_line1] = player_2.C_Hand[player_2.current_card];
					player_1.No_line1++;
					player_2.change_line = -4;
					for (int i = 0; i < 2; i++)
					{
						player_2.C_Hand[player_2.top_hand] = player_2.C_Lib[player_2.top_lib - i];
						player_2.top_hand++;
						player_2.top_lib--;
					}
					break;
				}
				if (functype == '2')
				{
					player_2.C_Table[0][player_2.No_line1] = player_2.C_Hand[player_2.current_card];
					player_2.No_line1++;
					player_2.change_line = 1;
					if (player_2.top_trash > 0)
					{
						srand(time(0));
						int num;
						bool flag = false;
						for (int i = 0; i < player_2.top_trash; i++)
						{
							if (player_2.C_Trash[i].code[1] != '_')
							{
								flag = true;
								break;
							}
						}
						while (flag)
						{
							num = rand() % (player_2.top_trash - 1);
							if (player_2.C_Trash[num].code[1] != '_')
								break;
						}
						switch (player_2.C_Trash[num].code[0])
						{
						case 'A':
						{
							player_2.C_Table[0][player_2.No_line1++] = player_2.C_Trash[num];
							player_2.value_line1 += player_2.C_Trash[num].value;
							player_2.value_sum += player_2.C_Trash[num].value;
							break;
						}
						case 'B':
						{
							player_2.C_Table[1][player_2.No_line2++] = player_2.C_Trash[num];
							player_2.value_line2 += player_2.C_Trash[num].value;
							player_2.value_sum += player_2.C_Trash[num].value;
							break;
						}
						case 'C':
						{
							player_2.C_Table[2][player_2.No_line3++] = player_2.C_Trash[num];
							player_2.value_line3 += player_2.C_Trash[num].value;
							player_2.value_sum += player_2.C_Trash[num].value;
							break;
						}
						}
						for (int i = num; i < player_2.top_trash; i++)
						{
							player_2.C_Trash[i] = player_2.C_Trash[i + 1];
						}
						player_2.top_trash--;
					}
					break;
				}

			}
		}
		case 'B':
		{
			char fun = player_2.C_Hand[player_2.current_card].code[1];
			if (fun != '_')
			{
				player_2.C_Table[1][player_2.No_line2] = player_2.C_Hand[player_2.current_card];
				player_2.No_line2++;
				player_2.change_line = 2;
				break;
			}
			else
			{
				char functype = player_2.C_Hand[player_2.current_card].code[2];
				if (functype == '1')
				{
					player_1.C_Table[1][player_1.No_line2] = player_2.C_Hand[player_2.current_card];
					player_1.No_line2++;
					player_2.change_line = -5;
					for (int i = 0; i < 2; i++)
					{
						player_2.C_Hand[player_2.top_hand] = player_2.C_Lib[player_2.top_lib - i];
						player_2.top_hand++;
						player_2.top_lib--;
					}
					break;
				}
				if (functype == '2')
				{
					player_2.C_Table[1][player_2.No_line2] = player_2.C_Hand[player_2.current_card];
					player_2.No_line2++;
					player_2.change_line = 2;
					if (player_2.top_trash > 0)
					{
						srand(time(0));
						int num;
						bool flag = false;
						for (int i = 0; i < player_2.top_trash; i++)
						{
							if (player_2.C_Trash[i].code[1] != '_')
							{
								flag = true;
								break;
							}
						}
						while (flag)
						{
							num = rand() % (player_2.top_trash - 1);
							if (player_2.C_Trash[num].code[1] != '_')
								break;
						}
						switch (player_2.C_Trash[num].code[0])
						{
						case 'A':
						{
							player_2.C_Table[0][player_2.No_line1++] = player_2.C_Trash[num];
							player_2.value_line1 += player_2.C_Trash[num].value;
							player_2.value_sum += player_2.C_Trash[num].value;
							break;
						}
						case 'B':
						{
							player_2.C_Table[1][player_2.No_line2++] = player_2.C_Trash[num];
							player_2.value_line2 += player_2.C_Trash[num].value;
							player_2.value_sum += player_2.C_Trash[num].value;
							break;
						}
						case 'C':
						{
							player_2.C_Table[2][player_2.No_line3++] = player_2.C_Trash[num];
							player_2.value_line3 += player_2.C_Trash[num].value;
							player_2.value_sum += player_2.C_Trash[num].value;
							break;
						}
						}
						for (int i = num; i < player_2.top_trash; i++)
						{
							player_2.C_Trash[i] = player_2.C_Trash[i + 1];
						}
						player_2.top_trash--;
					}
					break;
				}
			}
		}
		case 'C':
		{
			char fun = player_2.C_Hand[player_2.current_card].code[1];
			if (fun != '_')
			{
				player_2.C_Table[2][player_2.No_line3] = player_2.C_Hand[player_2.current_card];
				player_2.No_line3++;
				player_2.change_line = 3;
				break;
			}
			else
			{
				char functype = player_2.C_Hand[player_2.current_card].code[2];
				if (functype == '1')
				{
					player_1.C_Table[2][player_1.No_line3] = player_2.C_Hand[player_2.current_card];
					player_1.No_line3++;
					player_2.change_line = -6;
					for (int i = 0; i < 2; i++)
					{
						player_2.C_Hand[player_2.top_hand] = player_2.C_Lib[player_2.top_lib - i];
						player_2.top_hand++;
						player_2.top_lib--;
					}
					break;
				}
				if (functype == '2')
				{
					player_2.C_Table[1][player_2.No_line2] = player_2.C_Hand[player_2.current_card];
					player_2.No_line2++;
					player_2.change_line = 2;
					if (player_2.top_trash > 0)
					{
						srand(time(0));
						int num;
						bool flag = false;
						for (int i = 0; i < player_2.top_trash; i++)
						{
							if (player_2.C_Trash[i].code[1] != '_')
							{
								flag = true;
								break;
							}
						}
						while (flag)
						{
							num = rand() % (player_2.top_trash - 1);
							if (player_2.C_Trash[num].code[1] != '_')
								break;
						}
						switch (player_2.C_Trash[num].code[0])
						{
						case 'A':
						{
							player_2.C_Table[0][player_2.No_line1++] = player_2.C_Trash[num];
							player_2.value_line1 += player_2.C_Trash[num].value;
							player_2.value_sum += player_2.C_Trash[num].value;
							break;
						}
						case 'B':
						{
							player_2.C_Table[1][player_2.No_line2++] = player_2.C_Trash[num];
							player_2.value_line2 += player_2.C_Trash[num].value;
							player_2.value_sum += player_2.C_Trash[num].value;
							break;
						}
						case 'C':
						{
							player_2.C_Table[2][player_2.No_line3++] = player_2.C_Trash[num];
							player_2.value_line3 += player_2.C_Trash[num].value;
							player_2.value_sum += player_2.C_Trash[num].value;
							break;
						}
						}
						for (int i = num; i < player_2.top_trash; i++)
						{
							player_2.C_Trash[i] = player_2.C_Trash[i + 1];
						}
						player_2.top_trash--;
					}
					break;
				}
			}
		}
		}
		for (int i = player_2.current_card; i < player_2.top_hand; i++)
		{
			player_2.C_Hand[i] = player_2.C_Hand[i + 1];
		}
		player_2.top_hand -= 1;
		player_2.isput = true;
	}
	if(player_1.isgiveup==false)
		current_player = P1;
}
void Game::P2_Giveup()
{
	if (current_player == P2)
	{
		cout << "P2 has Given up this small game" << endl;
		player_2.isgiveup = true;
		current_player = P1;
	}
}
void Game::Auto()
{
	if (player_1.isgiveup == false)
	{
		if (player_2.top_hand > 0)
			P2_Put();
		else
			P2_Giveup();
	}
	if (player_1.isgiveup == true)
	{
		int value_hand = 0;
		for (int i = 0; i < player_2.top_hand; i++)
		{
			value_hand += player_2.C_Hand[i].value;
		}
		if (player_1.value_sum < player_2.value_sum)
		{
			P2_Giveup();
		}
		else
		{
			if (player_1.value_sum - player_2.value_sum > value_hand)
			{
				P2_Giveup();
			}
			else
			{
				P2_Put();
			}
		}

		
	}
}

void Game::Count(Player* P)
{
	if (P->isput == true)
	{
		switch (P->change_line)
		{
		case 1:
			if (P->No_line1 != 0)
			{
					P->value_line1 += P->C_Table[0][P->No_line1-1].value;
			}
			break;
		case 2:
			if (P->No_line2 != 0)
			{
					P->value_line2 += P->C_Table[1][P->No_line2-1].value;
			}
			break;
		case 3:
			if (P->No_line3 != 0)
			{
					P->value_line3 += P->C_Table[2][P->No_line3-1].value;
			}
			break;
		case -1:
			player_2.value_line1 += player_2.C_Table[0][player_2.No_line1 - 1].value;
			break;
		case -2:
			player_2.value_line2 += player_2.C_Table[1][player_2.No_line2 - 1].value;
			break;
		case -3:
			player_2.value_line3 += player_2.C_Table[2][player_2.No_line3 - 1].value;
			break;
		case -4:
			player_1.value_line1 += player_1.C_Table[0][player_1.No_line1 - 1].value;
			break;
		case -5:
			player_1.value_line2 += player_1.C_Table[1][player_1.No_line2 - 1].value;
			break;
		case -6:
			player_1.value_line3 += player_1.C_Table[2][player_1.No_line3 - 1].value;
			break;

		default:
			break;
		}
		P->isput = false;
		cout << "P1 line_3 value:" << player_1.value_line3 << endl;
		cout << "P1 line_2 value:" << player_1.value_line2 << endl;
		cout << "P1 line_1 value:" << player_1.value_line1 << endl;
		cout << "P2 line_3 value:" << player_2.value_line3 << endl;
		cout << "P2 line_2 value:" << player_2.value_line2 << endl;
		cout << "P2 line_1 value:" << player_2.value_line1 << endl;
	}
}
void Game::sGameOver()
{
	if ((player_1.isgiveup == true&&player_2.isgiveup==true)||(player_1.top_hand==0&&player_2.isgiveup==true)||(player_2.top_hand==0&&player_1.isgiveup==true))
	{
		//Sleep(1000);
		Check();
		player_1.isgiveup = false;
		player_2.isgiveup = false;
	}
}
void Game::bGameOver()
{
	if (player_1.HP == 0)
	{
		cout << "Lose" << endl;
		isGameover = true;
		game_state = lose;
	}
	if (player_2.HP == 0)
	{
		cout << "Win" << endl;
		isGameover=true;
		game_state = win;
	}
}
void Game::Check()
{
	if (player_1.value_sum > player_2.value_sum)
	{
		player_2.HP--; 
		Clear();
	}
	else if (player_1.value_sum < player_2.value_sum)
	{
		player_1.HP--;
		Clear();
	}
	else
	{

	}
}
void Game::Clear()
{
	if (player_1.No_line1 > 0)
	{
		for (int i = 0; i < player_1.No_line1; i++)
		{
			player_1.C_Trash[player_1.top_trash] = player_1.C_Table[0][i];
			player_1.top_trash++;
		}
	}
	if(player_1.No_line2 > 0)
	{
		for (int i = 0; i < player_1.No_line2; i++)
		{
			player_1.C_Trash[player_1.top_trash] = player_1.C_Table[1][i];
			player_1.top_trash++;
		}
	}
	if(player_1.No_line3 > 0)
	{
		for (int i = 0; i < player_1.No_line3; i++)
		{
			player_1.C_Trash[player_1.top_trash] = player_1.C_Table[2][i];
			player_1.top_trash++;
		}
	}
	if (player_2.No_line1 > 0)
	{
		for (int i = 0; i < player_2.No_line1; i++)
		{
			player_2.C_Trash[player_2.top_trash] = player_2.C_Table[0][i];
			player_2.top_trash++;
		}
	}
	if (player_2.No_line2 > 0)
	{
		for (int i = 0; i < player_2.No_line2; i++)
		{
			player_2.C_Trash[player_2.top_trash] = player_2.C_Table[1][i];
			player_2.top_trash++;
		}
	}
	if (player_2.No_line3 > 0)
	{
		for (int i = 0; i < player_2.No_line3; i++)
		{
			player_2.C_Trash[player_2.top_trash] = player_2.C_Table[2][i];
			player_2.top_trash++;
		}
	}
	player_1.No_line1 =  0;
	player_1.No_line2 = 0;
	player_1.No_line3 = 0;
	player_2.No_line1 = 0;
	player_2.No_line2 = 0;
	player_2.No_line3 = 0;
	player_1.value_line1 = 0;
	player_1.value_line2 = 0;
	player_1.value_line3 = 0;
	player_2.value_line1 = 0;
	player_2.value_line2 = 0;
	player_2.value_line3 = 0;
}

void Game::Run()
{
	Input();
	Count(&player_1);
	Draw();
	Sleep(500);
	Auto();
	Count(&player_2);
	Draw();
	sGameOver();
	bGameOver();
	/*Input();
	Logic();
	Draw();*/

}

void Game::GameOver()
{
	
}
int main()
{

	Game Gwent;
	Gwent.Init();
	while (Gwent.window.isOpen())
	{
		Gwent.Run();
	}
}
