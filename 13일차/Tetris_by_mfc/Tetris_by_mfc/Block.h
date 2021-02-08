#pragma once
#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "pch.h"
#include "Tetris_by_mfcDlg.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "CBColor.h"
using namespace std;

vector<vector<int>> v[7] = {
	{
		{0, 0, 0, 0},
		{ 1, 1, 1, 1 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{0, 0, 0, 0},
		{0, 2, 2, 0},
		{2, 2, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0},
		{3, 3, 0, 0},
		{3, 3, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{4, 0, 0},
		{4, 4, 4},
		{0, 0, 0}
	},
	{
		{0, 0, 5},
		{5, 5, 5},
		{0, 0, 0}
	},
	{
		{0, 6, 0},
		{6, 6, 6},
		{0, 0, 0}
	},
	{
		{0, 0, 0, 0},
		{7, 7, 0, 0},
		{0, 7, 7, 0},
		{0, 0, 0, 0}
	}
};

CMutex g_mutex(FALSE, NULL);

class Block {
private:
	vector<vector<int>> block;
	int color, len, xpos, ypos;
	CTetrisbymfcDlg *p;
	CClientDC *dc;
	CBrush *br;
	CPen *pen;
public:
	Block(CTetrisbymfcDlg *p) {
		this->p = p;
		dc = new CClientDC(p);
	}

	void setColor(int color) {
		this->color = color;
	}

	void setLen(int len) {
		this->len = len;
	}
	void setXpos(int xpos) {
		this->xpos = xpos;
	}

	void setYpos(int ypos) {
		this->ypos = ypos;
	}
	void setBlock(vector<vector<int>> block) {
		this->block = block;
	}

	int getColor() {
		return color;
	}

	int getLen() {
		return len;
	}

	int getXpos() {
		return xpos;
	}

	int getYpos() {
		return ypos;
	}

	vector<vector<int>>& getBlock() {
		return block;
	}

	void getRandBlockColor() {
		srand(time(NULL));
		int randData = rand() % 7;
		this->xpos = 84;
		this->ypos = 0;
		this->block = v[randData];
		this->len = v[randData].size();
		this->color = randData;
	}

	void storeBlock(int height,int width,vector<vector<int>> &board) {
		int x = xpos / 21;
		int y = ypos / 21;
		for (int i = y; i < y + len; i++) {
			for (int k = x; k < x + len; k++) {
				if (i < height && k < width && block[i - y][k - x]) {
					board[i][k] = block[i - y][k - x];
				}
			}
		}
	}

	void Lotation(vector<vector<int>>& board, int height, int width) {
		vector<vector<int>> temp;
		temp.resize(len);
		for (int i = 0; i < len; i++) temp[i].resize(len, 0);

		for (int i = 0; i < len; i++)
			for (int k = 0; k < len; k++)
				temp[k][len - 1 - i] = block[i][k];

		if (checkMnMxXposYpos(xpos, ypos, temp,board,height,width)) return;

		eraseBlock();
		block = temp;
		printBlock();
	}


	bool Down(vector<vector<int>>& board,int height,int width) {
		g_mutex.Lock();
		if (checkMnMxXposYpos(xpos, ypos + 21, block, board, height, width)) {
			storeBlock(height, width, board);
			getRandBlockColor();
			g_mutex.Unlock();
			return true;
		}
		eraseBlock();
		ypos += 21;
		printBlock();
		g_mutex.Unlock();
		return false;
	}

	void left(vector<vector<int>>& board, int height, int width) {
		if (checkMnMxXposYpos(xpos - 21, ypos, block, board, height, width)) return;
		eraseBlock();
		xpos -= 21;
		printBlock();
	}

	void right(vector<vector<int>>& board, int height, int width) {
		if (checkMnMxXposYpos(xpos + 21, ypos, block, board, height, width)) return;
		eraseBlock();
		xpos += 21;
		printBlock();
	}

	bool checkMnMxXposYpos(int xpos, int ypos, vector<vector<int>> &block, vector<vector<int>> &board, int height,int width) {

		int mnx = 1e9, mxx = 0, mny = 1e9, mxy = 0;

		xpos /= 21;
		ypos /= 21;

		for (int i = ypos; i < ypos + len; i++) {
			for (int k = xpos; k < xpos + len; k++) {
				if (i >= 0 && k >= 0 && i < height && k < width && board[i][k] && block[i - ypos][k - xpos]) return 1;
				if (block[i - ypos][k - xpos]) {
					mnx = min(mnx, k);
					mxx = max(mxx, k);
					mny = min(mny, i);
					mxy = max(mxy, i);
				}
			}
		}
		if (mnx < 0 || mny < 0 || mxx >= width || mxy >= height) return 1;
		return 0;
	}


	void printBlock() {
		Tcolor col = cbcolor->getColor(color);

		br = new CBrush(RGB(col.x,col.y,col.z));
		pen = new CPen(PS_SOLID, 1, RGB(col.x, col.y, col.z));
		dc->SelectObject(br);
		dc->SelectObject(pen);

		for (int i = 0; i < len; i++) {
			for (int k = 0; k < len; k++) {

				if(block[i][k])
					dc->Rectangle(xpos + k * 21 , ypos + i * 21, xpos + 20 + k * 21, ypos + 20 + i * 21);
			}
		}
	}

	void eraseBlock() {
		br = new CBrush(RGB(240, 240, 240));
		pen = new CPen(PS_SOLID, 1, RGB(240, 240, 240));
		dc->SelectObject(br);
		dc->SelectObject(pen);
		for (int i = 0; i < len; i++) {
			for (int k = 0; k < len; k++) {

				if (block[i][k])
					dc->Rectangle(xpos + k * 21, ypos + i * 21, xpos + 20 + k * 21, ypos + 20 + i * 21);
			}
		}
	}
};

#endif