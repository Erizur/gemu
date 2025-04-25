{
  lib,
  stdenv,
  pkg-config,
  sdl3,
  ...
}:
stdenv.mkDerivation {
  pname = "gemu";
  version = "0.1.0";

  src = lib.cleanSource ./.;

  installPhase = ''
    runHook preInstall
    install -Dm755 "build/gemu" -t "$out/bin"
    runHook postInstall
  '';

  nativeBuildInputs = [
    pkg-config
    sdl3
  ];

  meta = with lib; {
    description = "A Game Boy emulator written in C.";
    homepage = "https://github.com/Grazen0/gemu";
    license = licenses.mit;
  };
}
