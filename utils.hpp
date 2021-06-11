#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
	class iterator_category {};
	class input_iterator_tag {};
	class output_iterator_tag {};
	class bidirectional_iterator_tag : public input_iterator_tag {};
	class random_access_iterator_tag : public bidirectional_iterator_tag {};
}

#endif
