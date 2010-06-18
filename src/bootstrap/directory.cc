#include "includes.h"

#include "../string.h"
#include "../directory.h"
#include "../errors.h"


namespace fancy {
  namespace bootstrap {

    void init_directory_class()
    {
      DEF_CLASSMETHOD(DirectoryClass,
                      "create:",
                      "Creates a Directory with a given name, if it doesn't already exist.",
                      create);
    }

    CLASSMETHOD(DirectoryClass, create)
    {
      EXPECT_ARGS("Directory##create:", 1);
      string dirname = (const char *)args[0]->to_s().value();
      if(mkdir(dirname.c_str(), 0777) == 0) {
        return new Directory(dirname);
      } else {
        throw new IOError("Could not create directory: ", dirname);
      }
    }

  }
}
