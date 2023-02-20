{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    # nativeBuildInputs is usually what you want -- tools you need to run
    nativeBuildInputs = [ pkgs.gcc12 
                          pkgs.cmake 
                          pkgs.gmp 
                          pkgs.fmt 
                          pkgs.doctest 
                          pkgs.bash ];
}
