# shell.nix
{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  # List the packages you need for development
  packages = [
    pkgs.clang # The GNU C++ compiler
    pkgs.clang-tools
    pkgs.cmake # CMake build system generator
    # Add other C++ libraries here, e.g., pkgs.boost, pkgs.opencv
  ];

  buildInputs = [
    pkgs.magic-enum
    pkgs.spdlog
    pkgs.doctest
  ];

  nativeBuildInputs = [
    pkgs.cmake
  ];

  # Environment variables or commands to run when entering the shell
  shellHook = ''
    echo "Welcome to the Nix C++ development shell!"
  '';
}