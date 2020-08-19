/**
 * @file      account_db.hh
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/19 16:27:41:994
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
 *         1.Date         -- 2020/8/19 16:27:41:994
 *           Author       -- RW
 *           Modification -- Created file
 *
 */
#ifndef __ACCOUNT_DB_HH__
#define __ACCOUNT_DB_HH__

#ifdef  ACCOUNT_DB_GLOBAL
#define ACCOUNT_DB_EXT
#else
#define ACCOUNT_DB_EXT extern
#endif /* ACCOUNT_DB_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <QStringList>





/** @addtogroup ACCOUNT_DB
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
QStringList Get_All_Account_Type_Names();



/*============================================================================*/
/*                                   @CLASS                                   */
/*============================================================================*/
                                                                                

/**
  * @}
  */ 
		
#endif /* __ACCOUNT_DB_HH__ */
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

