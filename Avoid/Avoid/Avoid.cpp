#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Game.h"


int main()
{
	// ������ ��� ���� : �ʱⰪ ���� 
	// time�� ��� : ������ �� ���� �ʱⰪ�� �޸� ��� 
	// *��ȣ���� ������ ����� �����ϰ� ��� -- NULLó�� 
	srand(time(NULL));
	
	// �� Startup
	Game Avoid;
	while (Avoid.Running()) 
		//Game Loop (���� ������ ���� ������ �ۿ�) 
	{
		// �� Update 
		Avoid.Update();
		/* �Ʒ� �Լ� ����
		this->EventHandler(); 
		this->UpdatePlayer();
		this->UpdateEnemy();
		this->CollisionCheck();
		this->UpdatePointText();
		*/

		// �� Render
		Avoid.Render();
	}
}

/*initWindow 600
* initspawn static cast
*/
