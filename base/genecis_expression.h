/**
 * @file genecis_expression.h
 */
 
#ifndef GENECIS_BASE_GENECIS_EXPRESSION_H
#define GENECIS_BASE_GENECIS_EXPRESSION_H

namespace genecis {
namespace base {

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

}	// end of namespace base
}	// end of namespace genecis
#endif
