% Cleanup
clearvars
close all

% Load logs and set variables
load n_pieces_placed_log.txt;
player1Wins = 291;
player2Wins = 767;
gameDraws = 37;
load scores.txt
load simulations_log.txt;

% Analyse and plot results
% Number of pieces placed
figure('Position', [699, 259, 300, 300]);
histogram(n_pieces_placed_log);
xlabel('Number of pieces placed');
ylabel('Frequency');

% Wins for each player
figure('Position', [699, 259, 300, 300]);
X = categorical({'Player 1', 'Player 2', 'Draws'});
Y = [player1Wins player2Wins gameDraws];
bar(X, Y);
ylabel('Frequency');

% Score player
figure('Position', [699, 259, 300, 300]);
histogram(scores(:,1));
figure('Position', [699, 259, 300, 300]);
histogram(scores(:,2));

% Simulations per round
figure('Position', [699, 259, 600, 300]);
bar(0:1:size(simulations_log,1) - 1, simulations_log(:,[1,3]), 'stacked');
set(gca, 'YScale', 'log');
set(gca, 'YGrid', 'on', 'XGrid', 'off');
hold on;
plot(0:1:size(simulations_log,1) - 1, simulations_log(:,2), 'b-^');
xlabel('Round');
ylabel('Number of simulations');
legend('Minimum', 'Maximum', 'Average', 'Location', 'southoutside', 'Orientation', 'Horizontal');