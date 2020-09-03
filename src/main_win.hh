/**
 * @file      main_win.hh
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/19 0:41:29:783
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
 *         1.Date         -- 2020/8/19 0:41:29:783
 *           Author       -- RW
 *           Modification -- Created file
 *
 */
#ifndef __MAIN_WIN_HH__
#define __MAIN_WIN_HH__

#ifdef  MAIN_WIN_GLOBAL
#define MAIN_WIN_EXT
#else
#define MAIN_WIN_EXT extern
#endif /* MAIN_WIN_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <QMainWindow>


 
/** @addtogroup MAIN_WIN
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
QT_BEGIN_NAMESPACE
namespace Ui { class CMainWin; }
QT_END_NAMESPACE

class CMainWin : public QMainWindow
{
    Q_OBJECT

public:
    CMainWin(QWidget *parent = nullptr);
    ~CMainWin();

private slots:
    void On_OpenAction_Triggered();
    void On_NewAction_Triggered();
    void On_SaveAction_Triggered();
    void On_SaveAsAction_Triggered();
    void On_AccountsMgrAction_Triggered();
    void On_CurrenciesMgrAction_Triggered();

private:
    Ui::CMainWin *ui;
    bool m_bValid;
};




/**
  * @}
  */ 
		
#endif /* __MAIN_WIN_HH__ */
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

