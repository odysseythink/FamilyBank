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

private:
    Config();
    void __Load_Setttings();

private:
    static Config *m_iInstance;
    string m_strDbFilePath;
};
                                                                                                                                                                                                                                                                                                    
/**                                                                                                                                                                                                                    
  * @}                                                                                                                                                               
  */                                                                                                                                                                
		                                                                                                          
#endif /* __CONFIG_HH__ */                                                     
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

