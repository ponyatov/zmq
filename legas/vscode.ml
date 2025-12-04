let touch name ?(c = "") () =
  (* if not (Sys.file_exists name) then *)
  let f = open_out name in
  output_string f c;
  close_out f

let mkd name ?(c = "!.gitignore\n") () =
  if not (Sys.file_exists name) then Sys.mkdir name 0o755;
  touch (Filename.concat name ".gitignore") ~c:c ()

open Unix

let vscode () = 
  mkd ".vscode";
  touch ".vscode/.gitignore" ~c:"!.gitignore";
  touch ".vscode/extensions.json" ();
  touch ".vscode/launch.json" ();
  touch ".vscode/settings.json" ();
  touch ".vscode/.gitignore" ();
  touch ".vscode/c_cpp_properties.json" ();
  touch ".vscode/tasks.json" ();
