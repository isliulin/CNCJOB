#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QTimer>
#include <QPixmap>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QLabel>
#include "mytcpserver.h"
#include "processhogwork.h"
#include "package_bgs/MixtureOfGaussianV2BGS.h"
#include "package_bgs/FrameDifferenceBGS.h"
using namespace cv;
using namespace std;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    Mat showimg;                                /* 可以去掉 */
    MyTcpServer *server;                        /* 服务器端 */
    Mat hogpeople(Mat image);
    void setlablepic(QLabel *lable, Mat image);//label显示Mat图像
    bool hogflag;
    void init();
    bool havepeople;
    processhogwork* worker; //多线程

    //背景建模车辆统计使用
    IBGS *bgs;
    int carnum;
    Rect rect;
    QString dir;  //车辆文件夹
    QString fileName;//datalist.txt
    Mat subImg;


//多物体检测
    bool multiflag;
    double MHI_DURATION;
    int N;
    int CONTOUR_MAX_AERA;
    IplImage **buf;
    int last;
    IplImage *mhi;
    IplImage* motion;
    void update_mhi(IplImage* img, IplImage* dst);
    Mat multitrack(Mat image);
    IplImage* image;


signals:
    void getlocalFrameSignal(); //获取车辆图像

private:
    Ui::Dialog *ui;

    QTimer *timer;                              /* 定时器，更新界面 */
private slots:
    void getFrame(); //获取网络图像
    void getlocalFrame();
    void showprocess();
    void on_pushButton_clicked(); //
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_setimagedir_clicked(); //设置车辆目录
    void on_setdatalist_clicked(); //设置车辆datalist.txt
    void on_pushButton_4_clicked(); //车辆统计
};

#endif // DIALOG_H