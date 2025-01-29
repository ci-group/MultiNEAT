from skbuild import setup

setup(
    name="multineat",
    version="0.13",
    description="MultiNEAT Python",
    url="https://github.com/ci-group/MultiNEAT",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    packages=["multineat"],  # Python package name
    package_dir={"": "src/python"},  # Path to Python source files
    cmake_args=[
        "-DSKBUILD=ON",  # Ensure CMake recognizes it's being built with scikit-build
    ],
    python_requires="==3.11",
)
