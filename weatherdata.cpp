#include "weatherdata.h"

Today::Today()
{
    date="0000-00-00";
    city="null";
    fl=u8"无数据";
    fx=u8"无数据";
    ganmao=u8"无数据";
    pm25=u8"无数据";
    notice=u8"无数据";
    quality=u8"无数据";
    shidu=u8"无数据";
    type=u8"无数据";
    sunrise="00:00";
    sunset="00:00";
    wendu="null";
}

Today& Today::operator=(const QJsonObject& obj)
{
    QString dateStr=obj.value("date").toString();
    date=QDate::fromString(dateStr, "yyyyMMdd").toString("yyyy-MM-dd");
    city=obj.value("cityInfo").toObject().value("city").toString();

    // 解析data
    QJsonObject dataObj=obj.value("data").toObject();
    shidu=dataObj.value("shidu").toString();
    pm25=QString::number( dataObj.value("pm25").toDouble() );
    quality=dataObj.value("quality").toString();
    wendu=dataObj.value("wendu").toString()+u8"°";
    ganmao=dataObj.value("ganmao").toString();
    QJsonArray forecastArr=dataObj.value("forecast").toArray();
    QJsonObject todayObj=forecastArr.at(0).toObject();
    fx=todayObj.value("fx").toString();
    fl=todayObj.value("fl").toString();
    type=todayObj.value("type").toString();
    sunrise=todayObj.value("sunrise").toString();
    sunset=todayObj.value("sunset").toString();
    notice=todayObj.value("notice").toString();
    return *this;
}

Forecast::Forecast()
{
    date=u8"00日星期0";   // 日期
    week=u8"星期0";       // 星期
    high=u8"高温 0.0℃";   // 最高温度
    low=u8"低温 0.0℃";    // 最低温度
    aqi="0";            // 质量
    type="undefined";   // 天气
}

Forecast& Forecast::operator=(const QJsonObject& obj)
{
    date=obj.value("date").toString();
    week=obj.value("week").toString();
    high=obj.value("high").toString();
    low=obj.value("low").toString();
    aqi=QString::number( obj.value("aqi").toDouble() );
    type=obj.value("type").toString();
    return *this;
}
