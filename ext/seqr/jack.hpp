
VALUE rb_Jack = Qnil;

///
// Include objects in module

#include "jack/constants.hpp"
#include "jack/client.hpp"

///
// Bind to Ruby module

void Init_Jack()
{
  rb_Jack = rb_define_module_under(rb_ThisModule, "Jack");
  
  Init_Jack_Constants();
  Init_Jack_Client();
}
