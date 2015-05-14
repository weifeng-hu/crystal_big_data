
namespace ithaca { namespace py {

class interface
{
public:
  interface( char* input_path );
  ~interface(){};

public:
  PyObject* main_module;
  PyObject* main_dict;

public:
  PyObject* pyfile;
  PyObject* global;
  PyObject* local;

public:
  bool isInitialized;

};

} }
