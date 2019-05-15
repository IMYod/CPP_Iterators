 /**
 * A demo program for itertools.
 *
 * @author Erel Segal-Halevi
 * @since  2019-05
 */


#include <iostream>
#include <list>
using namespace std;

#include "range.hpp"
#include "chain.hpp"
#include "zip.hpp"
#include "product.hpp"
#include "powerset.hpp"
#include "badkan.hpp"
#define COMMA ,

using namespace itertools;

template<typename Iterable>
string iterable_to_string(const Iterable& iterable) {
	ostringstream ostr;
	for (decltype(*iterable.begin()) i : iterable){
		ostr << i << ",";
	}
	return ostr.str();
}

int main() {

	badkan::TestCase testcase;
	int grade=0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0) {
		
		//*Ranges*/
		testcase.setname("Ranges");
		testcase.CHECK_EQUAL(iterable_to_string(range(5, 9)),string("5,6,7,8,"));
		testcase.CHECK_EQUAL(iterable_to_string(range(1.05, 5.05)),string("1.05,2.05,3.05,4.05,"));
		
		int j = -10;
		for (int i : range(-10, 10))
		{
			testcase.CHECK_EQUAL(i, j);
			j++;
		}
		
		j = 0;
		for (int i : range(0, 100))
		{
			testcase.CHECK_EQUAL(i, j);
			j++;
		}
		
		j = -20;
		for (int i : range(-20, 1))
		{
			testcase.CHECK_EQUAL(i, j);
			j++;
		}
		
		double d = 8000.66;
		for (double i : range(8000.66, 8025.66))
		{
			testcase.CHECK_EQUAL(i, d);
			d++;
		}
		
		j = -1000000;
		for (int i : range(-1000000, -999990))
		{
			testcase.CHECK_EQUAL(i, j);
			j++;
		}
		
		for (int i : range(0, 0))
			testcase.CHECK_EQUAL(1, 0);
           
     		//testcase.CHECK_EQUAL(iterable_to_string(chain(range(0.5, 2.5), string("876"))),string("0.5,1.5,8,7,"));
          

         //*Chain*/
         testcase.setname("Chain"); 
        
        j = 1;
		for (int i : chain(range(1, 5), range(5, 9)))
		{
			testcase.CHECK_EQUAL(i, j);
			j++;
		}
		testcase.CHECK_EQUAL(j, 9);
		
		d = -30.5;
		for (double i : chain(range(-30.5, 0.5), range(0.5, 30.5)))
		{
			testcase.CHECK_EQUAL(i, d);
			d++;
		}
		testcase.CHECK_EQUAL(d, 30.5);
		
		string s="abcdef";
		char c='a';
		for (char i : chain(range('a', 'd'), range('d', 'g')))
		{
			testcase.CHECK_EQUAL(i, c);
			c++;
		}
		testcase.CHECK_EQUAL(c, 'a'+6);
		
		s="vwxycpp";
		j=0;
		for (char ch : chain(range('v', 'z'), string("cpp")))
		{
			testcase.CHECK_EQUAL(ch, s[j]);
			j++;
		}
		testcase.CHECK_EQUAL(j, 7);
		
		s="abcdefghijklmnopqrstuvwxyz";
		j=0;
		for (char ch : chain(range('a', 'w'), string("wxyz")))
		{
			testcase.CHECK_EQUAL(ch, s[j]);
			j++;
		}
		testcase.CHECK_EQUAL(j, 26);

         testcase.setname("multi chain");
		 testcase.CHECK_EQUAL(iterable_to_string(chain(chain(range(0,4), range(1,5)), chain(range(2,4), range(3,3))))
			,string("0,1,2,3,1,2,3,4,2,3,"));

		 testcase.CHECK_EQUAL(iterable_to_string(chain(chain(range('5',':'), range('H','K')), string("%^&")))
			,string("5,6,7,8,9,H,I,J,%,^,&,"));
		
		
        
         //*zip*/
         testcase.setname("Zip"); 
         
         testcase.CHECK_EQUAL(iterable_to_string(zip(range(1,6), string("hello"))),string("1,h,2,e,3,l,4,l,5,o,"));
         testcase.CHECK_EQUAL(iterable_to_string(zip(string("ILv +"), string(" oeC+"))),string("I, ,L,o,v,e, ,C,+,+,")); //It's must be mestake
	
	 std::list<int> list1 = {2,5,11,17};
	 std::list<int> list2 = {3,7,13,19};
         testcase.CHECK_EQUAL(iterable_to_string(zip(list1, list2)),string("2,3,5,7,11,13,17,19,"));


         testcase.setname("multi zip"); 

         testcase.CHECK_EQUAL(iterable_to_string(zip(zip(range(1,6), string("hello")),zip(range(1,6), string("hello"))))
		,string("1,h,1,h,2,e,2,e,3,l,3,l,4,l,4,l,5,o,5,o,"));

	testcase.CHECK_EQUAL(iterable_to_string(zip(zip(range('T','W'), string("eds")),zip(range(1,4), string("3.1")))),
		string("T,e,1,3,U,d,2,.,V,s,3,1,"));

	testcase.CHECK_EQUAL(iterable_to_string(zip(chain(range(-1,1), range(50,52)),zip(range('A','E'), string("////")))),
		string("-1,A,/,0,B,/,50,C,/,51,D,/,"));

	
	//*prduct*/
         testcase.setname("Product"); 

	testcase.CHECK_EQUAL(iterable_to_string(product(range(1,4), string("hello"))),
		string("1,h,1,e,1,l,1,l,1,o,2,h,2,e,2,l,2,l,2,o,3,h,3,e,3,l,3,l,3,o,"));

	testcase.CHECK_EQUAL(iterable_to_string(product(range('a','c'), range('a','c'))),
		string("a,a,a,b,b,a,b,b,"));


         testcase.setname("empty product"); 

	for (auto i : product(range(1,3), range(5,5)))
        	testcase.CHECK_EQUAL(0,1);

	for (auto i : product(range(3,3), range(1,5)))
        	testcase.CHECK_EQUAL(0,1);


        testcase.setname("multy product"); 
	
	testcase.CHECK_EQUAL(iterable_to_string(product(chain(range('1','3'), range('2','4')), range(3,5))),
		string("1,3,1,4,2,3,2,4,2,3,2,4,3,3,3,4,"));

	testcase.CHECK_EQUAL(iterable_to_string(product(zip(range('1','3'), range('2','4')), range(3,5))),
		string("1,2,3,1,2,4,2,3,3,2,3,4,"));

	testcase.CHECK_EQUAL(iterable_to_string(product(range(1,3), product(range('o','q'), string("ab")))),
		string("1,o,a,1,o,b,1,p,a,1,p,b,2,o,a,2,o,b,2,p,a,2,p,b,"));


	//*powerset*/
        testcase.setname("PowerSet");

	//this test failed even when I return right answer
	testcase.CHECK_EQUAL(iterable_to_string(powerset(range(1,1))),
		string("{}"));

	//this test failed even when I return right answer
	testcase.CHECK_EQUAL(iterable_to_string(powerset(range(1,4))),
		string("{},{1},{2},{1,2},{3},{1,3},{2,3},{1,2,3},"));


	testcase.CHECK_EQUAL(iterable_to_string(powerset(zip(range('m','o'),range(15,17)))),
		string("{},{m,15},{n,16},{m,15,n,16},"));
	

	testcase.setname("multy powerset");

	int sum = 0;
	for (auto i : powerset(range(1,5)))
		for (auto j : i)
			sum += j;
	testcase.CHECK_EQUAL(sum,80);
	
	//this test failed even when I return right answer
	testcase.CHECK_EQUAL(iterable_to_string(powerset(product(range(2,4), range(10,12)))),
		string("{},{2,10},{2,11},{2,10,2,11},{3,10},{2,10,3,10},{2,11,3,10},{2,10,2,11,3,10},{3,11},{2,10,3,11},{2,11,3,11},{2,10,2,11,3,11},{3,10,3,11},{2,10,3,10,3,11},{2,11,3,10,3,11},{2,10,2,11,3,10,3,11},"));

	//this test failed even when I return right answer
	testcase.CHECK_EQUAL(iterable_to_string(powerset(chain(zip(range(9,10),range(0,1)),zip(range(5,7),range(-2,0))))),
		string("{},{m,15},{n,16},{m,15,n,16},"));
	

	string sets[] = {"","7,1,7,2,","8,1,8,2,","7,1,7,2,8,1,8,2,","9,1,9,2,","7,1,7,2,9,1,9,2,","8,1,8,2,9,1,9,2,","7,1,7,2,8,1,8,2,9,1,9,2,"};
	uint setsIndex = 0;
	for (auto i : powerset(range(7,10))){
		testcase.CHECK_EQUAL(iterable_to_string(product(i,range(1,3))),
		sets[setsIndex++]);
	}


		;
		

    grade = testcase.grade();
	} else {
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "Your grade is: "  << grade << endl;
	return 0;
}








