#include <string>
#include <iostream>
#include <stdlib.h>
#include <set>
#include "multiset.hpp"
#include <list>

#ifndef LEAK_TEST
# define LEAK_TEST 0
#endif

#ifndef TEST_NS
# define TEST_NS ft
#endif

#ifndef TEST_TV
# define TEST_TV int
#endif

static int iter = 0;

void	printSize(TEST_NS::multiset<TEST_TV> const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	//std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		TEST_NS::multiset<TEST_TV>::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}


template <typename multiset>
void	ft_erase(multiset &mp, const TEST_TV param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param);
	printSize(mp);
}


TEST_TV			main()
{
	{
		std::cout << "==================== insert test ===========================" << std::endl;

		TEST_NS::multiset<TEST_TV> multiset_insert1;

		// first insert function version (single parameter):
		multiset_insert1.insert (100);
		multiset_insert1.insert (200);


		TEST_NS::multiset<TEST_TV>::iterator ret_insert1;
		ret_insert1 = multiset_insert1.insert ( 200 );
		printSize(multiset_insert1);

		// second insert function version (with hTEST_TV position):
		TEST_NS::multiset<TEST_TV>::iterator it = multiset_insert1.begin();
		multiset_insert1.insert (it, 300);	// max efficiency inserting
		multiset_insert1.insert (it, 150);	// no max efficiency inserting

		// third insert function version (range insertion):
		TEST_NS::multiset<TEST_TV> multiset_insert2;
		multiset_insert2.insert(multiset_insert1.begin(), multiset_insert1.find(300));

		// showing contents:
		std::cout << "multiset_insert1 contains:\n";
		for (it=multiset_insert1.begin(); it!=multiset_insert1.end(); ++it)
			std::cout << *it << '\n';

		std::cout << "multiset_insert2 contains:\n";
		for (it=multiset_insert2.begin(); it!=multiset_insert2.end(); ++it)
			std::cout << *it << '\n';

		std::cout << "==================== insert test end ===========================" << std::endl;


		std::cout << "==================== erase test start =======================" << std::endl;
		TEST_NS::multiset<TEST_TV> multiset_erase1;
		TEST_NS::multiset<TEST_TV>::iterator iter_erase1;

		// insert some values:
		multiset_erase1.insert(10);
		multiset_erase1.insert(20);
		multiset_erase1.insert(30);
		multiset_erase1.insert(40);
		multiset_erase1.insert(50);
		multiset_erase1.insert(60);

		iter_erase1=multiset_erase1.find(20);
		multiset_erase1.erase (iter_erase1);									 // erasing by iter_erase1erator

		std::cout << "size : " << multiset_erase1.size() << std::endl;

		multiset_erase1.erase (30);									// erasing by key
		std::cout << "size : " << multiset_erase1.size() << std::endl;


		iter_erase1=multiset_erase1.find (50);
		multiset_erase1.erase ( iter_erase1, multiset_erase1.end() );		// erasing by range
		std::cout << "size : " << multiset_erase1.size() << std::endl;

		// show content:
		for (iter_erase1=multiset_erase1.begin(); iter_erase1!=multiset_erase1.end(); ++iter_erase1)
			std::cout << *iter_erase1 << '\n';
		
		std::cout << "==================== erase test end ===========================" << std::endl;


		std::cout << "==================== swap test start ==========================" << std::endl;

		TEST_NS::multiset<TEST_TV> multiset_swap1,multiset_swap2;

		multiset_swap1.insert(100);
		multiset_swap1.insert(200);

		multiset_swap2.insert(11);
		multiset_swap2.insert(22);
		multiset_swap2.insert(33);

		multiset_swap1.swap(multiset_swap2);

		std::cout << "multiset_swap1 contains:\n";
		for (TEST_NS::multiset<TEST_TV>::iterator iter_swap = multiset_swap1.begin(); iter_swap != multiset_swap1.end(); ++iter_swap)
			std::cout << *iter_swap << '\n';

		std::cout << "multiset_swap2 contains:\n";
		for (TEST_NS::multiset<TEST_TV>::iterator iter_swap = multiset_swap2.begin(); iter_swap != multiset_swap2.end(); ++iter_swap)
			std::cout << *iter_swap << '\n';

		std::cout << "==================== swap test end ===========================" << std::endl;

		std::cout << "==================== clear test start ===========================" << std::endl;
		TEST_NS::multiset<TEST_TV> multiset_clear1;

		multiset_clear1.insert(100);
		multiset_clear1.insert(200);
		multiset_clear1.insert(300);

		std::cout << "multiset_clear1 contains:\n";
		for (TEST_NS::multiset<TEST_TV>::iterator iter_clear1=multiset_clear1.begin(); iter_clear1!=multiset_clear1.end(); ++iter_clear1)
			std::cout << *iter_clear1 << '\n';

		multiset_clear1.clear();
		multiset_clear1.insert(1101);
		multiset_clear1.insert(2202);

		std::cout << "multiset_clear1 contains:\n";
		for (TEST_NS::multiset<TEST_TV>::iterator iter_clear1=multiset_clear1.begin(); iter_clear1!=multiset_clear1.end(); ++iter_clear1)
			std::cout << *iter_clear1 << '\n';
		
		std::cout << "==================== clear test end =============================" << std::endl;

		std::cout << "==================== key_comp test start ===========================" << std::endl;

		TEST_NS::multiset<TEST_TV> multiset_key_comp1;

		TEST_NS::multiset<TEST_TV>::key_compare mycomp = multiset_key_comp1.key_comp();

		multiset_key_comp1.insert(100);
		multiset_key_comp1.insert(200);
		multiset_key_comp1.insert(300);

		std::cout << "multiset_key_comp1 contains:\n";

		int highest = *multiset_key_comp1.rbegin();		 // key value of last element

		TEST_NS::multiset<TEST_TV>::iterator iter_kc1 = multiset_key_comp1.begin();
		do {
			std::cout << *iter_kc1 << '\n';
		} while ( mycomp(*iter_kc1++, highest) );

		std::cout << '\n';

		std::cout << "==================== key_comp test end =============================" << std::endl;

		std::cout << "==================== value_comp test start =============================" << std::endl;
		
		TEST_NS::multiset<TEST_TV> multiset_valuecomp;

		multiset_valuecomp.insert(1001);
		multiset_valuecomp.insert(2002);
		multiset_valuecomp.insert(3003);

		std::cout << "multiset_valuecomp contains:\n";

		TEST_TV highest_vc = *multiset_valuecomp.rbegin();					// last element

		TEST_NS::multiset<TEST_TV>::iterator iter_valuecomp = multiset_valuecomp.begin();
		do {
			std::cout << *iter_valuecomp << '\n';
		} while ( multiset_valuecomp.value_comp()(*iter_valuecomp++, highest_vc) );

		std::cout << "==================== value_comp test end =============================" << std::endl;

		std::cout << "==================== count test start =============================" << std::endl;
		
		TEST_NS::multiset<TEST_TV> multiset_count;
		TEST_TV i;

		multiset_count.insert(1);
		multiset_count.insert(5);
		multiset_count.insert(7);

		for (i=0; i<10; i++)
		{
			std::cout << i;
			if (multiset_count.count(i)>0)
				std::cout << " is an element of multiset_count.\n";
			else 
				std::cout << " is not an element of multiset_count.\n";
		}

		
		std::cout << "==================== count test end =============================" << std::endl;

		std::cout << "==================== bound test start =============================" << std::endl;

		TEST_NS::multiset<TEST_TV> multiset_lb1;
		TEST_NS::multiset<TEST_TV>::iterator itlow,itup;


		multiset_lb1.insert(20);
		multiset_lb1.insert(40);
		multiset_lb1.insert(60);
		multiset_lb1.insert(80);
		multiset_lb1.insert(100);

		itlow=multiset_lb1.lower_bound (20);	// itlow points to 20
		std::cout << *itlow << std::endl;

		// if (itlow != multiset_lb1.end())
		// 	std::cout << itlow->first << " | " << itlow->second << std::endl;
		// else
		// 	std::cout << "can not find" << std::endl;
		itup=multiset_lb1.upper_bound (80);	 // itup points to 100 (not 80!)

		std::cout << *itup << std::endl;

		multiset_lb1.erase(itlow,itup);				// erases [itlow,itup)

		//print content:
		for (TEST_NS::multiset< TEST_TV>::iterator it=multiset_lb1.begin(); it!=multiset_lb1.end(); ++it)
			std::cout << *it << '\n';


		std::cout << "==================== bound test end =============================" << std::endl;

		std::cout << "==================== equal_range test start =============================" << std::endl;
	
		TEST_NS::multiset< TEST_TV> multiset_equalrange;

		multiset_equalrange.insert(10);
		multiset_equalrange.insert(20);
		multiset_equalrange.insert(30);

		TEST_NS::pair<TEST_NS::multiset< TEST_TV>::iterator,TEST_NS::multiset< TEST_TV>::iterator> ret;
		ret = multiset_equalrange.equal_range(20);

		std::cout << "lower bound points to: ";
		std::cout << *ret.first << '\n';

		std::cout << "upper bound points to: ";
		std::cout << *ret.second << '\n';

		
		std::cout << "==================== equal_range test end =============================" << std::endl;

		// // std::list<T3> lst;
		// // unsigned int lst_size = 7;
		// // for (unsigned int i = 0; i < lst_size; ++i)
		// // 	lst.push_back(T3(lst_size - i, i));

		// // TEST_NS::multiset<T1, T2> mp(lst.begin(), lst.end());
		// // TEST_NS::multiset<T1, T2>::iterator ibegin = mp.begin(), iend = mp.end();

		// // TEST_NS::multiset<T1, T2> mp_range(ibegin, --(--iend));
		// // for (int i = 0; ibegin != iend; ++ibegin)
		// // 	ibegin->second = ++i * 5;

		// // ibegin = mp.begin(); iend = --(--mp.end());
		// // TEST_NS::multiset<T1, T2> mp_copy(mp);
		// // for (int i = 0; ibegin != iend; ++ibegin)
		// // 	ibegin->second = ++i * 7;

		// // std::cout << "\t-- PART ONE --" << std::endl;
		// // printSize(mp);
		// // printSize(mp_range);
		// // printSize(mp_copy);

		// // mp = mp_copy;
		// // mp_copy = mp_range;
		// // mp_range.clear();

		// // std::cout << "\t-- PART TWO --" << std::endl;
		// // printSize(mp);
		// // printSize(mp_range);
		// // printSize(mp_copy);

		std::cout << "==================== erase test start =============================" << std::endl;

		TEST_NS::multiset< TEST_TV> multiset_erase2;

		multiset_erase2.insert(5);
		multiset_erase2.insert(15);
		multiset_erase2.insert(25);
		multiset_erase2.insert(35);

		multiset_erase2.erase(multiset_erase2.begin(), multiset_erase2.end());

		std::cout << multiset_erase2.size() << std::endl;

		for (TEST_NS::multiset< TEST_TV>::iterator iter = multiset_erase2.begin(); iter != multiset_erase2.end(); iter++)
			std::cout << *iter << std::endl;

		std::cout << "==================== erase test end =============================" << std::endl;


		std::cout << "==================== tricky erase test start =============================" << std::endl;


		TEST_NS::multiset<TEST_TV> st;

		st.insert(42);

		st.insert(50);
		st.insert(25);

		st.insert(46);
		st.insert(21);
		st.insert(30);
		st.insert(55);

		st.insert(18);
		st.insert(23);
		st.insert(28);
		st.insert(35);
		st.insert(44);
		st.insert(48);
		st.insert(53);
		st.insert(80);

		st.insert(12);
		st.insert(20);
		st.insert(22);
		st.insert(24);
		st.insert(27);
		st.insert(29);
		st.insert(33);
		st.insert(38);

		st.insert(43);
		st.insert(45);
		st.insert(47);
		st.insert(49);
		st.insert(51);
		st.insert(54);
		st.insert(60);
		st.insert(90);

		printSize(st);

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

		ft_erase(st, 25); // right != NULL; left != NULL
		ft_erase(st, 55); // right != NULL; left != NULL

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

		ft_erase(st, 24); // right != NULL; left != NULL
		ft_erase(st, 54); // right != NULL; left != NULL

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

		ft_erase(st, 22); // right == NULL; left == NULL
		ft_erase(st, 51); // right == NULL; left == NULL
		

		ft_erase(st, 21); // right == NULL; left != NULL
		ft_erase(st, 53); // right != NULL; left == NULL

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

		ft_erase(st, 20); // right == NULL; left != NULL

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

		ft_erase(st, 23); // right != NULL; left != NULL

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

		ft_erase(st, 42); // right != NULL; left != NULL; parent == NULL

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

		ft_erase(st, 38); // right != NULL; left != NULL; parent == NULL

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

		ft_erase(st, 35); // right != NULL; left != NULL; parent == NULL

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

		ft_erase(st, 33); // right != NULL; left != NULL; parent == NULL

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

		TEST_NS::multiset< TEST_TV> multiset_const;

		multiset_const.insert(1);
		multiset_const.insert(2);
		multiset_const.insert(3);
		multiset_const.insert(4);

		//TEST_NS::multiset< TEST_TV>::const_iterator c_iter = multiset_const.begin();
		//c_iter->second = 11;

		

		std::cout << "==================== const iter test end ==============================" << std::endl;


		std::cout << "==================== tricky erase iterator start ==============================" << std::endl;
		

		TEST_NS::multiset<int> multiset_teis;

		multiset_teis.insert(4);
		multiset_teis.insert(3);
		multiset_teis.insert(1);
		multiset_teis.insert(7);

		for (TEST_NS::multiset<int>::iterator iter = multiset_teis.begin(); iter != multiset_teis.end(); iter++)
			std::cout << *iter << std::endl;
		
		TEST_NS::multiset<int>::iterator iter = multiset_teis.begin();
		std::cout << "this iter : " << *iter << std::endl;

		iter++; // iter-> 3
		iter++; // iter -> 4
		iter++; // iter -> 7
		iter++; // iter -> end;

		multiset_teis.erase(4); // delet (4); (root node)

		std::cout << "--iter" << std::endl;
		iter--;
		std::cout << "this iter : " << *iter << std::endl;

		for (TEST_NS::multiset<int>::iterator iter = multiset_teis.begin(); iter != multiset_teis.end(); iter++)
			std::cout << *iter << std::endl;
		
		std::cout << "==================== tricky erase iterator end ==============================" << std::endl;
	}


	if (LEAK_TEST != 0)
		system("leaks a.out > leaks_result; cat leaks_result | grep leaked > leaks_out && rm -rf leaks_result");
}
