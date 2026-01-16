#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QPixmap>
#include <QTimer>
#include <QPainter>

#include <dinosaur.h> //恐龙类
#include <gamebackground.h> //游戏背景类
#include <track.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event) override;   // 绘画事件

private:
    void initDinosaurs();   //初始化恐龙素材容器
    void initBackgrounds();
    void initTracks();
    void upDataFrame();     //刷新帧

private:
    Ui::Widget *ui;
    QVector<Dinosaur*> mDinosaurs;  //恐龙素材容器
    Dinosaur *p_mCurrentDinosaur;     //当前恐龙素材
    QPixmap* p_mCurrentDinosaurFrame; //当前恐龙帧
    QTimer*p_mUpDateFrameTimer;        //更新帧定时器

    QVector<GameBackground*>mBackgrounds; //背景素材容器
    GameBackground *p_mCurrentBackground; //当前背景素材

    QPixmap*p_mCurrentBackgroundPixmap;
    int mBackgroundSpeed;                 //背景速度
    int mBackgroundOffest;

    QPixmap* p_mCurrentTrackPixmap;
    int mTrackSpeed;
    int mTrackoffest;
};
#endif // WIDGET_H
