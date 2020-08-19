/**
 * @file      db.cpp
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/19 0:22:22:627
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
 *         1.Date         -- 2020/8/19 0:22:22:627
 *           Author       -- RW
 *           Modification -- Created file
 *
 */

#define  DB_GLOBAL

/* includes-------------------------------------------------------------------*/
#include <QDebug>
#include <glog/logging.h>
#include "db.hh"



    
/** @defgroup DB                                            
  * @brief DB system modules                                
  * @{                                                                         
  */
    
/* Private typedef&macro&definde----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static QSqlDatabase s_DB;



/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
                                                                                
/** @defgroup DB_Private_Functions                          
  * @{                                                                         
  */                                                                            
                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/** @defgroup DB_GLOBAL_Functions                          
  * @{                                                                         
  */        

QSqlError Load_Db(const string& filepath)
{
    if(s_DB.isOpen()){
        s_DB.close();
    }

    s_DB = QSqlDatabase::addDatabase("QSQLITE");
    s_DB.setDatabaseName(QString::fromStdString(filepath));

    if (!s_DB.open())
        return s_DB.lastError();

    /*
    QStringList tables = s_DB.tables();
    QSqlQuery q;
    QString sql;
    if (!tables.contains("tb_puzzle", Qt::CaseInsensitive)){
        sql = "CREATE TABLE tb_puzzle (\
                   id      INTEGER       PRIMARY KEY ASC AUTOINCREMENT\
                                         UNIQUE,\
                   level   INTEGER       DEFAULT (3),\
                   content VARCHAR (512),\
                   solved  BOOLEAN       DEFAULT (0) \
               );";
        if (!q.exec(sql)){
            return q.lastError();
        }
    }
    */

    return QSqlError();
}

                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

