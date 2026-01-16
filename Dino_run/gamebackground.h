#ifndef GAMEBACKGROUND_H
#define GAMEBACKGROUND_H
#include<QPixmap>
#include<QString>

class GameBackground
{
public:
    GameBackground(QString BackgroundMaterialPath);
    ~GameBackground();
    bool getJoinState();
    QPixmap *getBackgroundPixmap();
private:
    QString mBackgroundMaterialPath;    //背景素材地址
    QPixmap *p_mBackgroundPixmap;           //背景像素
    bool mIsJoin;                       //是否加入
};

#endif // GAMEBACKGROUND_H
