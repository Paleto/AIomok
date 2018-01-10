// 오목 AI 프로그램에 도전 1016년 12월 22일 13시 10분 
// 처음 목표는 컴퓨터가 스스로 돌을 놓을 수 있는 정도로 구현해본다.


#include "game.h"

int main()
{
	pDraw()->CursorView(HIDE);
	
	CGAME game;
	while(game.playGame());

	pDraw()->CursorView(SHOW);
	return 0;
}
