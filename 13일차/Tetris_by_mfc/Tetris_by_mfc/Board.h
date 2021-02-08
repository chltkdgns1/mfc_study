#pragma once
#ifndef __BOARD__H_
#define __BOARD__H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <time.h>
#include "pch.h"
#include "Tetris_by_mfcDlg.h"
#include "CBColor.h"
using namespace std;

#define error p->MessageBox(L"통과")
#define print(A) p->MessageBox(A) 

class Board {

private :
	int height, width, score;
	CTetrisbymfcDlg *p;
	CClientDC *dc;
	CBrush *br;
	CPen *pen;
public:
	vector<vector<int>> board;

	Board(CTetrisbymfcDlg *p) {
		height = width = 0;
		dc = new CClientDC(p);
		this->p = p;
		score = 0;
		printScoreLevel();
	}

	void mustInit(int height,int width) { // 캡슐화
		this->height = height;
		this->width = width;;
		boardInit();
	}

	void boardInit() {
		if (height <=0 || width <=0) {
			p->MessageBox(L"길이와 넓이가 설정되기 전에 보드를 초기화했습니다.");
			return;
		}
		board.resize(height);
		for (int i = 0; i < height; i++) board[i].resize(width, 0);
	}

	void setHeight(int height) {
		this->height = height;
	}

	void setWidth(int width) {
		this->width = width;
	}

	void setBoard(vector<vector<int>> board) {
		this->board = board;
	}

	int getHeight() {
		return height;
	}

	int getWidth() {
		return width;
	}

	void downLine(int y) {
		for (int i = y - 1; i >= 0; i--) {
			for (int k = 0; k < width; k++) {
				board[i + 1][k] = board[i][k];
			}
		}
		for (int k = 0; k < width; k++) board[0][k] = 0;
	}

	void printScoreLevel() {
		CString str;
		str.Format(_T("LEVEL : %d"), score / 100 + 1);
		p->idc_level.SetWindowTextW(str);
		str.Format(_T("SCORE : %d"), score);
		p->idc_score.SetWindowTextW(str);
	}

	void deleteLine(int &speed) {
		int line = 0;
		for (int i = height - 1; i >= 0; i--) {
			int cnt = 0;
			for (int k = 0; k < width; k++) {
				if (board[i][k]) cnt++;
			}

			if (cnt == width) { // 한줄이 모두 채워지면
				downLine(i);
				line++; i++;
			}
		}

		speed = 400 - (score / 100) * 100;
		score += line * 10;
		printScoreLevel();

		if (line) {
			for (int i = 0; i < height; i++) {
				for (int k = 0; k < width; k++) {
					if (!board[i][k]) {
						br = new CBrush(RGB(240, 240, 240));
						pen = new CPen(PS_SOLID, 1, RGB(240, 240, 240));
						dc->SelectObject(br);
						dc->SelectObject(pen);
						dc->Rectangle(k * 21, i * 21, 20 + k * 21, 20 + i * 21);
					}
					else {
						Tcolor  col = cbcolor->getColor(board[i][k] - 1);
						br = new CBrush(RGB(col.x, col.y, col.z));
						pen = new CPen(PS_SOLID, 1, RGB(col.x, col.y, col.z));
						dc->SelectObject(br);
						dc->SelectObject(pen);
						dc->Rectangle(k * 21, i * 21, 20 + k * 21, 20 + i * 21);
					}
				}
			}
		}
	}

	void printBoard() {	
		br = new CBrush(RGB(240, 240, 240));
		pen = new CPen(PS_SOLID, 1, RGB(240, 240, 240));
		dc->SelectObject(br);
		dc->SelectObject(pen);
		for (int i = 0; i < height; i++) {
			for (int k = 0; k < width; k++) {
				dc->Rectangle(k * 21,i * 21, 20 + k * 21, 20 + i * 21);
			}
		}
	}
};


#endif