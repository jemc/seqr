
#include <ruby.h>
#include <jack/jack.h>

/// 
// Module/Class Hierarchy

/* c-extension: seqr */           void Init_seqr();
VALUE Seqr               = Qnil;  void Init_Seqr();
  VALUE Jack             = Qnil;  void Init_Jack();
    VALUE Jack_Client    = Qnil;  void Init_Jack_Client();
    VALUE Jack_Options   = Qnil;  void Init_Jack_Options();
    VALUE Jack_PortFlags = Qnil;  void Init_Jack_PortFlags();
    VALUE Jack_Status    = Qnil;  void Init_Jack_Status();

///
// Function Declarations

static jack_client_t* Jack_Client_ptr(VALUE self);
static void Jack_Client_ptr_free(jack_client_t* ptr);

VALUE Jack_Client_k_alloc(VALUE klass);

VALUE Jack_Client_m_initialize (int argc, VALUE* argv, VALUE self);
VALUE Jack_Client_m_activate   (VALUE self);
VALUE Jack_Client_m_deactivate (VALUE self);
VALUE Jack_Client_m_name(VALUE self);

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
  Jack_Client    = rb_define_class_under (Jack, "Client", rb_cObject);
  Init_Jack_Client();
  
  Jack_Options   = rb_define_module_under(Jack, "Options");
  Jack_PortFlags = rb_define_module_under(Jack, "PortFlags");
  Jack_Status    = rb_define_module_under(Jack, "Status");
  Init_Jack_Options();
  Init_Jack_PortFlags();
  Init_Jack_Status();
}

void Init_Jack_Client()
{
  // rb_define_alloc_func(Jack_Client, Jack_Client_k_alloc);
  rb_define_method(Jack_Client, "initialize",
                   Jack_Client_m_initialize,  -1);
  rb_define_method(Jack_Client, "activate",
                   Jack_Client_m_activate,    0);
  rb_define_method(Jack_Client, "deactivate",
                   Jack_Client_m_deactivate,  0);
  rb_define_method(Jack_Client, "name",
                   Jack_Client_m_name,        0);
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

///
// Function Implementations

static jack_client_t* Jack_Client_ptr(VALUE self)
{
  jack_client_t* ptr;
  VALUE ptr_obj;
  
  ptr_obj = rb_iv_get(self, "@ptr");
  if(ptr_obj != Qnil)
  {
    Data_Get_Struct(ptr_obj, jack_client_t, ptr);
    return ptr;
  }
  else
  {
    rb_raise(rb_eRuntimeError, "Illegal action on dead Jack::Client");
    return NULL;
  }
}

static void Jack_Client_ptr_free(jack_client_t* ptr)
{
  jack_client_close(ptr);
}

VALUE Jack_Client_m_initialize(int argc, VALUE* argv, VALUE self)
{
  jack_client_t* ptr;
  char*          name;
  int            options;
  jack_status_t  status;
  
  // Accept custom name as first argument
  if(argc >= 1)
    name = StringValueCStr(argv[0]);
  else
    name = (char*)"Jack::Client"; // default name
  
  // Accept custom options as second argument
  if(argc >= 2)
    options = NUM2INT(argv[1]);
  else
    options = JackNullOption; // default options
  
  // Open the client
  ptr = jack_client_open(name, options, &status);
  if(ptr == NULL)
    rb_raise(rb_eRuntimeError, "Failed to open the Jack::Client");
  
  // Save the reference to the client in the @ptr ivar
  rb_iv_set(self, "@ptr", 
    Data_Wrap_Struct(rb_cObject, NULL, Jack_Client_ptr_free, ptr));
  
  return self;
}

VALUE Jack_Client_m_activate(VALUE self)
{
  return INT2NUM(jack_activate(Jack_Client_ptr(self)));
}

VALUE Jack_Client_m_deactivate(VALUE self)
{
  return INT2NUM(jack_deactivate(Jack_Client_ptr(self)));
}

VALUE Jack_Client_m_name(VALUE self)
{
  return rb_str_new2(jack_get_client_name(Jack_Client_ptr(self)));
}