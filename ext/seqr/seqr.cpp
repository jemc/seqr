
#include <ruby.h>
#include <jack/jack.h>


/// 
// Module/Class Hierarchy

/* c-extension: seqr */  extern "C" void Init_seqr();
VALUE Seqr                 = Qnil;  void Init_Seqr();
  VALUE Jack               = Qnil;  void Init_Jack();
    VALUE Jack_Client      = Qnil;  void Init_Jack_Client();
    
    VALUE Jack_Options     = Qnil;  void Init_Jack_Options();
    VALUE Jack_PortFlags   = Qnil;  void Init_Jack_PortFlags();
    VALUE Jack_Status      = Qnil;  void Init_Jack_Status();
    
    VALUE Jack_Error       = Qnil;  void Init_Jack_Error();
    VALUE Jack_StatusError = Qnil;  void Init_Jack_StatusError();


///
// Function Declarations

jack_client_t* Jack_Client_ptr(VALUE self);
void Jack_Client_ptr_free(jack_client_t* ptr);
extern "C" VALUE Jack_Client_k_alloc(VALUE klass);
extern "C" VALUE Jack_Client_m_open(VALUE self, VALUE _options, VALUE _name);
extern "C" VALUE Jack_Client_m_activate   (VALUE self);
extern "C" VALUE Jack_Client_m_deactivate (VALUE self);
extern "C" VALUE Jack_Client_m_name(VALUE self);
void Jack_StatusError_raise(const char* str, int status);
extern "C" VALUE Jack_StatusError_m_initialize (int argc, VALUE* argv, VALUE self);


///
// Module/Class Initialization

void Init_seqr()
{
  Seqr = rb_define_module("Seqr");
  Init_Seqr();
}

void Init_Seqr()
{
  Jack = rb_define_module_under(Seqr, "Jack");
  Init_Jack();
}

void Init_Jack()
{
  Jack_Client      = rb_define_class_under (Jack, "Client", rb_cObject);
  Init_Jack_Client();
  
  Jack_Options     = rb_define_module_under(Jack, "Options");
  Jack_PortFlags   = rb_define_module_under(Jack, "PortFlags");
  Jack_Status      = rb_define_module_under(Jack, "Status");
  Init_Jack_Options();
  Init_Jack_PortFlags();
  Init_Jack_Status();
  
  Jack_Error       = rb_define_class_under(Jack, "Error", rb_eRuntimeError);
  Jack_StatusError = rb_define_class_under(Jack, "StatusError", Jack_Error);
  Init_Jack_Error();
  Init_Jack_StatusError();
}

void Init_Jack_Client()
{
  rb_define_method(Jack_Client, "open",
  RUBY_METHOD_FUNC(Jack_Client_m_open),        2);
  rb_define_method(Jack_Client, "activate",
  RUBY_METHOD_FUNC(Jack_Client_m_activate),    0);
  rb_define_method(Jack_Client, "deactivate",
  RUBY_METHOD_FUNC(Jack_Client_m_deactivate),  0);
  rb_define_method(Jack_Client, "name",
  RUBY_METHOD_FUNC(Jack_Client_m_name),        0);
}

void Init_Jack_Options()
{
  rb_define_const(Jack_Options, "NullOption",    INT2NUM(JackNullOption));
  rb_define_const(Jack_Options, "NoStartServer", INT2NUM(JackNoStartServer));
  rb_define_const(Jack_Options, "UseExactName",  INT2NUM(JackUseExactName));
  rb_define_const(Jack_Options, "ServerName",    INT2NUM(JackServerName));
  rb_define_const(Jack_Options, "LoadName",      INT2NUM(JackLoadName));
  rb_define_const(Jack_Options, "LoadInit",      INT2NUM(JackLoadInit));
  rb_define_const(Jack_Options, "SessionID",     INT2NUM(JackSessionID));
}

void Init_Jack_PortFlags()
{
  rb_define_const(Jack_PortFlags, "IsInput",     INT2NUM(JackPortIsInput));
  rb_define_const(Jack_PortFlags, "IsOutput",    INT2NUM(JackPortIsOutput));
  rb_define_const(Jack_PortFlags, "IsPhysical",  INT2NUM(JackPortIsPhysical));
  rb_define_const(Jack_PortFlags, "CanMonitor",  INT2NUM(JackPortCanMonitor));
  rb_define_const(Jack_PortFlags, "IsTerminal",  INT2NUM(JackPortIsTerminal));
}

void Init_Jack_Status()
{
  rb_define_const(Jack_Status, "Failure",        INT2NUM(JackFailure));
  rb_define_const(Jack_Status, "InvalidOption",  INT2NUM(JackInvalidOption));
  rb_define_const(Jack_Status, "NameNotUnique",  INT2NUM(JackNameNotUnique));
  rb_define_const(Jack_Status, "ServerStarted",  INT2NUM(JackServerStarted));
  rb_define_const(Jack_Status, "ServerFailed",   INT2NUM(JackServerFailed));
  rb_define_const(Jack_Status, "ServerError",    INT2NUM(JackServerError));
  rb_define_const(Jack_Status, "NoSuchClient",   INT2NUM(JackNoSuchClient));
  rb_define_const(Jack_Status, "LoadFailure",    INT2NUM(JackLoadFailure));
  rb_define_const(Jack_Status, "InitFailure",    INT2NUM(JackInitFailure));
  rb_define_const(Jack_Status, "ShmFailure",     INT2NUM(JackShmFailure));
  rb_define_const(Jack_Status, "VersionError",   INT2NUM(JackVersionError));
  rb_define_const(Jack_Status, "BackendError",   INT2NUM(JackBackendError));
  rb_define_const(Jack_Status, "ClientZombie",   INT2NUM(JackClientZombie));
}

void Init_Jack_Error()
{
  
}

void Init_Jack_StatusError()
{
  rb_define_method(Jack_StatusError, "initialize",
  RUBY_METHOD_FUNC(Jack_StatusError_m_initialize),  -1);
}

///
// Function Implementations

jack_client_t* Jack_Client_ptr(VALUE self)
{
  jack_client_t* ptr;
  VALUE ptr_obj;
  
  ptr_obj = rb_iv_get(self, "@ptr");
  if(ptr_obj == Qnil)
  {
    rb_raise(Jack_Error, "Illegal action on dead Jack::Client");
    return NULL;
  }

  Data_Get_Struct(ptr_obj, jack_client_t, ptr);
  return ptr;
}

void Jack_Client_ptr_free(jack_client_t* ptr)
{
  jack_client_close(ptr);
}

extern "C" VALUE Jack_Client_m_open(VALUE self, VALUE _name, VALUE _options)
{
  jack_client_t* ptr;
  jack_status_t  status;
  
  ptr = jack_client_open(StringValueCStr(_name), 
                         (jack_options_t)NUM2INT(_options), 
                         &status);
  
  rb_iv_set(self, "@ptr", 
    Data_Wrap_Struct(rb_cObject, NULL, Jack_Client_ptr_free, ptr));
  
  return INT2FIX(status);
}

extern "C" VALUE Jack_Client_m_activate(VALUE self)
{
  return INT2NUM(jack_activate(Jack_Client_ptr(self)));
}

extern "C" VALUE Jack_Client_m_deactivate(VALUE self)
{
  return INT2NUM(jack_deactivate(Jack_Client_ptr(self)));
}

extern "C" VALUE Jack_Client_m_name(VALUE self)
{
  return rb_str_new2(jack_get_client_name(Jack_Client_ptr(self)));
}



void Jack_StatusError_raise(const char* str, int status)
{
  VALUE args[2];
  args[0] = rb_str_new2(str);
  args[1] = INT2NUM(status);
  rb_exc_raise(rb_class_new_instance(sizeof(args), args, Jack_StatusError));
}

extern "C" VALUE Jack_StatusError_m_initialize(int argc, VALUE* argv, VALUE self)
{
  jack_status_t status;
  
  // Accept status bitflags as optional second argument
  status = (jack_status_t)((argc >= 2) ? NUM2INT(argv[1]) : 0);
  
  // Pass first argument to super if it is there
  rb_call_super((argc >= 1), argv);
  
  // Retain status and generate accessors
  if(status)
  {
    rb_iv_set(self, "@status", argv[1]);
    rb_define_attr(rb_class_of(self), "status", 1, 0);
  }
  
  return self;
}