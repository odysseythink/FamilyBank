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
#include <QDateTime>
#include <glog/logging.h>
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
    { "AED", 2, ".", ",", true, "د.إ.‏", "UAE Dirham",0.},
    { "AFN", 0, ",", ",", true, "؋", "Afghani",0.},
    { "ALL", 0, ",", " ", false, "Lekë", "Lek",0.},
    { "AMD", 2, ".", ",", false, "֏", "Armenian Dram",0.},
    { "ANG", 2, ",", ",", true, "NAf.", "Netherlands Antillian Guilder",0.},
    { "AOA", 2, ",", " ", false, "Kz", "Kwanza",0.},
    { "ARS", 2, ",", ".", true, "$", "Argentine Peso",0.},
    { "AUD", 2, ".", ",", true, "$", "Australian Dollar",0.},
    { "AWG", 2, ",", ".", true, "Afl.", "Aruban Guilder",0.},
    { "AZN", 2, ",", " ", true, "₼", "Azerbaijanian Manat",0.},
    { "BAM", 2, ",", ".", false, "KM", "Convertible Marks",0.},
    { "BBD", 2, ".", ",", true, "$", "Barbados Dollar",0.},
    { "BDT", 2, ".", ",", true, "৳", "Taka",0.},
    { "BGN", 2, ",", " ", false, "лв.", "Bulgarian Lev",0.},
    { "BHD", 3, ".", ",", true, "د.ب.‏", "Bahraini Dinar",0.},
    { "BIF", 0, ",", " ", false, "FBu", "Burundi Franc",0.},
    { "BMD", 2, ".", ",", true, "$", "Bermudian Dollar",0.},
    { "BND", 2, ",", ".", true, "$", "Brunei Dollar",0.},
    { "BOB", 2, ",", ".", true, "Bs", "Boliviano",0.},
    { "BOV", 2, ".", "", false, "BOV", "Mvdol",0.},
    { "BRL", 2, ",", ".", true, "R$", "Brazilian Real",0.},
    { "BSD", 2, ".", ",", true, "$", "Bahamian Dollar",0.},
    { "BTN", 2, ".", ",", true, "Nu.", "Ngultrum",0.},
    { "BWP", 2, ".", " ", true, "P", "Pula",0.},
    { "BYN", 0, ",", " ", false, "Br", "Belarussian Ruble",0.},
    { "BYR", 0, ",", " ", false, "Br", "Old Belarussian Ruble",0.},
    { "BZD", 2, ".", ",", true, "$", "Belize Dollar",0.},
    { "CAD", 2, ",", " ", true, "$", "Canadian Dollar",0.},
    { "CDF", 2, ",", " ", true, "FC", "Congolese Franc",0.},
    { "CHE", 2, ".", "", false, "CHE", "WIR Euro",0.},
    { "CHF", 2, ",", "'", true, "CHF", "Swiss Franc",0.},
    { "CHW", 2, ".", "", false, "CHW", "WIR Franc",0.},
    { "CLF", 2, ".", "", false, "CLF", "Unidades de fomento",0.},
    { "CLP", 0, ",", ".", true, "$", "Chilean Peso",0.},
    { "CNY", 2, ".", ",", true, "¥", "Yuan Renminbi",0.},
    { "COP", 0, ",", ".", true, "$", "Colombian Peso",0.},
    { "COU", 2, ".", "", false, "COU", "Unidad de Valor Real",0.},
    { "CRC", 0, ",", ".", true, "₡", "Costa Rican Colon",0.},
    { "CUP", 2, ".", ",", true, "$", "Cuban Peso",0.},
    { "CVE", 2, "$", " ", false, "​", "Cape Verde Escudo",0.},
    { "CYP", 2, ".", "", false, "CYP", "Cyprus Pound",0.},
    { "CZK", 2, ",", " ", false, "Kč", "Czech Koruna",0.},
    { "DJF", 0, ",", " ", true, "Fdj", "Djibouti Franc",0.},
    { "DKK", 2, ",", ".", true, "kr", "Danish Krone",0.},
    { "DOP", 2, ".", ",", true, "$", "Dominican Peso",0.},
    { "DZD", 2, ",", " ", false, "DA", "Algerian Dinar",0.},
    { "EEK", 2, ".", "", false, "EEK", "Kroon",0.},
    { "EGP", 2, ".", ",", true, "ج.م.‏", "Egyptian Pound",0.},
    { "ERN", 2, ".", ",", true, "Nfk", "Nakfa",0.},
    { "ETB", 2, ".", ",", true, "Br", "Ethiopian Birr",0.},
    { "EUR", 2, ",", " ", true, "€", "Euro",0.},
    { "FJD", 2, ".", ",", true, "$", "Fiji Dollar",0.},
    { "FKP", 2, ".", ",", true, "£", "Falkland Islands Pound",0.},
    { "GBP", 2, ".", ",", true, "£", "Pound Sterling",0.},
    { "GEL", 2, ",", " ", true, "₾", "Lari",0.},
    { "GHS", 2, ".", ",", true, "GH₵", "Ghana Cedi",0.},
    { "GIP", 2, ".", ",", true, "£", "Gibraltar Pound",0.},
    { "GMD", 2, ".", ",", true, "D", "Dalasi",0.},
    { "GNF", 0, ",", " ", true, "FG", "Guinea Franc",0.},
    { "GTQ", 2, ".", ",", true, "Q", "Quetzal",0.},
    { "GYD", 0, ".", ",", true, "$", "Guyana Dollar",0.},
    { "HKD", 2, ".", ",", true, "$", "Hong Kong Dollar",0.},
    { "HNL", 2, ".", ",", true, "L", "Lempira",0.},
    { "HRK", 2, ",", ".", false, "kn", "Croatian Kuna",0.},
    { "HTG", 2, ",", " ", false, "G", "Gourde",0.},
    { "HUF", 2, ",", " ", false, "HUF", "Forint",0.},
    { "IDR", 0, ",", ".", true, "Rp", "Rupiah",0.},
    { "ILS", 2, ".", ",", true, "₪", "New Israeli Sheqel",0.},
    { "INR", 2, ".", ",", true, "₹", "Indian Rupee",0.},
    { "IQD", 2, ".", ",", true, "د.ع.‏", "Iraqi Dinar",0.},
    { "IRR", 2, "/", ",", true, "ريال", "Iranian Rial",0.},
    { "ISK", 0, ",", ".", false, "ISK", "Iceland Krona",0.},
    { "JMD", 2, ".", ",", true, "$", "Jamaican Dollar",0.},
    { "JOD", 3, ".", ",", true, "د.ا.‏", "Jordanian Dinar",0.},
    { "JPY", 0, ".", ",", true, "¥", "Yen",0.},
    { "KES", 2, ".", ",", true, "Ksh", "Kenyan Shilling",0.},
    { "KGS", 2, ",", " ", false, "сом", "Som",0.},
    { "KHR", 2, ".", ",", false, "៛", "Riel",0.},
    { "KMF", 0, ",", " ", true, "CF", "Comoro Franc",0.},
    { "KPW", 2, ".", "", false, "KPW", "North Korean Won",0.},
    { "KRW", 0, ".", ",", true, "₩", "Won",0.},
    { "KWD", 3, ".", ",", true, "د.ك.‏", "Kuwaiti Dinar",0.},
    { "KYD", 2, ".", ",", true, "$", "Cayman Islands Dollar",0.},
    { "KZT", 2, ",", " ", false, "₸", "Tenge",0.},
    { "LAK", 0, ",", ".", true, "₭", "Kip",0.},
    { "LBP", 2, ".", ",", true, "ل.ل.‏", "Lebanese Pound",0.},
    { "LKR", 2, ".", ",", true, "Rs.", "Sri Lanka Rupee",0.},
    { "LRD", 2, ".", ",", true, "$", "Liberian Dollar",0.},
    { "LSL", 2, ".", "", false, "LSL", "Loti",0.},
    { "LTL", 2, ".", "", false, "LTL", "Lithuanian Litas",0.},
    { "LVL", 2, ".", "", false, "LVL", "Latvian Lats",0.},
    { "LYD", 3, ".", ",", true, "د.ل.‏", "Libyan Dinar",0.},
    { "MAD", 2, ",", " ", false, "DH", "Moroccan Dirham",0.},
    { "MDL", 2, ",", " ", false, "L", "Moldovan Leu",0.},
    { "MGA", 0, ",", " ", true, "Ar", "Malagasy Ariary",0.},
    { "MKD", 2, ",", " ", true, "den", "Denar",0.},
    { "MMK", 0, ".", ",", true, "K", "Kyat",0.},
    { "MNT", 0, ".", ",", true, "₮", "Tugrik",0.},
    { "MOP", 2, ",", " ", true, "MOP", "Pataca",0.},
    { "MRO", 0, ",", " ", true, "UM", "Ouguiya",0.},
    { "MTL", 2, ".", "", false, "MTL", "Maltese Lira",0.},
    { "MUR", 0, ",", " ", true, "Rs", "Mauritius Rupee",0.},
    { "MVR", 2, ".", ",", false, "ރ.", "Rufiyaa",0.},
    { "MWK", 2, ".", ",", true, "MK", "Kwacha",0.},
    { "MXN", 2, ".", ",", true, "$", "Mexican Peso",0.},
    { "MXV", 2, ".", "", false, "MXV", "Mexican Unidad de Inversion (UDI)",0.},
    { "MYR", 2, ".", ",", true, "RM", "Malaysian Ringgit",0.},
    { "MZN", 2, ",", " ", false, "MTn", "Metical",0.},
    { "NAD", 2, ",", " ", true, "$", "Namibia Dollar",0.},
    { "NGN", 2, ".", ",", true, "₦", "Naira",0.},
    { "NIO", 2, ".", ",", true, "C$", "Cordoba Oro",0.},
    { "NOK", 2, ",", " ", true, "kr", "Norwegian Krone",0.},
    { "NPR", 2, ".", ",", true, "रु", "Nepalese Rupee",0.},
    { "NZD", 2, ".", ",", true, "$", "New Zealand Dollar",0.},
    { "OMR", 3, ".", ",", true, "ر.ع.‏", "Rial Omani",0.},
    { "PAB", 2, ".", ",", true, "B/.", "Balboa",0.},
    { "PEN", 2, ".", ",", true, "S/.", "Nuevo Sol",0.},
    { "PGK", 2, ".", ",", true, "K", "Kina",0.},
    { "PHP", 2, ",", ",", true, "₱", "Philippine Peso",0.},
    { "PKR", 0, ".", ",", true, "Rs", "Pakistan Rupee",0.},
    { "PLN", 2, ",", " ", false, "zł", "Zloty",0.},
    { "PYG", 0, ",", ".", true, "₲", "Guarani",0.},
    { "QAR", 2, ".", ",", true, "ر.ق.‏", "Qatari Rial",0.},
    { "RON", 2, ",", ".", false, "RON", "New Leu",0.},
    { "RSD", 0, ",", ".", false, "RSD", "Serbian Dinar",0.},
    { "RUB", 2, ",", " ", true, "₽", "Russian Ruble",0.},
    { "RWF", 0, ",", " ", true, "RF", "Rwanda Franc",0.},
    { "SAR", 2, ".", ",", true, "ر.س.‏", "Saudi Riyal",0.},
    { "SBD", 2, ".", ",", true, "$", "Solomon Islands Dollar",0.},
    { "SCR", 2, ",", " ", true, "SR", "Seychelles Rupee",0.},
    { "SDG", 2, ".", ",", true, "SDG", "Sudanese Pound",0.},
    { "SEK", 2, ",", ".", false, "kr", "Swedish Krona",0.},
    { "SGD", 2, ".", ",", true, "$", "Singapore Dollar",0.},
    { "SHP", 2, ".", ",", true, "£", "Saint Helena Pound",0.},
    { "SLL", 0, ".", ",", true, "Le", "Leone",0.},
    { "SOS", 0, ".", ",", true, "S", "Somali Shilling",0.},
    { "SRD", 2, ",", ".", true, "$", "Surinam Dollar",0.},
    { "STD", 0, ",", " ", false, "Db", "Dobra",0.},
    { "SVC", 2, ".", "", false, "SVC", "El Salvador Colon",0.},
    { "SYP", 0, ",", " ", true, "LS", "Syrian Pound",0.},
    { "SZL", 2, ",", " ", true, "E", "Lilangeni",0.},
    { "THB", 2, ".", ",", true, "฿", "Baht",0.},
    { "TJS", 2, ",", " ", false, "смн", "Somoni",0.},
    { "TMM", 2, ".", "", false, "TMM", "Manat",0.},
    { "TND", 3, ",", " ", true, "DT", "Tunisian Dinar",0.},
    { "TOP", 2, ".", ",", true, "T$", "Pa'anga",0.},
    { "TRY", 2, ",", ".", false, "₺", "New Turkish Lira",0.},
    { "TTD", 2, ".", ",", true, "$", "Trinidad and Tobago Dollar",0.},
    { "TWD", 2, ".", ",", true, "NT$", "New Taiwan Dollar",0.},
    { "TZS", 0, ".", ",", true, "TSh", "Tanzanian Shilling",0.},
    { "UAH", 2, ",", " ", false, "₴", "Hryvnia",0.},
    { "UGX", 0, ".", ",", true, "USh", "Uganda Shilling",0.},
    { "USD", 2, ",", " ", true, "$", "US Dollar",0.},
    { "USN", 2, ".", "", false, "USN", "US Dollar (Next day)",0.},
    { "USS", 2, ".", "", false, "USS", "US Dollar (Same day)",0.},
    { "UYI", 2, ".", "", false, "UYI", "Uruguay Peso en Unidades Indexadas",0.},
    { "UYU", 2, ",", ".", true, "$", "Peso Uruguayo",0.},
    { "UZS", 0, ",", " ", true, "soʻm", "Uzbekistan Sum",0.},
    { "VEF", 2, ",", ".", true, "Bs.", "Bolivar Fuerte",0.},
    { "VND", 2, ",", ".", false, "₫", "Dong",0.},
    { "VUV", 0, ",", " ", true, "VT", "Vatu",0.},
    { "WST", 2, ".", ",", true, "WS$", "Tala",0.},
    { "XAF", 0, ",", " ", true, "FCFA", "CFA Franc BEAC",0.},
    { "XAG", 2, ".", "", false, "XAG", "Silver",0.},
    { "XAU", 2, ".", "", false, "XAU", "Gold",0.},
    { "XBA", 2, ".", "", false, "XBA", "European Composite Unit (EURCO)",0.},
    { "XBB", 2, ".", "", false, "XBB", "European Monetary Unit (E.M.U.-6)",0.},
    { "XBC", 2, ".", "", false, "XBC", "European Unit of Account 9 (E.U.A.-9)",0.},
    { "XBD", 2, ".", "", false, "XBD", "European Unit of Account 17 (E.U.A.-17)",0.},
    { "XCD", 2, ",", " ", true, "$", "East Caribbean Dollar",0.},
    { "XDR", 2, ",", " ", true, "XDR", "Special Drawing Rights",0.},
    { "XFO", 2, ".", "", false, "XFO", "Gold-Franc",0.},
    { "XFU", 2, ".", "", false, "XFU", "UIC-Franc",0.},
    { "XOF", 0, ",", " ", true, "CFA", "CFA Franc BCEAO",0.},
    { "XPD", 2, ".", "", false, "XPD", "Palladium",0.},
    { "XPF", 0, ",", " ", false, "FCFP", "CFP Franc",0.},
    { "XPT", 2, ".", "", false, "XPT", "Platinum",0.},
    { "XTS", 2, ".", "", false, "XTS", "Code for testing purposes",0.},
    { "XXX", 2, ".", "", false, "XXX", "No currency",0.},
    { "YER", 2, ".", ",", true, "ر.ي.‏", "Yemeni Rial",0.},
    { "ZAR", 2, ",", " ", true, "R", "Rand",0.},
    { "ZMK", 2, ".", "", false, "ZMK", "Zambian Kwacha",0.},
    { "ZWD", 2, ".", "", false, "ZWD", "Zimbabwe Dollar",0.}
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
            s_CurrenciesMap[ISO4217_CURRENCIES[index].iso_code] = &ISO4217_CURRENCIES[index];
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
            s_CurrenciesMap[ISO4217_CURRENCIES[index].iso_code] = &ISO4217_CURRENCIES[index];
        }
    }
    return &s_CurrenciesMap;
}

CurrencyInfo* Get_Currency_Info(string iso_code){
    if(s_CurrenciesMap.size() == 0){
        for(uint64_t index = 0; index < (sizeof(ISO4217_CURRENCIES)/sizeof(CurrencyInfo)); index++){
            s_CurrenciesMap[ISO4217_CURRENCIES[index].iso_code] = &ISO4217_CURRENCIES[index];
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
            s_CurrenciesMap[ISO4217_CURRENCIES[index].iso_code] = &ISO4217_CURRENCIES[index];
        }
    }
    if(s_CurrenciesMap.contains(iso_code)){
        return s_CurrenciesMap[iso_code]->name;
    }
    return "";
}

bool Add_Default_Currency(string& iso_code, QString& errmsg){
    if(s_CurrenciesMap.size() == 0){
        for(uint64_t index = 0; index < (sizeof(ISO4217_CURRENCIES)/sizeof(CurrencyInfo)); index++){
            s_CurrenciesMap[ISO4217_CURRENCIES[index].iso_code] = &ISO4217_CURRENCIES[index];
        }
    }

    CurrencyInfo* pInfo = nullptr;
    if(s_CurrenciesMap.contains(iso_code)){
        pInfo = s_CurrenciesMap[iso_code];
    }
    if(pInfo == nullptr){
        errmsg = QString::fromStdString(iso_code) + " not exist";
        return false;
    }
    string timestamp = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss").toStdString();
    QString sql = QString::asprintf("INSERT INTO tb_currency (iso_code,frac_digit,dec_char,"
                                    "grp_char,is_prefix,symbol,name,create_time) "
                                    "VALUES ('%s', %d, '%s', '%s', %d,'%s','%s', '%s');",
                                    pInfo->iso_code.c_str(),pInfo->frac_digit,
                                    pInfo->dec_char.c_str(),pInfo->grp_char.c_str(),
                                    pInfo->is_prefix,pInfo->symbol.c_str(),pInfo->name.c_str(),
                                    timestamp.c_str());
    QSqlError sqlErr;
    QSqlQuery q;
    LOG(INFO) << "sql=" << sql.toStdString();
    if (!q.exec(sql)){
        errmsg = q.lastError().text();
        return false;
    }
    LOG(INFO) << "Add_Default_Currency success";
    return true;
}

bool Get_All_Currencies_IsoCode_Name_From_Db(QList<QPair<QString, QString>>& res, QString& errmsg){
    QString sql = QString("SELECT iso_code,name FROM tb_currency;");
    LOG(INFO) << "sql:" << sql.toStdString();
    QSqlQuery q;
    if(q.exec(sql)){
        while (q.next()) {
            int fieldNo = q.record().indexOf("iso_code");
            QString code = q.value(fieldNo).toString();
            fieldNo = q.record().indexOf("name");
            QString name = q.value(fieldNo).toString();
            QPair<QString, QString> info(code, name);
            res << info;

        }
        return true;
    }
    LOG(WARNING) << "Get_All_Currencies_IsoCode_Name_From_Db error:" << q.lastError().text().toStdString();
    errmsg = q.lastError().text();
    return false;
}

bool Delete_Currency_By_IsoCode(string isoCode, QString& errmsg){
    QString sql = QString::asprintf("DELETE FROM tb_currency WHERE iso_code='%s';", isoCode.c_str());

    LOG(INFO) << "sql:" << sql.toStdString();
    QSqlQuery q;
    if (!q.exec(sql)){
        errmsg = q.lastError().text();
        return false;
    }
    return true;
}

bool Update_CurrencyInfo(CurrencyInfo* pInfo, QString& errmsg){
    if(pInfo == nullptr){
        errmsg = "invalid arg";
        return false;
    }
    string timestamp = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss").toStdString();
    QString sql = QString::asprintf("UPDATE tb_currency SET frac_digit=%d,dec_char='%s',grp_char='%s',\
                                     is_prefix=%d,symbol='%s',exchange_rate=%f,update_time='%s' \
                                     WHERE iso_code='%s';",
                                     pInfo->frac_digit, pInfo->dec_char.c_str(),pInfo->grp_char.c_str(),
                                     pInfo->is_prefix, pInfo->symbol.c_str(), pInfo->exchange_rate,
                                     timestamp.c_str(), pInfo->iso_code.c_str());

    LOG(INFO) << "sql:" << sql.toStdString();
    QSqlQuery q;
    if (!q.exec(sql)){
        errmsg = q.lastError().text();
        return false;
    }
    return true;
}

/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/

