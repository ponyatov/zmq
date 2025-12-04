let hpp () = 
  touch ("inc/" ^ app ^ ".hpp") ~c:"#pragma once

#include <iostream>

extern int main(int argc, char* argv[]);
extern void arg(int argc, char* argv);
" ();

let cpp () =
  touch
    ("src/" ^ app ^ ".cpp")
    ~c:("#include \"" ^ app ^ ".hpp\"

extern int main(int argc, char* argv[]) {  //
    arg(0, argv[0]);
    for (int i = 1; i < argc; i++) {  //
        arg(i, argv[i]);
    }
    return 0;
}

extern void arg(int argc, char* argv) {  //
    std::clog << \"arg[\" << argc << \"] = <\" << argv << \"]\\n\";
}
")
    ();;

let ini() =   
  touch     ("lib/" ^ app ^ ".ini") ~c:"# line comment\n" ()
