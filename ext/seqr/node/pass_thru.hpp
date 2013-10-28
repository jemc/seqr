
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


NODE_W_ALLOC(PassThruNode)

///
// Bind to Ruby object

void Init_PassThruNode()
{
  rb_PassThruNode = rb_define_class_under(rb_ThisModule, "PassThruNode", rb_Node);
  
  rb_define_alloc_func(rb_PassThruNode, PassThruNode_w_alloc);
}
