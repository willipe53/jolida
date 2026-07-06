#!/usr/bin/env bash
# Run markdownlint-cli2 without npx (avoids npm "devdir" warnings from Cursor sandbox).
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

unset npm_config_devdir

BIN="$ROOT/node_modules/.bin/markdownlint-cli2"
if [[ ! -x "$BIN" ]]; then
  echo "lint-markdown: installing markdownlint-cli2 (one-time)..." >&2
  npm install --no-fund --no-audit >/dev/null
fi

exec "$BIN" "$@"
