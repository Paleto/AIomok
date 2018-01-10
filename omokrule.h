#ifndef __OMOKRULE_H__
#define __OMOKRULE_H__

#include "draw.h"

struct Point{
	int x, y;
};

class COMOKRULE
{
protected:
	static int nBoard[SIZE+2][SIZE+2];

public:
	COMOKRULE();
	virtual ~COMOKRULE() {;}
	
	void GetRect(Point &p1, Point &p2);
	void SetBoard(int (*arr)[SIZE + 2]);
	bool IsEmpty(int x, int y);
	bool IsFive(int x, int y, int nStone);
	bool IsSix(int x, int y, int nStone);
	
	bool IsTwo(int x, int y, int nStone);
	bool IsOpenTwo(int x, int y, int nStone);

	bool IsThree(int x, int y, int nStone);
	virtual bool IsOpenThree(int x, int y, int nStone){}
	
	bool IsFour(int x, int y, int nStone);
	bool IsOpenFour(int x, int y, int nStone);

	bool IsDoubleFour(int x, int y, int nStone);
	
	//open open
	bool IsDoubleThree(int x, int y, int nStone);
	//open close
	bool IsThree_Three(int x, int y, int nStone);
	//close close
	bool Is_Three_Three(int x, int y, int nStone);
	
	bool IsDoubleTwo(int x, int y, int nStone);
	bool IsTwo_Two(int x, int y, int nStone);
	bool Is_Two_Two(int x, int y, int nStone);

	//open three
	bool IsFourThree(int x, int y, int nStone);
	//close three
	bool IsFour_Three(int x, int y, int nStone);

	//open three
	bool IsFourTwo(int x, int y, int nStone);
	//close three
	bool IsFour_Two(int x, int y, int nStone);

	bool IsTwoThree(int x, int y, int nStone);
	bool Is_TwoThree(int x, int y, int nStone);
	bool IsTwo_Three(int x, int y, int nStone);
	bool Is_Two_Three(int x, int y, int nStone);
	

protected:
	void SetStone(int x, int y, int nStone);
	void GetDirTable(int &x, int &y, int i);
	bool IsTwo(int x, int y, int nStone, int nDir);
	bool IsOpenTwo(int x, int y, int nStone, int nDir);

	bool IsThree(int x, int y, int nStone, int nDir);
	virtual bool IsOpenThree(int x, int y, int nStone, int nDir	) {	}
	
	bool IsFour(int x, int y, int nStone, int nDir);
	int  IsOpenFour(int x, int y, int nStone, int nDir);
	bool IsFive(int x, int y, int nStone, int nDir);
	bool IsEmpty(int &x, int &y, int nStone, int i);
	bool IsForbidden(int x, int y, int nStone);
	int  GetStoneCount(int x, int y, int nStone, int nDir);
};

class CGOMOKURULE : public COMOKRULE
{
public:

	virtual bool IsOpenThree(int x, int y, int nStone, int nDir	);
	virtual bool IsOpenThree(int x, int y, int nStone);
};

class CNORMALRULE : public COMOKRULE
{
public:

	virtual bool IsOpenThree(int x, int y, int nStone, int nDir	);
	virtual bool IsOpenThree(int x, int y, int nStone);
};

class CRENJURULE : public COMOKRULE
{
public:

	virtual bool IsOpenThree(int x, int y, int nStone, int nDir	);
	virtual bool IsOpenThree(int x, int y, int nStone);
};

#endif
