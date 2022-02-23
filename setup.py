import sys

try:
    from skbuild import setup
except ImportError:
    print(
        "Please update pip, you need pip 10 or greater,\n"
        " or you need to install the PEP 518 requirements in pyproject.toml yourself",
        file=sys.stderr,
    )
    raise

setup(
    name="multineat",
    version="0.8", # Update version in conda/meta.yaml as well
    packages=['multineat'],
    cmake_install_dir="multineat",
)
