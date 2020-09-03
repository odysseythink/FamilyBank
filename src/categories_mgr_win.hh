/**
 * @file      categories_mgr_win.hh
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/9/3 1:13:10:754
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
 *         1.Date         -- 2020/9/3 1:13:10:754
 *           Author       -- RW
 *           Modification -- Created file
 *
 */
#ifndef __CATEGORIES_MGR_WIN_HH__
#define __CATEGORIES_MGR_WIN_HH__

#ifdef  CATEGORIES_MGR_WIN_GLOBAL
#define CATEGORIES_MGR_WIN_EXT
#else
#define CATEGORIES_MGR_WIN_EXT extern
#endif /* CATEGORIES_MGR_WIN_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
 
/** @addtogroup CATEGORIES_MGR_WIN
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
#include <QDialog>

namespace Ui {
class CCategoriesMgrWin;
}

class CCategoriesMgrWin : public QDialog
{
    Q_OBJECT

public:
    explicit CCategoriesMgrWin(QWidget *parent = nullptr);
    ~CCategoriesMgrWin();

private:
    Ui::CCategoriesMgrWin *ui;
};
                                                                                



/**
  * @}
  */ 
		
#endif /* __CATEGORIES_MGR_WIN_HH__ */
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

