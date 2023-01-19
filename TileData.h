#pragma once
#include <vector>
using namespace std;

class TileData
{
	bool isRevealed = false;
	bool isMine = false;
	bool isFlag = false;
	bool isCounted = false;
	vector <TileData*> mineNeighbors;

public:
	bool getRevealStatus();
	bool getMineStatus();
	bool getFlagStatus();
	bool getCountedStatus();
	int getNumOfNeighbors();

	void setRevealStatus(bool status);
	void setMineStatus(bool status);
	void setFlagStatus(bool status);
	void setCountedStatus(bool status);
	void setNumOfNeighbors(int neighbors);
};

