
///
// C++ class to form as a base for CPP2RB objects

class Cpp2Rb
{
  public:
    std::vector<VALUE*> rb_param_list;
    
    virtual void cpp2rb_mark()
    {
      for (auto it=this->rb_param_list.begin(); 
           it!=this->rb_param_list.end(); ++it)
        rb_gc_mark(**it);
    };
};


///
// Ruby wrapping functions for C++ classes

// Macro to define garbage collector marking function
#define CPP2RB_W_MARK(Kls) \
extern "C" void Kls ## _w_mark(Kls* p) { p->cpp2rb_mark(); }

// Macro to define deallocator function
#define CPP2RB_W_FREE(Kls) \
extern "C" void Kls ## _w_free(Kls* p) { delete p; }

// Macro to define allocator function
#define CPP2RB_W_ALLOC(Kls) \
extern "C" VALUE Kls ## _w_alloc(VALUE klass) \
{ return Data_Wrap_Struct(klass, Kls ## _w_mark, Kls ## _w_free, new Kls()); }

// Macro to define pointer unwrapping function
#define CPP2RB_W_GET(Kls) \
extern "C" Kls* Kls ## _w_get(VALUE self) \
{ Kls* p; Data_Get_Struct(self, Kls, p); return p; }

// Macro to define all 4 '_w_' functions
#define CPP2RB_W_FUNCS(Kls) \
  CPP2RB_W_MARK(Kls) \
  CPP2RB_W_FREE(Kls) \
  CPP2RB_W_ALLOC(Kls) \
  CPP2RB_W_GET(Kls)

// Call this macro to register the defined functions as part of the class
#define CPP2RB_W_FUNCS_REG(Kls) \
  rb_define_alloc_func(rb_ ## Kls, Kls ## _w_alloc);


///
// Ruby-accessible C++ parameter creator macros

std::mutex CPP2RB_P_LOCK;

// Use in a class definition to add the appropriate members
#define CPP2RB_P_MEMBER(TypeName, ParamName) \
  VALUE rb_ ## ParamName = Qnil; \
  TypeName ParamName;

// Use to define the ruby interfacing getter/setter funcs
#define CPP2RB_P_FUNCS(Kls, ParamName, TypeFunc) \
extern "C" VALUE Kls ## _m_ ## ParamName(VALUE self) \
{ return Kls ## _w_get(self)->rb_ ## ParamName; } \
extern "C" VALUE Kls ## _m_ ## ParamName ## _setter_private(Kls* c_self, VALUE new_val) \
{ c_self->rb_ ## ParamName = new_val; \
  CPP2RB_P_LOCK.lock(); \
  c_self->ParamName = TypeFunc(new_val); \
  CPP2RB_P_LOCK.unlock(); \
  return new_val; } \
extern "C" VALUE Kls ## _m_ ## ParamName ## _setter(VALUE self, VALUE new_val) \
{ return Kls ## _m_ ## ParamName ## _setter_private(Kls ## _w_get(self), new_val); }

// Use anywhere to set the value of a param 
//   while maintaining Ruby/C++ synchronization for the param
#define CPP2RB_P_SET(Kls, Instance, ParamName, Value) \
  Kls ## _m_ ## ParamName ## _setter_private(Instance, Value);

// Use in object constructor to register params as part of Cpp2Rb object
#define CPP2RB_P_INIT(Kls, ParamName, InitialValue) \
  this->rb_param_list.push_back(&rb_ ## ParamName); \
  CPP2RB_P_SET(Kls, this, ParamName, InitialValue);

// Use in object constructor to register params as part of Cpp2Rb object
#define CPP2RB_P_INIT_BACKEND(Kls, ParamName, InitialValue, InitialCValue) \
  this->rb_param_list.push_back(&rb_ ## ParamName); \
  this->rb_ ## ParamName = InitialValue; \
  this->ParamName        = InitialCValue;

// Use in Init function to register the funcs with Ruby
#define CPP2RB_P_FUNCS_REG(Kls, ParamName, RubyParamName) \
  rb_define_method(rb_ ## Kls, RubyParamName, \
         RUBY_METHOD_FUNC(Kls ## _m_ ## ParamName),            0); \
  rb_define_method(rb_ ## Kls, RubyParamName "=", \
         RUBY_METHOD_FUNC(Kls ## _m_ ## ParamName ## _setter), 1);



///
// Ruby VALUE to C++ type conversion functions / macros

#define CPP2RB_VALUE_TO_BOOL      RTEST
#define CPP2RB_VALUE_TO_DOUBLE    NUM2DBL

std::vector<double> CPP2RB_VALUE_TO_VEC_DOUBLE(VALUE ary)
{
  std::vector<double> vec;
  
  for(int i=0; i<RARRAY_LEN(ary); i++)
    vec.push_back(NUM2DBL(rb_ary_entry(ary, i)));
  
  return vec;
}


///
// Ruby VALUE from C++ type conversion functions / macros

#define CPP2RB_VALUE_FROM_BOOL(x)   (x ? Qtrue : Qfalse)
#define CPP2RB_VALUE_FROM_DOUBLE    DBL2NUM

VALUE CPP2RB_VALUE_FROM_DOUBLE_ARRAY(std::initializer_list<double> list)
{
  VALUE a = rb_ary_new();
  for(auto it=list.begin(); it!=list.end(); ++it)
    rb_ary_push(a, CPP2RB_VALUE_FROM_DOUBLE(*it));
  
  return a;
}