#/usr/bin/env zsh

# This script creates a sandbbox for testing small programs.
set -euo pipefail

formatted_date=$(date +"%Y-%m-%d-%H-%M-%S")
sandbox_dir="sandbox/$formatted_date"
mkdir -p "$sandbox_dir"
