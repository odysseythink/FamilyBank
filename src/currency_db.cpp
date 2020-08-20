/**
 * @file      currency_db.cpp
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/19 17:26:40:790
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
 *         1.Date         -- 2020/8/19 17:26:40:790
 *           Author       -- RW
 *           Modification -- Created file
 *
 */

#define  CURRENCY_DB_GLOBAL

/* includes-------------------------------------------------------------------*/
#include "currency_db.hh"
#include "config.hh"



    
/** @defgroup CURRENCY_DB                                            
  * @brief CURRENCY_DB system modules                                
  * @{                                                                         
  */
    
/* Private typedef&macro&definde----------------------------------------------*/





/* Private variables ---------------------------------------------------------*/
CurrencyInfo ISO4217_CURRENCIES[] =
{
    { "AED", 2, ".", ",", true, "د.إ.‏", "UAE Dirham" },
    { "AFN", 0, ",", ",", true, "؋", "Afghani" },
    { "ALL", 0, ",", " ", false, "Lekë", "Lek" },
    { "AMD", 2, ".", ",", false, "֏", "Armenian Dram" },
    { "ANG", 2, ",", ",", true, "NAf.", "Netherlands Antillian Guilder" },
    { "AOA", 2, ",", " ", false, "Kz", "Kwanza" },
    { "ARS", 2, ",", ".", true, "$", "Argentine Peso" },
    { "AUD", 2, ".", ",", true, "$", "Australian Dollar" },
    { "AWG", 2, ",", ".", true, "Afl.", "Aruban Guilder" },
    { "AZN", 2, ",", " ", true, "₼", "Azerbaijanian Manat" },
    { "BAM", 2, ",", ".", false, "KM", "Convertible Marks" },
    { "BBD", 2, ".", ",", true, "$", "Barbados Dollar" },
    { "BDT", 2, ".", ",", true, "৳", "Taka" },
    { "BGN", 2, ",", " ", false, "лв.", "Bulgarian Lev" },
    { "BHD", 3, ".", ",", true, "د.ب.‏", "Bahraini Dinar" },
    { "BIF", 0, ",", " ", false, "FBu", "Burundi Franc" },
    { "BMD", 2, ".", ",", true, "$", "Bermudian Dollar" },
    { "BND", 2, ",", ".", true, "$", "Brunei Dollar" },
    { "BOB", 2, ",", ".", true, "Bs", "Boliviano" },
    { "BOV", 2, ".", "", false, "BOV", "Mvdol" },
    { "BRL", 2, ",", ".", true, "R$", "Brazilian Real" },
    { "BSD", 2, ".", ",", true, "$", "Bahamian Dollar" },
    { "BTN", 2, ".", ",", true, "Nu.", "Ngultrum" },
    { "BWP", 2, ".", " ", true, "P", "Pula" },
    { "BYN", 0, ",", " ", false, "Br", "Belarussian Ruble" },
    { "BYR", 0, ",", " ", false, "Br", "Old Belarussian Ruble" },
    { "BZD", 2, ".", ",", true, "$", "Belize Dollar" },
    { "CAD", 2, ",", " ", true, "$", "Canadian Dollar" },
    { "CDF", 2, ",", " ", true, "FC", "Congolese Franc" },
    { "CHE", 2, ".", "", false, "CHE", "WIR Euro" },
    { "CHF", 2, ",", "'", true, "CHF", "Swiss Franc" },
    { "CHW", 2, ".", "", false, "CHW", "WIR Franc" },
    { "CLF", 2, ".", "", false, "CLF", "Unidades de fomento" },
    { "CLP", 0, ",", ".", true, "$", "Chilean Peso" },
    { "CNY", 2, ".", ",", true, "¥", "Yuan Renminbi" },
    { "COP", 0, ",", ".", true, "$", "Colombian Peso" },
    { "COU", 2, ".", "", false, "COU", "Unidad de Valor Real" },
    { "CRC", 0, ",", ".", true, "₡", "Costa Rican Colon" },
    { "CUP", 2, ".", ",", true, "$", "Cuban Peso" },
    { "CVE", 2, "$", " ", false, "​", "Cape Verde Escudo" },
    { "CYP", 2, ".", "", false, "CYP", "Cyprus Pound" },
    { "CZK", 2, ",", " ", false, "Kč", "Czech Koruna" },
    { "DJF", 0, ",", " ", true, "Fdj", "Djibouti Franc" },
    { "DKK", 2, ",", ".", true, "kr", "Danish Krone" },
    { "DOP", 2, ".", ",", true, "$", "Dominican Peso" },
    { "DZD", 2, ",", " ", false, "DA", "Algerian Dinar" },
    { "EEK", 2, ".", "", false, "EEK", "Kroon" },
    { "EGP", 2, ".", ",", true, "ج.م.‏", "Egyptian Pound" },
    { "ERN", 2, ".", ",", true, "Nfk", "Nakfa" },
    { "ETB", 2, ".", ",", true, "Br", "Ethiopian Birr" },
    { "EUR", 2, ",", " ", true, "€", "Euro" },
    { "FJD", 2, ".", ",", true, "$", "Fiji Dollar" },
    { "FKP", 2, ".", ",", true, "£", "Falkland Islands Pound" },
    { "GBP", 2, ".", ",", true, "£", "Pound Sterling" },
    { "GEL", 2, ",", " ", true, "₾", "Lari" },
    { "GHS", 2, ".", ",", true, "GH₵", "Ghana Cedi" },
    { "GIP", 2, ".", ",", true, "£", "Gibraltar Pound" },
    { "GMD", 2, ".", ",", true, "D", "Dalasi" },
    { "GNF", 0, ",", " ", true, "FG", "Guinea Franc" },
    { "GTQ", 2, ".", ",", true, "Q", "Quetzal" },
    { "GYD", 0, ".", ",", true, "$", "Guyana Dollar" },
    { "HKD", 2, ".", ",", true, "$", "Hong Kong Dollar" },
    { "HNL", 2, ".", ",", true, "L", "Lempira" },
    { "HRK", 2, ",", ".", false, "kn", "Croatian Kuna" },
    { "HTG", 2, ",", " ", false, "G", "Gourde" },
    { "HUF", 2, ",", " ", false, "HUF", "Forint" },
    { "IDR", 0, ",", ".", true, "Rp", "Rupiah" },
    { "ILS", 2, ".", ",", true, "₪", "New Israeli Sheqel" },
    { "INR", 2, ".", ",", true, "₹", "Indian Rupee" },
    { "IQD", 2, ".", ",", true, "د.ع.‏", "Iraqi Dinar" },
    { "IRR", 2, "/", ",", true, "ريال", "Iranian Rial" },
    { "ISK", 0, ",", ".", false, "ISK", "Iceland Krona" },
    { "JMD", 2, ".", ",", true, "$", "Jamaican Dollar" },
    { "JOD", 3, ".", ",", true, "د.ا.‏", "Jordanian Dinar" },
    { "JPY", 0, ".", ",", true, "¥", "Yen" },
    { "KES", 2, ".", ",", true, "Ksh", "Kenyan Shilling" },
    { "KGS", 2, ",", " ", false, "сом", "Som" },
    { "KHR", 2, ".", ",", false, "៛", "Riel" },
    { "KMF", 0, ",", " ", true, "CF", "Comoro Franc" },
    { "KPW", 2, ".", "", false, "KPW", "North Korean Won" },
    { "KRW", 0, ".", ",", true, "₩", "Won" },
    { "KWD", 3, ".", ",", true, "د.ك.‏", "Kuwaiti Dinar" },
    { "KYD", 2, ".", ",", true, "$", "Cayman Islands Dollar" },
    { "KZT", 2, ",", " ", false, "₸", "Tenge" },
    { "LAK", 0, ",", ".", true, "₭", "Kip" },
    { "LBP", 2, ".", ",", true, "ل.ل.‏", "Lebanese Pound" },
    { "LKR", 2, ".", ",", true, "Rs.", "Sri Lanka Rupee" },
    { "LRD", 2, ".", ",", true, "$", "Liberian Dollar" },
    { "LSL", 2, ".", "", false, "LSL", "Loti" },
    { "LTL", 2, ".", "", false, "LTL", "Lithuanian Litas" },
    { "LVL", 2, ".", "", false, "LVL", "Latvian Lats" },
    { "LYD", 3, ".", ",", true, "د.ل.‏", "Libyan Dinar" },
    { "MAD", 2, ",", " ", false, "DH", "Moroccan Dirham" },
    { "MDL", 2, ",", " ", false, "L", "Moldovan Leu" },
    { "MGA", 0, ",", " ", true, "Ar", "Malagasy Ariary" },
    { "MKD", 2, ",", " ", true, "den", "Denar" },
    { "MMK", 0, ".", ",", true, "K", "Kyat" },
    { "MNT", 0, ".", ",", true, "₮", "Tugrik" },
    { "MOP", 2, ",", " ", true, "MOP", "Pataca" },
    { "MRO", 0, ",", " ", true, "UM", "Ouguiya" },
    { "MTL", 2, ".", "", false, "MTL", "Maltese Lira" },
    { "MUR", 0, ",", " ", true, "Rs", "Mauritius Rupee" },
    { "MVR", 2, ".", ",", false, "ރ.", "Rufiyaa" },
    { "MWK", 2, ".", ",", true, "MK", "Kwacha" },
    { "MXN", 2, ".", ",", true, "$", "Mexican Peso" },
    { "MXV", 2, ".", "", false, "MXV", "Mexican Unidad de Inversion (UDI)" },
    { "MYR", 2, ".", ",", true, "RM", "Malaysian Ringgit" },
    { "MZN", 2, ",", " ", false, "MTn", "Metical" },
    { "NAD", 2, ",", " ", true, "$", "Namibia Dollar" },
    { "NGN", 2, ".", ",", true, "₦", "Naira" },
    { "NIO", 2, ".", ",", true, "C$", "Cordoba Oro" },
    { "NOK", 2, ",", " ", true, "kr", "Norwegian Krone" },
    { "NPR", 2, ".", ",", true, "रु", "Nepalese Rupee" },
    { "NZD", 2, ".", ",", true, "$", "New Zealand Dollar" },
    { "OMR", 3, ".", ",", true, "ر.ع.‏", "Rial Omani" },
    { "PAB", 2, ".", ",", true, "B/.", "Balboa" },
    { "PEN", 2, ".", ",", true, "S/.", "Nuevo Sol" },
    { "PGK", 2, ".", ",", true, "K", "Kina" },
    { "PHP", 2, ",", ",", true, "₱", "Philippine Peso" },
    { "PKR", 0, ".", ",", true, "Rs", "Pakistan Rupee" },
    { "PLN", 2, ",", " ", false, "zł", "Zloty" },
    { "PYG", 0, ",", ".", true, "₲", "Guarani" },
    { "QAR", 2, ".", ",", true, "ر.ق.‏", "Qatari Rial" },
    { "RON", 2, ",", ".", false, "RON", "New Leu" },
    { "RSD", 0, ",", ".", false, "RSD", "Serbian Dinar" },
    { "RUB", 2, ",", " ", true, "₽", "Russian Ruble" },
    { "RWF", 0, ",", " ", true, "RF", "Rwanda Franc" },
    { "SAR", 2, ".", ",", true, "ر.س.‏", "Saudi Riyal" },
    { "SBD", 2, ".", ",", true, "$", "Solomon Islands Dollar" },
    { "SCR", 2, ",", " ", true, "SR", "Seychelles Rupee" },
    { "SDG", 2, ".", ",", true, "SDG", "Sudanese Pound" },
    { "SEK", 2, ",", ".", false, "kr", "Swedish Krona" },
    { "SGD", 2, ".", ",", true, "$", "Singapore Dollar" },
    { "SHP", 2, ".", ",", true, "£", "Saint Helena Pound" },
    { "SLL", 0, ".", ",", true, "Le", "Leone" },
    { "SOS", 0, ".", ",", true, "S", "Somali Shilling" },
    { "SRD", 2, ",", ".", true, "$", "Surinam Dollar" },
    { "STD", 0, ",", " ", false, "Db", "Dobra" },
    { "SVC", 2, ".", "", false, "SVC", "El Salvador Colon" },
    { "SYP", 0, ",", " ", true, "LS", "Syrian Pound" },
    { "SZL", 2, ",", " ", true, "E", "Lilangeni" },
    { "THB", 2, ".", ",", true, "฿", "Baht" },
    { "TJS", 2, ",", " ", false, "смн", "Somoni" },
    { "TMM", 2, ".", "", false, "TMM", "Manat" },
    { "TND", 3, ",", " ", true, "DT", "Tunisian Dinar" },
    { "TOP", 2, ".", ",", true, "T$", "Pa'anga" },
    { "TRY", 2, ",", ".", false, "₺", "New Turkish Lira" },
    { "TTD", 2, ".", ",", true, "$", "Trinidad and Tobago Dollar" },
    { "TWD", 2, ".", ",", true, "NT$", "New Taiwan Dollar" },
    { "TZS", 0, ".", ",", true, "TSh", "Tanzanian Shilling" },
    { "UAH", 2, ",", " ", false, "₴", "Hryvnia" },
    { "UGX", 0, ".", ",", true, "USh", "Uganda Shilling" },
    { "USD", 2, ",", " ", true, "$", "US Dollar" },
    { "USN", 2, ".", "", false, "USN", "US Dollar (Next day)" },
    { "USS", 2, ".", "", false, "USS", "US Dollar (Same day)" },
    { "UYI", 2, ".", "", false, "UYI", "Uruguay Peso en Unidades Indexadas" },
    { "UYU", 2, ",", ".", true, "$", "Peso Uruguayo" },
    { "UZS", 0, ",", " ", true, "soʻm", "Uzbekistan Sum" },
    { "VEF", 2, ",", ".", true, "Bs.", "Bolivar Fuerte" },
    { "VND", 2, ",", ".", false, "₫", "Dong" },
    { "VUV", 0, ",", " ", true, "VT", "Vatu" },
    { "WST", 2, ".", ",", true, "WS$", "Tala" },
    { "XAF", 0, ",", " ", true, "FCFA", "CFA Franc BEAC" },
    { "XAG", 2, ".", "", false, "XAG", "Silver" },
    { "XAU", 2, ".", "", false, "XAU", "Gold" },
    { "XBA", 2, ".", "", false, "XBA", "European Composite Unit (EURCO)" },
    { "XBB", 2, ".", "", false, "XBB", "European Monetary Unit (E.M.U.-6)" },
    { "XBC", 2, ".", "", false, "XBC", "European Unit of Account 9 (E.U.A.-9)" },
    { "XBD", 2, ".", "", false, "XBD", "European Unit of Account 17 (E.U.A.-17)" },
    { "XCD", 2, ",", " ", true, "$", "East Caribbean Dollar" },
    { "XDR", 2, ",", " ", true, "XDR", "Special Drawing Rights" },
    { "XFO", 2, ".", "", false, "XFO", "Gold-Franc" },
    { "XFU", 2, ".", "", false, "XFU", "UIC-Franc" },
    { "XOF", 0, ",", " ", true, "CFA", "CFA Franc BCEAO" },
    { "XPD", 2, ".", "", false, "XPD", "Palladium" },
    { "XPF", 0, ",", " ", false, "FCFP", "CFP Franc" },
    { "XPT", 2, ".", "", false, "XPT", "Platinum" },
    { "XTS", 2, ".", "", false, "XTS", "Code for testing purposes" },
    { "XXX", 2, ".", "", false, "XXX", "No currency" },
    { "YER", 2, ".", ",", true, "ر.ي.‏", "Yemeni Rial" },
    { "ZAR", 2, ",", " ", true, "R", "Rand" },
    { "ZMK", 2, ".", "", false, "ZMK", "Zambian Kwacha" },
    { "ZWD", 2, ".", "", false, "ZWD", "Zimbabwe Dollar" }
};

static QMap<string, CurrencyInfo*> s_CurrenciesMap;


/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
                                                                                
/** @defgroup CURRENCY_DB_Private_Functions                          
  * @{                                                                         
  */                                                                            
                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/** @defgroup CURRENCY_DB_Global_Functions
  * @{                                                                         
  */

QString Get_Default_Currency_Name(){
    if(s_CurrenciesMap.size() == 0){
        for(uint64_t index = 0; index < (sizeof(ISO4217_CURRENCIES)/sizeof(CurrencyInfo)); index++){
            s_CurrenciesMap[ISO4217_CURRENCIES[index].curr_iso_code] = &ISO4217_CURRENCIES[index];
        }
    }
    if(s_CurrenciesMap.contains(Config::GetInstance()->Get_BaseCurrencyISOCode())){
        return QString::fromStdString(s_CurrenciesMap[Config::GetInstance()->Get_BaseCurrencyISOCode()]->name);
    }

    return "";
}

QMap<string, CurrencyInfo*>* Get_All_Currencies_Info(){
    if(s_CurrenciesMap.size() == 0){
        for(uint64_t index = 0; index < (sizeof(ISO4217_CURRENCIES)/sizeof(CurrencyInfo)); index++){
            s_CurrenciesMap[ISO4217_CURRENCIES[index].curr_iso_code] = &ISO4217_CURRENCIES[index];
        }
    }
    return &s_CurrenciesMap;
}

CurrencyInfo* Get_Currency_Info(string iso_code){
    if(s_CurrenciesMap.size() == 0){
        for(uint64_t index = 0; index < (sizeof(ISO4217_CURRENCIES)/sizeof(CurrencyInfo)); index++){
            s_CurrenciesMap[ISO4217_CURRENCIES[index].curr_iso_code] = &ISO4217_CURRENCIES[index];
        }
    }
    if(s_CurrenciesMap.contains(iso_code)){
        return s_CurrenciesMap[iso_code];
    }
    return nullptr;
}

string Get_Currency_Name(string iso_code){
    if(s_CurrenciesMap.size() == 0){
        for(uint64_t index = 0; index < (sizeof(ISO4217_CURRENCIES)/sizeof(CurrencyInfo)); index++){
            s_CurrenciesMap[ISO4217_CURRENCIES[index].curr_iso_code] = &ISO4217_CURRENCIES[index];
        }
    }
    if(s_CurrenciesMap.contains(iso_code)){
        return s_CurrenciesMap[iso_code]->name;
    }
    return "";
}
                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

