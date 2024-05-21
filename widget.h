#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include <QList>
#include <QNetworkAccessManager> // 注意要 先在.pro文件的QT后面，加上network
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>
#include <QMessageBox>
#include <QTimer>
#include <QPainter>

#include "WeatherTool.h"
#include "weatherdata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    virtual bool eventFilter(QObject* watched, QEvent* event);

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void getWeatherInfo(QNetworkAccessManager *manager); // 发起请求
    void parseJson(QByteArray& bytes);  // 解析json数据
    void setLabelContent();  // 把数据更新到界面
    void paintSunRiseSet(); // 绘制日出日落
    void paintCurve();  // 绘制温度曲线

private:
    Ui::Widget *ui;
    QMenu *exitMenu; // 右键退出菜单
    QAction *exitAct; // 右键退出行为
    QPoint mPos;  // 拖动窗口移动的点
    // UI
    QList<QLabel*> forecast_week_list;      // 星期
    QList<QLabel*> forecast_date_list;      // 日期
    QList<QLabel*> forecast_aqi_list;       // 天气指数
    QList<QLabel*> forecast_type_list;      // 天气
    QList<QLabel*> forecast_typeIco_list;   // 天气图标
    QList<QLabel*> forecast_high_list;      // 高温
    QList<QLabel*> forecast_low_list;       // 低温

    // 网络请求成员
    QNetworkAccessManager *manager;
    QString url;        // 接口链接
    QString city;       // 请求城市
    QString cityTmp;    // 临时存放城市变量，防止输入错误的城市，原来的城市还在
    WeatherTool tool;   // 天气工具对象

    // 本地数据
    Today today;
    Forecast forecast[6];

    static const QPoint sun[2]; // 日出日落底线
    static const QRect sunRiseSet[2]; // 日出日落时间
    static const QRect rect[2];     // 日出日落圆弧
    QTimer *sunTimer;   // 定时更新

private slots:
    void slot_exitApp(); // 退出槽函数
    void replyFinished(QNetworkReply* reply);
    void on_refreshBt_clicked();
    void on_searchBt_clicked();
};
#endif // WIDGET_H
