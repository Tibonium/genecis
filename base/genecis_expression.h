/**
 * @file genecis_expression.h
 */
#pragma once

#include <genecis/base/genecis_defines.h>

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(base)

template<class E>
class genecis_expression {
public:
	typedef E	expression_type ;
	
	// Expression accessors
	const expression_type& operator() () const {
		return *static_cast<const expression_type*> (this) ;
	}
	
	expression_type& operator() () {
		return *static_cast<expression_type*> (this) ;
	}

protected:
	genecis_expression() {} ;
	~genecis_expression() {} ;
};

END_NAMESPACE
END_NAMESPACE
