#include <cassert>
#include <iostream>

#include "DataStructure.h"

DataStructure::DataStructure() {
	width = 0;
	height = 0;
	size = 0;

	data = NULL;
}

DataStructure::~DataStructure() {

}

void DataStructure::clear() {
	_aligned_free(data);
	width = 0;
	height = 0;
	size = 0;
	data = NULL;
}

DataStructure::DataStructure(int _width, int _height, const float* _data) {
	clear();

	assert(_width > 0);
	assert(_height > 0);
	assert(_data != NULL);

	width = _width;    // detector count
	height = _height;  // angle count
	size = (size_t)width * height;

	data = 0;
	data = (float*)_aligned_malloc(size * sizeof(float),16);

	size_t i;
	for (i = 0; i < size; ++i) {
		data[i] = _data[i];
	}
}

DataStructure::DataStructure(int _width, int _height, float _data) {
	clear();
	assert(_width > 0);
	assert(_height > 0);

	width = _width;
	height = _height;
	size = (size_t)width * height;

	data = 0;
	assert(size > 0);
	assert((size_t)size == (size_t)width * height);
	assert(data == NULL);
	data = (float*)_aligned_malloc(size * sizeof(float), 16);

	size_t i;
	for (i = 0; i < size; ++i) {
		data[i] = _data;
	}
}

void DataStructure::setData(float _data) {
	assert(data != NULL);
	assert(size > 0);

	size_t i;
	for (i = 0; i < size; ++i) {
		data[i] = _data;
	}
}
