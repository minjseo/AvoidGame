#pragma once

// C++ 제공 라이브러리
#include <iostream> // 입출력 흐름 _ cout << / cin >> 
#include <sstream> // 흐름약자(str) _ pt << / 
#include <vector>  //Vector 배열 함수

#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

using namespace sf;
using namespace std;

class Game
{
private:

	RenderWindow* Window; //동적 할당 '포인터선언'
	Event Event;

	CircleShape Player;   //Element ①
	RectangleShape Enemy; //Element ②-1

	vector<RectangleShape> EnemyArrary; //Element ②-2
	int EnemyMax; 
	float IntervalMax;
	float IntervalStart;

	int Point; 
	Font Font; //윈도우 폰트파일 정보 리딩 (화면 노출 '준비')
	Text PointText; // 화면에 '점수' 텍스트 노출
	Text GameOverText; // 화면에 '게임종료' 텍스트 노출 

	bool GameOverState;

public:
	
	// ▼---------------------- Startup ▼ GameFlow ▼
	Game();  //생성자
	void InitWindowPointer();
	void InitWindow();
	// ▼---------------------- Update
	const bool Running() const;
	void EventHandler();
	void Update();
	// ▼---------------------- Render
	void Render();
	// ▼---------------------- ShutDown ▲ GameFlow ▲
	~Game();//소멸자
	void DeleteWindow();
	// ▼---------------------- Element_P(사용자액션O)
	void InitPlayer();
	void UpdatePlayer();
	// ▼---------------------- Element_E(사용자액션X)
	void InitEnemy();
	void InitSpawn();
	void SpawnEnemy(); 
	void UpdateEnemy();
	// ▼---------------------- Collision_C
	void CollisionCheck();
	// ▼---------------------- Font/Text
	void InitFont();
	void InitPointText();
	void UpdatePointText();
	void InitGameOverText();
	void PrintGameOverText();

};  

