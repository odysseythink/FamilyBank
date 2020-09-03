/**
 * @file      payees_mgr_win.cpp
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/9/3 1:19:9:430
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
 *         1.Date         -- 2020/9/3 1:19:9:430
 *           Author       -- RW
 *           Modification -- Created file
 *
 */

#define  PAYEES_MGR_WIN_GLOBAL

/* includes-------------------------------------------------------------------*/
#include "payees_mgr_win.hh"
#include "ui_payees_mgr_win.h"


    
/** @defgroup PAYEES_MGR_WIN                                            
  * @brief PAYEES_MGR_WIN system modules                                
  * @{                                                                         
  */
    
/* Private typedef&macro&definde----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
                                                                                
/** @defgroup PAYEES_MGR_WIN_Private_Functions                          
  * @{                                                                         
  */                                                                            
                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/** @defgroup CPayeesMgrWin_CLASS_Functions                          
  * @{                                                                         
  */       

CPayeesMgrWin::CPayeesMgrWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPayeesMgrWin)
{
    ui->setupUi(this);
}

CPayeesMgrWin::~CPayeesMgrWin()
{
    delete ui;
}


                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/




