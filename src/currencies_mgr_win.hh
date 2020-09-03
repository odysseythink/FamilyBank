/**
 * @file      currencies_mgr_win.hh
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/9/3 1:15:52:273
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
 *         1.Date         -- 2020/9/3 1:15:52:273
 *           Author       -- RW
 *           Modification -- Created file
 *
 */
#ifndef __CURRENCIES_MGR_WIN_HH__
#define __CURRENCIES_MGR_WIN_HH__

#ifdef  CURRENCIES_MGR_WIN_GLOBAL
#define CURRENCIES_MGR_WIN_EXT
#else
#define CURRENCIES_MGR_WIN_EXT extern
#endif /* CURRENCIES_MGR_WIN_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <QDialog>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include "currency_db.hh"


/** @addtogroup CURRENCIES_MGR_WIN
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
class CCurrenciesMgrWin;
class CCurrencyEditWin;
}

class CCurrencyEditWin : public QDialog
{
    Q_OBJECT

public:
    explicit CCurrencyEditWin(CurrencyInfo* pInfo, string baseCurrencyIsoCode, QWidget *parent = nullptr);
    ~CCurrencyEditWin();

private:
    void __Update_Format();

private slots:
    void __On_Accepted();
    void __On_Param_Changed();

private:
    Ui::CCurrencyEditWin *ui;
    CurrencyInfo* m_iInfo;
    std::string m_strBaseCurrencyIsoCode;
};

class CCurrenciesMgrWin : public QDialog
{
    Q_OBJECT

public:
    explicit CCurrenciesMgrWin(QWidget *parent = nullptr);
    ~CCurrenciesMgrWin();

private slots:
    void __On_AddBtn_Clicked();
    void __On_EditBtn_Clicked();
    void __On_DelBtn_Clicked();
    void __On_SetAsBaseBtn_Clicked();
    void __On_Currency_Select(const QModelIndex& index);

private:
    Ui::CCurrenciesMgrWin *ui;
    std::shared_ptr<QSqlTableModel> m_iCurrenciesModel;
    std::string m_strCurCurrencyIsoCode;
    std::string m_strBaseCurrencyIsoCode;
};




/**
  * @}
  */ 
		
#endif /* __CURRENCIES_MGR_WIN_HH__ */
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

#ifndef PAYEES_MGR_WIN_HH
#define PAYEES_MGR_WIN_HH



#endif // PAYEES_MGR_WIN_HH
