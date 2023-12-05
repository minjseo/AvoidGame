#pragma once

// C++ ���� ���̺귯��
#include <iostream> // ����� �帧 _ cout << / cin >> 
#include <sstream> // �帧����(str) _ pt << / 
#include <vector>  //Vector �迭 �Լ�

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

	RenderWindow* Window; //���� �Ҵ� '�����ͼ���'
	Event Event;

	CircleShape Player;   //Element ��
	RectangleShape Enemy; //Element ��-1

	vector<RectangleShape> EnemyArrary; //Element ��-2
	int EnemyMax; 
	float IntervalMax;
	float IntervalStart;

	int Point; 
	Font Font; //������ ��Ʈ���� ���� ���� (ȭ�� ���� '�غ�')
	Text PointText; // ȭ�鿡 '����' �ؽ�Ʈ ����
	Text GameOverText; // ȭ�鿡 '��������' �ؽ�Ʈ ���� 

	bool GameOverState;

public:
	
	// ��---------------------- Startup �� GameFlow ��
	Game();  //������
	void InitWindowPointer();
	void InitWindow();
	// ��---------------------- Update
	const bool Running() const;
	void EventHandler();
	void Update();
	// ��---------------------- Render
	void Render();
	// ��---------------------- ShutDown �� GameFlow ��
	~Game();//�Ҹ���
	void DeleteWindow();
	// ��---------------------- Element_P(����ھ׼�O)
	void InitPlayer();
	void UpdatePlayer();
	// ��---------------------- Element_E(����ھ׼�X)
	void InitEnemy();
	void InitSpawn();
	void SpawnEnemy(); 
	void UpdateEnemy();
	// ��---------------------- Collision_C
	void CollisionCheck();
	// ��---------------------- Font/Text
	void InitFont();
	void InitPointText();
	void UpdatePointText();
	void InitGameOverText();
	void PrintGameOverText();

};  

