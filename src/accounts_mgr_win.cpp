/**
 * @file      accounts_mgr_win.cpp
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/29 0:47:54:900
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
 *         1.Date         -- 2020/8/29 0:47:54:900
 *           Author       -- RW
 *           Modification -- Created file
 *
 */

#define  ACCOUNTS_MGR_WIN_GLOBAL

/* includes-------------------------------------------------------------------*/
#include <QMessageBox>
#include "accounts_mgr_win.hh"
#include "ui_accounts_mgr_win.h"
#include "ui_account_add_win.h"
#include "account_db.hh"
#include "currency_db.hh"
#include "db.hh"


    
/** @defgroup ACCOUNTS_MGR_WIN                                            
  * @brief ACCOUNTS_MGR_WIN system modules                                
  * @{                                                                         
  */
    
/* Private typedef&macro&definde----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
                                                                                
/** @defgroup ACCOUNTS_MGR_WIN_Private_Functions                          
  * @{                                                                         
  */                                                                            
                                                                                
/**                                                                             
  * @}                                                                         
  */

/** @defgroup CAccountAddWin_CLASS_Functions
  * @{
  */

CAccountAddWin::CAccountAddWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAccountAddWin)
{
    ui->setupUi(this);
}

CAccountAddWin::~CAccountAddWin()
{
    delete ui;
}

void CAccountAddWin::__On_Accepted()
{
    QString errmsg;
    if(ui->m_iNameEdit->text() == ""){
        QMessageBox::critical(this, tr("请输入账户名"), tr("请输入账户名"));
        return;
    }
    AccountInfo info;
    info.name = ui->m_iNameEdit->text().toStdString();
    info.type = 1;
    info.currency_iso_code = Get_Base_Currency_Iso_Code(errmsg);
    if(info.currency_iso_code == ""){
        QMessageBox::critical(this, tr("获取基础货币失败"), tr("获取基础货币失败：")+errmsg);
        return;
    }

    info.start_balance = 0.;
    info.remark = "";
    info.close = 0;
    info.instution_num = "";
    info.instution_name = "";
    info.overdraft_balance = 0.;
    if(!Add_Account(&info, errmsg)){
        QMessageBox::critical(this, tr("新增账户失败"), tr("新增账户失败：")+errmsg);
    }
}

/**
  * @}
  */
                                                                                
/** @defgroup CAccountsMgrWin_CLASS_Functions                          
  * @{                                                                         
  */                                                                            

CAccountsMgrWin::CAccountsMgrWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAccountsMgrWin)
{
    ui->setupUi(this);
    QString errmsg;
    ui->m_iAccountTypeEdit->addItems(Get_All_Account_Type_Names());

    m_iAccountsNameModel = std::make_shared<QSqlQueryModel>();
    m_iAccountsNameModel->setQuery("SELECT name FROM tb_account");
    ui->m_iAccountsNameView->setModel(m_iAccountsNameModel.get());

    QList<QPair<QString, QString>> allCurrenciesInfo;
    if(Get_All_Currencies_IsoCode_Name_From_Db(allCurrenciesInfo, errmsg)){
         for (int i = 0; i < allCurrenciesInfo.size(); ++i) {
            ui->m_iCurrencyEdit->addItem(allCurrenciesInfo.at(i).second, allCurrenciesInfo.at(i).first);
         }
    }

    m_strCurAccountName = "";
}

CAccountsMgrWin::~CAccountsMgrWin()
{
    delete ui;
}

void CAccountsMgrWin::__On_AccountName_Select(const QModelIndex &index)
{
    int row = index.row();
    QSqlRecord record = m_iAccountsNameModel->record(row);
    QString name = record.value("name").toString();
    QString errmsg;
    AccountInfo info;
    if(!Get_AccountInfo_By_Name(&info, name.toStdString(), errmsg)){
        QMessageBox::critical(this, tr("获取账户信息失败"), tr("获取账户信息失败 :") + errmsg);
    } else {
        ui->m_iDetailWidget->setEnabled(true);
        ui->m_iAccountTypeEdit->setCurrentIndex(info.type);
        int32_t index = ui->m_iCurrencyEdit->findData(QString::fromStdString(info.currency_iso_code));
        if(index == -1){
            QMessageBox::critical(this, tr("账户信息错误"), tr("账户的对应的货币不存在:") + QString::fromStdString(info.currency_iso_code));
            ui->m_iDetailWidget->setEnabled(false);
            return;
        }
        ui->m_iCurrencyEdit->setCurrentIndex(index);
        ui->m_iStartBalanceEdit->setValue(info.start_balance);
        ui->m_iRemarkEdit->setText(info.remark.c_str());
        if(info.close){
            ui->m_iAccountClosedEdit->setChecked(true);
            ui->m_iDetailWidget->setEnabled(false);
            ui->m_iAccountClosedEdit->setEnabled(true);
        } else {
            ui->m_iAccountClosedEdit->setChecked(false);
            ui->m_iDetailWidget->setEnabled(true);
        }
        ui->m_iInstutionNameEdit->setText(info.instution_name.c_str());
        ui->m_iInstutionNumEdit->setText(info.instution_num.c_str());
        m_strCurAccountName = name;
    }
}

void CAccountsMgrWin::__On_AccountClose_State_Changed(int stat)
{
    if(stat == Qt::Checked){
        ui->m_iAccountTypeEdit->setEnabled(false);
        ui->m_iCurrencyEdit->setEnabled(false);
        ui->m_iStartBalanceEdit->setEnabled(false);
        ui->m_iRemarkEdit->setEnabled(false);
        ui->m_iInstutionNameEdit->setEnabled(false);
        ui->m_iInstutionNumEdit->setEnabled(false);
        ui->m_iOverdraftBalanceEdit->setEnabled(false);
        ui->m_iTemplateEdit->setEnabled(false);
        ui->m_iExcludeSumEdit->setEnabled(false);
        ui->m_iExcludeBudgetEdit->setEnabled(false);
        ui->m_iExcludeReportsEdit->setEnabled(false);
    } else {
        ui->m_iAccountTypeEdit->setEnabled(true);
        ui->m_iCurrencyEdit->setEnabled(true);
        ui->m_iStartBalanceEdit->setEnabled(true);
        ui->m_iRemarkEdit->setEnabled(true);
        ui->m_iInstutionNameEdit->setEnabled(true);
        ui->m_iInstutionNumEdit->setEnabled(true);
        ui->m_iOverdraftBalanceEdit->setEnabled(true);
        ui->m_iTemplateEdit->setEnabled(true);
        ui->m_iExcludeSumEdit->setEnabled(true);
        ui->m_iExcludeBudgetEdit->setEnabled(true);
        ui->m_iExcludeReportsEdit->setEnabled(true);
    }
}

void CAccountsMgrWin::__On_ApplyBtn_Clicked()
{
    if(m_strCurAccountName == ""){
        QMessageBox::critical(this, tr("当前账户名错误"), tr("当前账户名为空"));
        return;
    }
    AccountInfo info;
    info.name = m_strCurAccountName.toStdString();
    info.type = ui->m_iAccountTypeEdit->currentIndex();
    info.currency_iso_code = ui->m_iCurrencyEdit->currentData().toString().toStdString();
    info.start_balance = ui->m_iStartBalanceEdit->value();
    info.remark = ui->m_iRemarkEdit->toPlainText().toStdString();
    info.close = ui->m_iAccountClosedEdit->isChecked() ? 1 : 0;
    info.instution_name = ui->m_iInstutionNameEdit->text().toStdString();
    info.instution_num = ui->m_iInstutionNumEdit->text().toStdString();
    info.overdraft_balance = ui->m_iOverdraftBalanceEdit->value();
    QString errmsg;
    if(!Update_AccountInfo(&info, errmsg)){
        QMessageBox::critical(this, tr("更新账户信息错误"), tr("更新账户信息错误：")+errmsg);
    }
}

void CAccountsMgrWin::__On_AddBtn_Clicked()
{
    std::shared_ptr<CAccountAddWin> pWin = std::make_shared<CAccountAddWin>();
    if(pWin->exec() == QDialog::Accepted){
        m_iAccountsNameModel->setQuery("SELECT name FROM tb_account");
        ui->m_iDetailWidget->setEnabled(false);
    }
}

void CAccountsMgrWin::__On_DelBtn_Clicked()
{
    QMessageBox::StandardButton btn = QMessageBox::question(this, tr("删除账户"), tr("是否删除账户:") + m_strCurAccountName);
    if(btn == QMessageBox::Yes){
        QString errmsg;
        if(!Delete_Account_By_Name(m_strCurAccountName.toStdString(), errmsg)){
            QMessageBox::critical(this, tr("删除账户错误"), tr("删除账户错误：")+errmsg);
        }
        m_iAccountsNameModel->setQuery("SELECT name FROM tb_account");
        ui->m_iDetailWidget->setEnabled(false);
    }
}



/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

