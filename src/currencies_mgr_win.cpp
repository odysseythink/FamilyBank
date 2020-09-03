/**
 * @file      currencies_mgr_win.cpp
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/9/3 1:16:53:842
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
 *         1.Date         -- 2020/9/3 1:16:53:842
 *           Author       -- RW
 *           Modification -- Created file
 *
 */

#define  CURRENCIES_MGR_WIN_GLOBAL

/* includes-------------------------------------------------------------------*/
#include <QMessageBox>
#include <QDebug>
#include <glog/logging.h>
#include "currencies_mgr_win.hh"
#include "ui_currencies_mgr_win.h"
#include "ui_currency_edit_win.h"
#include "currency_select_win.hh"
#include "db.hh"

    
/** @defgroup CURRENCIES_MGR_WIN                                            
  * @brief CURRENCIES_MGR_WIN system modules                                
  * @{                                                                         
  */
    
/* Private typedef&macro&definde----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
                                                                                
/** @defgroup CURRENCIES_MGR_WIN_Private_Functions                          
  * @{                                                                         
  */                                                                            
                                                                                
/**                                                                             
  * @}                                                                         
  */

/** @defgroup CCurrencyEditWin_CLASS_Functions
  * @{
  */

CCurrencyEditWin::CCurrencyEditWin(CurrencyInfo* pInfo, string baseCurrencyIsoCode, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCurrencyEditWin)
{
    ui->setupUi(this);
    m_iInfo = pInfo;
    m_strBaseCurrencyIsoCode = baseCurrencyIsoCode;
    if(m_iInfo == nullptr || m_strBaseCurrencyIsoCode == ""){
        ui->m_iOkBtn->setEnabled(false);
        ui->m_iBaseCurrencyLbl->setEnabled(false);
        ui->m_iExchangeRateEdit->setEnabled(false);
        ui->m_iSymbolEdit->setEnabled(false);
        ui->m_iIsPrefixEdit->setEnabled(false);
        ui->m_iDecCharEdit->setEnabled(false);
        ui->m_iFracDigitEdit->setEnabled(false);
        ui->m_iGrpCharEdit->setEnabled(false);
        setWindowTitle(tr("null currency"));
        return;
    }
    ui->m_iBaseCurrencyLbl->setText(QString::asprintf("1%s = ", m_strBaseCurrencyIsoCode.c_str()));
    ui->m_iExchangeRateEdit->setValue(m_iInfo->exchange_rate);
    ui->m_iSymbolEdit->setText(m_iInfo->symbol.c_str());
    ui->m_iIsPrefixEdit->setChecked(m_iInfo->is_prefix);
    ui->m_iDecCharEdit->setText(m_iInfo->dec_char.c_str());
    ui->m_iFracDigitEdit->setValue(m_iInfo->frac_digit);
    ui->m_iGrpCharEdit->setText(m_iInfo->grp_char.c_str());
    __Update_Format();
    setWindowTitle(QString::asprintf("编辑货币%s配置", m_iInfo->iso_code.c_str()));
}

CCurrencyEditWin::~CCurrencyEditWin()
{
    delete ui;
}

void CCurrencyEditWin::__Update_Format()
{
    QString formatStr = QString::asprintf("1%s234%s567%s", ui->m_iGrpCharEdit->text().toLocal8Bit().data(),
                                          ui->m_iGrpCharEdit->text().toLocal8Bit().data(),
                                          ui->m_iDecCharEdit->text().toLocal8Bit().data());
    for(int iLoop = 1; iLoop <= ui->m_iFracDigitEdit->value(); iLoop++){
        formatStr += QString::number(iLoop);
    }
    if(ui->m_iIsPrefixEdit->isChecked()){
        formatStr = ui->m_iSymbolEdit->text() + " " + formatStr;
    } else {
        formatStr =  formatStr + " " + ui->m_iSymbolEdit->text();
    }
    ui->m_iFormatLbl->setText(formatStr);
}

void CCurrencyEditWin::__On_Accepted()
{
    m_iInfo->exchange_rate = ui->m_iExchangeRateEdit->value();
    m_iInfo->symbol = ui->m_iSymbolEdit->text().toStdString();
    m_iInfo->is_prefix = ui->m_iIsPrefixEdit->isChecked();
    m_iInfo->dec_char = ui->m_iDecCharEdit->text().toStdString();
    m_iInfo->frac_digit = ui->m_iFracDigitEdit->value();
    m_iInfo->grp_char = ui->m_iGrpCharEdit->text().toStdString();
    QString errmsg;
    if(!Update_CurrencyInfo(m_iInfo, errmsg)){
        QMessageBox::critical(nullptr, tr("更新货币配置失败"),
                    tr("更新货币配置失败:") + errmsg);
    }
}

void CCurrencyEditWin::__On_Param_Changed()
{
    __Update_Format();
}

/**
  * @}
  */

/** @defgroup CCurrenciesMgrWin_CLASS_Functions
  * @{                                                                         
  */                                                                            

CCurrenciesMgrWin::CCurrenciesMgrWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCurrenciesMgrWin)
{
    ui->setupUi(this);

    m_iCurrenciesModel = std::make_shared<QSqlTableModel>(this, Get_Db());
    m_iCurrenciesModel->setTable("tb_currency");


    m_iCurrenciesModel->setHeaderData(m_iCurrenciesModel->fieldIndex("name"),Qt::Horizontal,tr("名称"));
    m_iCurrenciesModel->setHeaderData(m_iCurrenciesModel->fieldIndex("symbol"),Qt::Horizontal,tr("符号"));
    m_iCurrenciesModel->setHeaderData(m_iCurrenciesModel->fieldIndex("exchange_rate"),Qt::Horizontal,tr("汇率"));
    m_iCurrenciesModel->setHeaderData(m_iCurrenciesModel->fieldIndex("update_time"),Qt::Horizontal,tr("更新时间"));

    m_iCurrenciesModel->select();

    ui->m_iCurrenciesView->setModel(m_iCurrenciesModel.get());

    ui->m_iCurrenciesView->setColumnHidden(m_iCurrenciesModel->fieldIndex("id"),true);
    ui->m_iCurrenciesView->setColumnHidden(m_iCurrenciesModel->fieldIndex("iso_code"),true);
    ui->m_iCurrenciesView->setColumnHidden(m_iCurrenciesModel->fieldIndex("frac_digit"),true);
    ui->m_iCurrenciesView->setColumnHidden(m_iCurrenciesModel->fieldIndex("dec_char"),true);
    ui->m_iCurrenciesView->setColumnHidden(m_iCurrenciesModel->fieldIndex("grp_char"),true);
    ui->m_iCurrenciesView->setColumnHidden(m_iCurrenciesModel->fieldIndex("is_prefix"),true);
    ui->m_iCurrenciesView->setColumnHidden(m_iCurrenciesModel->fieldIndex("create_time"),true);

    m_strCurCurrencyIsoCode = "";
    ui->m_iDelBtn->setEnabled(false);
    ui->m_iEditBtn->setEnabled(false);
    ui->m_iSetAsBaseBtn->setEnabled(false);
    QString title = tr("货币管理 - 基础货币:");
    QString errmsg;
    m_strBaseCurrencyIsoCode = Get_Base_Currency_Iso_Code(errmsg);
    title += m_strBaseCurrencyIsoCode.c_str();
    setWindowTitle(title);
}

CCurrenciesMgrWin::~CCurrenciesMgrWin()
{
    delete ui;
}

void CCurrenciesMgrWin::__On_AddBtn_Clicked()
{
    std::shared_ptr<CCurrencySelectWin> pWin = std::make_shared<CCurrencySelectWin>(this);
    if(pWin->exec() == QDialog::Accepted){
        QString errmsg;
        string isoCode = pWin->Get_Selected_Currency_IsoCode();
        if(!Add_Default_Currency(isoCode, errmsg)){
            QMessageBox::critical(nullptr, tr("添加货币失败"),
                        tr("添加货币失败:") + errmsg);
            return;
        }
        m_iCurrenciesModel->select();
        ui->m_iDelBtn->setEnabled(false);
        ui->m_iEditBtn->setEnabled(false);
        ui->m_iSetAsBaseBtn->setEnabled(false);
    }
}

void CCurrenciesMgrWin::__On_EditBtn_Clicked()
{
    int row = ui->m_iCurrenciesView->currentIndex().row();
    QSqlRecord record = m_iCurrenciesModel->record(row);
    CurrencyInfo info;
    info.iso_code = record.value("iso_code").toString().toStdString();
    info.frac_digit = record.value("frac_digit").toUInt();
    info.dec_char = record.value("dec_char").toString().toStdString();
    info.grp_char = record.value("grp_char").toString().toStdString();
    info.is_prefix = record.value("is_prefix").toBool();
    info.symbol = record.value("symbol").toString().toStdString();
    info.name = record.value("name").toString().toStdString();
    info.exchange_rate = record.value("exchange_rate").toDouble();
    std::shared_ptr<CCurrencyEditWin> pWin = std::make_shared<CCurrencyEditWin>(&info, m_strBaseCurrencyIsoCode, this);
    if(pWin->exec() == QDialog::Accepted){
        m_iCurrenciesModel->select();
        ui->m_iDelBtn->setEnabled(false);
        ui->m_iEditBtn->setEnabled(false);
        ui->m_iSetAsBaseBtn->setEnabled(false);
    }
}

void CCurrenciesMgrWin::__On_DelBtn_Clicked()
{
    QMessageBox::StandardButton btn = QMessageBox::question(this, tr("删除货币"), tr("是否删除货币:") + m_strCurCurrencyIsoCode.c_str());
    if(btn == QMessageBox::Yes){
        QString errmsg;
        if(!Delete_Currency_By_IsoCode(m_strCurCurrencyIsoCode, errmsg)){
            QMessageBox::critical(this, tr("删除账户错误"), tr("删除账户错误：")+errmsg);
        }
        m_iCurrenciesModel->select();
        ui->m_iDelBtn->setEnabled(false);
        ui->m_iEditBtn->setEnabled(false);
        ui->m_iSetAsBaseBtn->setEnabled(false);
    }
}

void CCurrenciesMgrWin::__On_SetAsBaseBtn_Clicked()
{

}

void CCurrenciesMgrWin::__On_Currency_Select(const QModelIndex &index)
{
    int row = index.row();
    QSqlRecord record = m_iCurrenciesModel->record(row);
    m_strCurCurrencyIsoCode = record.value("iso_code").toString().toStdString();
    if(m_strCurCurrencyIsoCode != ""){
        if(m_strBaseCurrencyIsoCode == m_strCurCurrencyIsoCode){
            ui->m_iDelBtn->setEnabled(false);
            ui->m_iSetAsBaseBtn->setEnabled(false);
        } else {
            ui->m_iDelBtn->setEnabled(true);
            ui->m_iSetAsBaseBtn->setEnabled(true);
        }
        ui->m_iEditBtn->setEnabled(true);
    }
}



/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

