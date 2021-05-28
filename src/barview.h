#ifndef BARVIEW_H
#define BARVIEW_H
 
#include <QMainWindow>
#include <QMap>

#include "connect_to_mysql.h"

 
class BarView : public QWidget
{
    Q_OBJECT
 
public:
    BarView(QWidget *parent = 0);
    ~BarView();
 
protected:
    void paintEvent(QPaintEvent *e);

 
private:
    int getMaxVal(QList<int> list);
 
private:
    QMap<QString, int> m_answerMap;
    QList<int> m_numList;
    QList<QString> m_answerStrList;
    int m_nPeopleCount;

public:
	void changeValues(struct WeatherInfo info);

};
 
#endif // BARVIEW_H
