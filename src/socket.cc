#include "socket.h"
#include "array.h"
#include "symbol.h"
#include "PracticalSocket.h"
#include "bootstrap/core_classes.h"

namespace fancy {

  Socket::Socket(const string &hostname, const int &port) :
    FancyObject(SocketClass), _hostname(hostname)
	{
	}

  Socket::~Socket()
  {
  }

  string Socket::to_s() const
  {
    return "<File:" + _hostname + ">"; // + " [" + _mode + "]>";
  }

  string File::filename() const
  {
    return _filename;
  }


  fstream& File::file()
  {
    return _file;
  }

  void File::open()
  {
    _file.open(_filename.c_str(), _openmode);
  }

  bool File::is_open()
  {
    return _file.is_open();
  }

  bool File::eof()
  {
    return _file.eof();
  }

  void File::close()
  {
    _file.close();
  }

  bool File::good() const
  {
    return _file.good();
  }


}
