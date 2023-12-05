#include "Game.h"

// ��-------------------------------------------------------------------------- Startup
Game::Game()
{
	this->InitWindowPointer(); //������ ����, �ʱ�ȭ
	this->InitWindow();

	this->InitPlayer(); //�÷��̾� ���� �ʱ�ȭ 

	this->InitEnemy(); //�� ���� �ʱ�ȭ
	this->InitSpawn(); //�� ���� ȣ��ȭ

	this->Point = 0; //���� �ʱ�ȭ
	this->InitFont(); //��Ʈ �ʱ�ȭ 
	this->InitPointText(); //�ؽ�Ʈ �ʱ�ȭ 
	this->InitGameOverText(); //'��������' �ʱ�ȭ

	this->GameOverState = false; //���� ������� =���� 

}
void Game::InitWindowPointer()
{
	//������ ���� �ʱ�ȭ 
	this->Window = nullptr;
}
void Game::InitWindow()
{
	//������ ���� ���� 
	this->Window = new RenderWindow(VideoMode(1280, 720), "Avoid Game", Style::Titlebar | Style::Close);

	//������ �ݺ� ���� 
	this->Window->setFramerateLimit(60); //60fps : 1�ʿ� 60 frame
}
// ��-------------------------------------------------------------------------- Update
const bool Game::Running() const
{
	return this->Window->isOpen(); 
}
void Game::EventHandler()
{
	//�̺�Ʈ �߻� ����
	while (this->Window->pollEvent(Event)) 
		//pollEvent : ���콺Ŭ��+Ű����Ÿ���� ��� ����
	{
		//�̺�Ʈ ���� �Ǵ�
		switch (Event.type)
		{
		case Event::Closed:
			//����
			this->Window->close();
			break;

		case Event::KeyPressed: //KeyPressed : Ű���Ÿ���� �� ����
			if (Event.key.code == Keyboard::Escape) this->Window->close();
			break;
		}
	}
}
void Game::Update()
{
	this->EventHandler();

	// ! = NOT --> !�� ����� true
	if (!this->GameOverState) 
	{
		this->UpdatePlayer();
		this->UpdateEnemy();
		this->CollisionCheck();
		this->UpdatePointText();
	}
}
// ��-------------------------------------------------------------------------- Render
void Game::Render()
{
	//Clear
	this->Window->clear(Color(255, 94, 0, 255)); //rgb,Alpha

	//Draw Player
	this->Window->draw(this->Player);

	//Draw Enemy
	for (int i = 0; i < this->EnemyArrary.size(); i++) {
		this->Window->draw(this->EnemyArrary[i]);
	}

	//Draw Text
	this->Window->draw(this->PointText);
	this->Window->draw(this->GameOverText);
	
	//Display _�ڸ� �������̿����� 
	this->Window->display();
}
// ��-------------------------------------------------------------------------- Shut Down
Game::~Game()
{
	this->DeleteWindow();
}
void Game::DeleteWindow()
{
	//������ �޸𸮿��� ����
	delete this->Window;
}
// ��-------------------------------------------------------------------------- Elements_P
void Game::InitPlayer()
{
	this->Player.setRadius(30.0f);
	this->Player.setFillColor(Color(208, 255, 0,255));
	this->Player.setPosition(
		float (this->Window->getSize().x/2) - 35.0f,
		float (this->Window->getSize().y/2) - 35.0f); 
		/* {x:ȭ�� ���λ����� y.���� ������} / 2   -   ��������ŭ ��, ��� �̵�
		// sfml ����, ������ ���Ͱ� �ܰ����� ��������̹Ƿ�, ���� ��ġ�� ���� �˰��� �ۼ�
		// getSize�� Ÿ���� int �̹Ƿ�, float���� ���� ���� ����ȯ�� 
		*/ 
}
void Game::UpdatePlayer() //'���ӷ��� ��'�� ���ȴ����� Ȯ���ϴ� �� (�̺�Ʈ ����X)  
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		this->Player.move(-5.0f, 0.0f); 
		//sfml���� �����ϴ� move�Լ�_float���� �Է�
		//(x,y) x��ǥ�� +���� ������, -���� �����̵� 
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		this->Player.move(5.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		this->Player.move(0.0f, -5.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		this->Player.move(0.0f, 5.0f);
	}
	//else if�� 4�� �ϳ�(�����̵� only --> if�� 4�� ������ ����(�밢���̵�)
	//if �� �밢 �̵���, �ӵ� �ߺ� ���Ǿ� ���� �̵����� ���� (��������->�ڵ�)
}
// ��-------------------------------------------------------------------------- Elements_E
void Game::InitEnemy()
{
	this->Enemy.setSize(Vector2f(15.0f, 195.0f)); //Vector2f �� sfml Ư���ؼ� ���
	this->Enemy.setFillColor(Color(0, 76, 255, 255));
	this->Enemy.setPosition(100, 100); 
	//�� ���� �ǹ�X -> SpawnEnemy -> setPosition���� x�� �������� set
}
void Game::InitSpawn()
{
	this->EnemyMax = 75;
	this->IntervalMax = 10.0f;
	this->IntervalStart = 0.0f;
	//spawn
}
void Game::SpawnEnemy()
{
	this->Enemy.setPosition( static_cast<float>(rand()%1280), 0.0f);
	//â ���α��� 1280 ����, x�� ��ġ ����
	this->EnemyArrary.push_back(this->Enemy);
	//initEnmy 1���� Ǫ�ù����� EnemyArray, �ټ��� enemy
}
void Game::UpdateEnemy()
{
	// Enemy Maximun
	if (this->EnemyArrary.size() < this->EnemyMax) 
	{
		//Enemy Spawn Interval Delay
		if (this->IntervalMax <= this->IntervalStart) 
		{
			this->SpawnEnemy();
			this->IntervalStart = 0.0f;
		}
		else 
		{ 
			this->IntervalStart += 1.0f; 
		}
	}

	for (int i = 0; i < this->EnemyArrary.size(); i++) 
	{
		this->EnemyArrary[i].move(0.0f, 4.0f);

		for (int i = 0; i < this->EnemyArrary.size(); i++) 
		{
			//������ �ٱ����� ����� Enemy ����
			if (this->EnemyArrary[i].getPosition().y >= Window->getSize().y) 
			{
				this->EnemyArrary.erase(this->EnemyArrary.begin() + i);

				//�����Ǵ� Enemy ���� => ����
				Point++;
			}
		}
	}

	/*this->Enemy.move(0.0f, 1.0f);
	--> 1���� �� ������
	--> EnermyArray ���������� �ٲ������
	*/
}
// ��-------------------------------------------------------------------------- Collision_C
void Game::CollisionCheck() 
{
	for (int i = 0; i < EnemyArrary.size(); i++) 
	{
		//Player�� Collision ����(bound) 
		//EnemyArray[i]�� Collision ����(bound)�� '����'�ߴ��� Ȯ��
		if (this->Player.getGlobalBounds().intersects(
			this->EnemyArrary[i].getGlobalBounds()))
		{
			/*	�浹O true->��������
				�浹X false -> ��������
			//�Ҹ��ڿ� �ִ� �Լ�
			*/
			this->GameOverState = true; 
			// ������ ����� ���°� �ƴϸ� (false�� �ƴϸ�) -> 'void Update'����
			// ������ ����� ���°� �̸�  (true�̸�) -> 'void Update' ������
			this->PrintGameOverText();
		}
	}
}
// ��-------------------------------------------------------------------------- Font/Text
void Game::InitFont() 
{
	// \Documents\AvoidGame\Avoid\Avoid -> Font ������ ����/��Ʈ �ٿ��ֱ�

	if (this->Font.loadFromFile("Font/NanumSquareB.ttf")) 
	{
		cout <<"Load Complere" << endl;
	}
	else 
	{
		cout << "Load Fail";
	}
}
void Game::InitPointText()
{
	//�ؽ�Ʈ�� �׷������� �ν� -> ����(initPlayer/Enemy) �ʱ�ȭ ��İ� ���� 
	//this->font ���� �����ؿ� ���� �������
	this->PointText.setFont(this->Font);
	this->PointText.setCharacterSize(55);
	this->PointText.setFillColor(Color::Black);
	this->PointText.setPosition(
		this->Window->getSize().x / 2 - 130,
		this->Window->getSize().y - 630
	);
}
void Game::UpdatePointText()
{
	//�ҹ��� -> �ӽú����� ��������
	stringstream pt;
	pt << "SCORE : " << Point;
	this->PointText.setString(pt.str());
}
void Game::InitGameOverText()
{
	//�ؽ�Ʈ�� �׷������� �ν� -> ����(initPlayer/Enemy) �ʱ�ȭ ��İ� ���� 
	//this->font ���� �����ؿ� ���� �������
	this->GameOverText.setFont(this->Font);
	this->GameOverText.setCharacterSize(185);
	this->GameOverText.setFillColor(Color::White);
	this->GameOverText.setPosition(
		this->Window->getSize().x / 2 -515,
		this->Window->getSize().y - 485
	);
}
void Game::PrintGameOverText()
{
	//�ҹ��� -> �ӽú����� ��������
	stringstream pt;
	pt << "GAME OVER";
	this->GameOverText.setString(pt.str());
}