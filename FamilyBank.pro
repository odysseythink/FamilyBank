QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/account_db.cpp \
    src/accounts_mgr_win.cpp \
    src/categories_mgr_win.cpp \
    src/config.cpp \
    src/currencies_mgr_win.cpp \
    src/currency_db.cpp \
    src/currency_select_win.cpp \
    src/db.cpp \
    src/file_properties_win.cpp \
    src/main.cpp \
    src/main_win.cpp \
    src/payees_mgr_win.cpp

HEADERS += \
    src/account_db.hh \
    src/accounts_mgr_win.hh \
    src/categories_mgr_win.hh \
    src/config.hh \
    src/currencies_mgr_win.hh \
    src/currency_db.hh \
    src/currency_select_win.hh \
    src/db.hh \
    src/file_properties_win.hh \
    src/main_win.hh \
    src/payees_mgr_win.hh \
    src/version.h

FORMS += \
    src/account_add_win.ui \
    src/accounts_mgr_win.ui \
    src/categories_mgr_win.ui \
    src/currencies_mgr_win.ui \
    src/currency_edit_win.ui \
    src/currency_select_win.ui \
    src/file_properties_win.ui \
    src/main_win.ui \
    src/payees_mgr_win.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lglog

RESOURCES += \
    resource/res.qrc

RC_ICONS = logo-256x256.ico
