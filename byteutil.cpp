#include "byteutil.h"

int strToHex(char *ch, char *hex)
{
  int high,low;
  int tmp = 0;
  if(ch == nullptr || hex == nullptr){
    return -1;
  }

  if(strlen(ch) == 0){
    return -2;
  }

  while(*ch){
    tmp = (int)*ch;
    high = tmp >> 4;
    low = tmp & 15;
    *hex++ = valueToHexCh(high); //先写高字节
    *hex++ = valueToHexCh(low); //其次写低字节
    ch++;
  }
  *hex = '\0';
  return 0;
}

int hexToStr(char *hex, char *ch)
{
  int high,low;
  int tmp = 0;
  if(hex == NULL || ch == NULL){
    return -1;
  }

  if(strlen(hex) %2 == 1){
    return -2;
  }

  while(*hex){
    high = hexCharToValue(*hex);
    if(high < 0){
      *ch = '\0';
      return -3;
    }
    hex++; //指针移动到下一个字符上
    low = hexCharToValue(*hex);
    if(low < 0){
      *ch = '\0';
      return -3;
    }
    tmp = (high << 4) + low;
    *ch++ = (char)tmp;
    hex++;
  }
  *ch = '\0';
  return 0;
}

int hexCharToValue(const char ch){
  int result = 0;
  //获取16进制的高字节位数据
  if(ch >= '0' && ch <= '9'){
    result = (int)(ch - '0');
  }
  else if(ch >= 'a' && ch <= 'z'){
    result = (int)(ch - 'a') + 10;
  }
  else if(ch >= 'A' && ch <= 'Z'){
    result = (int)(ch - 'A') + 10;
  }
  else{
    result = -1;
  }
  return result;
}

char valueToHexCh(const int value)
{
  char result = '\0';
  if(value >= 0 && value <= 9){
    result = (char)(value + 48); //48为ascii编码的'0’字符编码值
  }
  else if(value >= 10 && value <= 15){
    result = (char)(value - 10 + 65); //减去10则找出其在16进制的偏移量，65为ascii的'A'的字符编码值
  }
  else{
    ;
  }

  return result;
}

int hexChartoByte(char *s,char *byte)
{
    int i,n = 0;
    for(i = 0; s[i]; i += 2)
    {
        if(s[i] >= 'A' && s[i] <= 'F')
            byte[n] = s[i] - 'A' + 10;
        else byte[n] = s[i] - '0';
        if(s[i + 1] >= 'A' && s[i + 1] <= 'F')
            byte[n] = (byte[n] << 4) | (s[i + 1] - 'A' + 10);
        else byte[n] = (byte[n] << 4) | (s[i + 1] - '0');
        ++n;
    }
        return n;
}

unsigned char chartoAscii(const unsigned char cha)
{
    unsigned char ascii;
    if ((cha >= 0x0A) && (cha <= 0x0F))
    {
        ascii = cha + 'A' - 10;
    }
    else
    {
        ascii = cha + '0';
    }
    return ascii;
}

/* 全局常量定义 */
const char	* base64char	= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char	padding_char	= '=';


/*编码代码
 * const unsigned char * sourcedata， 源数组
 * char * base64 ，码字保存
 */
int base64Encode( const unsigned char * sourcedata, char * base64 )
{
    int		i		= 0, j = 0;
    unsigned char	trans_index	= 0; /* 索引是8位，但是高两位都为0 */
    const int	datalength	= strlen( (const char *) sourcedata );
    for (; i < datalength; i += 3 )
    {
/*
 * 每三个一组，进行编码
 * 要编码的数字的第一个
 */
        trans_index	= ( (sourcedata[i] >> 2) & 0x3f);
        base64[j++]	= base64char[(int) trans_index];
/* 第二个 */
        trans_index = ( (sourcedata[i] << 4) & 0x30);
        if ( i + 1 < datalength )
        {
            trans_index	|= ( (sourcedata[i + 1] >> 4) & 0x0f);
            base64[j++]	= base64char[(int) trans_index];
        }else{
            base64[j++] = base64char[(int) trans_index];

            base64[j++] = padding_char;

            base64[j++] = padding_char;

            break;                  /* 超出总长度，可以直接break */
        }
/* 第三个 */
        trans_index = ( (sourcedata[i + 1] << 2) & 0x3c);
        if ( i + 2 < datalength )       /* 有的话需要编码2个 */
        {
            trans_index	|= ( (sourcedata[i + 2] >> 6) & 0x03);
            base64[j++]	= base64char[(int) trans_index];

            trans_index	= sourcedata[i + 2] & 0x3f;
            base64[j++]	= base64char[(int) trans_index];
        }else  {
            base64[j++] = base64char[(int) trans_index];

            base64[j++] = padding_char;

            break;
        }
    }

    base64[j] = '\0';

    return(0);
}


/** 在字符串中查询特定字符位置索引
 * const char *str ，字符串
 * char c，要查找的字符
 */
inline int numStrchr( const char *str, char c ) /*  */
{
    const char *pindex = strchr( str, c );
    if ( NULL == pindex )
    {
        return(-1);
    }
    return(pindex - str);
}


/* 解码
 * const char * base64 码字
 * unsigned char * dedata， 解码恢复的数据
 */
int base64Decode( const char * base64, unsigned char * dedata )
{
    int	i		= 0, j = 0;
    int	trans[4]	= { 0, 0, 0, 0 };
    for (; base64[i] != '\0'; i += 4 )
    {
/* 每四个一组，译码成三个字符 */
        trans[0]	= numStrchr( base64char, base64[i] );
        trans[1]	= numStrchr( base64char, base64[i + 1] );
/* 1/3 */
        dedata[j++] = ( (trans[0] << 2) & 0xfc) | ( (trans[1] >> 4) & 0x03);

        if ( base64[i + 2] == '=' )
        {
            continue;
        }else  {
            trans[2] = numStrchr( base64char, base64[i + 2] );
        }
/* 2/3 */
        dedata[j++] = ( (trans[1] << 4) & 0xf0) | ( (trans[2] >> 2) & 0x0f);

        if ( base64[i + 3] == '=' )
        {
            continue;
        }else  {
            trans[3] = numStrchr( base64char, base64[i + 3] );
        }

/* 3/3 */
        dedata[j++] = ( (trans[2] << 6) & 0xc0) | (trans[3] & 0x3f);
    }

    dedata[j] = '\0';

    return(0);
}

//base64 编解码函数实现
/**
* @brief 对 ASCII 字符串进行 base64 编码
*
* @param strString 待编码的字符串
*
* @return srs::string 返回编码后的字符串
*
* @note 对于字符串中含有非 ASCII 字符串型的字符, 代码将抛出 std::string 型异常, 请捕获
*/
std::string b64EncodeString(const std::string &strString)
{
    int nByteSrc = strString.length();
    std::string pszSource = strString;

    int i = 0;
    for(i; i < nByteSrc; i++)
        if( pszSource[i] < 0 || pszSource[i] > 127 )
            throw "can not encode Non-ASCII characters";

    const char *enkey = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string pszEncode(nByteSrc*4/3 + 4, '\0');
    int nLoop = nByteSrc %3 == 0 ? nByteSrc : nByteSrc - 3;
    int n = 0;
    for(i=0; i < nLoop; i+=3 )
    {
        pszEncode[n] = enkey[pszSource[i]>>2];
        pszEncode[n+1] = enkey[((pszSource[i]&3)<<4) | ((pszSource[i+1] & 0xF0)>>4)];
        pszEncode[n+2] = enkey[((pszSource[i+1] & 0x0f)<<2) | ((pszSource[i+2] & 0xc0 )>>6)];
        pszEncode[n+3] = enkey[pszSource[i+2] & 0x3F];
        n += 4;
    }

    switch(nByteSrc%3)
    {
    case 0:
        pszEncode[n] = '\0';
        break;

    case 1:
        pszEncode[n] = enkey[pszSource[i]>>2];
        pszEncode[n+1] = enkey[((pszSource[i]&3)<<4) | ((0&0xf0)>>4)];
        pszEncode[n+2] = '=';
        pszEncode[n+3] = '=';
        pszEncode[n+4] = '\0';
        break;

    case 2:
        pszEncode[n] = enkey[pszSource[i]>>2];
        pszEncode[n+1] = enkey[((pszSource[i]&3)<<4) | ((pszSource[i+1]&0xf0)>>4)];
        pszEncode[n+2] = enkey[(( pszSource[i+1]&0xf)<<2 ) | ((0&0xc0)>>6)];
        pszEncode[n+3] = '=';
        pszEncode[n+4] = '\0';
        break;
    }

    return pszEncode.c_str();
}

/**
* @brief 对 base64 编码后的字符串进行解码
*
* @param strString 待解码的字符串
*
* @return std::string 返回解码后的字符串
*
* @note 对于非base64编码的字符串或已损坏的base64字符串进行解码会抛出 std::string 型异常, 请捕获
*/
std::string b64DecodeString(const std::string &strString)
{
    int nByteSrc = strString.length();
    std::string pszSource = strString;

    const int dekey[] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        62, // '+'
        -1, -1, -1,
        63, // '/'
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
        -1, -1, -1, -1, -1, -1, -1,
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
        13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
        -1, -1, -1, -1, -1, -1,
        26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
        39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
    };

    if(nByteSrc%4 != 0)
        throw "bad base64 string";

    std::string pszDecode(nByteSrc*3/4+4, '\0');
    int nLoop = pszSource[nByteSrc-1]  == '=' ? nByteSrc - 4 : nByteSrc;
    int b[4];
    int i = 0, n = 0;
    for(i = 0; i < nLoop; i += 4 )
    {
        b[0] = dekey[pszSource[i]];        b[1] = dekey[pszSource[i+1]];
        b[2] = dekey[pszSource[i+2]];    b[3] = dekey[pszSource[i+3]];
        if(b[0] == -1 || b[1] == -1 || b[2] == -1 || b[3] == -1)
            throw "bad base64 string";

        pszDecode[n] = (b[0] << 2) | ((b[1] & 0x30) >> 4);
        pszDecode[n+1] = ((b[1] & 0xf) << 4) | ((b[2] & 0x3c) >> 2);
        pszDecode[n+2] =  ((b[2] & 0x3) << 6) | b[3];

        n+=3;
    }

    if( pszSource[nByteSrc-1] == '=' && pszSource[nByteSrc-2] == '=' )
    {
        b[0] = dekey[pszSource[i]];        b[1] = dekey[pszSource[i+1]];
        if(b[0] == -1 || b[1] == -1)
            throw "bad base64 string";

        pszDecode[n] = (b[0] << 2) | ((b[1] & 0x30) >> 4);
        pszDecode[n+1] = '\0';
    }

    if( pszSource[nByteSrc-1] == '=' && pszSource[nByteSrc-2] != '=' )
    {
        b[0] = dekey[pszSource[i]];        b[1] = dekey[pszSource[i+1]];
        b[2] = dekey[pszSource[i+2]];
        if(b[0] == -1 || b[1] == -1 || b[2] == -1)
            throw "bad base64 string";

        pszDecode[n] = (b[0] << 2) | ((b[1] & 0x30) >> 4);
        pszDecode[n+1] = ((b[1] & 0xf) << 4) | ((b[2] & 0x3c) >> 2);
        pszDecode[n+2] = '\0';
    }

    if( pszSource[nByteSrc-1] != '=' && pszSource[nByteSrc-2] != '=' )
        pszDecode[n] = '\0';

    return pszDecode;
}

