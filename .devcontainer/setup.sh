#!/usr/bin/env bash
set -euo pipefail

/opt/cs50/bin/postCreateCommand

# Some official starter executables target x86-64, even on an ARM workstation.
# Docker Desktop supplies emulation; this supplies their Linux runtime.
if [ "$(uname -m)" = aarch64 ]; then
    if ! dpkg-query -W libc6-amd64-cross >/dev/null 2>&1; then
        sudo apt-get update -qq
        sudo env DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends libc6-amd64-cross
    fi
    printf '%s\n' 'export QEMU_LD_PREFIX=/usr/x86_64-linux-gnu' | sudo tee /etc/profile.d/cs50x-local.sh >/dev/null
fi

echo 'CS50x local environment ready.'
