/*-------------------------------------------------------------------
  StringTok.h: String with Token Operation for Arduino Boards Including Arduino Mega
  Copyright ⓒ 2016-Forever ACE Lab, Korea.
  All Rights Reserved. Personal and non-commercial purpose only.
  -------------------------------------------------------------------*/

#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

//#define DEF_ARDUINO_MEGA

/////////////////////////////////////////////////////////////////////
class StringTok
{
  public:
    // Constructor //////////////////////////////////////////////////
    StringTok(void) {
      empty();
    }
    StringTok(char ch) {
      setString(ch);
    }
    StringTok(const char *ptr) {
      setString(ptr);
    }
    StringTok(const String & str) {
      setString(str);
    }
    StringTok(const StringTok & str) {
      setString(str);  // 복사 생성자(copy constructor)
    }

    // Basic Methods ////////////////////////////////////////////////
    char getAt(int nPos) const {
      return m_str[nPos];
    }
    char getLastAt(void) const {
      return getAt(getLength() - 1);   // Get the last character.
    }
    size_t getLength(void) const {
      return m_str.length();
    }
    StringTok getToken(void);
    StringTok getTokenNum(void);  // Get a token that is a number with or without exponent
    StringTok getTokenWhite(void);  // Get a Token only separated by white characters
    int getPosTok(void) const {
      return m_nPosTok;
    }
    int getPosLine(void) const {
      return m_str.indexOf(EOL);
    }
    String getLeft(int nCount) const;
    String getRight(int nCount) const;
    String getMid(int nFirst, int nCount) const;

    String getString(void) const {
      return m_str;
    }
    String getQuote(void) const { // "abc" -> abc
      String sTmp(m_str), sQuote;  sTmp.trim();
      if (sTmp.length() == 0 || sTmp[0] != '"') return sQuote;
      for (int i = 1; i < sTmp.length(); i++) {
        if (sTmp[i] == '"') break;
        else  sQuote += sTmp[i];
      }
      return sQuote;
    }
    String getLine(void) const {
      int nPos = m_str.indexOf(EOL); if (nPos < 0) return "";
      return m_str.substring(0, nPos);
    }
    String cutLine(void) {
      int nPos = m_str.indexOf(EOL); if (nPos < 0) return "";
      String sLine = m_str.substring(0, nPos);
      if (nPos + 1 < getLength()) setString(m_str.substring(nPos + 1));
      else empty();
      return sLine;
    }

    void setString(char ch) {
      m_str = ch;
      initPosTok();
    }
    void setString(const char *ptr) {
      m_str = ptr;
      initPosTok();
    }
    void setString(const String & str) {
      m_str = str;
      initPosTok();
    }
    void setString(const StringTok & str) {
      setString(str.getString());
    }
    void setPosTok(int nPos) {
      m_nPosTok = nPos;
    }

    void appendString(char ch) {
      m_str += ch;
    }
    void appendString(const char *ptr) {
      m_str += ptr;
    }
    void appendString(const String & str) {
      m_str += str;
    }
    void appendString(const StringTok & str) {
      appendString(str.getString());
    }

    char charAt(int nPos) const {
      return getAt(nPos);
    }
    char charLastAt(void) const {
      return getLastAt();
    }
    size_t length(void) const {
      return getLength();
    }
    String toString(void) const {
      return getString();
    }
    long toInt(void) const {
      return m_str.toInt();
    }
    long toLong(void) const {
      return toInt();
    }
    float toFloat(void) const {
      return m_str.toFloat();
    }
    double toDouble(void) const {
      return toFloat();
    }
    void trim(void) {
      m_str.trim();
    }
    long atoi(void) const {
      return toInt();
    }
    float atof(void) const {
      return toFloat();
    }
    void empty(void) {
      setString("");
    }
    static bool isDelimit(char ch);
    static bool isWhite(char ch);
    bool isEmpty(void) const {
      return getLength() == 0;
    }
    bool hasLine(void) const {
      return m_str.indexOf(EOL) >= 0;
    }
    void initPosTok(void) {
      setPosTok(0);
    }

    // Unary Operations /////////////////////////////////////////////
    StringTok & operator=(const StringTok & str)
    {
      setString(str);
      return *this;
    }
    StringTok & operator=(const String & str)
    {
      setString(str);
      return *this;
    }
    StringTok & operator=(const char *ptr)
    {
      setString(ptr);
      return *this;
    }
    StringTok & operator=(char ch)
    {
      setString(ch);
      return *this;
    }
    char operator[](int nPos) const {
      return getAt(nPos);
    }

    // Serial Operations /////////////////////////////////////////////
    void appendSerial(void) {
      m_str += getSerialInput();
    }
#ifdef DEF_ARDUINO_MEGA
    void appendSerial1(void) {
      m_str += getSerial1Input();
    }
    void appendSerial2(void) {
      m_str += getSerial2Input();
    }
    void appendSerial3(void) {
      m_str += getSerial3Input();
    }
#endif

    void inputSerial(void) {
      m_str = getSerialInput();
      initPosTok();
    }
#ifdef DEF_ARDUINO_MEGA
    void inputSerial1(void) {
      m_str = getSerial1Input();
      initPosTok();
    }
    void inputSerial2(void) {
      m_str = getSerial2Input();
      initPosTok();
    }
    void inputSerial3(void) {
      m_str = getSerial3Input();
      initPosTok();
    }
#endif

    void clearSerial(void) {
      while (Serial.available() > 0) Serial.read();
      initPosTok();
    }
#ifdef DEF_ARDUINO_MEGA
    void clearSerial1(void) {
      while (Serial1.available() > 0) Serial1.read();
      initPosTok();
    }
    void clearSerial2(void) {
      while (Serial2.available() > 0) Serial2.read();
      initPosTok();
    }
    void clearSerial3(void) {
      while (Serial3.available() > 0) Serial3.read();
      initPosTok();
    }
#endif

    void printSerial(void) {
      Serial.print(m_str);
    }
    void printlnSerial(void) {
      Serial.println(m_str);
    }
#ifdef DEF_ARDUINO_MEGA
    void printSerial1(void) {
      Serial1.print(m_str);
    }
    void printlnSerial1(void) {
      Serial1.println(m_str);
    }
    void printSerial2(void) {
      Serial2.print(m_str);
    }
    void printlnSerial2(void) {
      Serial2.println(m_str);
    }
    void printSerial3(void) {
      Serial3.print(m_str);
    }
    void printlnSerial3(void) {
      Serial3.println(m_str);
    }
#endif

    static String getSerialInput(void) {
      String str;
      while (Serial.available() > 0) str += (char)Serial.read();
      return str;
    }
#ifdef DEF_ARDUINO_MEGA
    static String getSerial1Input(void) {
      String str;
      while (Serial1.available() > 0) str += (char)Serial1.read();
      return str;
    }
    static String getSerial2Input(void) {
      String str;
      while (Serial2.available() > 0) str += (char)Serial2.read();
      return str;
    }
    static String getSerial3Input(void) {
      String str;
      while (Serial3.available() > 0) str += (char)Serial3.read();
      return str;
    }
#endif

    static bool isAvailableSerial(void) {
      return Serial.available() > 0;
    }
#ifdef DEF_ARDUINO_MEGA
    static bool isAvailableSerial1(void) {
      return Serial1.available() > 0;
    }
    static bool isAvailableSerial2void) {
      return Serial2.available() > 0;
    }
    static bool isAvailableSerial3void) {
      return Serial3.available() > 0;
    }
#endif

    // SoftwareSerial Operations /////////////////////////////////////////////
    // SoftwareSerial의 입력을 문자열로 반환
    void appendSerial(SoftwareSerial & swSerial) {
      m_str += getSerialInput(swSerial);
    }
    void inputSerial(SoftwareSerial & swSerial) {
      m_str = getSerialInput(swSerial);
      initPosTok();
    }
    void clearSerial(SoftwareSerial & swSerial) {
      while (swSerial.available() > 0) swSerial.read();
      initPosTok();
    }
    void printSerial(SoftwareSerial & swSerial) {
      swSerial.print(m_str);
    }
    void printlnSerial(SoftwareSerial & swSerial) {
      swSerial.println(m_str);
    }
    static String getSerialInput(SoftwareSerial & swSerial)
    {
      String str;
      while (swSerial.available() > 0) str += (char)swSerial.read();
      return str;
    }
    static bool isAvailableSerial(SoftwareSerial & swSerial) {
      return swSerial.available() > 0;
    }

  private:
    // Internal Variables ///////////////////////////////////////////
    static const char EOL = '\n'; // End of line
    String m_str;
    int m_nPosTok; // Token position
};
/////////////////////////////////////////////////////////////////////

/*-------------------------------------------------------------------
  Basic Methods
  -------------------------------------------------------------------*/
inline bool StringTok::isDelimit(char ch)
{
  static const char pChar[] = " +-*/<>=()&|!,;:@#$%^\t\r\n";    // Array for delimeter
  size_t nChar = strlen(pChar);
  for (int i = 0; i < nChar; i++)  if (ch == pChar[i])  return true;
  return false;
}

inline bool StringTok::isWhite(char ch)
{
  static const char pChar[] = " \t\r\n";    // Array for white characters
  size_t nChar = strlen(pChar);
  for (int i = 0; i < nChar; i++)  if (ch == pChar[i])  return true;
  return false;
}

inline StringTok StringTok::getToken(void)
{
  size_t nInput = getLength();
  StringTok str;
  while (isWhite(m_str[m_nPosTok])) {
    m_nPosTok++;
    if (m_nPosTok >= nInput)  return str;
  }
  str.m_str = m_str[m_nPosTok], m_nPosTok++;
  if (isDelimit(str[0]))  return str;

  while (m_nPosTok < nInput)
  {
    if (isDelimit(m_str[m_nPosTok]))  return str;
    str.m_str += m_str[m_nPosTok], m_nPosTok++;
  }
  return str;
}

inline StringTok StringTok::getTokenWhite(void)
{
  size_t nInput = getLength();
  StringTok str;
  while (isWhite(m_str[m_nPosTok])) {
    m_nPosTok++;
    if (m_nPosTok >= nInput)  return str;
  }
  str.m_str = m_str[m_nPosTok], m_nPosTok++;

  while (m_nPosTok < nInput)
  {
    if (isWhite(m_str[m_nPosTok]))  return str;
    str.m_str += m_str[m_nPosTok], m_nPosTok++;
  }
  return str;
}

inline StringTok StringTok::getTokenNum(void)
{
  StringTok sToken = getToken();
  StringTok sTokenAdd;
  if ((sToken[0] == '-' || sToken[0] == '+') && (m_nPosTok < getLength()) && !isDelimit(getAt(m_nPosTok)))
  {
    sTokenAdd = getToken();
    sToken = sToken.getString() + sTokenAdd.getString();
  }
  if (sToken.getLastAt() == 'e' || sToken.getLastAt() == 'E') // Exponent
  {
    sTokenAdd = getToken();
    sToken = sToken.getString() + sTokenAdd.getString();
    if ((sTokenAdd[0] == '-' || sTokenAdd[0] == '+') && (m_nPosTok < getLength()) && !isDelimit(getAt(m_nPosTok)))
    {
      sTokenAdd = getToken();
      sToken = sToken.getString() + sTokenAdd.getString();
    }
  }
  return sToken;
}

inline String StringTok::getLeft(int nCount) const
{
  String str;
  for (int i = 0; i < nCount; i++)  str += m_str[i];
  return str;
}

inline String StringTok::getRight(int nCount) const
{
  String str;
  for (int i = getLength() - nCount; i < getLength(); i++)  str += m_str[i];
  return str;
}

inline String StringTok::getMid(int nFirst, int nCount) const
{
  String str;
  for (int i = nFirst; i < nFirst + nCount; i++)  str += m_str[i];
  return str;
}

#undef DEF_ARDUINO_MEGA

/////////////////////////////////////////////////////////////////////

/*-------------------------------------------------------------------
  Revision Records
  ---------------------------------------------------------------------
  C(2016-12-05)
  R(2018-04-01): the line operations were added.
  -------------------------------------------------------------------*/
