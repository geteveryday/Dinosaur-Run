#include "gamebackground.h"

GameBackground::GameBackground(QString BackgroundMaterialPath)
    :mBackgroundMaterialPath(BackgroundMaterialPath)
{

    p_mBackgroundPixmap = new QPixmap(mBackgroundMaterialPath);
    if(!p_mBackgroundPixmap->isNull())
    {
        mIsJoin =true;
    }
    else
    {
        mIsJoin =false;
    }
}

GameBackground::~GameBackground()
{
    delete p_mBackgroundPixmap;
}

bool GameBackground::getJoinState()
{
    return mIsJoin;
}

QPixmap *GameBackground::getBackgroundPixmap()
{
    return p_mBackgroundPixmap;
}

