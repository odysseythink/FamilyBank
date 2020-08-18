/**
 * @file      version.h
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/18 21:27:56:359
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
 *         1.Date         -- 2020/8/18 21:27:56:359
 *           Author       -- RW
 *           Modification -- Created file
 *
 */
#ifndef __VERSION_H__
#define __VERSION_H__

#ifdef __cplusplus
extern "C"{
#endif /** __cplusplus */

#ifdef  VERSION_GLOBAL
#define VERSION_EXT
#else
#define VERSION_EXT extern
#endif /** VERSION_GLOBAL */

/*============================================================================*/
/*                                  @INCLUDES                                 */
/*============================================================================*/

/** @addtogroup VERSION
  * @{
  */

/*============================================================================*/
/*                            @MACROS & @TYPEDEFS                             */
/*============================================================================*/
#define APP_NAME "FamilyBank"
#define APP_VERSION "0.0.1"



/*============================================================================*/
/*                              @GLOBAL VIRIABLES                             */
/*============================================================================*/

/*============================================================================*/
/*                                    @FUNCS                                  */
/*============================================================================*/
                                                                                
#ifdef __cplusplus                                                              
}                                                                               
#endif /** __cplusplus */                                                       
                                                                                
/**
  * @}
  */ 
		
#endif /** __VERSION_H__ */                                       
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

