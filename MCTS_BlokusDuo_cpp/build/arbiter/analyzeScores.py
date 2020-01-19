numberOfFiles = 1095

with open("scores.txt", "w") as log:
  for i in range(1, numberOfFiles + 1):
    with open("win_logs/game" + str(i) + ".txt") as file:
      for line in file:
        scorePlayer1 = -int(line.split("/")[0].split(" ")[-2])
        scorePlayer2 = -int(line.split("/")[1].split(" ")[1].split(",")[0])
        log.write(str(scorePlayer1) + " " + str(scorePlayer2) + "\n")
