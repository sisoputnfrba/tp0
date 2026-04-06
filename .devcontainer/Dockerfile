FROM ghcr.io/raniagus/entorno-docker/ubuntu:22.04

ARG CSPEC_COMMIT=043089d9c55871526f1d6728af4d0febdbe8c38a
ARG COMMONS_VERSION=1.9.0

RUN useradd -m -s /bin/bash vscode \
    && echo "vscode ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/vscode \
    && chmod 0440 /etc/sudoers.d/vscode

RUN curl -L https://github.com/mumuki/cspec/archive/${CSPEC_COMMIT}.tar.gz \
    | tar -xz -C /tmp \
    && make -C /tmp/cspec-${CSPEC_COMMIT} debug install \
    && rm -rf /tmp/cspec-${CSPEC_COMMIT}

RUN curl -L https://github.com/sisoputnfrba/so-commons-library/archive/${COMMONS_VERSION}.tar.gz \
    | tar -xz -C /tmp \
    && make -C /tmp/so-commons-library-${COMMONS_VERSION} debug install \
    && rm -rf /tmp/so-commons-library-${COMMONS_VERSION}

USER vscode
