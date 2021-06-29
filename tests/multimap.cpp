#include <string>
#include <iostream>
#include <stdlib.h>
#include <map>
#include "multimap.hpp"
#include <list>

#ifndef LEAK_TEST
# define LEAK_TEST 0
#endif

#ifndef TEST_NS
# define TEST_NS ft
#endif

#ifndef TEST_TK
# define TEST_TK char
#endif

#ifndef TEST_TV
# define TEST_TV int
#endif

#define T1 int
#define T2 std::string
typedef TEST_NS::multimap<T1, T2>::value_type T3;

static int iter = 0;


template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

void	printSize(TEST_NS::multimap<T1, T2> const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	//std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		TEST_NS::multimap<T1, T2>::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

void	printSize(TEST_NS::multimap<TEST_TK, TEST_TV> const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	//std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		TEST_NS::multimap<TEST_TK, TEST_TV>::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}


template <typename MULTIMAP>
void	ft_erase(MULTIMAP &mp, const T1 param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param);
	printSize(mp);
}


TEST_TV			main()
{
	std::cout << "==================== insert test ===========================" << std::endl;

	TEST_NS::multimap<TEST_TK,TEST_TV> multimap_insert1;

	// first insert function version (single parameter):
	multimap_insert1.insert ( TEST_NS::pair<TEST_TK,TEST_TV>('a',100) );
	multimap_insert1.insert ( TEST_NS::pair<TEST_TK,TEST_TV>('z',200) );

	TEST_NS::multimap<TEST_TK,TEST_TV>::iterator ret_insert1;
	ret_insert1 = multimap_insert1.insert ( TEST_NS::pair<TEST_TK,TEST_TV>('z',500) );
	printSize(multimap_insert1);

	// second insert function version (with hTEST_TV position):
	TEST_NS::multimap<TEST_TK,TEST_TV>::iterator it = multimap_insert1.begin();
	multimap_insert1.insert (it, TEST_NS::pair<TEST_TK,TEST_TV>('b',300));	// max efficiency inserting
	multimap_insert1.insert (it, TEST_NS::pair<TEST_TK,TEST_TV>('c',400));	// no max efficiency inserting

	// third insert function version (range insertion):
	TEST_NS::multimap<TEST_TK,TEST_TV> multimap_insert2;
	multimap_insert2.insert(multimap_insert1.begin(),multimap_insert1.find('c'));

	// showing contents:
	std::cout << "multimap_insert1 contains:\n";
	for (it=multimap_insert1.begin(); it!=multimap_insert1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "multimap_insert2 contains:\n";
	for (it=multimap_insert2.begin(); it!=multimap_insert2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "==================== insert test end ===========================" << std::endl;


	std::cout << "==================== erase test start =======================" << std::endl;
	TEST_NS::multimap<TEST_TK,TEST_TV> multimap_erase1;
	TEST_NS::multimap<TEST_TK,TEST_TV>::iterator iter_erase1;

	// insert some values:
	multimap_erase1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('a', 10));
	multimap_erase1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('b', 20));
	multimap_erase1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('c', 30));
	multimap_erase1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('d', 40));
	multimap_erase1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('e', 50));
	multimap_erase1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('f', 60));

	iter_erase1=multimap_erase1.find('b');
	multimap_erase1.erase (iter_erase1);									 // erasing by iter_erase1erator

	std::cout << "size : " << multimap_erase1.size() << std::endl;

	multimap_erase1.erase ('c');									// erasing by key
	std::cout << "size : " << multimap_erase1.size() << std::endl;


	iter_erase1=multimap_erase1.find ('e');
	multimap_erase1.erase ( iter_erase1, multimap_erase1.end() );		// erasing by range
	std::cout << "size : " << multimap_erase1.size() << std::endl;

	// show content:
	for (iter_erase1=multimap_erase1.begin(); iter_erase1!=multimap_erase1.end(); ++iter_erase1)
		std::cout << iter_erase1->first << " => " << iter_erase1->second << '\n';
	
	std::cout << "==================== erase test end ===========================" << std::endl;


	std::cout << "==================== swap test start ==========================" << std::endl;

	TEST_NS::multimap<TEST_TK,TEST_TV> multimap_swap1,multimap_swap2;

	multimap_swap1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('x', 100));
	multimap_swap1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('y', 200));

	multimap_swap2.insert(TEST_NS::pair<TEST_TK, TEST_TV>('a', 11));
	multimap_swap2.insert(TEST_NS::pair<TEST_TK, TEST_TV>('b', 22));
	multimap_swap2.insert(TEST_NS::pair<TEST_TK, TEST_TV>('c', 33));

	multimap_swap1.swap(multimap_swap2);

	std::cout << "multimap_swap1 contains:\n";
	for (TEST_NS::multimap<TEST_TK,TEST_TV>::iterator iter_swap = multimap_swap1.begin(); iter_swap != multimap_swap1.end(); ++iter_swap)
		std::cout << iter_swap->first << " => " << iter_swap->second << '\n';

	std::cout << "multimap_swap2 contains:\n";
	for (TEST_NS::multimap<TEST_TK,TEST_TV>::iterator iter_swap = multimap_swap2.begin(); iter_swap != multimap_swap2.end(); ++iter_swap)
		std::cout << iter_swap->first << " => " << iter_swap->second << '\n';

	std::cout << "==================== swap test end ===========================" << std::endl;

	std::cout << "==================== clear test start ===========================" << std::endl;
	TEST_NS::multimap<TEST_TK,TEST_TV> multimap_clear1;

	multimap_clear1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('x', 100));
	multimap_clear1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('y', 200));
	multimap_clear1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('z', 300));

	std::cout << "multimap_clear1 contains:\n";
	for (TEST_NS::multimap<TEST_TK,TEST_TV>::iterator iter_clear1=multimap_clear1.begin(); iter_clear1!=multimap_clear1.end(); ++iter_clear1)
		std::cout << iter_clear1->first << " => " << iter_clear1->second << '\n';

	multimap_clear1.clear();
	multimap_clear1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('a', 1101));
	multimap_clear1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('b', 2202));

	std::cout << "multimap_clear1 contains:\n";
	for (TEST_NS::multimap<TEST_TK,TEST_TV>::iterator iter_clear1=multimap_clear1.begin(); iter_clear1!=multimap_clear1.end(); ++iter_clear1)
		std::cout << iter_clear1->first << " => " << iter_clear1->second << '\n';
	
	std::cout << "==================== clear test end =============================" << std::endl;

	std::cout << "==================== key_comp test start ===========================" << std::endl;

	TEST_NS::multimap<TEST_TK,TEST_TV> multimap_key_comp1;

	TEST_NS::multimap<TEST_TK,TEST_TV>::key_compare mycomp = multimap_key_comp1.key_comp();

	multimap_key_comp1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('a', 100));
	multimap_key_comp1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('b', 200));
	multimap_key_comp1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('c', 300));

	std::cout << "multimap_key_comp1 contains:\n";

	TEST_TK highest = multimap_key_comp1.rbegin()->first;		 // key value of last element

	TEST_NS::multimap<TEST_TK,TEST_TV>::iterator iter_kc1 = multimap_key_comp1.begin();
	do {
		std::cout << iter_kc1->first << " => " << iter_kc1->second << '\n';
	} while ( mycomp((*iter_kc1++).first, highest) );

	std::cout << '\n';

	std::cout << "==================== key_comp test end =============================" << std::endl;

	std::cout << "==================== value_comp test start =============================" << std::endl;
	
	TEST_NS::multimap<TEST_TK,TEST_TV> multimap_valuecomp;

	multimap_valuecomp.insert(TEST_NS::pair<TEST_TK, TEST_TV>('x', 1001));
	multimap_valuecomp.insert(TEST_NS::pair<TEST_TK, TEST_TV>('y', 2002));
	multimap_valuecomp.insert(TEST_NS::pair<TEST_TK, TEST_TV>('z', 3003));

	std::cout << "multimap_valuecomp contains:\n";

	TEST_NS::pair<TEST_TK,TEST_TV> highest_vc = *multimap_valuecomp.rbegin();					// last element

	TEST_NS::multimap<TEST_TK,TEST_TV>::iterator iter_valuecomp = multimap_valuecomp.begin();
	do {
		std::cout << iter_valuecomp->first << " => " << iter_valuecomp->second << '\n';
	} while ( multimap_valuecomp.value_comp()(*iter_valuecomp++, highest_vc) );

	std::cout << "==================== value_comp test end =============================" << std::endl;

	std::cout << "==================== count test start =============================" << std::endl;
	
	TEST_NS::multimap<TEST_TK,TEST_TV> multimap_count;
	TEST_TK c;

	multimap_count.insert(TEST_NS::pair<TEST_TK, TEST_TV>('a', 101));
	multimap_count.insert(TEST_NS::pair<TEST_TK, TEST_TV>('c', 202));
	multimap_count.insert(TEST_NS::pair<TEST_TK, TEST_TV>('f', 303));

	for (c='a'; c<'h'; c++)
	{
		std::cout << c;
		if (multimap_count.count(c)>0)
			std::cout << " is an element of multimap_count.\n";
		else 
			std::cout << " is not an element of multimap_count.\n";
	}

	
	std::cout << "==================== count test end =============================" << std::endl;

	std::cout << "==================== bound test start =============================" << std::endl;

	TEST_NS::multimap<TEST_TK, TEST_TV> multimap_lb1;
	TEST_NS::multimap<TEST_TK, TEST_TV>::iterator itlow,itup;


	multimap_lb1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('a', 20));
	multimap_lb1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('b', 40));
	multimap_lb1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('c', 60));
	multimap_lb1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('d', 80));
	multimap_lb1.insert(TEST_NS::pair<TEST_TK, TEST_TV>('e', 100));

	itlow=multimap_lb1.lower_bound ('b');	// itlow points to b
	std::cout << itlow->first << std::endl;

	// if (itlow != multimap_lb1.end())
	// 	std::cout << itlow->first << " | " << itlow->second << std::endl;
	// else
	// 	std::cout << "can not find" << std::endl;
	itup=multimap_lb1.upper_bound ('d');	 // itup points to e (not d!)

	std::cout << itup->first << std::endl;

	multimap_lb1.erase(itlow,itup);				// erases [itlow,itup)

	//print content:
	for (TEST_NS::multimap<TEST_TK, TEST_TV>::iterator it=multimap_lb1.begin(); it!=multimap_lb1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';


	std::cout << "==================== bound test end =============================" << std::endl;

	std::cout << "==================== equal_range test start =============================" << std::endl;
  
	TEST_NS::multimap<TEST_TK, TEST_TV> multimap_equalrange;

	multimap_equalrange.insert(TEST_NS::pair<TEST_TK, TEST_TV>('a', 10));
	multimap_equalrange.insert(TEST_NS::pair<TEST_TK, TEST_TV>('b', 20));
	multimap_equalrange.insert(TEST_NS::pair<TEST_TK, TEST_TV>('c', 30));

	TEST_NS::pair<TEST_NS::multimap<TEST_TK, TEST_TV>::iterator,TEST_NS::multimap<TEST_TK, TEST_TV>::iterator> ret;
	ret = multimap_equalrange.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';

	
	std::cout << "==================== equal_range test end =============================" << std::endl;

	// std::list<T3> lst;
	// unsigned int lst_size = 7;
	// for (unsigned int i = 0; i < lst_size; ++i)
	// 	lst.push_back(T3(lst_size - i, i));

	// TEST_NS::multimap<T1, T2> mp(lst.begin(), lst.end());
	// TEST_NS::multimap<T1, T2>::iterator ibegin = mp.begin(), iend = mp.end();

	// TEST_NS::multimap<T1, T2> mp_range(ibegin, --(--iend));
	// for (int i = 0; ibegin != iend; ++ibegin)
	// 	ibegin->second = ++i * 5;

	// ibegin = mp.begin(); iend = --(--mp.end());
	// TEST_NS::multimap<T1, T2> mp_copy(mp);
	// for (int i = 0; ibegin != iend; ++ibegin)
	// 	ibegin->second = ++i * 7;

	// std::cout << "\t-- PART ONE --" << std::endl;
	// printSize(mp);
	// printSize(mp_range);
	// printSize(mp_copy);

	// mp = mp_copy;
	// mp_copy = mp_range;
	// mp_range.clear();

	// std::cout << "\t-- PART TWO --" << std::endl;
	// printSize(mp);
	// printSize(mp_range);
	// printSize(mp_copy);

	std::cout << "==================== erase test start =============================" << std::endl;

	TEST_NS::multimap<TEST_TK, TEST_TV> multimap_erase2;

	multimap_erase2.insert(TEST_NS::pair<TEST_TK, TEST_TV>('a', 5));
	multimap_erase2.insert(TEST_NS::pair<TEST_TK, TEST_TV>('b', 15));
	multimap_erase2.insert(TEST_NS::pair<TEST_TK, TEST_TV>('e', 25));
	multimap_erase2.insert(TEST_NS::pair<TEST_TK, TEST_TV>('z', 35));

	multimap_erase2.erase(multimap_erase2.begin(), multimap_erase2.end());

	std::cout << multimap_erase2.size() << std::endl;

	for (TEST_NS::multimap<TEST_TK, TEST_TV>::iterator iter = multimap_erase2.begin(); iter != multimap_erase2.end(); iter++)
		std::cout << iter->first << " | " << iter->second << std::endl;

	std::cout << "==================== erase test end =============================" << std::endl;

	std::cout << "==================== input test start =============================" << std::endl;

	TEST_NS::multimap<int, std::string> multimap_input;
	multimap_input.insert(TEST_NS::pair<int, std::string>(0, "AAAAAA"));
	multimap_input.insert(TEST_NS::pair<int, std::string>(1, "BBBBB"));
	multimap_input.insert(TEST_NS::pair<int, std::string>(2, "CCCC"));
	multimap_input.insert(TEST_NS::pair<int, std::string>(3, "DDD"));
	multimap_input.insert(TEST_NS::pair<int, std::string>(4, "EE"));
	multimap_input.insert(TEST_NS::pair<int, std::string>(5, "F"));

	multimap_input.insert(TEST_NS::pair<int, std::string>(10 , "Hi there"));
	multimap_input.insert(TEST_NS::pair<int, std::string>(10 , "Hi there"));
	for(TEST_NS::multimap<int, std::string>::iterator iter = multimap_input.begin(); iter != multimap_input.end(); iter++)
		std::cout << iter->first << " | " << iter->second << std::endl;

	std::cout << "==================== input test end =============================" << std::endl;


	std::cout << "==================== tricky erase test start =============================" << std::endl;


	TEST_NS::multimap<T1, T2> mp;

	mp.insert(TEST_NS::pair<T1, T2>(42, "lol"));

	mp.insert(TEST_NS::pair<T1, T2>(50, "mdr"));
	mp.insert(TEST_NS::pair<T1, T2>(25, "funny"));

	mp.insert(TEST_NS::pair<T1, T2>(46, "bunny"));
	mp.insert(TEST_NS::pair<T1, T2>(21, "fizz"));
	mp.insert(TEST_NS::pair<T1, T2>(30, "buzz"));
	mp.insert(TEST_NS::pair<T1, T2>(55, "fuzzy"));

	mp.insert(TEST_NS::pair<T1, T2>(18, "bee"));
	mp.insert(TEST_NS::pair<T1, T2>(23, "coconut"));
	mp.insert(TEST_NS::pair<T1, T2>(28, "diary"));
	mp.insert(TEST_NS::pair<T1, T2>(35, "fiesta"));
	mp.insert(TEST_NS::pair<T1, T2>(44, "hello"));
	mp.insert(TEST_NS::pair<T1, T2>(48, "world"));
	mp.insert(TEST_NS::pair<T1, T2>(53, "this is a test"));
	mp.insert(TEST_NS::pair<T1, T2>(80, "hey"));

	mp.insert(TEST_NS::pair<T1, T2>(12, "no"));
	mp.insert(TEST_NS::pair<T1, T2>(20, "idea"));
	mp.insert(TEST_NS::pair<T1, T2>(22, "123"));
	mp.insert(TEST_NS::pair<T1, T2>(24, "345"));
	mp.insert(TEST_NS::pair<T1, T2>(27, "27"));
	mp.insert(TEST_NS::pair<T1, T2>(29, "29"));
	mp.insert(TEST_NS::pair<T1, T2>(33, "33"));
	mp.insert(TEST_NS::pair<T1, T2>(38, "38"));

	mp.insert(TEST_NS::pair<T1, T2>(43, "1"));
	mp.insert(TEST_NS::pair<T1, T2>(45, "2"));
	mp.insert(TEST_NS::pair<T1, T2>(47, "3"));
	mp.insert(TEST_NS::pair<T1, T2>(49, "4"));
	mp.insert(TEST_NS::pair<T1, T2>(51, "5"));
	mp.insert(TEST_NS::pair<T1, T2>(54, "6"));
	mp.insert(TEST_NS::pair<T1, T2>(60, "7"));
	mp.insert(TEST_NS::pair<T1, T2>(90, "8"));

	printSize(mp);

	/* A classic btree should give this:
	 *                                      42
	 *                     /                                            \
	 *                    25                                            50
	 *           /                 \                         /                       \
	 *          21                 30                       46                       55
	 *      /       \           /      \                /       \             /           \
	 *     18       23        28        35            44         48         53             80
	 *   /   \    /    \    /    \     /   \        /   \       /   \     /    \         /     \
	 *  12   20  22    24  27    29  33    38     43    45    47    49   51    54       60      90
	 *
	 * */

	ft_erase(mp, 25); // right != NULL; left != NULL
	ft_erase(mp, 55); // right != NULL; left != NULL

	/* After deleting 25 and 55, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    24                                            50
	 *           /                 \                         /                      \
	 *          21                 30                       46                      54
	 *      /       \           /      \                /       \             /           \
	 *     18       23        28        35            44         48         53             80
	 *   /   \    /         /    \     /   \        /   \       /   \     /              /     \
	 *  12   20  22        27    29  33    38     43    45    47    49   51             60      90
	 *
	 * */

	ft_erase(mp, 24); // right != NULL; left != NULL
	ft_erase(mp, 54); // right != NULL; left != NULL

	/* After deleting 24 and 54, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    23                                            50
	 *           /                 \                         /                      \
	 *          21                 30                       46                      53
	 *      /       \           /      \                /       \             /           \
	 *     18       22        28        35            44         48         51             80
	 *   /   \              /    \     /   \        /   \       /   \                    /     \
	 *  12   20            27    29  33    38     43    45    47    49                  60      90
	 *
	 * */


	ft_erase(mp, 22); // right == NULL; left == NULL
	ft_erase(mp, 51); // right == NULL; left == NULL
	

	ft_erase(mp, 21); // right == NULL; left != NULL
	ft_erase(mp, 53); // right != NULL; left == NULL

	/* After deleting 22, 51 and then 21, 53, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    23                                            50
	 *           /                 \                         /                      \
	 *          20                 30                       46                      80
	 *      /                   /      \                /       \                /        \
	 *     18                 28        35            44         48             60         90
	 *   /                  /    \     /   \        /   \       /   \
	 *  12                 27    29  33    38     43    45    47    49
	 *
	 * */

	ft_erase(mp, 20); // right == NULL; left != NULL

	/* After deleting 20, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    23                                            50
	 *           /                 \                         /                      \
	 *          18                 30                       46                      80
	 *      /                   /      \                /       \                /        \
	 *     12                 28        35            44         48             60         90
	 *                      /    \     /   \        /   \       /   \
	 *                     27    29  33    38     43    45    47    49
	 *
	 * */

	ft_erase(mp, 23); // right != NULL; left != NULL

	/* After deleting 23, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /      \                /       \                /        \
	 *                        28        35            44         48             60         90
	 *                      /    \     /   \        /   \       /   \
	 *                     27    29  33    38     43    45    47    49
	 *
	 * */

	ft_erase(mp, 42); // right != NULL; left != NULL; parent == NULL

	/* After deleting 42, I would get:
	 *                                      38
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /      \                /       \                /        \
	 *                        28        35            44         48             60         90
	 *                      /    \     /            /   \       /   \
	 *                     27    29  33           43    45    47    49
	 *
	 * */

	ft_erase(mp, 38); // right != NULL; left != NULL; parent == NULL

	/* After deleting 38, I would get:
	 *                                      35
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /      \                /       \                /        \
	 *                        28        33            44         48             60         90
	 *                      /    \                  /   \       /   \
	 *                     27    29               43    45    47    49
	 *
	 * */

	ft_erase(mp, 35); // right != NULL; left != NULL; parent == NULL

	/* After deleting 35, I would get:
	 *                                      33
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /                       /       \                /        \
	 *                        28                      44         48             60         90
	 *                      /    \                  /   \       /   \
	 *                     27    29               43    45    47    49
	 *
	 * */

	ft_erase(mp, 33); // right != NULL; left != NULL; parent == NULL

	/* After deleting 33, I would get:
	 *                                      30
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 28                       46                      80
	 *                          /      \                /       \                /        \
	 *                        27       29             44         48             60         90
	 *                                              /   \       /   \
	 *                                            43    45    47    49
	 *
	 * */



	std::cout << "==================== tricky erase test end =============================" << std::endl;


	std::cout << "==================== const iter test start ==============================" << std::endl;

	TEST_NS::multimap<TEST_TK, TEST_TV> multimap_const;

	multimap_const.insert(TEST_NS::pair<TEST_TK, TEST_TV>('a', 1));
	multimap_const.insert(TEST_NS::pair<TEST_TK, TEST_TV>('b', 2));
	multimap_const.insert(TEST_NS::pair<TEST_TK, TEST_TV>('c', 3));
	multimap_const.insert(TEST_NS::pair<TEST_TK, TEST_TV>('d', 4));

	//TEST_NS::multimap<TEST_TK, TEST_TV>::const_iterator c_iter = multimap_const.begin();
	//c_iter->second = 11;

	

	std::cout << "==================== const iter test start ==============================" << std::endl;


	std::cout << "==================== tricky erase iterator start ==============================" << std::endl;
	

	TEST_NS::multimap<int, int> multimap_teis;

	multimap_teis.insert(TEST_NS::pair<int, int>(4, 4));
	multimap_teis.insert(TEST_NS::pair<int, int>(3, 3));
	multimap_teis.insert(TEST_NS::pair<int, int>(1, 1));
	multimap_teis.insert(TEST_NS::pair<int, int>(7, 7));

	for (TEST_NS::multimap<int, int>::iterator iter = multimap_teis.begin(); iter != multimap_teis.end(); iter++)
		std::cout << iter->first << " | " << iter->second << std::endl;
	
	std::cout << "after earse" << std::endl;
	TEST_NS::multimap<int, int>::iterator iter = multimap_teis.begin();
	std::cout << "this iter : " << iter ->first << " | " << iter->second << std::endl;

	iter++; // iter-> 3
	iter++; // iter -> 4
	iter++; // iter -> 7
	iter++; // iter -> end;

	multimap_teis.erase(4); // delete begin (4); (root node)

	std::cout << "--iter" << std::endl;
	iter--;
	std::cout << "this iter : " << iter ->first << " | " << iter->second << std::endl;

	for (TEST_NS::multimap<int, int>::iterator iter = multimap_teis.begin(); iter != multimap_teis.end(); iter++)
		std::cout << iter->first << " | " << iter->second << std::endl;
	
	std::cout << "==================== tricky erase iterator end ==============================" << std::endl;


	if (LEAK_TEST != 0)
		system("leaks a.out > leaks_result; cat leaks_result | grep leaked > leaks_out && rm -rf leaks_result");
}
