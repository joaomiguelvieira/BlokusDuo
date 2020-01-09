#!/bin/fish

set testsPassed 0
set testsFailed 0

for i in (seq 1 100)
	set result (./blokus-host < game_logs3/game$i.txt | grep "Both pass!")

	if string match -q "Both pass!" -- "$result"
		set testsPassed (math $testsPassed + 1)
	else
		echo "TEST $i FAILED!"
		set testsFailed (math $testsFailed + 1)
	end
end

set totalTests (math $testsPassed + $testsFailed)

echo "PASSED $testsPassed/$totalTests"
