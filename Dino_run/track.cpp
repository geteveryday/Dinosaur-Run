
#include "track.h"


Track::Track(QString trackMaterialPath):
    mTrackMaterialPath(trackMaterialPath)
{
     p_mTrackPixmap = new QPixmap(mTrackMaterialPath);
    if(!p_mTrackPixmap->isNull())
    {
        mIsJoin =true;
    }
    else {
        mIsJoin = false;
    }
}

bool Track::getJoinState()
{
    return mIsJoin;
}

QPixmap *Track::getTrackPixmap()
{
    return p_mTrackPixmap;
}
