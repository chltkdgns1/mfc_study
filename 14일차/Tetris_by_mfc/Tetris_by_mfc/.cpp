#pragma once
#include "pch.h"
#include "Block.h"
#include "Board.h"

void Block::printBlock(CTetrisbymfcDlg *h) {
	//int cnt = 0;
	//for (int i = 0; i < len; i++) {
	//	for (int k = 0; k < len; k++) {
	//		if (block[i][k]) {

	//			CClientDC dc(h);
	//			dc.Rectangle(5 + k, 5 + i, 10 + k, 10 + i);
	//		}
	//	}
	//}
}

void Block::Lotation() {
	//vector<vector<int>> temp;
	//temp.resize(len);
	//for (int i = 0; i < len; i++) temp[i].resize(len, 0);

	//for (int i = 0; i < len; i++)
	//	for (int k = 0; k < len; k++)
	//		temp[k][len - 1 - i] = block[i][k];

	//if (checkMnMxXposYpos(xpos, ypos, temp)) return;

	//eraseBlock();
	//block = temp;
	//printBlock();
}

void Block::storeBlock(Board &board) {
	int rx = xpos / 2;
	int height = board.getHeight();
	int width = board.getWidth();
	vector<vector<int>> map = board.getMap();

	for (int i = ypos; i < ypos + len; i++) {
		for (int k = rx; k < rx + len; k++) {
			if (i < height && k < width && map[i - ypos][k - rx]) {
				map[i][k] = block[i - ypos][k - rx];
			}
		}
	}
}

bool Block::Down(Board &board) {
	if (checkMnMxXposYpos(xpos, ypos + 1, block, board)) {
		storeBlock(board);
		board.deleteLine();
		randBlockColor();
		return 0;
	}
	eraseBlock();
	ypos += 1;
	//printBlock();
	return 1;
}

void Block::Left(Board &board) {
	if (checkMnMxXposYpos(xpos - 1, ypos, block, board)) return;
	eraseBlock();
	xpos -= 2;
	//printBlock();
}

void Block::Right(Board &board) {
	if (checkMnMxXposYpos(xpos + 1, ypos, block, board)) return;
	eraseBlock();
	xpos += 2;
	//printBlock();
}

bool Block::checkMnMxXposYpos(int xpos, int ypos, vector<vector<int>> &block,Board &brd) {
	int mnx = 1e9, mxx = 0, mny = 1e9, mxy = 0;


	vector<vector<int>> map = brd.getMap();
	int height = brd.getHeight();
	int width = brd.getWidth();

	for (int i = ypos; i < ypos + len; i++) {
		for (int k = xpos; k < xpos + len; k++) {
			if (k >= 0 && i < height && k < width && map[i][k] && block[i - ypos][k - xpos]) return 1;
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

void Block::eraseBlock() {
	for (int i = 0; i < len; i++) {
		for (int k = 0; k < len; k++) {
			if (block[i][k]) {
				//gotoxy(xpos + k * 2 + 1, ypos + i);
				//cout << " ";
				//gotoxy(xpos + k * 2, ypos + i);
				//cout << " ";
			}
		}
	}
}

int Block::getLength() {
	return len;
}

void Block::randBlockColor() {
	int randData = rand() % 7;
	this->xpos = 4;
	this->ypos = 0;
	this->block = v[randData];
	this->len = v[randData].size();
	this->color = randData;
}