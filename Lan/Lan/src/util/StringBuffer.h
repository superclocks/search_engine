
#ifndef _Lan_util_StringBuffer_
#define _Lan_util_StringBuffer_



namespace Lan
{
	namespace util
	{
  class StringBuffer/*:LUCENE_BASE*/{
  public:
   ///Constructor. Allocates a buffer with the default length.
   StringBuffer();
   ///Constructor. Allocates a buffer of length initSize + 1
   StringBuffer(const int initSize);
   ///Constructor. Creates an instance of Stringbuffer containing a copy of 
   ///the string value
   StringBuffer(const char* value);
   ///Constructs a StringBuffer using another buffer. The StringBuffer can
   ///the be used to easily manipulate the buffer.
   StringBuffer(char* buf,int maxlen, const bool consumeBuffer);
   ///Destructor
   ~StringBuffer();
   ///Clears the Stringbuffer and resets it to it default empty state
   void clear();
   
   ///Appends a single character 
   void appendChar(const char chr);
   ///Appends a copy of the string value 
   void append(const char* value);
   ///Appends a copy of the string value
   void append(const char* value, size_t appendedLength);
   ///Appends an integer (after conversion to a character string)
   void appendInt(const int value);
   ///Appends a float_t (after conversion to a character string)
   void appendFloat(const double value, const int digits);
   ///Puts a copy of the string value in front of the current string in the StringBuffer
   void prepend(const char* value);
   ///Puts a copy of the string value in front of the current string in the StringBuffer
   void prepend(const char* value, unsigned int prependedLength);
   
   ///Contains the length of string in the StringBuffer
   ///Public so that analyzers can edit the length directly
   int len;
   ///Returns the length of the string in the StringBuffer
   int length() const;
   ///Returns a copy of the current string in the StringBuffer
   char* toString(); 
   ///Returns a null terminated reference to the StringBuffer's text
   char* getBuffer(); 


   ///reserve a minimum amount of data for the buffer. 
   ///no change made if the buffer is already longer than length
   void reserve(const int length);
  private:
   ///A buffer that contains strings
   char* buffer;
   ///The length of the buffer
   int bufferLength;
   bool bufferOwner;
   
   ///Has the buffer grown to a minimum length of minLength or bigger
   void growBuffer(const int minLength);
   ///Has the buffer grown to a minimum length of minLength or bigger and shifts the
   ///current string in buffer by skippingNInitialChars forward
   void growBuffer(const int minLength, const int skippingNInitialChars);

  };
	}
}
#endif
