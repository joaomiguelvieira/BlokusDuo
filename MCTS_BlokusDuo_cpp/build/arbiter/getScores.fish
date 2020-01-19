#!/bin/fish

if test (count $argv) -ge 1
  set logFolder $argv[1]
else
  set logFolder game_logs
end

for file in $logFolder/*.txt
  set filename (basename $file)
  ./blokus-host < $file | grep "Tiles:" > "win_logs/$filename"
end
