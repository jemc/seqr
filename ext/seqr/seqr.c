
#include <ruby.h>
#include <jack/jack.h>

/// 
// Module/Class Hierarchy

/* c-extension: seqr */         void Init_seqr();
VALUE Seqr             = Qnil;  void Init_Seqr();
  VALUE Jack           = Qnil;  void Init_Jack();
    VALUE Jack_Client  = Qnil;  void Init_Jack_Client();
    VALUE Jack_Options = Qnil;  void Init_Jack_Options();

///
// Function Declarations

static jack_client_t* Jack_Client_get(VALUE self);
VALUE Jack_Client_k_alloc(VALUE klass);
VALUE Jack_Client_m_initialize(VALUE self);
VALUE Jack_Client_m_close(VALUE self);

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
  Jack_Client  = rb_define_class_under (Jack, "Client", rb_cObject);
  Jack_Options = rb_define_module_under(Jack, "Options");
  Init_Jack_Client();
  Init_Jack_Options();
}

void Init_Jack_Client()
{
  rb_define_alloc_func(Jack_Client, Jack_Client_k_alloc);
  rb_define_method(Jack_Client, "initialize",
                   Jack_Client_m_initialize, 0);
  rb_define_method(Jack_Client, "close",
                   Jack_Client_m_close, 0);
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

///
// Function Implementations

static jack_client_t* Jack_Client_get(VALUE self)
{
  jack_client_t* ptr;
  Data_Get_Struct(self, jack_client_t, ptr);
  return ptr;
}

VALUE Jack_Client_k_alloc(VALUE klass)
{
  jack_client_t* ptr;
  ptr = jack_client_open("dog", JackNullOption, NULL);
  return Data_Wrap_Struct(klass, NULL, NULL, ptr);
}

VALUE Jack_Client_m_initialize(VALUE self)
{
  rb_iv_set(self, "@open", Qtrue);
  return self;
}

VALUE Jack_Client_m_close(VALUE self)
{
  if(rb_iv_get(self, "@open")==Qfalse)
    rb_raise(rb_eRuntimeError, "Cannot close. The client is not open.");
  
  rb_iv_set(self, "@open", Qfalse);
  return INT2NUM(jack_client_close(Jack_Client_get(self)));
}