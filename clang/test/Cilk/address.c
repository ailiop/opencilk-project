/* Test three ways to take the address of a reducer:
   1. __builtin_addressof returns leftmost view
   2. & returns current view
   3. && returns leftmost view
*/
// RUN: %clang_cc1 %s -triple aarch64-freebsd -fopencilk -verify -S -emit-llvm -disable-llvm-passes -o - | FileCheck %s
// expected-no-diagnostics
void identity(void* reducer, long * value);
void reduce(void* reducer, long* left, long* right);
extern void consume_address(long *);
// CHECK_LABEL: assorted_addresses
void assorted_addresses()
{
  // CHECK: call void @llvm.reducer.register
  long __attribute__((hyperobject, reducer(reduce, identity))) sum = 0;
  // CHECK-NOT: llvm.hyper.lookup
  // CHECK: call void @consume_address
  consume_address(__builtin_addressof(sum));
  // CHECK: call i8* @llvm.hyper.lookup
  // CHECK: call void @consume_address
  consume_address(&sum);
  // CHECK: call void @llvm.reducer.unregister
  // CHECK: ret void
}

