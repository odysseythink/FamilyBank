/**
 * @file      config.cpp
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/18 1:25:5:629
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
 *         1.Date         -- 2020/8/18 1:25:5:629
 *           Author       -- RW
 *           Modification -- Created file
 *
 */

#define  CONFIG_GLOBAL

/* includes-------------------------------------------------------------------*/
#include <QDebug>
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <glog/logging.h>
#include "config.hh"

    
/** @defgroup CONFIG                                            
  * @brief CONFIG system modules                                
  * @{                                                                         
  */
    
/* Private typedef&macro&definde----------------------------------------------*/
#define CONFIG_FILENAME "./config.json"


/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
                                                                                
/** @defgroup CONFIG_Private_Functions                          
  * @{                                                                         
  */                                                                            
                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/** @defgroup CONFIG_CLASS_Functions                          
  * @{                                                                         
  */        

Config * Config::m_iInstance = nullptr;


Config::Config()
{
    m_bUnCache = false;
    m_strCurDbFilePath = "";
    m_strBaseCurrencyISOCode = "CNY";

    QFile jsonFile(CONFIG_FILENAME);

    if(!jsonFile.exists()){
        m_bUnCache = true;
        __Update_Setttings_To_Local();
    } else {
        __Load_Setttings_From_Local(CONFIG_FILENAME);
    }
}

void Config::__Load_Setttings_From_Local(const QString& filepath)
{
    QFile jsonFile(filepath);

    if(jsonFile.exists()){
        if(!jsonFile.open(QIODevice::ReadOnly))
        {
            LOG(WARNING) << "could't open setting json file";
            qDebug() << "could't open setting json file";
            return;
        }

        QByteArray allData = jsonFile.readAll();
        jsonFile.close();

        QJsonParseError json_error;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));

        if(json_error.error != QJsonParseError::NoError)
        {
            LOG(WARNING) << "could't parse setting json file:" << json_error.errorString().toStdString();
            qDebug() << "could't parse setting json file:" << json_error.errorString();
            return;
        }

        QJsonObject rootObj = jsonDoc.object();

        if(rootObj.contains("cur_db_filepath") && rootObj["cur_db_filepath"].isString())
        {
            m_strCurDbFilePath = rootObj.value("cur_db_filepath").toString().toStdString();
        }

        if(rootObj.contains("base_currency_iso_code") && rootObj["base_currency_iso_code"].isString())
        {
            m_strBaseCurrencyISOCode = rootObj.value("base_currency_iso_code").toString().toStdString();
        }
    }
}

void Config::__Update_Setttings_To_Local()
{
    if(!m_bUnCache){
        return;
    }

    QJsonDocument document;
    QJsonObject rootObj;


    if(m_strCurDbFilePath != ""){
        rootObj.insert("cur_db_filepath", QString::fromStdString(m_strCurDbFilePath));
    }

    if(m_strBaseCurrencyISOCode != ""){
        rootObj.insert("base_currency_iso_code", QString::fromStdString(m_strBaseCurrencyISOCode));
    }

    document.setObject(rootObj);
    QFile file(CONFIG_FILENAME);
    if (!file.open(QIODevice::WriteOnly)) {
        LOG(WARNING) << "Fail to save contents to JSON file";
        qDebug() << "Fail to save contents to JSON file";
        return;
    }

    file.write(document.toJson());
    file.close();
    m_bUnCache = false;
}



/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

