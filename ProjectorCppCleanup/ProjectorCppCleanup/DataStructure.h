#pragma once
#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_

class DataStructure
{
public:
	DataStructure();
	DataStructure(int _width, int _height, float _data);
	DataStructure(int _width, int _height, const float* _data);
	virtual ~DataStructure();
	void clear();
	float* getData();
	void setData(float _data);
	int getWidth() const;
	int getHeight() const;
	int getSize() const;
	float& getData(int _index);

protected:
	float* data;

	int width;   // x
	int height;  // y
	int size;

};

inline int DataStructure::getWidth() const { return width; }

inline int DataStructure::getHeight() const { return height; }

inline int DataStructure::getSize() const { return size; }

inline float* DataStructure::getData() { return data; }

inline float& DataStructure::getData(int _index) {
	return data[_index];
}


#endif
