
VALUE rb_Jack_Client = Qnil;


///
// Ruby struct wrapping methods

extern "C" void Jack_Client_w_free(jack_client_t** p)
{
  ruby_xfree(p);
}

extern "C" jack_client_t** Jack_Client_w_get(VALUE self)
{
  jack_client_t** p;
  Data_Get_Struct(self, jack_client_t*, p);
  return p;
}

extern "C" VALUE Jack_Client_w_alloc(VALUE klass)
{
  return Data_Wrap_Struct(klass, NULL, Jack_Client_w_free, 
                          ruby_xmalloc(sizeof(jack_client_t*)));
}


///
// Function Implementations

extern "C" VALUE Jack_Client_m_open(VALUE self, VALUE _name, VALUE _options)
{
  jack_client_t** ptrptr;
  jack_status_t  status;
  
  ptrptr = Jack_Client_w_get(self);
  
  *ptrptr = jack_client_open(StringValueCStr(_name), 
                         (jack_options_t)NUM2INT(_options), 
                         &status);
  
  return rb_ary_new3(2, INT2FIX(*ptrptr), INT2FIX(status));
}

extern "C" VALUE Jack_Client_m_close(VALUE self)
{
  return INT2NUM(jack_client_close(*Jack_Client_w_get(self)));
}

extern "C" VALUE Jack_Client_m_activate(VALUE self)
{
  return INT2NUM(jack_activate(*Jack_Client_w_get(self)));
}

extern "C" VALUE Jack_Client_m_deactivate(VALUE self)
{
  return INT2NUM(jack_deactivate(*Jack_Client_w_get(self)));
}

extern "C" VALUE Jack_Client_m_name(VALUE self)
{
  return rb_str_new2(jack_get_client_name(*Jack_Client_w_get(self)));
}

///
// Bind to Ruby object

void Init_Jack_Client()
{
  rb_Jack_Client = rb_define_class_under(rb_Jack, "Client", rb_cObject);
  
  rb_define_alloc_func(rb_Jack_Client, Jack_Client_w_alloc);
  
  rb_define_method(rb_Jack_Client, "open",
    RUBY_METHOD_FUNC (Jack_Client_m_open),        2);
  rb_define_method(rb_Jack_Client, "activate",
    RUBY_METHOD_FUNC (Jack_Client_m_activate),    0);
  rb_define_method(rb_Jack_Client, "deactivate",
    RUBY_METHOD_FUNC (Jack_Client_m_deactivate),  0);
  rb_define_method(rb_Jack_Client, "name",
    RUBY_METHOD_FUNC (Jack_Client_m_name),        0);
}

