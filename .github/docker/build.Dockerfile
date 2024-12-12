# syntax=docker/dockerfile:1.4
FROM amr-registry.caas.intel.com/level-zero-linux-compute/ubuntu:24.10

SHELL ["/bin/bash", "-e", "-c"]

RUN --mount=type=cache,target=/var/cache/apt <<EOF
rm /etc/apt/apt.conf.d/docker-clean
apt-get update
apt-get install -y \
  ca-certificates \
  doxygen \
  git \
  python3 \
  python3-mako \
  python3-pip \
  python3-yaml \
  python3-sphinx-book-theme \
  sphinx
EOF

# RUN pip install Mako==1.1.0 PyYAML==5.2 sphinx-book-theme
