// Compile with:  em++ -s EXPORTED_FUNCTIONS="['_SquareVal', '_main']" -s EXPORTED_RUNTIME_METHODS="['cwrap']" Example5.cpp -o Example5.html 
// Any functions exported to JS must be listed above with an underscore prepended.

#include <emscripten.h>

extern "C" {
  double SquareVal(double val) {
    return val * val;
  }
}

int main()
{
  EM_ASM({
    SquareVal = Module.cwrap('SquareVal', 'number', ['number']);

    var x = 12.5;
    alert(`Computing: ${x} & ${x} = ${SquareVal(x)}`);
  });
}