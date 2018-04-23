#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#define VECT_START_LENGTH 5

#define vector_init(type) ({ 		 	     			\
		struct __vector_ { 	     				\
			type *vect;  		     			\
			size_t length;		     			\
			long max;					\
		};				     			\
		struct __vector_ *t = malloc(sizeof(*t)); 		\
		t->vect = malloc(sizeof(type) * VECT_START_LENGTH);	\
		t->length = VECT_START_LENGTH;				\
		t->max = -1;						\
		t;							\
})

/* Let's use this hacky gnu99 extension to return a value from the macro!
 * Unfortunately, I didn't find a way to do it without the container..
 */
#define vector_get(vec, pos, container) ({			\
		assert(vec &&					\
		       "vector might no be NULL pointer");	\
		struct __vector_{ 	     			\
			typeof(container) *vect;  		\
			size_t length;		     		\
			size_t max;				\
		};				     		\
		struct __vector_ *__tmp = (void *)vec; 		\
		container = __tmp->vect[pos]; 			\
})

#define vector_set(vec, pos, val) do {					    \
	assert(vec &&							    \
	       "vector might no be NULL pointer");		    	    \
	struct __vector_ { 	     					    \
		typeof(val) *vect;  					    \
		size_t length;		     				    \
		size_t max;						    \
	};				     				    \
	struct __vector_ *__tmp = (void *)vec; 				    \
	if (__tmp->max >= __tmp->length - 1) { 				    \
		__tmp->length *= 2; 					    \
		__tmp->vect = realloc(__tmp->vect, 			    \
				      sizeof(*__tmp->vect) * __tmp->length);\
	}								    \
	if (pos > __tmp->max)						    \
		__tmp->max = pos;					    \
									    \
	__tmp->vect[pos] = val; 					    \
} while(0)

#define vector_destroy(vec) do {				\
	assert(vec &&						\
	       "vector might no be NULL pointer");	  	\
	struct __vector_ { 	     				\
		void *vect;  					\
		size_t length;		     			\
		size_t max;					\
	};				     			\
	struct __vector_ *__tmp = (void *)vec; 			\
	free(__tmp->vect);					\
	free(__tmp);						\
} while(0)

#define vector_append(vec, val) do {					    \
	assert(vec &&							    \
	       "vector might no be NULL pointer");	  		    \
	struct __vector__ { 	     					    \
		typeof(val) *vect;  					    \
		size_t length;		     				    \
		size_t max;						    \
	};				     				    \
	struct __vector__ *__tmp = (void *)vec; 			    \
	if (__tmp->max >= __tmp->length - 1) { 				    \
		__tmp->length *= 2; 					    \
		__tmp->vect = realloc(__tmp->vect, 			    \
				      sizeof(*__tmp->vect) * __tmp->length);\
	}								    \
	__tmp->max++;							    \
	__tmp->vect[__tmp->max] = val;					    \
} while (0)
