#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Game.h"


int main()
{
	// 랜덤값 사용 시작 : 초기값 설정 
	// time값 사용 : 실행할 때 마다 초기값을 달리 사용 
	// *괄호안의 값으로 실행시 동일하게 사용 -- NULL처리 
	srand(time(NULL));
	
	// ▼ Startup
	Game Avoid;
	while (Avoid.Running()) 
		//Game Loop (무한 루프가 게임 루프로 작용) 
	{
		// ▼ Update 
		Avoid.Update();
		/* 아래 함수 포함
		this->EventHandler(); 
		this->UpdatePlayer();
		this->UpdateEnemy();
		this->CollisionCheck();
		this->UpdatePointText();
		*/

		// ▼ Render
		Avoid.Render();
	}
}

/*initWindow 600
* initspawn static cast
*/
