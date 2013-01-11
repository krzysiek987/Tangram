#ifndef _ACTUAL_MOVE_INFO_
#define _ACTUAL_MOVE_INFO_
class ActualMoveInfo{
 public:
    ActualMoveInfo(int actualMoveX,int actualMoveY):_actualMoveX(actualMoveX),_actualMoveY(actualMoveY){};
    int GetActualMoveX(){return _actualMoveX;}
    int GetActualMoveY(){return _actualMoveY;}
 private:
    int _actualMoveX;
    int _actualMoveY;
};

#endif
