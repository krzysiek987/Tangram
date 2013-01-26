#include "Shadow.h"

Shadow::Shadow()
{
    _size = 0;
    _points = NULL;
    _check_points = NULL;
}

Shadow::Shadow(int size, wxPoint* points, wxPoint* check_points)
{
    _size = size;
    _points = new wxPoint[size];
    for(int i=0;i<size;++i) {
        _points[i] = points[i];
    }
    _check_points = new wxPoint[size];
    for(int i=0;i<size;++i) {
        _check_points[i] = check_points[i];
    }
}

void Shadow::Set(int size,wxPoint* points,wxPoint* check_points)
{
    if(_points) delete _points;
    _size = size;
    _points = new wxPoint[size];
    for(int i=0;i<size;++i) {
        _points[i] = points[i];
    }
    _check_points = new wxPoint[size];
    for(int i=0;i<size;++i) {
        _check_points[i] = check_points[i];
    }
}

Shadow::~Shadow() {
    delete _points;
    delete _check_points;
}

wxPoint* Shadow::GetPoints() {
    return _points;
}

wxPoint* Shadow::GetCheckPoints() {
    return _check_points;
}

int Shadow::GetSize() {
    return _size;
}
