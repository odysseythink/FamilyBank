#include "main_win.hh"
#include "ui_main_win.h"

CMainWin::CMainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWin)
{
    ui->setupUi(this);
}

CMainWin::~CMainWin()
{
    delete ui;
}

