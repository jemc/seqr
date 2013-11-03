
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include <ruby.h>
#include <jack/jack.h>

#include "util/cpp2rb.hpp"

///
// Global pointer to the Toplevel Ruby module (Seqr)
VALUE rb_ThisModule = Qnil; extern "C" void Init_seqr();

///
// Include objects in module

#include "jack.hpp"
#include "node.hpp"

///
// Bind to Ruby module

extern "C" void Init_seqr()
{
  rb_ThisModule = rb_define_module("Seqr");
  Init_Jack();
  Init_Node();
}
