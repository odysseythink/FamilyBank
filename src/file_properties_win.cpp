/**
 * @file      file_properties_win.cpp
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/19 16:39:24:848
 * @copyright RW
 * @par         (c) COPYRIGHT 2010-2018 by RW Systems, Inc.    
 *                        All rights reserved.
 *                                                                    
 *       This software is confidential and proprietary to RW 
 *     Systems, Inc.  No part of this software may be reproduced,    
 *     stored, transmitted, disclosed or used in any form or by any means
 *     other than as expressly provided by the written license agreement    
 *     between RW Systems and its licensee.
 * @par History      
 *         1.Date         -- 2020/8/19 16:39:24:848
 *           Author       -- RW
 *           Modification -- Created file
 *
 */

#define  FILE_PROPERTIES_WIN_GLOBAL

/* includes-------------------------------------------------------------------*/
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "file_properties_win.hh"
#include "ui_file_properties_win.h"
#include "account_db.hh"
#include "currency_db.hh"
#include "currency_select_win.hh"
#include "config.hh"
#include "db.hh"



    
/** @defgroup FILE_PROPERTIES_WIN                                            
  * @brief FILE_PROPERTIES_WIN system modules                                
  * @{                                                                         
  */
    
/* Private typedef&macro&definde----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
                                                                                
/** @defgroup FILE_PROPERTIES_WIN_Private_Functions                          
  * @{                                                                         
  */                                                                            
                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/** @defgroup CFilePropertiesWin_CLASS_Functions                          
  * @{                                                                         
  */         

CFilePropertiesWin::CFilePropertiesWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CFilePropertiesWin),m_strBaseCurrencyIsoCode("")
{
    ui->setupUi(this);
    ui->m_iAccountTypeEdit->addItems(Get_All_Account_Type_Names());
    ui->m_iCurrencyLbl->setText(Get_Default_Currency_Name());
    m_strBaseCurrencyIsoCode = Config::GetInstance()->Get_BaseCurrencyISOCode();
}

CFilePropertiesWin::~CFilePropertiesWin()
{
    delete ui;
}

void CFilePropertiesWin::On_ChangeCurrencyBtn_Clicked()
{
    std::shared_ptr<CCurrencySelectWin> pWin = std::make_shared<CCurrencySelectWin>(this);
    if(pWin->exec() == QDialog::Accepted){
        qDebug() << "selected currency name=" << pWin->Get_Selected_Currency_Name().c_str();
        ui->m_iCurrencyLbl->setText(pWin->Get_Selected_Currency_Name().c_str());
        m_strBaseCurrencyIsoCode = pWin->Get_Selected_Currency_IsoCode();
    }
    if(__Check_All_Right()){
        ui->m_iOkBtn->setEnabled(true);
    } else {
        ui->m_iOkBtn->setEnabled(false);
    }
}

void CFilePropertiesWin::On_DatabaseFilePathBtn_Clicked()
{
     QString filename = QFileDialog::getSaveFileName(this, tr("选择数据库存储路径和文件名"),
                                                 "./untitled.db",
                                                 tr("Database file (*.db)"), nullptr, QFileDialog::DontConfirmOverwrite);
    if(filename != ""){
        QFile file(filename);
        if(file.exists()){
            if(QMessageBox::question(this, tr("文件名已存在"), tr("文件名已存在，是否覆盖？")) == QMessageBox::Yes){
                Close_Db();
                if(file.remove()){
                    ui->m_iDatabaseFilenNameEdit->setText(filename);
                } else {
                    QMessageBox::critical(nullptr, tr("删除文件失败")+filename+tr("失败"),
                            tr("删除文件失败")+filename+tr("失败"));
                }
            }
        } else {
            ui->m_iDatabaseFilenNameEdit->setText(filename);
        }
    }
    if(__Check_All_Right()){
        ui->m_iOkBtn->setEnabled(true);
    } else {
        ui->m_iOkBtn->setEnabled(false);
    }
}

void CFilePropertiesWin::On_DatabaseFilenName_Changed()
{
    QFileInfo dbFileInfo(ui->m_iDatabaseFilenNameEdit->text());
    QString dbFileSuffix = dbFileInfo.suffix();
    if(dbFileSuffix.compare("db", Qt::CaseInsensitive) != 0){
        QMessageBox::warning(this, tr("文件后缀错误"), tr("文件后缀必须为db"));
        QString dbFilename = dbFileInfo.path() + "/" + dbFileInfo.baseName() + ".db";
        ui->m_iDatabaseFilenNameEdit->setText(dbFilename);
    }
    if(__Check_All_Right()){
        ui->m_iOkBtn->setEnabled(true);
    } else {
        ui->m_iOkBtn->setEnabled(false);
    }
}

void CFilePropertiesWin::On_AccountName_Changed(const QString &name)
{
    if(__Check_All_Right()){
        ui->m_iOkBtn->setEnabled(true);
    } else {
        ui->m_iOkBtn->setEnabled(false);
    }
}

void CFilePropertiesWin::On_Owner_Changed(const QString &name)
{
    if(__Check_All_Right()){
        ui->m_iOkBtn->setEnabled(true);
    } else {
        ui->m_iOkBtn->setEnabled(false);
    }
}

void CFilePropertiesWin::On_Accept()
{
    QString errmsg;
    if (!Init_Db(ui->m_iDatabaseFilenNameEdit->text().toStdString(), errmsg)) {
        QMessageBox::critical(nullptr, "新建数据库失败",
                    "初始化数据库失败: " + errmsg);
        QFile file(ui->m_iDatabaseFilenNameEdit->text());
        if(file.exists()){
            file.remove();
        }
        return;
    }
    if(!Update_Base_Currency_Iso_Code(m_strBaseCurrencyIsoCode, errmsg)){
        QMessageBox::critical(nullptr, tr("新建数据库失败"),
                    "更新基础货币失败: " + errmsg);
        QFile file(ui->m_iDatabaseFilenNameEdit->text());
        if(file.exists()){
            file.remove();
        }
        return;
    }
    string owner = ui->m_iOwnerEdit->text().toStdString();
    if(!Update_Owner(owner, errmsg)){
        QMessageBox::critical(nullptr, tr("新建数据库失败"),
                    "更新所有者失败: " + errmsg);
        QFile file(ui->m_iDatabaseFilenNameEdit->text());
        if(file.exists()){
            file.remove();
        }
        return;
    }
    AccountInfo info;
    info.name = ui->m_iAccountNameEdit->text().toStdString();
    // 1 - 银行, 2 - 现金, 3 - 资产, 4 - 信用卡, 5 - 负债
    info.type = 2;
    if(ui->m_iAccountTypeEdit->currentText() == tr("银行")){
        info.type = 1;
    }else if(ui->m_iAccountTypeEdit->currentText() == tr("现金")){
        info.type = 2;
    }else if(ui->m_iAccountTypeEdit->currentText() == tr("资产")){
        info.type = 3;
    }else if(ui->m_iAccountTypeEdit->currentText() == tr("信用卡")){
        info.type = 4;
    }else if(ui->m_iAccountTypeEdit->currentText() == tr("负债")){
        info.type = 5;
    }
    info.number = ui->m_iAccountNumEdit->text().toStdString();
    info.initial_balances = ui->m_iAccountStartBalancesEdit->value();
    info.overdrawn_balances = ui->m_iAccountOverdrawnBalancesEdit->value();
    if(!Add_Account(&info, errmsg)){
        QMessageBox::critical(nullptr, tr("新建数据库失败"),
                    "添加账失败: " + errmsg);
        QFile file(ui->m_iDatabaseFilenNameEdit->text());
        if(file.exists()){
            file.remove();
        }
        return;
    }

    if(m_strBaseCurrencyIsoCode == ""){
        QMessageBox::critical(nullptr, tr("新建数据库失败"),
                    "未选择基础货币，无法添加数据库");
        QFile file(ui->m_iDatabaseFilenNameEdit->text());
        if(file.exists()){
            file.remove();
        }
        return;
    }
    if(!Add_Default_Currency(m_strBaseCurrencyIsoCode, errmsg)){
        QMessageBox::critical(nullptr, tr("新建数据库失败"),
                    tr("将默认基础货币配置添加到数据库中失败:") + errmsg);
        QFile file(ui->m_iDatabaseFilenNameEdit->text());
        if(file.exists()){
            file.remove();
        }
        return;
    }

    Config::GetInstance()->Set_CurDbFilePath(ui->m_iDatabaseFilenNameEdit->text().toStdString());
}

bool CFilePropertiesWin::__Check_All_Right()
{
    if(ui->m_iDatabaseFilenNameEdit->text() == ""){
        qDebug() << "m_iDatabaseFilenNameEdit is null";
        return false;
    }
    if(m_strBaseCurrencyIsoCode == ""){
        qDebug() << "m_strBaseCurrencyIsoCode is null";
        return false;
    }
    if(Get_Currency_Name(m_strBaseCurrencyIsoCode) == ""){
        qDebug() << "m_strBaseCurrencyIsoCode can't exist";
        return false;
    }
    if(ui->m_iOwnerEdit->text() == ""){
        qDebug() << "m_iOwnerEdit is null";
        return false;
    }
    if(ui->m_iAccountNameEdit->text() == ""){
        qDebug() << "m_iAccountNameEdit is null";
        return false;
    }
    return true;
}


                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

