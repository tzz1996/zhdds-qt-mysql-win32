#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <zhdds/zhdds_cpp.h>
#include <QMetaType>
#include <QString>

#include "Hello.h"
#include "HelloWorld.h"
#include "HelloWorldSupport.h"
#include "HelloSubscriber.h"

//QT_BEGIN_NAMESPACE
//class QAction;
//class QMenu;
//class QPlainTextEdit;
//QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void documentWasModified();
	// dds func
	void initPublisher();
	void initSubscriber();
	void sendOneMessage();
	void createParticipant();
	void deleteParticipant();
	// qt signal&slot
	void recv_msg(HelloWorldSeq dataSeq);

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QPlainTextEdit *textEdit;
    QString curFile;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
	// dds menu
	QMenu*                   publisherMenu;
	QMenu*                   subscriberMenu;
	QMenu*                   participantMenu;
	// dds act
	QAction*                 sendOneAct;
	QAction*                 initPublisherAct;
	QAction*                 initSubscriberAct;
	QAction*                 createParticipantAct;
	QAction*                 deleteParticipantAct;
	// dds participant & topic
	DDSDomainParticipant*    participant;
	DDSTopic *               topic;
	// dds publisher
	DDSPublisher*			 publisher;
    DDSDataWriter*			 dataWriter;
	HelloWorldDataWriter*    helloWriter;
	// dds subscriber
	HelloListener            helloListener;
	DDSSubscriber*			 subscriber;
    DDSDataReader*			 dataReader;
};

#endif
