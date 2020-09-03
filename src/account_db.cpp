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

bool Add_Account(AccountInfo* pInfo, QString& err){
    if(pInfo == nullptr){
        err = "invalid arg";
        return false;
    }
    QString sql = QString::asprintf("INSERT INTO tb_account (name,type,currency_iso_code, start_balance, instution_name, instution_num, overdraft_balance)\
                                     VALUES ('%s', %d, '%s', %f, '%s', '%s', %f);",
                                    pInfo->name.c_str(), pInfo->type, pInfo->currency_iso_code.c_str(),
                                    pInfo->start_balance, pInfo->instution_name.c_str(), pInfo->instution_num.c_str(),
                                    pInfo->overdraft_balance);
    QSqlError sqlErr;
    QSqlQuery q;
    if (!q.exec(sql)){
        err = q.lastError().text();
        return false;
    }
    return true;
}

bool Get_AccountInfo_By_Name(AccountInfo* pInfo, string name, QString& errmsg){
    if(pInfo == nullptr || name == ""){
        errmsg = "invalid arg";
        return false;
    }
    QString sql = QString::asprintf("SELECT name,type,currency_iso_code,start_balance,\
                                     remark,close,instution_name,instution_num,\
                                     overdraft_balance FROM tb_account WHERE name='%s';", name.c_str());

    LOG(INFO) << "sql:" << sql.toStdString();
    QSqlQuery q;
    if(q.exec(sql)){
        if (q.next()) {
            int fieldNo = q.record().indexOf("name");
            pInfo->name = q.value(fieldNo).toString().toStdString();
            fieldNo = q.record().indexOf("type");
            pInfo->type = q.value(fieldNo).toUInt();
            fieldNo = q.record().indexOf("currency_iso_code");
            pInfo->currency_iso_code = q.value(fieldNo).toString().toStdString();
            fieldNo = q.record().indexOf("start_balance");
            pInfo->start_balance = q.value(fieldNo).toDouble();
            fieldNo = q.record().indexOf("remark");
            pInfo->remark = q.value(fieldNo).toString().toStdString();
            fieldNo = q.record().indexOf("close");
            pInfo->close = q.value(fieldNo).toBool();
            fieldNo = q.record().indexOf("instution_name");
            pInfo->instution_name = q.value(fieldNo).toString().toStdString();
            fieldNo = q.record().indexOf("instution_num");
            pInfo->instution_num = q.value(fieldNo).toString().toStdString();
            fieldNo = q.record().indexOf("overdraft_balance");
            pInfo->overdraft_balance = q.value(fieldNo).toDouble();
            return true;
        }
        LOG(WARNING) << "Get_AccountInfo_By_Name no record";
        errmsg = "no record";
        return false;
    }
    LOG(WARNING) << "Get_AccountInfo_By_Name error:" << q.lastError().text().toStdString();
    errmsg = q.lastError().text();
    return false;
}

bool Update_AccountInfo(AccountInfo* pInfo, QString& errmsg){
    if(pInfo == nullptr){
        errmsg = "invalid arg";
        return false;
    }
    QString sql = QString::asprintf("UPDATE tb_account SET type=%d,currency_iso_code='%s',start_balance=%f,\
                                     remark='%s',close=%d,instution_name='%s',instution_num='%s',\
                                     overdraft_balance=%f WHERE name='%s';",
                                     pInfo->type, pInfo->currency_iso_code.c_str(),pInfo->start_balance,
                                     pInfo->remark.c_str(), pInfo->close, pInfo->instution_name.c_str(),
                                     pInfo->instution_num.c_str(), pInfo->overdraft_balance,
                                     pInfo->name.c_str());

    LOG(INFO) << "sql:" << sql.toStdString();
    QSqlQuery q;
    if (!q.exec(sql)){
        errmsg = q.lastError().text();
        return false;
    }
    return true;
}

bool Delete_Account_By_Name(string name, QString& errmsg){
    QString sql = QString::asprintf("DELETE FROM tb_account WHERE name='%s';", name.c_str());

    LOG(INFO) << "sql:" << sql.toStdString();
    QSqlQuery q;
    if (!q.exec(sql)){
        errmsg = q.lastError().text();
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

