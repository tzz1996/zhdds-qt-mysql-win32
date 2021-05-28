#include "barview.h"
#include <QPainter>

 
BarView::BarView(QWidget *parent):QWidget(parent)
{
    this->resize(500, 570);
 
    m_answerMap.insert("A", 2);
    m_answerMap.insert("ABCD", 1);
    m_answerMap.insert("AD", 3);
    m_answerMap.insert("BD", 10);
    m_answerMap.insert("AC", 2);
    m_answerMap.insert("BCD", 1);
 
    m_nPeopleCount = 0;
 
    m_answerStrList = m_answerMap.keys();
    m_numList = m_answerMap.values();
    foreach (int num, m_numList) {
        m_nPeopleCount += num;
    }
 
}
 
BarView::~BarView()
{
 
}
 
void BarView::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);
 
    if(m_numList.isEmpty())
    {
        return;
    }
 
    painter.setPen(Qt::black);
 
    int lineWidth = 360;
    int lineX = this->width()/2 - lineWidth/2;
    int lineY = 402;
    painter.drawLine(lineX, lineY, lineX + lineWidth, lineY);
 
    int answerCount = m_answerStrList.count();
    int maxWidth = 41;
    int maxHeight = 280;
 
    int curWidth = maxWidth - (answerCount - 1)*3;
    int unitWidth = lineWidth/answerCount;
 
    //��ȡѡ����ֵ�����Ǹ��������Ϊ��׼�߶ȣ�����������ֵ�ĸ߶�
    int maxVal = getMaxVal(m_numList);
    int unitHeight = 0;
    if(maxVal)
    {
        unitHeight = maxHeight/maxVal;
    }
 
    QFont ft;
    ft.setPixelSize(13);
    for(int i = 0; i < m_answerStrList.count(); ++i)
    {
        QString answerStr = m_answerStrList.at(i);
        int selectNum = m_numList.at(i);
        QString selectNumStr = QString::number(selectNum);
 
        int x = lineX + i*unitWidth + unitWidth/2 - curWidth/2;
        //������״ͼ
        int GraphHight = selectNum*unitHeight;
        QRect r = QRect(x, lineY - GraphHight, curWidth, GraphHight);
        QPainterPath path;
        path.addRect(r);
        painter.fillPath(path, QColor(185, 185, 185));
 
        //���ƴ�
        QFontMetrics metrics(ft);
        int charWitdh = metrics.width(answerStr);
        QRect answerRect;
/**     �Ա����ֳ��Ⱥ���״ͼ�Ŀ�ȣ�����״ͼ��������ֵĳ���Ϊ��׼�ử����֮��
 *      ��״ͼ�Ŀ����������֤��ʾȫ�����У������Ҳ��һ��
 */
        if(charWitdh < curWidth)
        {
            answerRect = QRect(x, lineY, curWidth, 30);
        }
        else
        {
            answerRect = QRect(x - (charWitdh - curWidth)/2, lineY, charWitdh, 30);
        }
        painter.drawText(answerRect, Qt::AlignCenter, answerStr);
 
        //����ÿ��ѡ���Ӧ��ֵ
        QRect percentRect;
        charWitdh = metrics.width(selectNumStr);
        if(charWitdh < curWidth)
        {
            percentRect = QRect(x, lineY - GraphHight - 30, curWidth, 30);
        }
        else
        {
            percentRect = QRect(x - (charWitdh - curWidth)/2, lineY - GraphHight - 40, charWitdh, 30);
        }
        painter.drawText(percentRect, Qt::AlignCenter, selectNumStr);
 
    }
}
 
int BarView::getMaxVal(QList<int> list)
{
    qSort(list.begin(), list.end());
    return list.last();
}

void BarView::changeValues(WeatherInfo info) {
	m_answerMap.clear();

	m_answerMap.insert("sample_id", QString::fromStdString(info.sample_id).toInt());
	m_answerMap.insert("pub_num", QString::fromStdString(info.pub_num).toInt());
	m_answerMap.insert("pub_stat", QString::fromStdString(info.pub_stat).toInt());
	m_answerMap.insert("temperature", QString::fromStdString(info.temperature).toFloat());
	m_answerMap.insert("humidity", QString::fromStdString(info.humidity).toFloat());
	m_answerMap.insert("wind_speed", QString::fromStdString(info.wind_speed).toInt());
	m_answerMap.insert("direction", QString::fromStdString(info.direction).toInt());

	m_answerStrList = m_answerMap.keys();
    m_numList = m_answerMap.values();
    foreach (int num, m_numList) {
        m_nPeopleCount += num;
    }
}
