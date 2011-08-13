
#ifndef __InputStream_h__
#define __InputStream_h__

class InputStream {

public:  
  virtual int16_t read() = 0;
  
  virtual int16_t read(uint8_t *buffer, uint16_t offset, uint16_t count) {
    int16_t bytesRead = 0;
    int16_t byte = 0;
    for(; bytesRead < count; ++bytesRead) {
      byte = this->read();
      if( byte == -1 ) {
        break;
      }
      buffer[ offset + bytesRead ] = (uint8_t)byte;
    }
    return bytesRead;
  }
  
};

#endif

