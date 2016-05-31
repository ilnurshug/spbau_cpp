#include <iostream>
#include <cassert>
#include <set>

#include "linked_ptr.h"

using namespace std;

using namespace smart_ptr;

void empty_test()
{
    linked_ptr<int> a;
    linked_ptr<int> copy(a);
    linked_ptr<int> assign = copy;

    assert(!static_cast<bool>(a));
    assert(a == copy);
    assert(a == assign);
    assert(assign == copy);
}

void int_test()
{
    linked_ptr<int> a(new int());
    linked_ptr<int> b(new int());
    auto assigned = a;
    auto copy(a);

    assert(a == copy);
    assert(a == assigned);
    assert(b != a);

    *a = 5;
    assert(*a == 5);
    assert(*copy == 5);
    assert(*assigned == 5);
}

void comparators_test()
{
    set<linked_ptr<double>> awesome;

    for (int i = 0; i < 1000; ++i)
    {
        awesome.insert(linked_ptr<double>(new double(i)));
    }

    auto dummy_object = linked_ptr<double>(new double(42));
    for (int i = 0; i < 1000; ++i)
    {
        set<linked_ptr<double>> strange_set;
        for (int j = 0; j < 100; ++j)
        {
            strange_set.insert(dummy_object);
        }
    }

    assert(*dummy_object == 42);
}

struct Mock
{
    static int link_counter;

    Mock()
    {
        ++link_counter;
    }

    Mock(Mock const&)
    {
        ++link_counter;
    }

    ~Mock()
    {
        --link_counter;
    }
};

int Mock::link_counter = 0;

void refs_test()
{
    {
        auto dummy_object = linked_ptr<Mock>(new Mock());

        for (int i = 0; i < 1000; ++i)
        {
            set<linked_ptr<Mock>> strange_set;
            for (int j = 0; j < 100; ++j)
            {
                strange_set.insert(dummy_object);
            }
        }

        assert(Mock::link_counter == 1);
    }
    assert(Mock::link_counter == 0);

    {
        auto dummy_object = linked_ptr<Mock>(new Mock());
        for (int i = 0; i < 1000; ++i)
        {
            dummy_object = dummy_object;
        }
        assert(Mock::link_counter == 1);
    }

    {
        set<linked_ptr<Mock>> strange_set;
        for (int j = 0; j < 100; ++j)
        {
            strange_set.insert(linked_ptr<Mock>(new Mock()));
        }

        assert(Mock::link_counter == 100);
    }
    assert(Mock::link_counter == 0);

}


static void test_empty_lptr()
{
    linked_ptr<int> lpi_empty;
    assert(!lpi_empty);
    lpi_empty.reset();
    assert(!lpi_empty);
    assert(!lpi_empty.get());
    assert(!lpi_empty.unique());
}

static void test_one_lptr()
{
    linked_ptr<int> lpi_single(new int(777));
    assert(lpi_single);
    lpi_single.reset(new int(666));
    assert(lpi_single);
    assert(lpi_single.get());
    assert(lpi_single.unique());
}

static void test_simple_assignment()
{
    using namespace std;
    linked_ptr<int> ptr1(new int(5));
    linked_ptr<int> ptr2(new int(6));
    assert(*ptr1 == 5);
    assert(*ptr2 == 6);
    ptr1 = ptr2;
    assert(*ptr1 == 6);
    assert(*ptr2 == 6);
}

static void test_many_lptr()
{
    linked_ptr<int> lp;
    lp = linked_ptr<int>(new int(777));
    auto lp1(lp);
    auto lp2(lp1);
    auto lp3(lp2);
    auto lp4(lp);
    auto lp5(lp1);
    auto lp6(lp1);
    auto lp7(lp3);
    auto lp8(lp7);
    auto lp9(lp5);

    lp7.reset();
    auto lp10(lp7);
    auto lp11(lp6);
    auto lp12(lp1);
    auto lp13(lp2);
    lp13.reset(new int(666));
    auto lp14(lp3);
    auto lp15(lp13);
    auto lp16(lp12);
    auto lp17(lp15);
}

static void test_lptr_conversions()
{

    struct base
    {
        virtual bool is_base() { return true; }
        virtual ~base() {}
    };
    struct derived : base
    {
        virtual bool is_base() { return false; }
    };
    linked_ptr<base> lptr(new base());
    assert(lptr->is_base());
    lptr = linked_ptr<base>(new derived());
    assert(!lptr->is_base());
}

static void test_lptr_delete()
{
    struct foo;
    linked_ptr<foo> lptr{};
    struct foo {}; //compiler error if not defined here
}

struct Base
{
    virtual ~Base() {}
};

struct Derived
    : public Base
{};

int main()
{
    empty_test();
    int_test();
    comparators_test();
    refs_test();

    test_empty_lptr();
    test_one_lptr();
    test_simple_assignment();
    test_many_lptr();
    test_lptr_conversions();
    test_lptr_delete();

    cout << "Passed" << endl;
    return 0;
}