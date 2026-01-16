#include "dinosaur.h"

Dinosaur::Dinosaur(QString dino_path)
    : mDinoMaterialPath(dino_path)
{
    // 正确加载所有动作图像
    p_mIdlePixmap = new QPixmap(QString(mDinoMaterialPath + "idle.png"));
    p_mDashPixmap = new QPixmap(QString(mDinoMaterialPath + "dash.png"));
    p_mMovePixmap = new QPixmap(QString(mDinoMaterialPath + "move.png"));
    p_mDeadPixmap = new QPixmap(QString(mDinoMaterialPath + "dead.png"));
    p_mJumpPixmap = new QPixmap(QString(mDinoMaterialPath + "jump.png"));

    // 判断是否加载成功（建议用isNull判断）
    if (p_mIdlePixmap->isNull() ||
        p_mDashPixmap->isNull() ||
        p_mMovePixmap->isNull() ||
        p_mDeadPixmap->isNull() ||
        p_mJumpPixmap->isNull())
    {
        mIsJoin = false;
    }
    else
    {
        mIsJoin = true;
    }

    // 设置初始状态
    setState(DinoState::idle);
    mFrameInterval =3;  //恐龙动画更新间隔
    mFrameCounter=0;
}

Dinosaur::~Dinosaur()
{
    delete p_mIdlePixmap;
    delete p_mDashPixmap;
    delete p_mMovePixmap;
    delete p_mDeadPixmap;
    delete p_mJumpPixmap;
}


QPixmap Dinosaur::getFrame()
{
    if (p_mCurrentPixmap)
    {

        QPixmap frame = p_mCurrentPixmap->copy(24 * (mCurrentFrameIndex), 0, 24, 24);
        //控制帧的刷新间隔
        mFrameCounter++;
        if(mFrameCounter>mFrameInterval)
        {
            mCurrentFrameIndex++;
            mFrameCounter =0;
        }
        //控制完整动作的周期
        if (mCurrentFrameIndex > mMaxFrameIndex)
        {
            mCurrentFrameIndex = 0;
        }
        return frame;
    }
    return QPixmap();
}



void Dinosaur::setState(Dinosaur::DinoState state)
{
    mNowState =state;
    mCurrentFrameIndex =0;
    switch (mNowState)
    {
        case DinoState::idle:  p_mCurrentPixmap=p_mIdlePixmap;      mMaxFrameIndex=2; break;
        case DinoState::dash:  p_mCurrentPixmap=p_mDashPixmap;      mMaxFrameIndex=5; break;
        case DinoState::dead:  p_mCurrentPixmap=p_mDeadPixmap;      mMaxFrameIndex=2; break;
        case DinoState::jump:  p_mCurrentPixmap=p_mJumpPixmap;      mMaxFrameIndex=3; break;
        case DinoState::move:  p_mCurrentPixmap=p_mMovePixmap;      mMaxFrameIndex=5; break;
    }
}

bool Dinosaur::getJoinState()
{
    return this->mIsJoin;
}


