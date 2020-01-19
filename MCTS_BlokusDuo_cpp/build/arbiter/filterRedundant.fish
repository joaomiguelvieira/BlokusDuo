#!/bin/fish

if test (count $argv) -ge 1
  set logFolder $argv[1]
else
  set logFolder game_logs
end

set renameFolder "$logFolder.rename"
mkdir $renameFolder
set numberOfGames (count $logFolder/*.txt)
set differentGames 1

for i in (seq 1 $numberOfGames)
  set original 1

  for j in (seq $i $numberOfGames)
    if test "$i" -ne "$j"
      set difference (diff "$logFolder/game$i.txt" "$logFolder/game$j.txt")

      if string match -q "$difference" -- ""
        set original 0
        break
      end
    end
  end

  if test "$original" -eq "1"
    cp "$logFolder/game$i.txt" "$renameFolder/game$differentGames.txt"
    set differentGames (math $differentGames + 1)
  end
end