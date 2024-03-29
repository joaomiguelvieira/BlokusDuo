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
h1 = histogram(n_pieces_placed_log);
h1.FaceAlpha = 1;
xlabel('Number of pieces placed');
ylabel('Frequency');
xlim([min(n_pieces_placed_log)-.5 max(n_pieces_placed_log)+.5]);
set(gca,'FontSize',10);
saveas(gcf,'n_pieces_placed','epsc');

% Wins for each player
figure('Position', [699, 259, 300, 300]);
X = categorical({'Player 1', 'Player 2', 'Draws'});
Y = [player1Wins player2Wins gameDraws];
b1 = bar(X, Y, 'BarWidth', 0.5);
b1.FaceColor = [0 0.4470 0.7410];
b1.FaceAlpha = 1;
xlabel('Winner');
ylabel('Frequency');
set(gca,'FontSize',10);
saveas(gcf,'wins','epsc');

% Score player
figure('Position', [699, 259, 300, 300]);
h2 = histogram(scores(:,1));
h2.FaceAlpha = 1;
xlabel('Score');
ylabel('Frequency');
xlim([min(scores(:,1))-.5 max(scores(:,1))+.5]);
set(gca,'FontSize',10);
saveas(gcf,'score_player_1','epsc');
figure('Position', [699, 259, 300, 300]);
h3 = histogram(scores(:,2));
h3.FaceAlpha = 1;
xlabel('Score');
ylabel('Frequency');
xlim([min(scores(:,2))-.5 max(scores(:,2))+.5]);
set(gca,'FontSize',10);
saveas(gcf,'score_player_2','epsc');

% Simulations per round
figure('Position', [699, 259, 600, 300]);
b2 = bar(0:1:size(simulations_log,1) - 1, simulations_log(:,[1,3]), 'stacked');
b2(1).FaceColor = [0 0.4470 0.7410];
set(gca, 'YScale', 'log');
set(gca, 'YGrid', 'on', 'XGrid', 'off');
hold on;
plot(0:1:size(simulations_log,1) - 1, simulations_log(:,2), 'k-*');
xlabel('Round');
ylabel('Number of simulations');
legend('Minimum', 'Maximum', 'Average', 'Location', 'southoutside', 'Orientation', 'Horizontal');
xlim([-.5, 37.5]);
set(gca,'FontSize',10);
saveas(gcf,'simulations_per_round','epsc');