/**
 * @file      config.hh
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/18 1:22:31:501
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
 *         1.Date         -- 2020/8/18 1:22:31:501
 *           Author       -- RW
 *           Modification -- Created file
 *
 */
#ifndef __CONFIG_HH__
#define __CONFIG_HH__

#ifdef  CONFIG_GLOBAL
#define CONFIG_EXT
#else
#define CONFIG_EXT extern
#endif /* CONFIG_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/
#include <string>
#include <QString>


using namespace std;


/** @addtogroup CONFIG
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
class Config
{
public:
    static Config* GetInstance()
    {
        if(m_iInstance == nullptr) { //判断是否第一次调用
            m_iInstance = new Config();
        }
        return m_iInstance;
    }
    string Get_DbFilePath(){
        return m_strDbFilePath;
    }
    void Set_DbFilePath(const string& filepath){
        if(m_strDbFilePath != filepath){
            m_bUnCache = true;
            m_strDbFilePath = filepath;
            __Update_Setttings_To_Local();
        }
    }

    string Get_BaseCurrencyISOCode(){
        return m_strBaseCurrencyISOCode;
    }
    void Set_BaseCurrencyISOCode(const string& code){
        if(m_strBaseCurrencyISOCode != code){
            m_bUnCache = true;
            m_strBaseCurrencyISOCode = code;
            __Update_Setttings_To_Local();
        }
    }

private:
    Config();
    void __Load_Setttings_From_Local(const QString& filepath);
    void __Update_Setttings_To_Local();

private:
    static Config *m_iInstance;
    bool m_bUnCache;
    string m_strDbFilePath;
    string m_strBaseCurrencyISOCode;
};
                                                                                                                                                                                                                                                                                                    
/**                                                                                                                                                                                                                    
  * @}                                                                                                                                                               
  */                                                                                                                                                                
		                                                                                                          
#endif /* __CONFIG_HH__ */                                                     
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

