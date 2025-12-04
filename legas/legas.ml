let app = Sys.getcwd () |> String.split_on_char '/' |> List.rev |> List.hd
let title = "PcapPlusPlus"
let about = ""
let author = "Dmitry Ponyatov"
let email = "dponyatov@gmail.com"
let year = 2025
let license = "MIT"
let github = "github: https://github.com/ponyatov/" ^ app
let orig = "https://github.com/seladb/PcapPlusPlus.git"
let tag = "v25.05";;

#use "lib/legas.ml"

#use "legas/files.ml"

dirs();;
bins();;
giti();;
apt();;
readme();;

#use "legas/ocaml.ml"

#use "legas/doc.ml"
doc();

#use "legas/mk.ml";;
mk();;

let gitref = "ref/" ^ tag

let git () =
  if not (Sys.file_exists (Filename.concat gitref "README.md")) then
    Sys.command
      ("git clone -o orig -b " ^ tag ^ " --depth 1 " ^ orig ^ " " ^ gitref)
    = 0
  else true

let refdirs ?(p = Sys.is_directory) d =
  Sys.readdir d |> Array.to_list
  |> List.filter (fun f -> p (Filename.concat d f))
  |> List.filter (fun f ->
      not (List.mem f [ "."; ".."; ".git"; ".github"; ".vscode" ]))
;;

refdirs gitref |> List.iter (fun d -> mkd d ());;

let rfd ?(p = Sys.is_directory) r d =
  Sys.readdir (Filename.concat r d)
  |> Array.to_list
  |> List.filter (fun f -> p (r ^ '/' ^ d ^ '/' f))
  |> List.map (fun f -> Filename.concat d f)
;;

rfd "ref/v25.05" "Pcap++";;

let refiles d =
  refdirs d ~p:Sys.is_regular_file
  |> List.filter (fun f -> not (Sys.file_exists f))
;;

refiles gitref
(* let vibe0 () = *)
(* iterate over ref/${ref} - touch files not exists - mkdir dirs not exists -
   skip dirs: .git *)
;;

let dotfiles () =
  Sys.command "cp ~/em/.clang-format ./" |> ignore;
  Sys.command "cp ~/em/.prettierrc ./" |> ignore

#use "legas/cpp.ml"
hpp();cpp();
