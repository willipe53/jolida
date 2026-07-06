#!/usr/bin/env bash
# Point this repo at version-controlled hooks in .githooks/
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

if ! git rev-parse --git-dir >/dev/null 2>&1; then
  echo "install-git-hooks: not a git repository" >&2
  exit 1
fi

chmod +x .githooks/pre-commit
git config core.hooksPath .githooks

echo "Git hooks installed (core.hooksPath=.githooks)"
echo "Pre-commit will format markdown tables and run markdownlint / py_compile on staged files."
echo "Run 'npm install' once if node_modules/ is missing (markdownlint-cli2)."
