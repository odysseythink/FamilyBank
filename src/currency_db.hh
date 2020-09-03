/**
 * @file      currency_db.hh
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/19 17:26:21:249
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
 *         1.Date         -- 2020/8/19 17:26:21:249
 *           Author       -- RW
 *           Modification -- Created file
 *
 */
#ifndef __CURRENCY_DB_HH__
#define __CURRENCY_DB_HH__

#ifdef  CURRENCY_DB_GLOBAL
#define CURRENCY_DB_EXT
#else
#define CURRENCY_DB_EXT extern
#endif /* CURRENCY_DB_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <QString>
#include <QList>
#include <QPair>
#include <QMap>
#include <stdint.h>
#include <string>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>


using namespace std;

/** @addtogroup CURRENCY_DB
  * @{
  */
 
/*============================================================================*/
/*                             @MACROS & @TYPEDEFS                            */
/*============================================================================*/
struct _iso4217
{
    string   iso_code;
    uint32_t frac_digit;
    string   dec_char;
    string   grp_char;
    bool     is_prefix;
    string   symbol;
    string   name;
    double   exchange_rate;
};
typedef struct _iso4217 CurrencyInfo;



/*============================================================================*/
/*                             @GLOBAL VIRIABLES                              */
/*============================================================================*/
                                                                                
/*============================================================================*/
/*                                   @FUNCS                                   */
/*============================================================================*/
QString Get_Default_Currency_Name();
QMap<string, CurrencyInfo*>* Get_All_Currencies_Info();
CurrencyInfo* Get_Currency_Info(string iso_code);
string Get_Currency_Name(string iso_code);
bool Add_Default_Currency(string& iso_code, QString& errmsg);
bool Get_All_Currencies_IsoCode_Name_From_Db(QList<QPair<QString, QString>>& res, QString& errmsg);
bool Delete_Currency_By_IsoCode(string isoCode, QString& errmsg);
bool Update_CurrencyInfo(CurrencyInfo* pInfo, QString& errmsg);

/*============================================================================*/
/*                                   @CLASS                                   */
/*============================================================================*/
                                                                                

/**
  * @}
  */ 
		
#endif /* __CURRENCY_DB_HH__ */
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

