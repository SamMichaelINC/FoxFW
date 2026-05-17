{
  lib,
  buildPythonPackage,
  fetchPypi,
  setuptools,
  wheel,
  setuptools-git-versioning,
  oslex
}:

buildPythonPackage rec {
  pname = "ufbt";
  version = "0.2.6";

  src = fetchPypi {
    inherit pname version;
    hash = "sha256-TxqFiFhZjtLiW7q2ni6mBLwAdYw7Ho7PiXophmFXNjs=";
  };

  buildInputs = [
   setuptools-git-versioning
   oslex
  ];

  # do not run tests
  doCheck = false;

  # specific to buildPythonPackage, see its reference
  pyproject = true;
  build-system = [
    setuptools
    wheel
  ];
}
