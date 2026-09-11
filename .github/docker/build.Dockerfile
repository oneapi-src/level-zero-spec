# syntax=docker/dockerfile:1.4
# BASE_REGISTRY is the registry path prefix, passed in from the CI_BASE_IMAGE repo
# variable so the internal registry hostname is not stored in this public repo.
# BASE_IMAGE is the image name and tag; change it here to move to another distro.
ARG BASE_REGISTRY
ARG BASE_IMAGE=ubuntu-24.04:master
FROM ${BASE_REGISTRY}${BASE_IMAGE}

SHELL ["/bin/bash", "-e", "-c"]

RUN --mount=type=cache,target=/var/cache/apt <<EOF
apt-get update
apt-get install -y \
  build-essential \
  ca-certificates \
  cmake \
  doxygen \
  elfutils \
  git \
  python3 \
  python3-pip \
  python3-venv \
  universal-ctags \
  vtable-dumper
EOF

# Install Python dependencies into a virtualenv so we get the correct versions
# as specified in third_party/requirements.txt rather than the older versions
# provided by the Ubuntu apt packages (e.g. sphinx-book-theme 0.1.7 vs >= 1.1.2).
COPY third_party/requirements.txt /tmp/requirements.txt
RUN python3 -m venv /opt/spec-venv && \
    /opt/spec-venv/bin/pip install --upgrade pip && \
    /opt/spec-venv/bin/pip install -r /tmp/requirements.txt

# Put the venv on PATH so sphinx-build and other tools are found as bare commands.
# This ensures older checkouts (e.g. spec-base on master) work correctly before
# the generate_docs.py sys.executable fix has been merged.
ENV PATH="/opt/spec-venv/bin:$PATH"
