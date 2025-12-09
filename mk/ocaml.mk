ocaml: $(UTOP) $(DUNE) $(OFMT) $(OLSP) .ocamlformat .ocamlformat

$(OPAM):
	bash -c "sh <(curl -fsSL https://opam.ocaml.org/install.sh)"
$(HOME)/.opam: $(OPAM)
# sudo apt install -uy bubblewrap | --disable-sandboxing
	opam init --bare --disable-sandboxing -a

$(OCAMLC): $(OPAM)
# 	opam switch list-available ; opam switch list
	opam switch create cs3110 ocaml-base-compiler.5.2.0 && touch $@
	opam switch set cs3110 ; eval $(opam env --switch=cs3110)

$(UTOP) $(DUNE) $(OFMT) $(OLSP): $(OCAMLC)
	opam install -y utop dune ocamlformat ocaml-lsp-server ppx_string menhir
	$(MAKE) .ocamlformat .ocamlinit

.ocamlformat: $(OFMT)
	echo "version = `ocamlformat --version`" > $@

.ocamlinit:$(UTOP)
	echo "#use "topfind";;" > $@

$(CAMLP5): $(OCAMLC)
	opam install -y camlp5 && touch $@
