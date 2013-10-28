
///
// C++ class definition

VALUE rb_PassThruNode = Qnil;
class PassThruNode : public Node {
  public:
    PassThruNode()
    {
      printf("WHUPP\n");
    };
};


///
// Ruby struct wrapping methods

extern "C" VALUE PassThruNode_w_alloc(VALUE klass)
{
  return Data_Wrap_Struct(klass, Node_w_mark, Node_w_free, 
                          new PassThruNode());
}


///
// Bind to Ruby object

void Init_PassThruNode()
{
  rb_PassThruNode = rb_define_class_under(rb_ThisModule, "PassThruNode", rb_Node);
  
  rb_define_alloc_func(rb_PassThruNode, PassThruNode_w_alloc);
}
