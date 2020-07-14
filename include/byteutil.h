#ifndef BYTEUTILS_H
#define BYTEUTILS_H

#include <string>
#include "string.h"
using namespace std;

/**
 * �ַ���ת16�����ַ���(ascii)
 * @brief strToHex
 * @param ch
 * @param hex
 * @return
 */
int strToHex(char *ch, char *hex);
/**
 * 16�����ַ���תԭ��(ascii)
 * @brief hexToStr
 * @param hex
 * @param ch
 * @return
 */
int hexToStr(char *hex, char *ch);
/**
 * 16�����ַ���ת10����(ascii)
 * @brief hexCharToValue
 * @param ch
 * @return
 */
int hexCharToValue(const char ch);
/**
 * intֵת16����ֵ(ascii)
 * @brief valueToHexCh
 * @param value
 * @return
 */
char valueToHexCh(const int value);

/**
 * 16����ֵתchar(ascii)
 * @brief hexChartoByte
 * @param s
 * @param byte
 * @return
 */
int hexChartoByte(char *s,char *byte);

/**
 * charת16����ֵ(ascii)
 * @brief ChartoAscii
 * @param cha
 * @return
 */
unsigned char chartoAscii(const unsigned char cha);
/**
 * base64����
 * @brief base64_encode
 * @param sourcedata
 * @param base64
 * @return
 */
int base64Encode( const unsigned char * sourcedata, char * base64 );

/**
 * base64����
 * @brief base64_decode
 * @param base64
 * @param dedata
 * @return
 */
int base64Decode( const char * base64, unsigned char * dedata );

/**
 * �����ַ����е�����
 * @brief num_strchr
 * @param str
 * @param c
 * @return
 */
inline int numStrchr( const char *str, char c );

//
/**
 * base64 ����
 * @brief b64encodestring
 * @param strString
 * @return
 */
std::string b64EncodeString(const std::string &strString);      //�� ASCII �ַ������� base64 ����

/**
 *  base64 ����
 * @brief b64decodestring
 * @param strString
 * @return
 */
std::string b64DecodeString(const std::string &strString);      //�� base64 �������ַ������н���
#endif // BYTEUTILS_H

