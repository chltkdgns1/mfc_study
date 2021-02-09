#pragma once
#ifndef __CBCOLOR_H__
#define __CBCOLOR_H__

#include <vector>
#include <time.h>
using namespace std;

class Tcolor {
public:
	int x, y, z;
};

class CBColor {
private :
	vector<Tcolor> v;

public:

	void Print(CTetrisbymfcDlg *p) {
		for(int  i=0;i<v.size();i++){	
			CString str;
			str.Format(_T("%d %d %d"),v[i].x, v[i].y, v[i].z);
			p->MessageBox(str);
		}
	}

	Tcolor getRandomColor() {
		int x = rand() % 256;
		int y = rand() % 256;
		int z = rand() % 256;
		return {x,y,z };
	}

	CBColor(int n) {
		v.resize(n);
		srand(time(NULL));
		for (int i = 0; i < n; i++) {
			v[i] = getRandomColor();
		}
	}

	Tcolor getColor(int idx) {
		return v[idx];
	}
};

CBColor *cbcolor = new CBColor(7);

#endif