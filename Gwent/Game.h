#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>	
#include<Windows.h>
#include<iostream>
#include<sstream>
#include<string>
#include<time.h>

using namespace sf;
using namespace std;


#define WIDTH 1280
#define HEIGHT 960 
#define BUTTONWIDTH 96
#define BUTTONHEIGHT 52
#define HPWIDTH 29
#define HPHEIGHT 29
#define LINEVOLUME  9		//每行能容纳的卡牌上线
#define LIBNUM		22		//牌库容量
#define ORIGINNUM	7		//初始手牌数量
#define NHANDMAX	9		//手牌上限数量

class Card
{
public:
	string code;
	int value;
};
class Player
{
public:
	int player_id;
	int nC_hand;		//手牌数量
	int nC_lib;			//牌库卡牌数量
	int nC_trash;		//墓地卡牌数量
	int value_sum;		//战场数值
	int value_line1;
	int value_line2;
	int value_line3;
	int HP;
	Card C_Lib[30], C_Hand[30], C_Trash[30],C_Table[3][LINEVOLUME];
	int No_line1;
	int No_line2;
	int No_line3;
	int top_lib;
	int top_hand;
	int top_trash;
	Player();
	int current_card;
	bool isput;
	bool isskip;
	bool isgiveup;
	int change_line;
};

typedef enum Current_Player
{
	P1 ,
	P2
	
};

typedef enum GameState
{
	playing,
	win,
	lose
};
class Game
{
public:
	sf::RenderWindow window;
	int stage_width;
	int stage_height;
	bool isBegin;
	bool isGameover;
	bool isGamequit;
	bool BStart_on;
	Player player_1;
	Player player_2;
	Current_Player current_player;
	GameState game_state;

	Texture tBG,tBeginPaper, tButton,tBeginButton, tHP,tGrey,tWin,tLose;
	Sprite sBG,sBeginPaper,sBeginButton, sSkip_Button, sGiveup_Button, sPut_Button, sHP_P1, sHP_P2,sGrey,sWin,sLose;
	Music BGM;
	
	IntRect B_Giveup, B_Skip, B_Put,B_Satrt;
	IntRect HCard[NHANDMAX];

	Game();
	~Game();
	void Init();
	void Fill(Player* P);		//初始化牌库
	void Shuffle(Player* P);		//打乱牌库
	void Deal(Player* P);		//发牌
	void LoadMedia();

	void Draw();
	void Draw_BeginPaper();
	void Draw_BeginButton();
	void Draw_BG();
	void Draw_Button();
	void Draw_HP();
	void Draw_Cards();
	void Draw_TCards();
	void Draw_TCards2();
	void Draw_CardBack();
	void Draw_Value();
	void Draw_Value2();
	void Draw_CardNum();
	void Draw_Gameover();

	void Input();
	void M_Click(Vector2i mPosition);
	void Start_Click(Vector2i mPosition);

	void Logic();
	void Giveup();
	void Skip();
	void Put();
	void Count(Player* P);
	void P2_Put();
	void P2_Giveup();
	void Auto();
	void sGameOver();
	void bGameOver();
	void Check();
	void Clear();

	void Run();
	void GameOver();



};