/**
 * @file      account_db.cpp
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/19 16:27:55:965
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
 *         1.Date         -- 2020/8/19 16:27:55:965
 *           Author       -- RW
 *           Modification -- Created file
 *
 */

#define  ACCOUNT_DB_GLOBAL

/* includes-------------------------------------------------------------------*/
#include "account_db.hh"
    
/** @defgroup ACCOUNT_DB                                            
  * @brief ACCOUNT_DB system modules                                
  * @{                                                                         
  */
    
/* Private typedef&macro&definde----------------------------------------------*/



/* Private variables ---------------------------------------------------------*/
const char* ACCOUNT_TYPE_NAMES[] = {
    "银行",
    "现金",
    "资产",
    "信用卡",
    "负债",
};


/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
                                                                                
/** @defgroup ACCOUNT_DB_Private_Functions                          
  * @{                                                                         
  */                                                                            
                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/** @defgroup ACCOUNT_DB_Global_Functions                          
  * @{                                                                         
  */        

QStringList Get_All_Account_Type_Names(){
    QStringList res;
    for(auto v : ACCOUNT_TYPE_NAMES){
        res << QString(v);
    }
    return res;
}
                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

