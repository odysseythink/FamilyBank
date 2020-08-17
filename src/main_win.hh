#ifndef CMAINWIN_HH
#define CMAINWIN_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CMainWin; }
QT_END_NAMESPACE

class CMainWin : public QMainWindow
{
    Q_OBJECT

public:
    CMainWin(QWidget *parent = nullptr);
    ~CMainWin();

private:
    Ui::CMainWin *ui;
};
#endif // CMAINWIN_HH
