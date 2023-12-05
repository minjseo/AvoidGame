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


	//프로그램 종료 되지 않도록 하려면
	while (Window.isOpen()) 
	{
		//이벤트 발생 감지
		while (Window.pollEvent(Event)) 
		{
			//이벤트 종류 판단
			switch (Event.type) 
			{

			case Event::Closed:
				//동작
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






	/*무한루프X
	while (true) {}
	*/

	/*
		이벤트(Event) : (발생된) 사건 
		=> 소프트웨어, 어플리케이션의 상태 변화 : ★사용자★ 
			ex.검색창에 타이핑되는 것 - 이벤트O (사용자O)
			ex.검색창에 타이칭된 글자에 대한 연관검색어 노출- 이벤트X (사용자X)

		- Interface 장치와 관련된 '이벤트' : 키보드, 마우스, 터치스크린
			- 키보드 이벤트 : 키입력 (press *release 동착없음), 각각의 키 내용을 if로 구분 
			- 마우스 이벤트 : 클릭 press/release (땔때 동작반응), 휠 스크롤, 더블 클릭, 움직임, 드래그(press + move)
			- 터치 스크린 : 터치, 스와이프(넘김), 핀치(줌인/아웃)
		- Interface 장치와 관련없는 '이벤트'
			- 로딩 이벤트 : 데이터나 소프트웨어의 화면 구소 요소가 모두 화면에 띄워지면 발생되는 이벤트 

		이벤트 발생시, 이벤트 감지 ==> 적절한 동작 반응 (무시 포함)
			Event Listener ≒ Event Handler (유사/동일한 것으로 처리)
			- 1-1. Evnet Listening : 이벤트 감지 
			- 1-2. Event Handling : 감지된 이벤트에 대해서 적절한 동작
	*/