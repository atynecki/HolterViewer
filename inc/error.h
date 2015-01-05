

/** Error class header file */

#ifndef ERROR_H_
#define ERROR_H_

#include <iostream>
#include <string>

using namespace std;

/** Head class of error */
class Error{
protected:
  string what_;
public:
  Error(){}
  Error( const Error& er ):what_( er.what_ ){}
  Error( string what ):what_( what ){};
  virtual ~Error(){}
  virtual string get_error() const{
    return what_;
  }
};

/** I/0 error */
class OpenFileError: public Error {
public:
	OpenFileError(){}
	OpenFileError( const OpenFileError& er ): Error(er.what_ ){}
	OpenFileError( string what ): Error(what){};
	virtual ~OpenFileError(){}
	virtual string get_error() const{
	    return what_;
	}
};

class WriteFileError: public Error {
public:
	WriteFileError(){}
	WriteFileError( const WriteFileError& er ): Error(er.what_ ){}
	WriteFileError( string what ): Error(what){};
	virtual ~WriteFileError(){}
	virtual string get_error() const{
	    return what_;
	}
};

class ReadFileError: public Error {
public:
	ReadFileError(){}
	ReadFileError( const ReadFileError& er ): Error(er.what_ ){}
	ReadFileError( string what ): Error(what){};
	virtual ~ReadFileError(){}
	virtual string get_error() const{
	    return what_;
	}
};

//kolejne przypadki błędów
#endif /* ERROR_H_ */
