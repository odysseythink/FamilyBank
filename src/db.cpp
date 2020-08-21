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
#include "config.hh"



    
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

QSqlError Init_Db(const string& filepath)
{
    if(s_DB.isOpen()){
        s_DB.close();
    }

    s_DB = QSqlDatabase::addDatabase("QSQLITE");
    s_DB.setDatabaseName(QString::fromStdString(filepath));

    if (!s_DB.open())
        return s_DB.lastError();

    QStringList tables = s_DB.tables();
    QSqlQuery q;
    QString sql;
    if (!tables.contains("tb_system", Qt::CaseInsensitive)){
        sql = "CREATE TABLE tb_system (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, owner VARCHAR, base_currency_iso_code VARCHAR);";
        if (!q.exec(sql)){
            return q.lastError();
        }
        sql = QString("INSERT INTO tb_system (id, owner, base_currency_iso_code) VALUES (1, 'admin', '%1');").arg(Config::GetInstance()->Get_BaseCurrencyISOCode().c_str());
        if (!q.exec(sql)){
            return q.lastError();
        }
    }

    if (!tables.contains("tb_account", Qt::CaseInsensitive)){
        sql = "CREATE TABLE tb_account (id INTEGER PRIMARY KEY ASC AUTOINCREMENT UNIQUE, name VARCHAR (255) NOT NULL, type INTEGER NOT NULL, number VARCHAR (255), initial_balances DOUBLE DEFAULT (0.0), overdrawn_balances DOUBLE DEFAULT (0.0));";
        if (!q.exec(sql)){
            return q.lastError();
        }
    }
    return QSqlError();
}

bool Update_Base_Currency_Iso_Code(string& code, QString& err){
    QString sql = QString("UPDATE tb_system SET base_currency_iso_code = '%1' WHERE id = 1;").arg(code.c_str());
    QSqlError sqlErr;
    QSqlQuery q;
    if (!q.exec(sql)){
        err = q.lastError().text();
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

