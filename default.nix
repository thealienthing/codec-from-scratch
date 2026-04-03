{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  pname = "my-cmake-project";
  version = "0.1.0";

  src = ./.;

  nativeBuildInputs = with pkgs; [
    cmake
    ninja
  ];

  buildInputs = with pkgs; [
    spdlog
    doctest
    fmt
    sdl3
  ];

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Release"
  ];

  meta = with pkgs.lib; {
    description = "A C++ project with spdlog, doctest, and magic-enum";
    platforms = platforms.all;
  };
}