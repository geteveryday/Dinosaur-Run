/*
@autor:调试汪
@date:2025年10月20日
Dinosaur：恐龙，这个类用于维护恐龙的信息和方法
*/

#ifndef DINOSAUR_H
#define DINOSAUR_H
#include <QPixmap>
#include <QString>


class Dinosaur
{
public:
    Dinosaur(QString dino_path);
    ~Dinosaur();
    //恐龙状态
    enum class DinoState{
        idle = 0, //闲置
        move,     //移动
        dead,     //死亡
        jump,     //跳跃
        dash      //冲刺
    };

    QPixmap getFrame(); //获得恐龙当前处于的帧
   // bool addMaterial();   //加载素材
    void setState(DinoState state);    //设置恐龙状态
    bool getJoinState();               //获得恐龙是否加入成功
private:

    //恐龙信息
    QPixmap * p_mIdlePixmap; //闲置像素 3帧
    QPixmap * p_mMovePixmap; //移动像素 6帧
    QPixmap * p_mDeadPixmap; //死亡像素 5帧
    QPixmap * p_mJumpPixmap; //跳跃像素 4帧
    QPixmap * p_mDashPixmap; //冲刺像素 6帧
    QPixmap * p_mCurrentPixmap;//当前像素


    DinoState mNowState;   //恐龙当前状态
    bool mIsJoin;         //素材加入状态 0-失败 1-成功
    QString mDinoMaterialPath;  //素材地址
    int mCurrentFrameIndex;    //当前帧序号
    int mMaxFrameIndex;        //最大帧序号
    int mFrameInterval;           //帧间隔
    int mFrameCounter;         // 增加索引计速度器

};

#endif // DINOSAUR_H
