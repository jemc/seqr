
VALUE rb_Jack = Qnil;

///
// Include objects in module

#include "jack/client.hpp"
#include "jack/constants.hpp"

///
// Bind to Ruby module

void Init_Jack()
{
  rb_Jack = rb_eval_string("Seqr::Jack");
  rb_Jack_Client    = rb_define_class_under (rb_Jack, "Client", rb_cObject);
  Init_Jack_Client();
  
  rb_Jack_Options   = rb_define_module_under(rb_Jack, "Options");
  rb_Jack_PortFlags = rb_define_module_under(rb_Jack, "PortFlags");
  rb_Jack_Status    = rb_define_module_under(rb_Jack, "Status");
  Init_Jack_Options();
  Init_Jack_PortFlags();
  Init_Jack_Status();
}
