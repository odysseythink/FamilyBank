/**
 * @file      payees_mgr_win.hh
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/9/3 1:18:41:131
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
 *         1.Date         -- 2020/9/3 1:18:41:131
 *           Author       -- RW
 *           Modification -- Created file
 *
 */
#ifndef __PAYEES_MGR_WIN_HH__
#define __PAYEES_MGR_WIN_HH__

#ifdef  PAYEES_MGR_WIN_GLOBAL
#define PAYEES_MGR_WIN_EXT
#else
#define PAYEES_MGR_WIN_EXT extern
#endif /* PAYEES_MGR_WIN_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <QDialog>



 
/** @addtogroup PAYEES_MGR_WIN
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
class CPayeesMgrWin;
}

class CPayeesMgrWin : public QDialog
{
    Q_OBJECT

public:
    explicit CPayeesMgrWin(QWidget *parent = nullptr);
    ~CPayeesMgrWin();

private:
    Ui::CPayeesMgrWin *ui;
};




/**
  * @}
  */ 
		
#endif /* __PAYEES_MGR_WIN_HH__ */
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

