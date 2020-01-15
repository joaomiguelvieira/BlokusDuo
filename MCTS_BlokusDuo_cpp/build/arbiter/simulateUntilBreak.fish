#!/bin/fish

if test (count $argv) -ge 1
  mkdir $argv[1]
  set logFolder $argv[1]
else
  set logFolder game_logs_until_break
end

set i 1
while true
  ../MCTS_BlokusDuo_cpp > "$logFolder/game$i.txt"
  set result (./blokus-host < $logFolder/game$i.txt | grep "Both pass!")

  if string match -q "Both pass!" -- "$result"
    echo "INFO: test $argv[1].$i passed!"
  else
    echo "ERROR: test $argv[1].$i failed! Exiting..."
    break
  end

  set i (math $i + 1)
end
