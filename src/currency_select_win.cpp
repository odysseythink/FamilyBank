/**
 * @file      currency_select_win.cpp
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/19 18:7:41:189
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
 *         1.Date         -- 2020/8/19 18:7:41:189
 *           Author       -- RW
 *           Modification -- Created file
 *
 */

#define  CURRENCY_SELECT_WIN_GLOBAL

/* includes-------------------------------------------------------------------*/
#include <QDebug>
#include <QTableWidgetItem>
#include <QHeaderView>
#include "currency_select_win.hh"
#include "ui_currency_select_win.h"
#include "currency_db.hh"



    
/** @defgroup CURRENCY_SELECT_WIN                                            
  * @brief CURRENCY_SELECT_WIN system modules                                
  * @{                                                                         
  */
    
/* Private typedef&macro&definde----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
                                                                                
/** @defgroup CURRENCY_SELECT_WIN_Private_Functions                          
  * @{                                                                         
  */                                                                            
                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/** @defgroup CCurrencySelectWin_CLASS_Functions                          
  * @{                                                                         
  */                                                                            

CCurrencySelectWin::CCurrencySelectWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCurrencySelectWin)
{
    ui->setupUi(this);

    m_iCurrencyModel = make_shared<QStandardItemModel>(this);

    QStringList currencyTableHeader;
    currencyTableHeader << tr("ISO码") << tr("名称") ;
    m_iCurrencyModel->setHorizontalHeaderLabels(currencyTableHeader);
//    ui->m_iCurrencyTableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
//    ui->m_iCurrencyView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QMap<string, CurrencyInfo*>* pMap = Get_All_Currencies_Info();
    if(pMap != nullptr){
        qDebug() << "all currencies info map size=" << pMap->size();
        QMap<string, CurrencyInfo*>::const_iterator iter = pMap->constBegin();
//        int row = 0;
        while (iter != pMap->constEnd()) {
            QString name = QString::fromStdString(iter.value()->name);
            QString isoCode = QString::fromStdString(iter.key());
//            qDebug() << "name=" << name << ",isoCode=" << isoCode;
            QList<QStandardItem*> rowItems;
            QStandardItem* pItem = new QStandardItem(isoCode);
            rowItems << pItem;
            pItem = new QStandardItem(name);
            rowItems << pItem;
            m_iCurrencyModel->appendRow(rowItems);
            ++iter;
        }
    }
    m_iFilterModel = make_shared<QSortFilterProxyModel>(this);
    m_iFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_iFilterModel->setSourceModel(m_iCurrencyModel.get());
    ui->m_iCurrencyView->setModel(m_iFilterModel.get());
    ui->m_iCurrencyView->horizontalHeader()->setFont(QFont("Courier New", 10, QFont::Bold));
    ui->m_iCurrencyView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);//对第0列单独设置固定宽度
    ui->m_iCurrencyView->setColumnWidth(0, 50);//设置固定宽度
}

CCurrencySelectWin::~CCurrencySelectWin()
{
    delete ui;
}

CurrencyInfo *CCurrencySelectWin::Get_Selected_Currency_Info()
{
    return Get_Currency_Info(m_strCurrentCurrencyIsoCode);
}

string CCurrencySelectWin::Get_Selected_Currency_Name()
{
    qDebug() << "m_strCurrentCurrencyIsoCode=" << m_strCurrentCurrencyIsoCode.c_str();
    return Get_Currency_Name(m_strCurrentCurrencyIsoCode);
}

string CCurrencySelectWin::Get_Selected_Currency_IsoCode()
{
    return m_strCurrentCurrencyIsoCode;
}

void CCurrencySelectWin::On_SearchEdit_Changed(const QString& text)
{
    m_iFilterModel->setFilterFixedString(text);
    m_strCurrentCurrencyIsoCode = "";
    ui->m_iOkBtn->setEnabled(false);
}

void CCurrencySelectWin::On_Currency_Pressed(const QModelIndex &index)
{
    qDebug() << "select row=" << index.row() << ",colum=" << index.column();
    QModelIndex isoCodeIndex = index.sibling(index.row(), 0);
    m_strCurrentCurrencyIsoCode = m_iFilterModel->data(isoCodeIndex).toString().toStdString();
    qDebug() << "m_strCurrentCurrencyIsoCode=" << m_strCurrentCurrencyIsoCode.c_str();
    ui->m_iOkBtn->setEnabled(true);
}



/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

