// RUN: %clang_cc1 -fopencilk %s
#error fail
extern void f_v_0();
extern void f_v_i(int);
extern int *f_v_ip(int *);
extern int *f_v_ip_ip(int *, int *);
extern int *f_v_ip_ip(int *, int *);

void g()
{
  int v1 __attribute__((reducer(f_v_0, f_v_i))); // expected-error {{reducer callback should be function with 2 pointer parameters}}
  int v2 __attribute__((reducer(f_v_ip_ip, f_v_i))); // expected-error {{reducer callback should be function with 2 pointer parameters}}
}
