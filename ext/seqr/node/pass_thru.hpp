
///
// C++ class definition

VALUE rb_PassThruNode = Qnil;
class PassThruNode : public Node {};


///
// Bind to Ruby object

void Init_PassThruNode()
{
  rb_PassThruNode = rb_define_class_under(rb_ThisModule, "PassThruNode", rb_Node);
}
