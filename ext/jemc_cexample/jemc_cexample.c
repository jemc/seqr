
#include <ruby.h>


VALUE JEMC     = Qnil;
VALUE JEMC_CExample = Qnil;


void Init_jemc_cexample();
void m_JEMC_CExample_hello();


void Init_jemc_cexample()
{
  JEMC          = rb_define_module("JEMC");
  JEMC_CExample = rb_define_module_under(JEMC, "CExample");
  
  rb_define_singleton_method(JEMC_CExample,"hello",
                           m_JEMC_CExample_hello, 0);
}


void m_JEMC_CExample_hello()
{
  return;
}