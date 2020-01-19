#!/bin/fish

if test (count $argv) -ge 1
  set logFolder $argv[1]
else
  set logFolder game_logs
end

for file in $logFolder/*.txt
  set nLines (wc $file)
  set nLines (string split " " -- $nLines)[7]
  echo $nLines >> n_pieces_placed_log.txt
end
