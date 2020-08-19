/**
 * @file      file_properties_win.hh
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/19 16:40:2:156
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
 *         1.Date         -- 2020/8/19 16:40:2:156
 *           Author       -- RW
 *           Modification -- Created file
 *
 */
#ifndef __FILE_PROPERTIES_WIN_HH__
#define __FILE_PROPERTIES_WIN_HH__

#ifdef  FILE_PROPERTIES_WIN_GLOBAL
#define FILE_PROPERTIES_WIN_EXT
#else
#define FILE_PROPERTIES_WIN_EXT extern
#endif /* FILE_PROPERTIES_WIN_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <QDialog>



/** @addtogroup FILE_PROPERTIES_WIN
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
class CFilePropertiesWin;
}

class CFilePropertiesWin : public QDialog
{
    Q_OBJECT

public:
    explicit CFilePropertiesWin(QWidget *parent = nullptr);
    ~CFilePropertiesWin();

private:
    Ui::CFilePropertiesWin *ui;
};




/**
  * @}
  */ 
		
#endif /* __FILE_PROPERTIES_WIN_HH__ */
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

