/**
 * @file      main_win.cpp
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/19 0:41:19:693
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
 *         1.Date         -- 2020/8/19 0:41:19:693
 *           Author       -- RW
 *           Modification -- Created file
 *
 */

#define  MAIN_WIN_GLOBAL

/* includes-------------------------------------------------------------------*/
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include "main_win.hh"
#include "ui_main_win.h"
#include "db.hh"
#include "config.hh"
#include "file_properties_win.hh"
#include "version.h"



    
/** @defgroup MAIN_WIN                                            
  * @brief MAIN_WIN system modules                                
  * @{                                                                         
  */
    
/* Private typedef&macro&definde----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
                                                                                
/** @defgroup CMainWin_Private_Functions                          
  * @{                                                                         
  */                                                                            
                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/** @defgroup CMainWin_CLASS_Functions                          
  * @{                                                                         
  */     

/*
    菜单：
        - 视图
        - 管理
          - 账户
          - 交易人
          - 类别
          - 计划/模板
          - 预算
          - 归类
          - 货币
          - Tags
        - 记账
          - 添加
          - 显示
          - Show all...
          - 配置计划
          - Post scheduled
        - 报表
          - 统计
          - 走势
          - 余额
          - 预算
          - 汽车花费
        - 工具
          - 显示欢迎窗口
          - 信息统计
          - 匿名
        - 帮助
          - 帮助内容
          - 获取在线帮助
          - check the update
          - Release Notes
          - 报告问题
          - 翻译这个程序
          - 关于

*/

CMainWin::CMainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWin)
{
    ui->setupUi(this);
    m_bValid = false;
    QString winTitle = QString::asprintf("%s - v%s",APP_NAME, APP_VERSION);
    if(Config::GetInstance()->Get_CurDbFilePath() != ""){
        QFile dbFile(Config::GetInstance()->Get_CurDbFilePath().c_str());
        if(!dbFile.exists()){
            QMessageBox::critical(nullptr, "Unable to load database", "database file :" + QString::fromStdString(Config::GetInstance()->Get_CurDbFilePath()) + " not exist");
            return;           
        }

        QString errmsg;
        bool isOk = Init_Db(Config::GetInstance()->Get_CurDbFilePath(), errmsg);
        if(!isOk) {
            QMessageBox::critical(nullptr, "Unable to load database",
                        "Error load database: " + errmsg);
            return;
        }

        QString owner = Get_Db_Owner(errmsg);
        if(owner == ""){
            QMessageBox::critical(nullptr, "Unable to get owner of database",
                        "Error get owner of database: " + errmsg);
            return;
        }
        QFileInfo fileInfo(Config::GetInstance()->Get_CurDbFilePath().c_str());
        winTitle = fileInfo.fileName() + " - " + owner + " - " + winTitle;
    }
    m_bValid = true;
    setWindowTitle(winTitle);
}

CMainWin::~CMainWin()
{
    delete ui;
}

void CMainWin::On_OpenAction_Triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("选择数据库文件"), ".", tr("database Files(*.db)"));
    if(path.length() == 0) {
        QMessageBox::information(NULL, tr("数据库文件"), tr("你没有选择任何数据库文件."));
    } else {
        QString errmsg;
        if (!Init_Db(path.toStdString(), errmsg)) {
            QMessageBox::critical(nullptr, tr("无法加载数据库"),
                        "加载数据库失败: " + errmsg);
            m_bValid = false;
            return;
        }
        m_bValid = true;
    }
}

void CMainWin::On_NewAction_Triggered()
{
    std::shared_ptr<CFilePropertiesWin> pWin = std::make_shared<CFilePropertiesWin>(this);
    if(pWin->exec() == QDialog::Accepted){
        QString winTitle = QString::asprintf("%s - v%s",APP_NAME, APP_VERSION);
        if(Config::GetInstance()->Get_CurDbFilePath() != ""){
            QFileInfo fileInfo(Config::GetInstance()->Get_CurDbFilePath().c_str());
            QString errmsg;
            QString owner = Get_Db_Owner(errmsg);
            if(owner == ""){
                QMessageBox::critical(nullptr, "Unable to get owner of database",
                            "Error get owner of database: " + errmsg);
                winTitle = fileInfo.fileName() + " - " + winTitle;
            } else {

                winTitle = fileInfo.fileName() + " - " + owner + " - " + winTitle;
            }
        }
        LOG(INFO) << "On_NewAction_Triggered winTitle=" << winTitle.toStdString();
        setWindowTitle(winTitle);
    }
}

void CMainWin::On_SaveAction_Triggered()
{

}

void CMainWin::On_SaveAsAction_Triggered()
{

}


                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

