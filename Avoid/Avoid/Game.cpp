#include "Game.h"

// ▼-------------------------------------------------------------------------- Startup
Game::Game()
{
	this->InitWindowPointer(); //윈도우 생성, 초기화
	this->InitWindow();

	this->InitPlayer(); //플레이어 정보 초기화 

	this->InitEnemy(); //적 정보 초기화
	this->InitSpawn(); //적 출현 호기화

	this->Point = 0; //점수 초기화
	this->InitFont(); //폰트 초기화 
	this->InitPointText(); //텍스트 초기화 
	this->InitGameOverText(); //'게임종료' 초기화

	this->GameOverState = false; //게임 종료상태 =거짓 

}
void Game::InitWindowPointer()
{
	//포인터 변수 초기화 
	this->Window = nullptr;
}
void Game::InitWindow()
{
	//윈도우 동적 생성 
	this->Window = new RenderWindow(VideoMode(1280, 720), "Avoid Game", Style::Titlebar | Style::Close);

	//일정히 반복 실행 
	this->Window->setFramerateLimit(60); //60fps : 1초에 60 frame
}
// ▼-------------------------------------------------------------------------- Update
const bool Game::Running() const
{
	return this->Window->isOpen(); 
}
void Game::EventHandler()
{
	//이벤트 발생 감지
	while (this->Window->pollEvent(Event)) 
		//pollEvent : 마우스클릭+키보드타이핑 모두 감지
	{
		//이벤트 종류 판단
		switch (Event.type)
		{
		case Event::Closed:
			//동작
			this->Window->close();
			break;

		case Event::KeyPressed: //KeyPressed : 키모드타이핑 만 감지
			if (Event.key.code == Keyboard::Escape) this->Window->close();
			break;
		}
	}
}
void Game::Update()
{
	this->EventHandler();

	// ! = NOT --> !로 결과는 true
	if (!this->GameOverState) 
	{
		this->UpdatePlayer();
		this->UpdateEnemy();
		this->CollisionCheck();
		this->UpdatePointText();
	}
}
// ▼-------------------------------------------------------------------------- Render
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
	
	//Display _★맨 마지막이여야함 
	this->Window->display();
}
// ▼-------------------------------------------------------------------------- Shut Down
Game::~Game()
{
	this->DeleteWindow();
}
void Game::DeleteWindow()
{
	//윈도우 메모리에서 제거
	delete this->Window;
}
// ▼-------------------------------------------------------------------------- Elements_P
void Game::InitPlayer()
{
	this->Player.setRadius(30.0f);
	this->Player.setFillColor(Color(208, 255, 0,255));
	this->Player.setPosition(
		float (this->Window->getSize().x/2) - 35.0f,
		float (this->Window->getSize().y/2) - 35.0f); 
		/* {x:화면 가로사이즈 y.세로 사이즈} / 2   -   반지름만큼 좌, 상단 이동
		// sfml 기준, 도형의 센터가 외곽선의 좌측상단이므로, 센터 위치를 위한 알고리즘 작성
		// getSize의 타입이 int 이므로, float으로 통일 위해 형변환요 
		*/ 
}
void Game::UpdatePlayer() //'게임루프 중'에 눌렸는지만 확인하는 것 (이벤트 감지X)  
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		this->Player.move(-5.0f, 0.0f); 
		//sfml에서 제공하는 move함수_float으로 입력
		//(x,y) x좌표의 +값은 오른쪽, -값은 왼쪽이동 
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
	//else if는 4중 하나(직선이동 only --> if는 4개 교집합 가능(대각선이동)
	//if 로 대각 이동시, 속도 중복 계산되어 직선 이동보다 빠름 (교정가능->코딩)
}
// ▼-------------------------------------------------------------------------- Elements_E
void Game::InitEnemy()
{
	this->Enemy.setSize(Vector2f(15.0f, 195.0f)); //Vector2f 은 sfml 특정해서 사용
	this->Enemy.setFillColor(Color(0, 76, 255, 255));
	this->Enemy.setPosition(100, 100); 
	//값 설정 의미X -> SpawnEnemy -> setPosition에서 x축 랜덤으로 set
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
	//창 가로길이 1280 기준, x축 위치 랜덤
	this->EnemyArrary.push_back(this->Enemy);
	//initEnmy 1개를 푸시백으로 EnemyArray, 다수의 enemy
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
			//윈도우 바깥으로 벗어나는 Enemy 삭제
			if (this->EnemyArrary[i].getPosition().y >= Window->getSize().y) 
			{
				this->EnemyArrary.erase(this->EnemyArrary.begin() + i);

				//삭제되는 Enemy 개수 => 점수
				Point++;
			}
		}
	}

	/*this->Enemy.move(0.0f, 1.0f);
	--> 1개의 적 움직임
	--> EnermyArray 움직임으로 바꿔줘야함
	*/
}
// ▼-------------------------------------------------------------------------- Collision_C
void Game::CollisionCheck() 
{
	for (int i = 0; i < EnemyArrary.size(); i++) 
	{
		//Player의 Collision 영역(bound) 
		//EnemyArray[i]의 Collision 영역(bound)이 '교차'했는지 확인
		if (this->Player.getGlobalBounds().intersects(
			this->EnemyArrary[i].getGlobalBounds()))
		{
			/*	충돌O true->게임종료
				충돌X false -> 게임진행
			//소멸자에 있는 함수
			*/
			this->GameOverState = true; 
			// 게임이 종료된 상태가 아니면 (false가 아니면) -> 'void Update'진행
			// 게임이 종료된 상태가 이면  (true이면) -> 'void Update' 미진행
			this->PrintGameOverText();
		}
	}
}
// ▼-------------------------------------------------------------------------- Font/Text
void Game::InitFont() 
{
	// \Documents\AvoidGame\Avoid\Avoid -> Font 새폴더 생성/폰트 붙여넣기

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
	//텍스트을 그래픽으로 인식 -> 도형(initPlayer/Enemy) 초기화 방식과 유사 
	//this->font 에는 리딩해온 내용 담고있음
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
	//소문자 -> 임시변수의 느낌으로
	stringstream pt;
	pt << "SCORE : " << Point;
	this->PointText.setString(pt.str());
}
void Game::InitGameOverText()
{
	//텍스트을 그래픽으로 인식 -> 도형(initPlayer/Enemy) 초기화 방식과 유사 
	//this->font 에는 리딩해온 내용 담고있음
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
	//소문자 -> 임시변수의 느낌으로
	stringstream pt;
	pt << "GAME OVER";
	this->GameOverText.setString(pt.str());
}