
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
#define CPP2RB_P_MEMBER(ParamName, TypeName, InitialValue) \
  VALUE rb_ ## ParamName = Qnil; \
  TypeName ParamName = InitialValue;

// Use to define the ruby interfacing getter/setter funcs
#define CPP2RB_P_FUNCS(Kls, ParamName, TypeFunc) \
extern "C" VALUE Kls ## _m_ ## ParamName(VALUE self) \
{ return Kls ## _w_get(self)->rb_ ## ParamName; } \
extern "C" VALUE Kls ## _m_ ## ParamName ## _setter(VALUE self, VALUE new_val) \
{ Kls* c_self = Kls ## _w_get(self); \
  c_self->rb_ ## ParamName = new_val; \
  CPP2RB_P_LOCK.lock(); \
  c_self->ParamName = TypeFunc(new_val); \
  CPP2RB_P_LOCK.unlock(); \
  return new_val; }

// Use in Init function to register the funcs with Ruby
#define CPP2RB_P_FUNCS_REG(Kls, ParamName, RubyParamName) \
  rb_define_method(rb_ ## Kls, RubyParamName, \
         RUBY_METHOD_FUNC(Kls ## _m_ ## ParamName),            0); \
  rb_define_method(rb_ ## Kls, RubyParamName "=", \
         RUBY_METHOD_FUNC(Kls ## _m_ ## ParamName ## _setter), 1);

// Use in object constructor to register params as part of Cpp2Rb object
#define CPP2RB_P_INIT(ParamName) \
  this->rb_param_list.push_back(&rb_ ## ParamName);


///
// Value to C++ type conversion functions / macros

std::vector<double> CPP2RB_VALUE_TO_VEC_DOUBLE(VALUE ary)
{
  std::vector<double> vec;
  
  for(int i=0; i<RARRAY_LEN(ary); i++)
    vec.push_back(NUM2DBL(rb_ary_entry(ary, i)));
  
  return vec;
}