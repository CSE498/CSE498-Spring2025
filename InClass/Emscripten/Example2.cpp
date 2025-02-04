// Compile with: em++ Example2.cpp -o Example2.html

#include <emscripten.h>

int main()
{
  EM_ASM({ alert('Hello from C++');  });
}