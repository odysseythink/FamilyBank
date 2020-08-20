/**
 * @file      currency_select_win.hh
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/19 18:7:36:114
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
 *         1.Date         -- 2020/8/19 18:7:36:114
 *           Author       -- RW
 *           Modification -- Created file
 *
 */
#ifndef __CURRENCY_SELECT_WIN_HH__
#define __CURRENCY_SELECT_WIN_HH__

#ifdef  CURRENCY_SELECT_WIN_GLOBAL
#define CURRENCY_SELECT_WIN_EXT
#else
#define CURRENCY_SELECT_WIN_EXT extern
#endif /* CURRENCY_SELECT_WIN_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <QDialog>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <memory>
#include "currency_db.hh"

using namespace std;

 
/** @addtogroup CURRENCY_SELECT_WIN
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
class CCurrencySelectWin;
}

class CCurrencySelectWin : public QDialog
{
    Q_OBJECT

public:
    explicit CCurrencySelectWin(QWidget *parent = nullptr);
    ~CCurrencySelectWin();
    CurrencyInfo* Get_Selected_Currency_Info();
    string Get_Selected_Currency_Name();
    string Get_Selected_Currency_IsoCode();

private slots:
    void On_SearchEdit_Changed(const QString& text);
    void On_Currency_Pressed(const QModelIndex &index);


private:
    Ui::CCurrencySelectWin *ui;
    shared_ptr<QStandardItemModel> m_iCurrencyModel;
    shared_ptr<QSortFilterProxyModel> m_iFilterModel;
    string m_strCurrentCurrencyIsoCode;
};




/**
  * @}
  */ 
		
#endif /* __CURRENCY_SELECT_WIN_HH__ */
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

