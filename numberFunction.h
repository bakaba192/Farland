#pragma once
#include "stdafx.h"


//=================================================================================================
//	##	숫자 매크로함수 [ numberFunction ]	##
//=================================================================================================

enum NUM_POSITION
{
	//포지션()
	PST_LEFT = 0,
	PST_RIGHT,
	PST_CENTER

};

#define PST_LEFT		PST_LEFT
#define PST_RIGHT		PST_RIGHT
#define PST_CENTER		PST_CENTER

inline void numberRender(HDC hdc, string imageName, int startX, int startY, int distance, int number, NUM_POSITION numPositon = PST_LEFT)
{
	if (numPositon == PST_LEFT)
	{
		int positonNum;
		if (number >= 10000)
		{
			positonNum = 4;
		}
		else if (number >= 1000)
		{
			positonNum = 3;
		}
		else if (number >= 100)
		{
			positonNum = 2;
		}
		else if (number >= 10)
		{
			positonNum = 1;
		}
		else
		{
			positonNum = 0;
		}
		if (number >= 10000) IMAGEMANAGER->findImage(imageName)->frameRender(hdc, startX, startY, number / 10000, 0);
		if (number >= 1000) IMAGEMANAGER->findImage(imageName)->frameRender(hdc, startX + distance* (positonNum - 3), startY, number % 10000 / 1000, 0);
		if (number >= 100) IMAGEMANAGER->findImage(imageName)->frameRender(hdc, startX + distance* (positonNum - 2), startY, number % 1000 / 100, 0);
		if (number >= 10) IMAGEMANAGER->findImage(imageName)->frameRender(hdc, startX + distance * (positonNum - 1), startY, number % 100 / 10, 0);
		IMAGEMANAGER->findImage(imageName)->frameRender(hdc, startX + distance* positonNum, startY, number % 10, 0);
	}
	else if (numPositon == PST_RIGHT)
	{
		if (number >= 10000) IMAGEMANAGER->findImage(imageName)->frameRender(hdc, startX - distance * 4, startY, number / 10000, 0);
		if (number >= 1000) IMAGEMANAGER->findImage(imageName)->frameRender(hdc, startX - distance * 3, startY, number % 10000 / 1000, 0);
		if (number >= 100) IMAGEMANAGER->findImage(imageName)->frameRender(hdc, startX - distance * 2, startY, number % 1000 / 100, 0);
		if (number >= 10) IMAGEMANAGER->findImage(imageName)->frameRender(hdc, startX - distance, startY, number % 100 / 10, 0);
		IMAGEMANAGER->findImage(imageName)->frameRender(hdc, startX, startY, number % 10, 0);
	}
	else if (numPositon == PST_CENTER)
	{
		int positonNum;
		if (number >= 10000)
		{
			positonNum = 4;
		}
		else if (number >= 1000)
		{
			positonNum = 3;
		}
		else if (number >= 100)
		{
			positonNum = 2;
		}
		else if (number >= 10)
		{
			positonNum = 1;
		}
		else
		{
			positonNum = 0;
		}

		int numW = IMAGEMANAGER->findImage(imageName)->getFrameWidth() / 2;
		int positonX = startX - ((distance)*positonNum) / 2;

		if (number >= 1000) IMAGEMANAGER->findImage(imageName)->frameRender(hdc, positonX - numW + distance* (positonNum - 4), startY, number / 10000, 0);
		if (number >= 1000) IMAGEMANAGER->findImage(imageName)->frameRender(hdc, positonX - numW + distance* (positonNum - 3), startY, number % 10000 / 1000, 0);
		if (number >= 100) IMAGEMANAGER->findImage(imageName)->frameRender(hdc, positonX - numW + distance* (positonNum - 2), startY, number % 1000 / 100, 0);
		if (number >= 10) IMAGEMANAGER->findImage(imageName)->frameRender(hdc, positonX - numW + distance * (positonNum - 1), startY, number % 100 / 10, 0);
		IMAGEMANAGER->findImage(imageName)->frameRender(hdc, positonX - numW + distance* positonNum, startY, number % 10, 0);

	}
}


