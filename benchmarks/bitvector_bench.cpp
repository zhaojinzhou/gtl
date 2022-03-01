// -------------------------------------------------------
// Copyright (c) Electronic Arts Inc. All rights reserved.
// -------------------------------------------------------


/*
 *  Used under electronicarts/EASTL BSD 3-Clause "New" or "Revised" License
 *  see: https://github.com/electronicarts/EASTL/blob/master/LICENSE
 *
 *  Modified by: Gregory Popovitch (greg7mdp@gmail.com)
 */


#include <gtl/stopwatch.hpp>
#include <gtl/bit_vector.hpp>
#include <bitset>
#include <cstdio>

using stopwatch = gtl::stopwatch<std::milli>;

namespace
{
    static constexpr size_t num_iter = 1000000;

	template <class Bitset>
	size_t TestSet(stopwatch& sw, Bitset& b)
	{
		gtl::start_snap x(sw);
		for(size_t i = 0; i < num_iter; ++i)
			b.set();
		return b.count();
	}

	template <class Bitset>
	size_t TestSetIndex(stopwatch& sw, Bitset& b, size_t index)
	{
		gtl::start_snap x(sw);
		for(size_t i = 0; i < num_iter; ++i)
			b.set(index);
        return b.count();
	}


	template <class Bitset>
	size_t TestReset(stopwatch& sw, Bitset& b)
	{
		gtl::start_snap x(sw);
		for(size_t i = 0; i < num_iter; ++i)
			b.reset();
        return b.count();
	}


	template <class Bitset>
	size_t TestFlip(stopwatch& sw, Bitset& b)
	{
		gtl::start_snap x(sw);
		for(size_t i = 0; i < num_iter; ++i)
			b.flip();
        return b.count();
	}


	template <class Bitset>
	size_t TestTest(stopwatch& sw, Bitset& b, unsigned nANDValue)
	{
        size_t temp = 0;
		gtl::start_snap x(sw);
		for(unsigned i = 0; i < num_iter; ++i)
			if (b.test(i & nANDValue))
                ++temp;
        return temp;
	}


	template <class Bitset>
	size_t TestCount(stopwatch& sw, Bitset& b)
	{
		size_t temp = 0;
		gtl::start_snap x(sw);
		for(size_t i = 0; i < num_iter; ++i)
			temp += b.count();
        return temp;
	}


	template <class Bitset>
	size_t TestRightShift(stopwatch& sw, Bitset& b, size_t n)
	{
		gtl::start_snap x(sw);
		for(size_t i = 0; i < num_iter; ++i)
			b >>= n;
        return b.count();
	}

} // namespace



int main()
{
	stopwatch sw1;
	stopwatch sw2;

    std::bitset<15>   std_bs15;
    gtl::bit_vector   gtl_bs15(15);

    std::bitset<150>   std_bs150;
    gtl::bit_vector   gtl_bs150(150);

    std::bitset<1500> std_bs1500;
    gtl::bit_vector   gtl_bs1500(1500);

    std::bitset<15000>   std_bs15000;
    gtl::bit_vector   gtl_bs15000(15000);

    auto show_res = [](const char *s, stopwatch &sw1, stopwatch &sw2) {
        printf("%-20s %14.2f %16.2f %10.2f\n", s, 
               sw1.start_to_snap(), 
               sw2.start_to_snap(), 
               sw1.start_to_snap()/sw2.start_to_snap());
    };
    size_t x = 0;

    printf("%-20s %14s %16s %10s\n", "time", "std::bitset", "gtl::bit_vector", "ratio");

    for(int i = 0; i < 2; ++i)
    {
        // ------------------------------------------
        // Test set()
        // ------------------------------------------

        x += TestSet(sw1, std_bs15);
        x += TestSet(sw2, gtl_bs15);

        if(i == 1) 
            show_res("bitset<15>/set()", sw1, sw2);

        TestSet(sw1, std_bs150);
        TestSet(sw2, gtl_bs150);

        if(i == 1) 
            show_res("bitset<150>/set()", sw1, sw2);

        TestSet(sw1, std_bs15000);
        TestSet(sw2, gtl_bs15000);

        if(i == 1)
            show_res("bitset<15000>/set()", sw1, sw2);

        TestSet(sw1, std_bs1500);
        TestSet(sw2, gtl_bs1500);
            
        if(i == 1) 
            show_res("bitset<1500>/set()", sw1, sw2);

            
        // ------------------------------------------
        // Test set(index)
        // ------------------------------------------
        x += TestSetIndex(sw1, std_bs15, 13);
        x += TestSetIndex(sw2, gtl_bs15, 13);

        if(i == 1)
            show_res("bitset<15>/set(i)", sw1, sw2);

        x += TestSetIndex(sw1, std_bs150, 127);
        x += TestSetIndex(sw2, gtl_bs150, 127);

        if(i == 1)
            show_res("bitset<150>/set(i)", sw1, sw2);

        x += TestSetIndex(sw1, std_bs1500, 730);
        x += TestSetIndex(sw2, gtl_bs1500, 730);

        if(i == 1)
            show_res("bitset<1500>/set(i)", sw1, sw2);

        x += TestSetIndex(sw1, std_bs15000, 73);
        x += TestSetIndex(sw2, gtl_bs15000, 73);

        if(i == 1)
            show_res("bitset<15000>/set(i)", sw1, sw2);


        // ------------------------------------------
        // Test reset()
        // ------------------------------------------
        x += TestReset(sw1, std_bs15);
        x += TestReset(sw2, gtl_bs15);

        if(i == 1)
            show_res("bitset<15>/reset", sw1, sw2);

        x += TestReset(sw1, std_bs150);
        x += TestReset(sw2, gtl_bs150);

        if(i == 1)
            show_res("bitset<150>/reset", sw1, sw2);

        x += TestReset(sw1, std_bs1500);
        x += TestReset(sw2, gtl_bs1500);

        if(i == 1)
            show_res("bitset<1500>/reset", sw1, sw2);

        x += TestReset(sw1, std_bs15000);
        x += TestReset(sw2, gtl_bs15000);

        if(i == 1)
            show_res("bitset<15000>/reset", sw1, sw2);


        // ------------------------------------------
        // Test flip
        // ------------------------------------------
        x += TestFlip(sw1, std_bs15);
        x += TestFlip(sw2, gtl_bs15);

        if(i == 1)
            show_res("bitset<15>/flip", sw1, sw2);

        x += TestFlip(sw1, std_bs150);
        x += TestFlip(sw2, gtl_bs150);

        if(i == 1)
            show_res("bitset<150>/flip", sw1, sw2);

        x += TestFlip(sw1, std_bs1500);
        x += TestFlip(sw2, gtl_bs1500);

        if(i == 1)
            show_res("bitset<1500>/flip", sw1, sw2);

        x += TestFlip(sw1, std_bs15000);
        x += TestFlip(sw2, gtl_bs15000);

        if(i == 1)
            show_res("bitset<15000>/flip", sw1, sw2);


        // ------------------------------------------
        // Test test
        // ------------------------------------------
        x += TestTest(sw1, std_bs15, 7);
        x += TestTest(sw2, gtl_bs15, 7);

        if(i == 1)
            show_res("bitset<15>/test", sw1, sw2);

        x += TestTest(sw1, std_bs150, 31);
        x += TestTest(sw2, gtl_bs150, 31);

        if(i == 1)
            show_res("bitset<150>/test", sw1, sw2);

        x += TestTest(sw1, std_bs1500, 1023);
        x += TestTest(sw2, gtl_bs1500, 1023);

        if(i == 1)
            show_res("bitset<1500>/test", sw1, sw2);

        x += TestTest(sw1, std_bs15000, 998);
        x += TestTest(sw2, gtl_bs15000, 998);

        if(i == 1)
            show_res("bitset<15000>/test", sw1, sw2);


        // ------------------------------------------
        // Test count
        // ------------------------------------------
        x += TestCount(sw1, std_bs15);
        x += TestCount(sw2, gtl_bs15);

        if(i == 1)
            show_res("bitset<15>/count", sw1, sw2);

        x += TestCount(sw1, std_bs150);
        x += TestCount(sw2, gtl_bs150);

        if(i == 1)
            show_res("bitset<150>/count", sw1, sw2);

        x += TestCount(sw1, std_bs1500);
        x += TestCount(sw2, gtl_bs1500);

        if(i == 1)
            show_res("bitset<1500>/count", sw1, sw2);

        x += TestCount(sw1, std_bs15000);
        x += TestCount(sw2, gtl_bs15000);

        if(i == 1)
            show_res("bitset<15000>/count", sw1, sw2);


        // ------------------------------------------
        // Test >>=
        // ------------------------------------------
        x += TestRightShift(sw1, std_bs15, 1);
        x += TestRightShift(sw2, gtl_bs15, 1);

        if(i == 1)
            show_res("bitset<15>/>>=/1", sw1, sw2);

        x += TestRightShift(sw1, std_bs150, 1);
        x += TestRightShift(sw2, gtl_bs150, 1);

        if(i == 1)
            show_res("bitset<150>/>>=/1", sw1, sw2);

        x += TestRightShift(sw1, std_bs1500, 1);
        x += TestRightShift(sw2, gtl_bs1500, 1);

        if(i == 1)
            show_res("bitset<1500>/>>=/1", sw1, sw2);

        x += TestRightShift(sw1, std_bs15000, 1);
        x += TestRightShift(sw2, gtl_bs15000, 1);

        if(i == 1)
            show_res("bitset<15000>/>>=/1", sw1, sw2);
            
    }
    return (int)x;
}
