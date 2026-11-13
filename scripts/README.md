Requirements:
  * Python 3 with `venv` and `pip`
  * [Doxygen](https://www.doxygen.nl/), for the documentation
  * CMake and a C/C++ compiler, for the build step (see the [top-level README](../README.md))
  * The Python packages in [third_party/requirements.txt](../third_party/requirements.txt);
    that file is the only list of package versions

Installing the Python packages (a Python virtual environment is recommended, so the
packages do not mix with the system Python):
  ~~~~
    python3 -m venv ~/.venv
    source ~/.venv/bin/activate
    python3 -m pip install -r ../third_party/requirements.txt
  ~~~~
  * This is needed once. On Windows (cmd), create it with `python -m venv %USERPROFILE%\.venv`
    and activate it with `%USERPROFILE%\.venv\Scripts\activate`.

Generating code and documentation, from this folder:
  ~~~~
    source ~/.venv/bin/activate
    python3 ./run.py
  ~~~~
  * If you use a virtual environment, activate it first in each new shell, as above.
    Without it, `run.py` cannot find the packages.
  * Generated headers are written to **include**, generated sources to **source**, and the
    documentation to **docs** (HTML in **docs/html**).
  * The version is read from the most recent git tag.
  * `--!build` skips the CMake build; `--!html` and `--!rst` skip the documentation.
    Run `python3 ./run.py --help` for all options.

Documentation is generated from the YaML and the programming guides using Doxygen, Breathe and Sphinx.
