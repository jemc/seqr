
#include <ruby.h>


VALUE JEMC     = Qnil;
VALUE CExample = Qnil;


void Init_JEMC_CExample();


void Init_JEMC_CExample()
{
  JEMC     = rb_define_module("JEMC");
  CExample = rb_define_module_under(JEMC, "CExample");
}