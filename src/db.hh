/**
 * @file      db.hh
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/19 0:22:10:797
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
 *         1.Date         -- 2020/8/19 0:22:10:797
 *           Author       -- RW
 *           Modification -- Created file
 *
 */
#ifndef __DB_HH__
#define __DB_HH__

#ifdef  DB_GLOBAL
#define DB_EXT
#else
#define DB_EXT extern
#endif /* DB_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <string>

using namespace std;



/** @addtogroup DB
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
void Close_Db();
bool Init_Db(const string& filepath, QString& errmsg);
bool Update_Base_Currency_Iso_Code(string& code, QString& err);
bool Update_Owner(string& owner, QString& err);
QString Get_Db_Owner(QString& errmsg);


/*============================================================================*/
/*                                   @CLASS                                   */
/*============================================================================*/
                                                                                

/**
  * @}
  */ 
		
#endif /* __DB_HH__ */
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

