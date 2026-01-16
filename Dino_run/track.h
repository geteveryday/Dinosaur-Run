#ifndef TRACK_H
#define TRACK_H
#include<QPixmap>
#include<QString>


class Track
{
public:
    Track(QString  trackMaterialPath);
    bool getJoinState();
    QPixmap*getTrackPixmap();
private:
    QPixmap* p_mTrackPixmap;
    QString mTrackMaterialPath;
    bool mIsJoin;
};

#endif // TRACK_H
