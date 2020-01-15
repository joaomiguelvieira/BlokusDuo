#!/bin/fish

if test (count $argv) -ge 1
  set logFolder $argv[1]
else
  set logFolder game_logs
end

set testsPassed 0
set testsFailed 0
set player1Wins 0
set player2Wins 0
set gameDraws 0

for gameLog in $logFolder/*.txt
	set result (./blokus-host < $gameLog | grep "Both pass!")
  set winner (./blokus-host < $gameLog | grep "Tiles:")

	if string match -q "Both pass!" -- "$result"
    echo "INFO: test $gameLog passed!" 
		set testsPassed (math $testsPassed + 1)

    if string match -q "*Player 1*" -- "$winner"
      set player1Wins (math $player1Wins + 1)
    else if string match -q "*Player 2*" -- "$winner"
      set player2Wins (math $player2Wins + 1)
    else
      set gameDraws (math $gameDraws + 1)
    end
	else
		echo "ERROR: test $gameLog failed!"
		set testsFailed (math $testsFailed + 1)
	end
end

set totalTests (math $testsPassed + $testsFailed)

set differentGames

set numberOfGames (count $logFolder/*.txt)

for i in (seq 1 $numberOfGames)
  set original 1

  for j in (seq $i $numberOfGames)
    if test "$i" -ne "$j"
      if string match -q (diff $gameLogs/game$i.txt $gameLogs/game$j.txt) -- ""
        set original 0
        break
      end
    end
  end

  if test "$original" -eq "1"
    set differentGames (math $differentGames + 1)
  end
end


echo "========== SUMMARY =========="
echo "Different games: $differentGames"
echo "-----------------------------"
echo "Player 1 victories: $player1Wins"
echo "Player 2 victories: $player2Wins"
echo "Game draws: $gameDraws"
echo "-----------------------------"
echo "Tests passed $testsPassed/$totalTests"
