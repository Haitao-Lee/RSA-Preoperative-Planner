#pragma once
#ifndef POINTSTOREREALIZE_H
#define POINTSTOREREALIZE_H

#include "pointStore.h"


pointStore::pointStore() {
	this->point[0] = 0;
	this->point[1] = 0;
	this->point[2] = 0;
	this->nextPoint = NULL;
	pointNum = 0;
}




void pointStore::addPoint(double picked[3]) {
	int num = this->pointNum;
	this->pointNum++;
	pointStore* curPoint = this;
	for (int i = 0;i < num;i++)
	{
		curPoint = curPoint->nextPoint;
		//curPoint->pointNum = num - i;
	}
	curPoint->point[0] = picked[0];
	curPoint->point[1] = picked[1];
	curPoint->point[2] = picked[2];
	curPoint->nextPoint = new pointStore();
	//curPoint = curPoint->nextPoint;
	
};



double* pointStore::getPoint(int rank) {
	if (rank <= 0 || rank > this->pointNum+1)
	{
		//std::cout << "getPoint input error!" << std::endl;
		return NULL;
	}
	pointStore* curPoint = this;
	for (int i = 0;i < rank - 1;i++)
	{
		//std::cout << "curPoint[" << i+1 <<"]:" << curPoint->point[0] << " " << curPoint->point[1] << " " << curPoint->point[2] << " " << std::endl;
		curPoint = curPoint->nextPoint;
	}
	return curPoint->point;
}



void pointStore::deleteLastPoint() {
	if (this->pointNum == 0)
	{
		return;
	}
	if (this->pointNum == 1)
	{
		pointNum = 0;
		delete(this->nextPoint);
		return;
	}
	pointStore* curPoint = this;
	for (int i = 0;i < this->pointNum - 1;i++)
	{
		curPoint = curPoint->nextPoint;
	}
	//std::cout << "delete point: " << curPoint->point[0] << " " << curPoint->point[1] << " " << curPoint->point[2] << " " << std::endl;
	delete(curPoint->nextPoint);
	//delete(curPoint);
	this->pointNum--;

}


void pointStore::changePoint(int rank, double* newPoint)
{
	if (rank <= 0 || rank > this->pointNum)
	{
		//std::cout << "getPoint input error!" << std::endl;
		return;
	}
	pointStore* curPoint = this;
	for (int i = 0;i < rank - 1;i++)
	{
		//std::cout << "curPoint[" << i+1 <<"]:" << curPoint->point[0] << " " << curPoint->point[1] << " " << curPoint->point[2] << " " << std::endl;
		curPoint = curPoint->nextPoint;
	}
	curPoint->point[0] = newPoint[0];
	curPoint->point[1] = newPoint[1];
	curPoint->point[2] = newPoint[2];
	return;
}

void pointStore::printSelf()
{
	if (this->pointNum == 0)
	{
		std::cout << "there is no point recorded!" << std::endl;
		return;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "there are totally " << this->pointNum << " points:" << std::endl;
	pointStore* curPoint = this;
	for (int i = 0;i < this->pointNum;i++)
	{
		std::cout << "point[" << i + 1 << "]:" << curPoint->point[0] << " " << curPoint->point[1] << " " << curPoint->point[2] << std::endl;
		curPoint = curPoint->nextPoint;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	return;
}

pointStore::~pointStore() {
	deleteAll();
}


void pointStore::clear()
{
	if (this->pointNum == 0)
		return;
	pointStore* curPoint = this;
	this->pointNum = 0;
	delete(curPoint->nextPoint);
}


void pointStore::deleteAll() {

	if (this->pointNum == 0)
	{
		return;
	}
	pointStore* curPoint = this;
	//std::cout << "curPoint" << curPoint->point[0] << " " << curPoint->point[1] << " " << curPoint->point[2] << std::endl;
	this->pointNum = 0;
	curPoint->nextPoint->deleteAll();
	delete(this);
}
#endif // !POINTSTOREREALIZE_H