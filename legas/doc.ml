let doc () =
  mkd "doc" ~c:"html/\n!.gitignore\n" ();
  Sys.command "doxygen -l" |> ignore;
  Sys.command "mv DoxygenLayout.xml doc/" |> ignore;
  Sys.command "cp ~/icons/control_64x64.png doc/logo.png" |> ignore
