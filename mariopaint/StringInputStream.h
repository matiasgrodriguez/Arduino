
#ifndef __StringInputStream_h__
#define __StringInputStream_h__

#include "InputStream.h"

class StringInputStream : public InputStream {
  
  const char *string;
  int16_t position;
  
public:

  StringInputStream(const char* string) {
    this->string = string;
    position = 0;
  }
  virtual ~StringInputStream() {
  }
  
  virtual int16_t read() {
    char currentChar = string[ position ];
    if( currentChar == '\0' ) {
      return -1;
    }
    position++;
    return currentChar;
  };
  
  //virtual int16_t read(uint8_t *buffer, uint16_t offset, uint16_t count) {
   // return InputStream::read( buffer, uint16_t offset, count );
  //}

  
};

#endif

