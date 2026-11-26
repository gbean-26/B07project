# AI-generated (Claude Code)
#
# !/usr/bin/env bash
# Plays many computer-vs-computer games and checks things that must always hold,
# since random moves make exact output comparison impossible:
#   - the program never crashes or hangs
#   - the computer never produces "Illegal move."
#
# Usage (from the project folder, inside WSL, after running make):
#   bash tests/computer_smoke.sh [games] [level] [moves]
#   defaults: 20 games, level 1, up to 300 moves per game

set -u
cd "$(dirname "$0")/.." || exit 1

GAMES=${1:-20}
LEVEL=${2:-1}
MOVES=${3:-300}

if [ ! -x ./chess ]; then
    echo "./chess not found, run make first"
    exit 1
fi

# failing games are saved here; cleared at the start of every run
outdir="tests/smoke_failures"
rm -rf "$outdir"
mkdir -p "$outdir"
input="$outdir/input.txt"

# one game: start it, then send "move" repeatedly (extra moves after the game ends are harmless)
{
    echo "game computer$LEVEL computer$LEVEL"
    for ((i = 0; i < MOVES; i++)); do echo "move"; done
} > "$input"

fail=0; mate=0; stale=0; unfinished=0

for ((g = 1; g <= GAMES; g++)); do
    out="$outdir/level${LEVEL}_game$g.out"
    timeout 20 ./chess < "$input" > "$out" 2>&1
    code=$?

    reason=""
    if [ "$code" -ne 0 ]; then
        reason="exit code $code (crash, or timeout if 124)"
    elif grep -q "Illegal move." "$out"; then
        reason="computer made an illegal move"
    fi

    if grep -q "Checkmate!" "$out"; then ((mate++))
    elif grep -q "Stalemate!" "$out"; then ((stale++))
    else ((unfinished++))
    fi

    if [ -n "$reason" ]; then
        ((fail++))
        echo "FAIL game $g: $reason -> $out"
    else
        rm -f "$out"   # keep only failing games
    fi
done

echo "----"
echo "level $LEVEL, $GAMES games, up to $MOVES moves each"
echo "checkmate: $mate  stalemate: $stale  unfinished: $unfinished"
echo "failed: $fail"
if [ "$fail" -gt 0 ]; then
    echo "failing game outputs are in $outdir"
    exit 1
fi
rm -rf "$outdir"
echo "all passed"
