#include "fail.h"

namespace ns {
    namespace ns2 {
        struct A {
        };
    }

    namespace {
        struct B {
        };
    }
}

int main() {
    ::ns::ns2::A a1;
    ns::ns2::A a2;
    struct ::ns::ns2::A a3;
    struct ns::ns2::A a4;

    ::ns::B b1;
    ns::B b2;
    struct ::ns::B b3;
    struct ns::B b4;

    _PASS;
}
