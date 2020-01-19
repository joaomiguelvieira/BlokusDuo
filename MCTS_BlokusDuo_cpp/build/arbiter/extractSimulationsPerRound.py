numberOfFiles = 1000

sim = dict()
for i in range(0, 38):
  sim[i] = list()

for i in range(1, numberOfFiles + 1):
  with open("sim_logs/game" + str(i) + ".txt") as file:
    for line in file:
      turn = line.split(" ")[1]
      sims = line.split(" ")[3]

      sim[int(turn)].append(int(sims))

with open("simulations_log.txt", "w") as file:
  for turn in sim:
    file.write(str(min(sim[turn])) + " " + str(sum(sim[turn]) / len(sim[turn])) + " " + str(max(sim[turn])) + "\n")
