#include "TileData.h"
#include <vector>

bool TileData::getRevealStatus()
{
	return isRevealed;
}

bool TileData::getMineStatus()
{
	return isMine;
}

bool TileData::getFlagStatus()
{
	return isFlag;
}

bool TileData::getCountedStatus()
{
	return isCounted;
}

int TileData::getNumOfNeighbors()
{
	return mineNeighbors.size();
}

void TileData::setRevealStatus(bool status)
{
	isRevealed = status;
}

void TileData::setMineStatus(bool status)
{
	isMine = status;
}

void TileData::setFlagStatus(bool status)
{
	isFlag = status;
}

void TileData::setCountedStatus(bool status)
{
	isCounted = status;
}

void TileData::setNumOfNeighbors(int neighbors)
{
	mineNeighbors.resize(neighbors);
}