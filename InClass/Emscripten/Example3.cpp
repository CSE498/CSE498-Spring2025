#include <emscripten.h>
#include <iostream>

// Create a JS function callable as a C++ function.
EM_JS(int, JSDoubleValue, (int value), {
  alert('Doubling: ' + value );
  return value * 2; // Double the input value.
});

int main()
{
  int val1 = 21;
  int val2 = JSDoubleValue(val1);

  std::cout << "val2 == " << val2 << std::endl;
}