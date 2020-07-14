#ifndef BYTEUTILS_H
#define BYTEUTILS_H

#include <string>
#include "string.h"
using namespace std;

/**
 * 字符串转16进制字符串(ascii)
 * @brief strToHex
 * @param ch
 * @param hex
 * @return
 */
int strToHex(char *ch, char *hex);
/**
 * 16进制字符串转原串(ascii)
 * @brief hexToStr
 * @param hex
 * @param ch
 * @return
 */
int hexToStr(char *hex, char *ch);
/**
 * 16进制字符串转10进制(ascii)
 * @brief hexCharToValue
 * @param ch
 * @return
 */
int hexCharToValue(const char ch);
/**
 * int值转16进制值(ascii)
 * @brief valueToHexCh
 * @param value
 * @return
 */
char valueToHexCh(const int value);

/**
 * 16进制值转char(ascii)
 * @brief hexChartoByte
 * @param s
 * @param byte
 * @return
 */
int hexChartoByte(char *s,char *byte);

/**
 * char转16进制值(ascii)
 * @brief ChartoAscii
 * @param cha
 * @return
 */
unsigned char chartoAscii(const unsigned char cha);
/**
 * base64编码
 * @brief base64_encode
 * @param sourcedata
 * @param base64
 * @return
 */
int base64Encode( const unsigned char * sourcedata, char * base64 );

/**
 * base64解码
 * @brief base64_decode
 * @param base64
 * @param dedata
 * @return
 */
int base64Decode( const char * base64, unsigned char * dedata );

/**
 * 查找字符串中的索引
 * @brief num_strchr
 * @param str
 * @param c
 * @return
 */
inline int numStrchr( const char *str, char c );

//
/**
 * base64 编码
 * @brief b64encodestring
 * @param strString
 * @return
 */
std::string b64EncodeString(const std::string &strString);      //对 ASCII 字符串进行 base64 编码

/**
 *  base64 解码
 * @brief b64decodestring
 * @param strString
 * @return
 */
std::string b64DecodeString(const std::string &strString);      //对 base64 编码后的字符串进行解码
#endif // BYTEUTILS_H

