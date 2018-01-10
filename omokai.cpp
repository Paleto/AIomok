#include "omokai.h"

COMOKAI::COMOKAI()
{
}

void COMOKAI::setRect()
{
	rule->GetRect(l, r);
	
	l.x -= 2; if(l.x < 1   ) l.x = 1;
	l.y -= 2; if(l.y < 1   ) l.y = 1;
	r.x += 2; if(r.x > SIZE) r.x = SIZE;
	r.y += 2; if(r.y > SIZE) r.y = SIZE;
}

void COMOKAI::initWeight()
{
	for(int i = 1; i <= SIZE; i++)
	{
		for(int j = 0; j <= SIZE; j++)
		{
			nWeight1[i][j] = -1;
			nWeight2[i][j] = -1;
		}
	}
}

bool COMOKAI::isFive(int &x, int &y, int nStone, int j, int i)
{
	if(rule->IsFive(j, i, nStone) || rule->IsSix(j, i, nStone))
	{
		x = j;
		y = i;
		return true;
	}
	else return false;
}

bool COMOKAI::findFive(int &x, int &y, int nStone)
{
	bool isFind = false;
	int  stone = (nStone + 1) % 2;
	
	for(int i = l.y; i <= r.y; i++)
	{
		for(int j = l.x; j <= r.x; j++)
		{
			if(!rule->IsEmpty(j, i)) continue;
			if(isFive(x, y, nStone, j, i)) return true;
			else isFind = isFive(x, y, stone, j, i);
		}
	}
	return isFind;
}

int temp = 0;

void COMOKAI::fillWeight(int nStone)
{
	int stone = (nStone + 1) % 2;
	int arrWeight[2][23] = {{200, 199, 190, 76, 71, 65, 60, 189, 190, 23, 30, 75, 73, 31, 29, 74, 70, 80, 20, 19, 25, 24, 50},
						    {198, 197,  90, 75, 70, 64, 59,  89,  90, 22, 29, 74, 72, 30, 28, 73, 59, 79, 19, 18, 24, 23, 40}};

	bool (COMOKRULE::*fp[23])(int, int, int) = {
		rule->IsFive,  //200
		rule->IsSix,   //199
		rule->IsFourThree, //190
		rule->IsFour_Three,//76
		rule->IsFourTwo,//71
		rule->IsFour_Two,//65
		rule->IsFour, //60
		rule->IsDoubleFour,//189
		rule->IsOpenFour,  //190
		rule->IsThree, //23
		rule->Is_Three_Three,//30
		rule->IsTwoThree, // 75
		rule->Is_TwoThree,// 73
		rule->IsTwo_Three, //31
		rule->Is_Two_Three, //29
		rule->IsThree_Three,//74
		rule->IsOpenThree, //70
		rule->IsDoubleThree, //80
		rule->Is_Two_Two, //20
		rule->IsTwo, //19
		rule->IsTwo_Two,//25
		rule->IsOpenTwo,//24
		rule->IsDoubleTwo, //50
	};
	
	for(int n = 0; n < 23; n++)
	{
		for(int i = l.y; i <= r.y; i++)
		{
			for(int j = l.x; j <= r.x; j++)
			{
				if(!rule->IsEmpty(j, i)) continue;
				if((rule->*fp[n])(j, i, nStone)) 
				{
					if(nWeight1[i][j] < arrWeight[0][n]) nWeight1[i][j] = arrWeight[0][n]; 
				}

				if((rule->*fp[n])(j, i, stone)) 
				{
					if(nWeight2[i][j] < arrWeight[1][n]) nWeight2[i][j] = arrWeight[1][n]; 
				}
			}
		}
	}
}

void COMOKAI::findPutPosition(int &x, int &y, int nStone)
{
	int temp = 0;
	int max1 = -100;
	int max2 = -100;
	int sum  = 0;
	int tx, ty;
	int x1, y1;
	
	fillWeight(nStone);
	for(int i = l.y; i <= r.y; i++)
	{
		for(int j = l.x; j <= r.x; j++)
		{
			if(nWeight1[i][j] > max1)
			{
				max1 = nWeight1[i][j];
				x = j;
				y = i;
			}
			if(nWeight2[i][j] > max2)
			{
				max2 = nWeight2[i][j];
				x1 = j;
				y1 = i;
			}
			if(sum < nWeight2[i][j] + nWeight1[i][j])
			{
				sum = nWeight2[i][j] + nWeight1[i][j];
				tx = j;
				ty = i;
			}
			pDraw()->gotoxy(0, temp++);
			printf("%d, %d, %d", max1, max2, sum);
		}
	}
	
	if(max1 > 100) return;
	else if(max2 >= 89)
	{
		x = x1;
		y = y1;
		return;
	}
	else if(max1 == 80) return;
	else if(max2 == 79) 
	{
		x = x1;
		y = y1;
		return;
	}
	else
	{
		x = tx;
		y = ty;
	}
}

void COMOKAI::play(int &x, int &y, int nStone, COMOKRULE *pr)
{
	rule = pr;
	initWeight();
	setRect();
	if(findFive(x, y, nStone)) return;
	findPutPosition(x, y, nStone);
}
