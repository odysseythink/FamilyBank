/**
 * @file      accounts_mgr_win.hh
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/29 0:47:39:684
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
 *         1.Date         -- 2020/8/29 0:47:39:684
 *           Author       -- RW
 *           Modification -- Created file
 *
 */
#ifndef __ACCOUNTS_MGR_WIN_HH__
#define __ACCOUNTS_MGR_WIN_HH__

#ifdef  ACCOUNTS_MGR_WIN_GLOBAL
#define ACCOUNTS_MGR_WIN_EXT
#else
#define ACCOUNTS_MGR_WIN_EXT extern
#endif /* ACCOUNTS_MGR_WIN_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <QDialog>
#include <QSqlQueryModel>
#include <memory>
#include <QSqlRecord>


/** @addtogroup ACCOUNTS_MGR_WIN
  * @{
  */
 
/*============================================================================*/
/*                             @MACROS & @TYPEDEFS                            */
/*============================================================================*/
                                                                                
/*============================================================================*/
/*                             @GLOBAL VIRIABLES                              */
/*============================================================================*/
                                                                                
/*============================================================================*/
/*                                   @FUNCS                                   */
/*============================================================================*/
                                                                                
/*============================================================================*/
/*                                   @CLASS                                   */
/*============================================================================*/
namespace Ui {
class CAccountsMgrWin;
class CAccountAddWin;
}

class CAccountAddWin : public QDialog
{
    Q_OBJECT

public:
    explicit CAccountAddWin(QWidget *parent = nullptr);
    ~CAccountAddWin();

private slots:
    void __On_Accepted();

private:
    Ui::CAccountAddWin *ui;
};

class CAccountsMgrWin : public QDialog
{
    Q_OBJECT

public:
    explicit CAccountsMgrWin(QWidget *parent = nullptr);
    ~CAccountsMgrWin();

private slots:
    void __On_AccountName_Select(const QModelIndex& index);
    void __On_AccountClose_State_Changed(int stat);
    void __On_ApplyBtn_Clicked();
    void __On_AddBtn_Clicked();
    void __On_DelBtn_Clicked();

private:
    Ui::CAccountsMgrWin *ui;
    std::shared_ptr<QSqlQueryModel> m_iAccountsNameModel;
    QString m_strCurAccountName;
};




/**
  * @}
  */ 
		
#endif /* __ACCOUNTS_MGR_WIN_HH__ */
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

