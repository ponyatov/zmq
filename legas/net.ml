let pcpp () =
  if not (Sys.file_exists "ref/pcpp/README.md") then
    Sys.command
      ("git clone -o orig -b v25.05 --depth 1 https://github.com/seladb/PcapPlusPlus.git ref/pcpp")
    = 0
  else true
