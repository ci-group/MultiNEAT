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
    version="0.12",  # Update version in conda/meta.yaml as well
    packages=["multineat"],
    cmake_install_dir="multineat",
    url="https://github.com/ci-group/MultiNEAT",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
)
