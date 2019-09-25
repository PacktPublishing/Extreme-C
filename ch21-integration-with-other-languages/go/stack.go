// File name: stack.go
// Description: Go wrapper around the cstack library

package main

/*
#cgo CFLAGS: -I..
#cgo LDFLAGS: -L.. -lcstack
#include <cstack.h>
*/
import "C"
import (
  "fmt"
)

type Stack struct {
  handler *C.cstack_t
}

func NewStack() *Stack {
  s := new(Stack)
  s.handler = C.cstack_new()
  C.cstack_ctor(s.handler, 100)
  return s
}

func (s *Stack) Destroy() {
  C.cstack_dtor(s.handler, C.deleter_t(C.free_value))
  C.cstack_delete(s.handler)
}

func (s *Stack) Size() int {
  return int(C.cstack_size(s.handler))
}

func (s *Stack) Push(item string) bool {
  value := C.make_value(C.CString(item), C.ulong(len(item) + 1))
  pushed := C.cstack_push(s.handler, value)
  return pushed == 1
}

func (s *Stack) Pop() (bool, string) {
  value := C.make_value(nil, 0)
  popped := C.cstack_pop(s.handler, &value)
  str := C.GoString(value.data)
  defer C.free_value(&value)
  return popped == 1, str
}

func (s *Stack) Clear() {
  C.cstack_clear(s.handler, C.deleter_t(C.free_value))
}

func main() {
  var stack = NewStack()
  stack.Push("Hello")
  stack.Push("World")
  stack.Push("!")
  fmt.Println("Stack size:", stack.Size())
  for stack.Size() > 0 {
    _, str := stack.Pop()
    fmt.Println("Popped >", str)
  }
  stack.Destroy()
}
