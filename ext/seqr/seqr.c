
#include <ruby.h>
#include <jack/jack.h>

// const char JEMC_CEXAMPLE_VERSION[] = "0.0.0";


VALUE Seqr           = Qnil;
  VALUE Ext          = Qnil;
    VALUE JackClient = Qnil;


jack_client_t* the_client;


VALUE JackClient_m_initialize(VALUE self)
{
  the_client = jack_client_open("dog", JackNullOption, NULL);
  rb_iv_set(self, "@open", Qtrue);
  return self;
}

VALUE JackClient_m_close(VALUE self)
{
  rb_iv_set(self, "@open", Qfalse);
  return INT2NUM(jack_client_close((jack_client_t *)the_client));
}


// VALUE m_JEMC_CExample_version(VALUE self)
// {
//   return rb_str_new2(JEMC_CEXAMPLE_VERSION);
// }

// VALUE m_JEMC_CExample_passthru(VALUE self, VALUE val)
// {
//   return val;
// }


void Init_seqr()
{
  Seqr       = rb_define_module("Seqr");
  Ext        = rb_define_module_under(Seqr, "Ext");
  JackClient = rb_define_class_under(Ext, "JackClient", rb_cObject);
  
  rb_define_method(JackClient, "initialize",
                   JackClient_m_initialize, 0);
  rb_define_method(JackClient, "close",
                   JackClient_m_close, 0);
  // rb_define_singleton_method(JEMC_CExample,"version",
  //                          m_JEMC_CExample_version, 0);
  // rb_define_singleton_method(JEMC_CExample,"passthru",
  //                          m_JEMC_CExample_passthru, 1);
}