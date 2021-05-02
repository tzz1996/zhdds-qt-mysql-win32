#include <QtGui>

#include "MainWindow.h"
#include "HelloPublisher.h"
#include "HelloSubscriber.h"


// ��û������Ŀ������moc.exe���ɵ�moc_MainWindow.cpp
// �ļ�������Ҫ�������ã����������Ӵ���
//#include "moc_MainWindow.cpp"


MainWindow::MainWindow()
{
	//
	// ע��HelloWorldSeq��������signal&slot����
	//
	qRegisterMetaType<HelloWorldSeq>("HelloWorldSeq");

	//
	// init mainwindow
	//
    textEdit = new QPlainTextEdit;
    setCentralWidget(textEdit);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();

    connect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));

    setCurrentFile("");
    setUnifiedTitleAndToolBarOnMac(true);

	textEdit->appendPlainText("init mainwindow complete.");
	textEdit->appendPlainText("please init participant before init pub/sub.");

	//
	// init dds
	//
	participant = NULL;
	topic = NULL;
	publisher = NULL;
	dataWriter = NULL;
	helloWriter = NULL;
	subscriber = NULL;
	dataReader = NULL;
	
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}


void MainWindow::newFile()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFile("");
    }
}


void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}


bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}


bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}


void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
               "write modern GUI applications using Qt, with a menu bar, "
               "toolbars, and a status bar."));

   textEdit->appendPlainText("push about one time");
}

void MainWindow::initPublisher() {
	textEdit->appendPlainText("init publisher...");
	//startPublisher();
    
	// ����������
    textEdit->appendPlainText("create publisher...");
    publisher = participant->create_publisher(
                        DDS_PUBLISHER_QOS_DEFAULT,
                        NULL,           /* ������ */
                        DDS_STATUS_MASK_NONE);
    if (publisher == NULL) {
        textEdit->appendPlainText("create publisher failed.");
        deleteParticipant();
    }
	textEdit->appendPlainText("create publisher success.");

    // ��������д����
    textEdit->appendPlainText("create datawriter...");
    dataWriter = publisher->create_datawriter(
                        topic,
                        DDS_DATAWRITER_QOS_DEFAULT,
                        NULL,           /* ������ */
                        DDS_STATUS_MASK_NONE);
    if (dataWriter == NULL) {
        textEdit->appendPlainText("create datawriter failed.");
        deleteParticipant();
    }
	textEdit->appendPlainText("create datawriter success.");

    // ת������д����
    helloWriter = HelloWorldDataWriter::narrow(dataWriter);
    if (helloWriter == NULL) {
        textEdit->appendPlainText("convert datawriter failed.");
        deleteParticipant();
    }

    // ��������ʵ��
	/*textEdit->appendPlainText("create data instance...");
    instance = HelloWorldTypeSupport::create_data_ex(
                        DDS_BOOLEAN_FALSE);
    if (instance == NULL) {
        textEdit->appendPlainText("create instance failed.");
        deleteParticipant();
    }
	textEdit->appendPlainText("create data instance success.");*/

	textEdit->appendPlainText("init publisher complete.");
}

void MainWindow::initSubscriber() {
	DDS_ReturnCode_t rc = DDS_RETCODE_OK;
    DDS_UnsignedLong i = 0;

	textEdit->appendPlainText("init subscriber...");

	// ��ʼ��helloListener��
	textEdit->appendPlainText("init helloListener...");
	HelloListener listener(1, 0);
	helloListener = listener;
	helloListener.main_window = this;
	if (helloListener.getSampleRcvdCount() == 0)
		textEdit->appendPlainText("init helloListener success.");
	else
		textEdit->appendPlainText("init helloListener failed.");

	// ����qt�źŲ�
	// ���壺ʹqt���߳̽��յ�dds�Զ������Ľ������ݵ��̵߳��źţ�
	//        �ﵽ��ͨ��dds���̼߳���������ʾ��������Ϣ��Ч����
	connect(&helloListener, SIGNAL(send_msg(HelloWorldSeq)), this, SLOT(recv_msg(HelloWorldSeq)));

	// ����������
    textEdit->appendPlainText("create subscriber...");
    subscriber = participant->create_subscriber(
                        DDS_SUBSCRIBER_QOS_DEFAULT,
                        NULL,           /* ������ */
                        DDS_STATUS_MASK_NONE);
    if (subscriber == NULL) {
        textEdit->appendPlainText("create subscriber failed.");
        return;
    }
    
	// �������ݶ�ȡ��
    textEdit->appendPlainText("create datareader...");
    dataReader = subscriber->create_datareader(
                        topic,
                        DDS_DATAREADER_QOS_DEFAULT,
                        &helloListener,
                        DDS_STATUS_MASK_ALL);
    if (dataReader == NULL) {
        textEdit->appendPlainText("create datareader failed.");
        return;
    }

	textEdit->appendPlainText("init subscriber complete.");
}

void MainWindow::sendOneMessage() {
	HelloWorld *instance = NULL; 
	DDS_ReturnCode_t rc;

	textEdit->appendPlainText("send one message...");
	// ��������ʵ��
	textEdit->appendPlainText("create data instance...");
    instance = HelloWorldTypeSupport::create_data_ex(
                        DDS_BOOLEAN_FALSE);
    if (instance == NULL) {
        textEdit->appendPlainText("create instance failed.");
        deleteParticipant();
    }
	textEdit->appendPlainText("create data instance success.");
	// ����һ������
	rc = helloWriter->write(
                        *instance, 
                        DDS_HANDLE_NIL);
	if (rc != DDS_RETCODE_OK) {
		textEdit->appendPlainText("write data to dds failed.");
		if (instance != NULL) {
			HelloWorldTypeSupport::delete_data_ex(instance,
							DDS_BOOLEAN_FALSE);
			instance = NULL;
			return;
		}
	}
	if (instance != NULL) {
        HelloWorldTypeSupport::delete_data_ex(instance,
                        DDS_BOOLEAN_FALSE);
        instance = NULL;
    }

	textEdit->appendPlainText("send one message complete!");
}

void MainWindow::createParticipant() {
	//
	// init dds participant
	//
	DDS_ReturnCode_t rc;

	textEdit->appendPlainText("create participant...");
    participant = DDSDomainParticipantFactory::get_instance()->
                        create_participant(
                        1,
                        DDS_PARTICIPANT_QOS_DEFAULT,
                        NULL,   /* ������ */
                        DDS_STATUS_MASK_NONE);
    if (participant == NULL) {
        textEdit->appendPlainText("create participant failed.");
        deleteParticipant();
    }
	textEdit->appendPlainText("create participant success.");

    // ע������
    textEdit->appendPlainText("register type...");
    rc = HelloWorldTypeSupport::register_type(
                        participant, 
                        HelloWorldTypeSupport::get_type_name());
    if (rc != DDS_RETCODE_OK) {
        textEdit->appendPlainText("register type failed.");
        deleteParticipant();
    }
	textEdit->appendPlainText("register type success.");

    // ��������
    textEdit->appendPlainText("create topic...");
    topic = participant->create_topic(
                        "hello world",
                        HelloWorldTypeSupport::get_type_name(), 
                        DDS_TOPIC_QOS_DEFAULT,
                        NULL,           /* ������ */
                        DDS_STATUS_MASK_NONE);
    if (topic == NULL) {
        textEdit->appendPlainText("create topic failed");
        deleteParticipant();
    }
	textEdit->appendPlainText("create topic success");

	textEdit->appendPlainText("create participant complete.");
}

void MainWindow::deleteParticipant() {
	DDS_ReturnCode_t rc;

	textEdit->appendPlainText("delete participant...");
	if (dataReader != NULL)
		dataReader->set_listener(NULL);
	if (participant != NULL) {
        // ɾ��������߰�����ʵ��
        rc = participant->delete_contained_entities();
        if (rc != DDS_RETCODE_OK) {
            textEdit->appendPlainText("participant->delete_contained_entities() failed.");
        }

		// ɾ���������
        rc = DDSDomainParticipantFactory::get_instance()->delete_participant(
                        participant);
        if (rc != DDS_RETCODE_OK) {
            textEdit->appendPlainText("delete participant failed.");
        }
    }
	textEdit->appendPlainText("delete participant complete.");
}

void MainWindow::recv_msg(HelloWorldSeq dataSeq) {
	QString s;
	QString direction;
	QString sample_id;
	QString temperature;
	QString wind_speed;

	s.sprintf("%s%d","hello",123);
	
	textEdit->appendPlainText("receive signal from class HelloSubscriber.");
	for (int i = 0; i < dataSeq.length(); ++i) {
		textEdit->appendPlainText("this is one of dataSeq[]");
		//textEdit->appendPlainText(s);
		direction.sprintf("direction:%d", dataSeq[i].direction);
		sample_id.sprintf("sample id:%d", dataSeq[i].sampleId);
		temperature.sprintf("temperature:%d", dataSeq[i].temperature);
		wind_speed.sprintf("wind speed:%d", dataSeq[i].wind_speed);

		textEdit->appendPlainText(direction);
		textEdit->appendPlainText(sample_id);
		textEdit->appendPlainText(temperature);
		textEdit->appendPlainText(wind_speed);
	}
}


void MainWindow::documentWasModified()
{
    setWindowModified(textEdit->document()->isModified());
}


void MainWindow::createActions()
{
	// dds start
	initPublisherAct = new QAction("init publisher...", this);
	connect(initPublisherAct, SIGNAL(triggered()), this, SLOT(initPublisher()));

	initSubscriberAct = new QAction("init subscriber...", this);
	connect(initSubscriberAct, SIGNAL(triggered()), this, SLOT(initSubscriber()));

	sendOneAct = new QAction("send one message...", this);
	connect(sendOneAct, SIGNAL(triggered()), this, SLOT(sendOneMessage()));

	createParticipantAct = new QAction("create participant...", this);
	connect(createParticipantAct, SIGNAL(triggered()), this, SLOT(createParticipant()));

	deleteParticipantAct = new QAction("delete participant...", this);
	connect(deleteParticipantAct, SIGNAL(triggered()), this, SLOT(deleteParticipant()));
	// dds end

    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);

    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);

    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

    copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

    pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));
}


void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);

	// publisher menu
	publisherMenu = menuBar()->addMenu("Publisher");
	publisherMenu->addAction(initPublisherAct);
	publisherMenu->addAction(sendOneAct);
	// subscriber menu
	subscriberMenu = menuBar()->addMenu("Subscriber");
	subscriberMenu->addAction(initSubscriberAct);
	// participant menu
	participantMenu = menuBar()->addMenu("participant");
	participantMenu->addAction(createParticipantAct);
	participantMenu->addAction(deleteParticipantAct);

    menuBar()->addSeparator();
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}


void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);

    fileToolBar->addAction(openAct);

    fileToolBar->addAction(saveAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
}


void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}


void MainWindow::readSettings()
{
    QSettings settings("Trolltech", "Application Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}


void MainWindow::writeSettings()
{
    QSettings settings("Trolltech", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}


bool MainWindow::maybeSave()
{
    if (textEdit->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}


void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}


bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}


void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}


QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

//#include "moc_MainWindow.cpp"