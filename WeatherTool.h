#ifndef WEATHERTOOL_H
#define WEATHERTOOL_H

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QCoreApplication>
#include <QFile>
#include <map>
#include <QDebug>

class WeatherTool
{
public:
    WeatherTool(){
        QString fileName=QCoreApplication::applicationDirPath(); // 获取应用程序的路径
        fileName+="/citycode.json";
        QFile file(fileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray json=file.readAll();
        file.close();
        QJsonParseError err;
        QJsonDocument jsonDoc=QJsonDocument::fromJson(json, &err);
        QJsonArray citys=jsonDoc.array();
        for(int i=0;i<citys.size();i++){
            QString code=citys.at(i).toObject().value("city_code").toString();
            QString city=citys.at(i).toObject().value("city_name").toString();
            if(code.size()>0) city2code.insert(std::pair<QString,QString>(city, code));
        }
    }
    QString operator[](const QString& city) { // 重载[]
        auto it=city2code.find(city);
        if(it==city2code.end()){
            it=city2code.find(city+u8"市");
        }
        if(it==city2code.end()){
            it=city2code.find(city+u8"区");
        }
        if(it==city2code.end()){
            it=city2code.find(city+u8"县");
        }
        if(it!=city2code.end()){
            return it->second;
        }
        return "000000000";
    }
private:
    std::map<QString, QString> city2code;
};


#endif // WEATHERTOOL_H
