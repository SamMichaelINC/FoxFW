{
  description = "Flipper dev flake";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }: 
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
      python = pkgs.python3.override {
        self = python;

        packageOverrides = pyfinal: pyprev: {
          oslex = pyfinal.callPackage ./oslex.nix { };
          ufbt = pyfinal.callPackage ./ufbt.nix { };
          mslex = pyfinal.callPackage ./mslex.nix { };
        };
      };

      base = pkgs.appimageTools.defaultFhsEnvArgs;

      fhs = pkgs.buildFHSEnv (
        base
        // {
          name = "ufbt";

          targetPkgs = pkgs: (
            (base.targetPkgs pkgs) ++
            ([
              pkgs.pkg-config
              pkgs.ncurses

              (python.withPackages (python-pkgs: with python-pkgs; [
                setuptools-git-versioning
                hatchling
                mslex
                oslex
                ufbt
              ]))
            ])
          );

          profile = ''
            export FHS=1;
            export FBT_TOOLCHAIN_PATH=$HOME/.ufbt
          '';
          runScript = ''
            zsh -i -c "source $FBT_TOOLCHAIN_PATH/current/scripts/toolchain/fbtenv.sh; exec zsh"
          '';
          extraOutputsToInstall = [ "dev" ];
        }
      );
    in {
      devShells."${system}".default = fhs.env;
    };
}
