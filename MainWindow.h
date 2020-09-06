#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>

#include "download/QDownloader.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void download();

private:
    QDownloader *m_downloader;

    QLineEdit *m_urlEdit;
    QLineEdit *m_fileEdit;
};
#endif // MAINWINDOW_H
