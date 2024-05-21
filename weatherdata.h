#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QObject>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDate>
#include <QPainter>
#include <QDateTime>
#include <QMessageBox>

class Today  // 当日天气预报数据
{
public:
    Today();
    Today& operator=(const QJsonObject& obj);
    QString date;   // 日期
    QString wendu;  // 温度
    QString city;   // 城市
    QString shidu;  // 湿度
    QString pm25;   // PM2.5
    QString quality;// 空气质量
    QString ganmao; // 感冒指数
    QString fx;     // 风向
    QString fl;     // 风力
    QString type;   // 天气
    QString sunrise;// 日出时间
    QString sunset; // 日落时间
    QString notice; // 注意信息
private:
};

class Forecast
{
public:
    Forecast();
    Forecast& operator=(const QJsonObject& obj);
    QString date;   // 日期
    QString week;   // 星期
    QString high;   // 最高温度
    QString low;    // 最低温度
    QString aqi;    // 质量
    QString type;   // 天气
};

#endif // WEATHERDATA_H
