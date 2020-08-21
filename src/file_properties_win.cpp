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
                file.remove();
                ui->m_iDatabaseFilenNameEdit->setText(filename);
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
    QSqlError err = Init_Db(ui->m_iDatabaseFilenNameEdit->text().toStdString());
    if (err.type() != QSqlError::NoError) {
        QMessageBox::critical(nullptr, "新建数据库失败",
                    "初始化数据库失败: " + err.text());
        QFile file(ui->m_iDatabaseFilenNameEdit->text());
        if(file.exists()){
            file.remove();
        }
        return;
    }
    QString errmsg;
    if(!Update_Base_Currency_Iso_Code(m_strBaseCurrencyIsoCode, errmsg)){
        QMessageBox::critical(nullptr, tr("新建数据库失败"),
                    "更新基础货币失败: " + errmsg);
        QFile file(ui->m_iDatabaseFilenNameEdit->text());
        if(file.exists()){
            file.remove();
        }
        return;
    }
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

