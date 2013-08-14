
#include <ruby.h>

const char JEMC_CEXAMPLE_VERSION[] = "0.0.0";


VALUE JEMC          = Qnil;
VALUE JEMC_CExample = Qnil;


void Init_jemc_cexample();

VALUE m_JEMC_CExample_dummy();
VALUE m_JEMC_CExample_version();
VALUE m_JEMC_CExample_passthru(VALUE self, VALUE val);


void Init_jemc_cexample()
{
  JEMC          = rb_define_module("JEMC");
  JEMC_CExample = rb_define_module_under(JEMC, "CExample");
  
  rb_define_singleton_method(JEMC_CExample,"dummy",
                           m_JEMC_CExample_dummy, 0);
  rb_define_singleton_method(JEMC_CExample,"version",
                           m_JEMC_CExample_version, 0);
  rb_define_singleton_method(JEMC_CExample,"passthru",
                           m_JEMC_CExample_passthru, 1);
}


VALUE m_JEMC_CExample_dummy()
{
  return Qnil;
}

VALUE m_JEMC_CExample_version()
{
  return rb_str_new2(JEMC_CEXAMPLE_VERSION);
}

VALUE m_JEMC_CExample_passthru(VALUE self, VALUE val)
{
  return val;
}