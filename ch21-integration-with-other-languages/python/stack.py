# File name: stack.py
# Description: The python wrapper around the cstack library

import platform
from ctypes import *

class value_t(Structure):
  _fields_ = [("data", c_char_p), ("len", c_int)]

class _NativeStack:
  def __init__(self):
    self.stackLib = cdll.LoadLibrary(
            "libcstack.dylib" if platform.system() == 'Darwin'
            else "libcstack.so")

    # value_t make_value(char*, size_t)
    self._makevalue_ = self.stackLib.make_value
    self._makevalue_.argtypes = [c_char_p, c_int]
    self._makevalue_.restype = value_t

    # value_t copy_value(char*, size_t)
    self._copyvalue_ = self.stackLib.copy_value
    self._copyvalue_.argtypes = [c_char_p, c_int]
    self._copyvalue_.restype = value_t

    # void free_value(value_t*)
    self._freevalue_ = self.stackLib.free_value
    self._freevalue_.argtypes = [POINTER(value_t)]

    # cstack_t* cstack_new()
    self._new_ = self.stackLib.cstack_new
    self._new_.argtypes = []
    self._new_.restype = c_void_p

    # void cstack_delete(cstack_t*)
    self._delete_ = self.stackLib.cstack_delete
    self._delete_.argtypes = [c_void_p]

    # void cstack_ctor(cstack_t*, int)
    self._ctor_ = self.stackLib.cstack_ctor
    self._ctor_.argtypes = [c_void_p, c_int]

    # void cstack_dtor(cstack_t*, deleter_t)
    self._dtor_ = self.stackLib.cstack_dtor
    self._dtor_.argtypes = [c_void_p, c_void_p]

    # size_t cstack_size(cstack_t*)
    self._size_ = self.stackLib.cstack_size
    self._size_.argtypes = [c_void_p]
    self._size_.restype = c_int

    # bool_t cstack_push(cstack_t*, value_t)
    self._push_ = self.stackLib.cstack_push
    self._push_.argtypes = [c_void_p, value_t]
    self._push_.restype = c_int

    # bool_t cstack_pop(cstack_t*, value_t*)
    self._pop_ = self.stackLib.cstack_pop
    self._pop_.argtypes = [c_void_p, POINTER(value_t)]
    self._pop_.restype = c_int

    # void cstack_clear(cstack_t*, deleter_t)
    self._clear_ = self.stackLib.cstack_clear
    self._clear_.argtypes = [c_void_p, c_void_p]

class Stack:
  def __enter__(self):
    self._nativeApi_ = _NativeStack()
    self._handler_ = self._nativeApi_._new_()
    self._nativeApi_._ctor_(self._handler_, 100)
    return self

  def __exit__(self, type, value, traceback):
    self._nativeApi_._dtor_(self._handler_, self._nativeApi_._freevalue_)
    self._nativeApi_._delete_(self._handler_)

  def size(self):
    return self._nativeApi_._size_(self._handler_)

  def push(self, item):
    result = self._nativeApi_._push_(self._handler_,
            self._nativeApi_._copyvalue_(item.encode('utf-8'), len(item)));
    if result != 1:
      raise Exception("Stack is full!")

  def pop(self):
    value = value_t()
    result = self._nativeApi_._pop_(self._handler_, byref(value))
    if result != 1:
      raise Exception("Stack is empty!")
    item = string_at(value.data, value.len)
    self._nativeApi_._freevalue_(value)
    return item

  def clear(self):
    self._nativeApi_._clear_(self._handler_, self._nativeApi_._freevalue_)

if __name__ == "__main__":
  with Stack() as stack:
    stack.push("Hello")
    stack.push("World")
    stack.push("!")
    print("Size after pushes:" + str(stack.size()))
    while stack.size() > 0:
      print(stack.pop())
    print("Size after pops:" + str(stack.size()))
    stack.push("Ba");
    stack.push("Bye!");
    print("Size before clear:" + str(stack.size()))
    stack.clear()
    print("Size after clear:" + str(stack.size()))
