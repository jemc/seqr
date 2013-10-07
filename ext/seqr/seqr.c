
#include <ruby.h>

// const char JEMC_CEXAMPLE_VERSION[] = "0.0.0";


VALUE Seqr           = Qnil;
  VALUE Ext          = Qnil;
    VALUE JackClient = Qnil;


void Init_seqr();



VALUE m_JackClient_dummy(VALUE self)
{
  return Qnil;
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
  
  rb_define_singleton_method(JackClient,"dummy",
                           m_JackClient_dummy, 0);
  // rb_define_singleton_method(JEMC_CExample,"version",
  //                          m_JEMC_CExample_version, 0);
  // rb_define_singleton_method(JEMC_CExample,"passthru",
  //                          m_JEMC_CExample_passthru, 1);
}