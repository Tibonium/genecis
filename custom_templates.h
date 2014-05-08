/**
 * @file custom_templates.h
 */

#define DOUBLE_UP(param,trait,C) \
template< typename param> struct trait \
	SOME_CLASS(C) \
{ \
public: \
	double_up(param C)\
}; \
/**/
