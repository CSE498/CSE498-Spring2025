#include <emscripten.h>
#include <iostream>


void Alert(const std::string & msg) {
  EM_ASM({
    var msg = UTF8ToString($0);
    alert(msg);
  }, msg.c_str()
  );
}

// // Create a JS function callable as a C++ function.
// EM_JS(void, Alert, (const char * msg), {
//   alert( UTF8ToString(msg) );
// });

int main()
{
  Alert("Did my alert work?");
}