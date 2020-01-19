#pragma once
#ifndef RANDARRAY_H
#define RANDARRAY_H
#include<vector>
#include<cstdlib>
#include<ctime>

void RandArray(std::vector<int> Original, std::vector<int> &newArray) {
	srand(unsigned(time(NULL)));
	for (int i = Original.size(); i > 0; i--) {
		int index = rand() % i;
		newArray.push_back(Original[index]);
		Original.erase(Original.begin() + index);
	}
}

#endif // RANDARRAY_H ///:~
