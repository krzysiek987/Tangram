#include "Shadow.h"

Shadow::Shadow()
{
    _size = 0;
    _points = NULL;
}

Shadow::Shadow(int size,wxPoint* points)
{
    _size = size;
    _points = new wxPoint[size];
    for(int i=0;i<size;++i) {
        _points[i] = points[i];
    }
}

void Shadow::Set(int size,wxPoint* points)
{
    if(_points) delete _points;
    _size = size;
    _points = new wxPoint[size];
    for(int i=0;i<size;++i) {
        _points[i] = points[i];
    }
}

Shadow::~Shadow() {
    delete _points;
}

wxPoint* Shadow::GetPoints() {
    return _points;
}

int Shadow::GetSize() {
    return _size;
}
