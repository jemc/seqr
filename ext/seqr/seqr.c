
#include <ruby.h>
#include <jack/jack.h>


VALUE Seqr            = Qnil;
  VALUE Jack          = Qnil;
    VALUE Jack_Client = Qnil;


static jack_client_t* Jack_Client_get(VALUE self);
VALUE Jack_Client_k_alloc(VALUE klass);
VALUE Jack_Client_m_initialize(VALUE self);
VALUE Jack_Client_m_close(VALUE self);


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


void Init_seqr()
{
  Seqr       = rb_define_module("Seqr");
  Jack       = rb_define_module_under(Seqr, "Jack");
  Jack_Client = rb_define_class_under(Jack, "Client", rb_cObject);
  
  rb_define_alloc_func(Jack_Client, Jack_Client_k_alloc);
  rb_define_method(Jack_Client, "initialize",
                   Jack_Client_m_initialize, 0);
  rb_define_method(Jack_Client, "close",
                   Jack_Client_m_close, 0);
}