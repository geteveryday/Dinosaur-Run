#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include <QDir>
#include <QStringList>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,p_mCurrentDinosaurFrame(new QPixmap()) // ✅ 分配内存
    ,p_mCurrentBackgroundPixmap(new QPixmap)
    ,mBackgroundOffest(0)

{
    ui->setupUi(this);
    initDinosaurs(); //初始化恐龙素材
    initBackgrounds();  //初始化恐龙素材
    p_mUpDateFrameTimer =new QTimer(this);
    connect(this->p_mUpDateFrameTimer,&QTimer::timeout,this,&Widget::upDataFrame);
    mBackgroundSpeed =1;    //设置背景更新速度
    p_mUpDateFrameTimer->start(30);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initDinosaurs()
{
    // 指定要读取的目录路径
//        QString dinobasePath = "./res/dino/";
        QString dinobasePath = ":/res/dino/";
        // 创建 QDir 对象
        QDir dir(dinobasePath);

        // 设置过滤器：只获取文件，不获取目录
        dir.setFilter(QDir::Dirs|QDir::NoDotAndDotDot  | QDir::NoSymLinks);

        // 获取文件列表
        QStringList fileList = dir.entryList(); // 只返回文件名，不含路径

        // 遍历文件列表
        for(const QString &fileName : fileList)
        {

            qDebug() << "文件名:" << fileName;
            QString path = dinobasePath + fileName+"/";  // 拼接路径
            qDebug() << "加载恐龙资源路径：" << path;

            Dinosaur *dino = new Dinosaur(path);

            // 如果恐龙对象有效（例如资源加载成功）
            if (dino->getJoinState())
            {
                mDinosaurs.append(dino);
                qDebug() << "恐龙加入容器成功：" << path;
            }
            else
            {
                delete dino;  // 防止内存泄漏
                qDebug() << "恐龙加载失败：" << path;
            }
        }


    // 如果容器中有恐龙，则取第一只为当前恐龙
    if (!mDinosaurs.isEmpty())
    {
        this->p_mCurrentDinosaur = mDinosaurs[0];
        qDebug() << "当前恐龙设置成功";
    }
    else
    {
        qDebug() << "未加载到任何恐龙资源！";
        this->p_mCurrentDinosaur = nullptr;
    }
}

void Widget::initBackgrounds()
{
//    QString backgroundBasePath = "./res/background/";
    QString backgroundBasePath = ":/res/background/";
    QDir dir(backgroundBasePath);
    // 设置过滤器：只获取文件，不获取目录
    dir.setFilter(QDir::Files|QDir::NoDotAndDotDot  | QDir::NoSymLinks);
     QStringList fileList = dir.entryList();
    for(QString &fileName :fileList)
    {
        qDebug()<<fileName;
        QString path = backgroundBasePath+fileName;
        GameBackground* background = new GameBackground(path);
        if(background->getJoinState())
        {
            mBackgrounds.append(background);
            qDebug("添加背景素材成功");
        }
        else
        {
            delete background;
        }
    }

    if(!mBackgrounds.isEmpty())
    {
        p_mCurrentBackground = mBackgrounds[0];
        p_mCurrentBackgroundPixmap=p_mCurrentBackground->getBackgroundPixmap();
    }
}

void Widget::initTracks()
{
    QString trackBasePath = "./res/track/";
}

void Widget::upDataFrame()
{
    if(p_mCurrentDinosaur)
    {
        *p_mCurrentDinosaurFrame=this->p_mCurrentDinosaur->getFrame();
    }

    update(); //触发重绘事件
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if(p_mCurrentBackground)
    {
        QPixmap background =p_mCurrentBackgroundPixmap->scaled(this->width(),this->height(),Qt::KeepAspectRatio,Qt::FastTransformation);
        int index =mBackgroundOffest;
        while(index<this->width())
        {
            painter.drawPixmap(index,0,background);
            index+=background.width();
        }

        mBackgroundOffest-=mBackgroundSpeed;
        if(mBackgroundOffest<=-(background.width()))
        {
            mBackgroundOffest+=background.width();
        }
    }
    if (p_mCurrentDinosaurFrame && !p_mCurrentDinosaurFrame->isNull())
    {

        // 动态选择缩放模式
        Qt::TransformationMode mode =Qt::FastTransformation;
        // 按窗口 DPI 放大（或固定 48x48）
        QPixmap map = p_mCurrentDinosaurFrame->scaled(48, 48, Qt::KeepAspectRatio, mode);

        // 在指定位置绘制恐龙
        painter.drawPixmap(50, 230, map);
    }
}

