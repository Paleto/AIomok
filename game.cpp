#include "game.h"

CGAME::CGAME()
{
	pOmok[0] = &black;
	pOmok[1] = &white;
}

// 게임이 시작할때 필요한 변수들을 초기화 하고,
// 화면에 표시해준다. 
void CGAME::initGame()
{
	x = y = CENTER;
	t1 = t2 = clock();
	passTriggerOn = false;
	isComputer = false;
	passCount = 0;
	stoneState[0] = 0;
	stoneState[1] = 0;
	drawTime();
	curStone = WHITE_STONE;
	pDraw()->printData(x, y, BLACK_STONE);
	pDraw()->stonePoint(x, y);
	pDraw()->showMsg(curStone);
	pOmok[curStone]->initOmok();
	pOmok[curStone]->cursorView(x, y); 
}

// main함수에서 이 함수를 호출하면 게임이 시작된다. 
bool CGAME::playGame()
{
	int result;
	
	system("cls");
	initGame();
	pDraw()->computerStoneColor();
	while(true)
	{
		// 1초마다 화면에 시간을 표시한다. 
		if(clock() - t1 >= 1000) drawTime();
		
		result = checkKey();
		switch(result)
		{
			// 키보드로부터 ESC키가 눌리면 게임을 종료한다. 
			case FINISH   : return false;
			// 오목이 되었으면 승자를 알리고, 계속할건지 물어본다. 
			case FIVEMOK  : return pDraw()->endMsg(curStone);
			// 착수가 불가능한 곳은 그 이유를 알린다. 
			case OCCUPIED :
			case SAMSAM   :
			case SASA     :
			case SIXMOK   : 
			case NOTUNDO  : 
				pDraw()->errMsg(result); 
				pOmok[curStone]->setBoard(x, y); 
				break;
			//착수가 됐거나, 한수 물렸을 때 돌을 바꾼다.  
			case PASS     : if(!passTriggerOn) passTriggerOn = true;
							stoneState[curStone]++;
			case CHANGE   : changeStone(); break;
			default       : break;
		}
		pOmok[curStone]->cursorView(x, y);
		if(checkTie()) return pDraw()->endMsg(TIED);
		Sleep(20);
	}
}

// 흑과 백의 둘 차례를 바꾼다. 
void CGAME::changeStone()
{
	// 흑백 둘이니 더해서 2로 나누면 교환이 된다. 
	curStone = (curStone + 1) % 2;
	isComputer = !isComputer;
	// 현재 둘 차례를 알려준다. 
	pDraw()->showMsg(curStone);
	if(passTriggerOn) passCount++;
}

bool CGAME::checkTie()
{
	if(!passTriggerOn) return false;

	bool isTied = false;
	if(passCount == 2)
	{
		if(stoneState[0] == 1 && stoneState[1] == 1) isTied = true;
		passTriggerOn = false;
		passCount     = 0;
		stoneState[0] = 0;  
		stoneState[1] = 0;  
	}
	return isTied;
}

// 1 초마다 화면에 시간을 표시한다. 
void CGAME::drawTime()
{
	time_t sec = (clock() - t2) / 1000;
	pDraw()->drawTime(sec);
	t1 = clock();   
}


int CGAME::getKey()
{
	int ch = getch();
	if(ch == 0 || ch == 0xE0) ch = getch();

	return ch;
}

int CGAME::checkKey()
{
    int ch, dx, dy;;

    if(isComputer) return pOmok[curStone]->placement(x, y, curStone);
	else if(kbhit()) ch = getKey();
    else return 0;
    
    dx = dy = 0;
    switch(ch)
    {
    	case UP    : --dy; break;
		case DOWN  : ++dy; break;
    	case LEFT  : --dx; break;
		case RIGHT : ++dx; break;

        case DEL   : return PASS;
        case ESC   : return FINISH;
        case ' '   : return pOmok[curStone]->placement(x, y, curStone);
        case 'u'   : 
        case 'U'   : return pOmok[curStone]->undo(); 
        default    : break;
	}
    pOmok[curStone]->setBoard(x, y);
    y += dy;
    x += dx;
    pDraw()->printData(x, y, CURSOR);

    return 0;
}
