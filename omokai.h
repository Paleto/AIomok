#ifndef __OMOKAI_H__
#define __OMOKAI_H__

#include "omokrule.h"

class COMOKAI
{
private :
	int nWeight1[SIZE + 2][SIZE + 2];
	int nWeight2[SIZE + 2][SIZE + 2];
	
	//left up
	Point l;
	//right bottom
	Point r;
	void setRect();
	void initWeight();
	bool isFive(int &x, int &y, int nStone, int j, int i);
	bool findFive(int &x, int &y, int nStone);
	void fillWeight(int nStone);
	void findPutPosition(int &x, int &y, int nStone);
	
	COMOKRULE *rule;
	
public :
	COMOKAI();
	virtual ~COMOKAI() {}
	
	void play(int &x, int &y, int nStone, COMOKRULE *pr);
};

#endif
