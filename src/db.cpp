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

void Close_Db(){
    if(s_DB.isOpen()){
        s_DB.close();
    }
}

bool Init_Db(const string& filepath, QString& errmsg)
{
    Close_Db();

    s_DB = QSqlDatabase::addDatabase("QSQLITE");
    s_DB.setDatabaseName(QString::fromStdString(filepath));

    if (!s_DB.open()){
        errmsg = s_DB.lastError().text();
        return false;
    }

    QStringList tables = s_DB.tables();
    QSqlQuery q;
    QString sql;
    if (!tables.contains("tb_system", Qt::CaseInsensitive)){
        sql = "CREATE TABLE tb_system (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, owner VARCHAR, base_currency_iso_code VARCHAR);";
        if (!q.exec(sql)){
            Close_Db();
            errmsg = q.lastError().text();
            return false;
        }
        sql = QString("INSERT INTO tb_system (id, owner, base_currency_iso_code) VALUES (1, 'admin', '%1');").arg(Config::GetInstance()->Get_BaseCurrencyISOCode().c_str());
        if (!q.exec(sql)){
            Close_Db();
            errmsg = q.lastError().text();
            return false;
        }
    }

    if (!tables.contains("tb_account", Qt::CaseInsensitive)){
        sql = "CREATE TABLE tb_account (id INTEGER PRIMARY KEY ASC AUTOINCREMENT UNIQUE, name VARCHAR (255) NOT NULL, type INTEGER NOT NULL, number VARCHAR (255), initial_balances DOUBLE DEFAULT (0.0), overdrawn_balances DOUBLE DEFAULT (0.0));";
        if (!q.exec(sql)){
            Close_Db();
            errmsg = q.lastError().text();
            return false;
        }
    }

    if (!tables.contains("tb_currency", Qt::CaseInsensitive)){
        sql = "CREATE TABLE tb_currency (id INTEGER PRIMARY KEY ASC AUTOINCREMENT, iso_code VARCHAR (10) UNIQUE NOT NULL, frac_digit INTEGER DEFAULT (2), dec_char VARCHAR (1) DEFAULT \".\", grp_char VARCHAR (1) DEFAULT \",\", is_prefix BOOLEAN DEFAULT (false), symbol VARCHAR (16), name VARCHAR (128));";
        if (!q.exec(sql)){
            Close_Db();
            errmsg = q.lastError().text();
            return false;
        }
    }
    return true;
}

bool Update_Base_Currency_Iso_Code(string& code, QString& errmsg){
    if(!s_DB.isOpen()){
        errmsg = "database is not opened";
        return false;
    }

    QString sql = QString("UPDATE tb_system SET base_currency_iso_code = '%1' WHERE id = 1;").arg(code.c_str());
    QSqlError sqlErr;
    QSqlQuery q;
    if (!q.exec(sql)){
        errmsg = q.lastError().text();
        return false;
    }
    return true;
}

bool Update_Owner(string& owner, QString& errmsg){
    if(!s_DB.isOpen()){
        errmsg = "database is not opened";
        return false;
    }

    QString sql = QString("UPDATE tb_system SET owner = '%1' WHERE id = 1;").arg(owner.c_str());
    QSqlError sqlErr;
    QSqlQuery q;
    if (!q.exec(sql)){
        errmsg = q.lastError().text();
        return false;
    }
    return true;
}

QString Get_Db_Owner(QString& errmsg){
    if(!s_DB.isOpen()){
        errmsg = "database is not opened";
        return "";
    }

    QString sql = QString("SELECT owner FROM tb_system WHERE id = 1;");
    QSqlError sqlErr;
    QSqlQuery q;

    if(q.exec(sql)){
        if (q.next()) {
            int fieldNo = q.record().indexOf("owner");
            QString owner = q.value(fieldNo).toString();
            return owner;
        }
        errmsg = "owner is not exist";
        return "";
    }
    errmsg = q.lastError().text();
    return "";
}
                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

