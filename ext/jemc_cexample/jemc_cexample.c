
#include <ruby.h>


VALUE JEMC     = Qnil;
VALUE CExample = Qnil;


void Init_jemc_cexample();


void Init_jemc_cexample()
{
  JEMC     = rb_define_module("JEMC");
  CExample = rb_define_module_under(JEMC, "CExample");
}