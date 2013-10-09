
#include <ruby.h>
#include <jack/jack.h>

// const char JEMC_CEXAMPLE_VERSION[] = "0.0.0";


VALUE Seqr           = Qnil;
  VALUE Ext          = Qnil;
    VALUE JackClient = Qnil;


static jack_client_t* JackClient_get(VALUE self);
VALUE JackClient_k_alloc(VALUE klass);
VALUE JackClient_m_initialize(VALUE self);
VALUE JackClient_m_close(VALUE self);


static jack_client_t* JackClient_get(VALUE self)
{
  jack_client_t* ptr;
  Data_Get_Struct(self, jack_client_t, ptr);
  return ptr;
}

VALUE JackClient_k_alloc(VALUE klass)
{
  jack_client_t* ptr;
  ptr = jack_client_open("dog", JackNullOption, NULL);
  return Data_Wrap_Struct(klass, NULL, NULL, ptr);
}

VALUE JackClient_m_initialize(VALUE self)
{
  rb_iv_set(self, "@open", Qtrue);
  return self;
}

VALUE JackClient_m_close(VALUE self)
{
  rb_iv_set(self, "@open", Qfalse);
  return INT2NUM(jack_client_close(JackClient_get(self)));
}


void Init_seqr()
{
  Seqr       = rb_define_module("Seqr");
  Ext        = rb_define_module_under(Seqr, "Ext");
  JackClient = rb_define_class_under(Ext, "JackClient", rb_cObject);
  
  rb_define_alloc_func(JackClient, JackClient_k_alloc);
  rb_define_method(JackClient, "initialize",
                   JackClient_m_initialize, 0);
  rb_define_method(JackClient, "close",
                   JackClient_m_close, 0);
}