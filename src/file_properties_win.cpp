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
#include "file_properties_win.hh"
#include "ui_file_properties_win.h"
#include "account_db.hh"
#include "currency_db.hh"
#include "currency_select_win.hh"



    
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
    ui(new Ui::CFilePropertiesWin)
{
    ui->setupUi(this);
    ui->m_iAccountTypeEdit->addItems(Get_All_Account_Type_Names());
    ui->m_iCurrencyLbl->setText(Get_Default_Currency_Name());
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
    }
}


                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

