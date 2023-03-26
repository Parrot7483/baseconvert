{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    # nativeBuildInputs is usually what you want -- tools you need to run
    nativeBuildInputs = [ pkgs.gcc12 
                          pkgs.clang-tools_14
                          pkgs.cmake 
                          pkgs.gmp 
                          pkgs.fmt 
                          pkgs.range-v3
                          pkgs.doctest 
                          pkgs.bash ];
}
