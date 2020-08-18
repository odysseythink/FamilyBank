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
#include "config.hh"
    
/** @defgroup CONFIG                                            
  * @brief CONFIG system modules                                
  * @{                                                                         
  */
    
/* Private typedef&macro&definde----------------------------------------------*/

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
    m_strDbFilePath = "";
}

void Config::__Load_Setttings()
{
    QFile loadFile("./config/config.json");
    if(!loadFile.exists()){

    }

    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
        return;
    }

    QByteArray allData = loadFile.readAll();
    loadFile.close();

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));

    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!";
        return;
    }

    QJsonObject rootObj = jsonDoc.object();

    QStringList keys = rootObj.keys();
    for(int i = 0; i < keys.size(); i++)
    {
        qDebug() << "key" << i << " is:" << keys.at(i);
    }

    //因为是预先定义好的JSON数据格式，所以这里可以这样读取
    if(rootObj.contains("first fruit"))
    {
       QJsonObject subObj = rootObj.value("first fruit").toObject();
       qDebug() << "describe is:" << subObj["describe"].toString();
       qDebug() << "icon is:" << subObj["icon"].toString();
       qDebug() << "name is:" << subObj["name"].toString();
    }

    if(rootObj.contains("second fruit"))
    {
       QJsonObject subObj = rootObj.value("second fruit").toObject();
       qDebug() << "describe is:" << subObj.value("describe").toString();
       qDebug() << "icon is:" << subObj.value("icon").toString();
       qDebug() << "name is:" << subObj.value("name").toString();
    }

    if(rootObj.contains("three fruit array"))
    {
       QJsonArray subArray = rootObj.value("three fruit array").toArray();
       for(int i = 0; i< subArray.size(); i++)
       {
           qDebug() << i<<" value is:" << subArray.at(i).toString();
       }
    }
}



/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

