{ pkgs ? import <nixpkgs> {} }:

let
  project = import ./default.nix { inherit pkgs; };
in
pkgs.mkShell {
  # Pulls in everything from buildInputs and nativeBuildInputs in default.nix
  inputsFrom = [ project ];

  # Extra tools for development only
  packages = with pkgs; [
    clang
    clang-tools # provides clangd for LSP
    
  ];

  shellHook = ''
    echo "--- C++ Development Environment Loaded ---"
    echo "Dependencies: spdlog, doctest, magic-enum"
    export CMAKE_PREFIX_PATH=/nix/store/bh3mwkp6sr153rpxh5sdmll5jls4i7pb-sdl3-3.4.0-dev
    cmake --version
  '';
}