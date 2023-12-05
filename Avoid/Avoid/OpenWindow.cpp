#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

using namespace sf;


void OpenWindow() 
{
	RenderWindow Window(VideoMode(1280, 720), "Avoid Game", Style::Titlebar | Style::Close);

	Event Event;


	//���α׷� ���� ���� �ʵ��� �Ϸ���
	while (Window.isOpen()) 
	{
		//�̺�Ʈ �߻� ����
		while (Window.pollEvent(Event)) 
		{
			//�̺�Ʈ ���� �Ǵ�
			switch (Event.type) 
			{

			case Event::Closed:
				//����
				Window.close();
				break;

			case Event::KeyPressed:
				if (Event.key.code == Keyboard::Escape) Window.close();
				break;
			}
		}

		//Clear
		Window.clear(Color(255, 0, 0, 255)); //rgb

		//Display
		Window.display();

	}
}






	/*���ѷ���X
	while (true) {}
	*/

	/*
		�̺�Ʈ(Event) : (�߻���) ��� 
		=> ����Ʈ����, ���ø����̼��� ���� ��ȭ : �ڻ���ڡ� 
			ex.�˻�â�� Ÿ���εǴ� �� - �̺�ƮO (�����O)
			ex.�˻�â�� Ÿ��Ī�� ���ڿ� ���� �����˻��� ����- �̺�ƮX (�����X)

		- Interface ��ġ�� ���õ� '�̺�Ʈ' : Ű����, ���콺, ��ġ��ũ��
			- Ű���� �̺�Ʈ : Ű�Է� (press *release ��������), ������ Ű ������ if�� ���� 
			- ���콺 �̺�Ʈ : Ŭ�� press/release (���� ���۹���), �� ��ũ��, ���� Ŭ��, ������, �巡��(press + move)
			- ��ġ ��ũ�� : ��ġ, ��������(�ѱ�), ��ġ(����/�ƿ�)
		- Interface ��ġ�� ���þ��� '�̺�Ʈ'
			- �ε� �̺�Ʈ : �����ͳ� ����Ʈ������ ȭ�� ���� ��Ұ� ��� ȭ�鿡 ������� �߻��Ǵ� �̺�Ʈ 

		�̺�Ʈ �߻���, �̺�Ʈ ���� ==> ������ ���� ���� (���� ����)
			Event Listener �� Event Handler (����/������ ������ ó��)
			- 1-1. Evnet Listening : �̺�Ʈ ���� 
			- 1-2. Event Handling : ������ �̺�Ʈ�� ���ؼ� ������ ����
	*/