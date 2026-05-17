{
  lib,
  buildPythonPackage,
  fetchPypi,
  setuptools,
  wheel,
  hatchling,
  mslex
}:

buildPythonPackage rec {
  pname = "oslex";
  version = "0.1.3";

  src = fetchPypi {
    inherit pname version;
    hash = "sha256-HtTNgsdd8qi8sNo0QAmEGDdTkzFV0MfZmfpTMTdoXy0=";
  };

  buildInputs = [
    hatchling
    mslex
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
