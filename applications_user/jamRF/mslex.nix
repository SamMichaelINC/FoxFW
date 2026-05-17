{
  lib,
  buildPythonPackage,
  fetchPypi,
  setuptools,
  wheel,
}:

buildPythonPackage rec {
  pname = "mslex";
  version = "1.3.0";

  src = fetchPypi {
    inherit pname version;
    hash = "sha256-ZByIfR09thDu4q83qOWr2j9wswBs39LQ0p3A0a4oqF0=";
  };

  buildInputs = [
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
