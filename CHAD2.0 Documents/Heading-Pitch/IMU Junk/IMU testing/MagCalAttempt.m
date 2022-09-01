%input the cvs file and save it as T

T = readtable('sdcard00.csv')
D = table2array(T(:,1:3))
RC = table2array(T(:, 4:6))

[A, b, extp] = magcal(D)

C = (D-b)*A;

figure(1)
plot3(D(:,1),D(:,2),D(:,3),'LineStyle','none','Marker','X','MarkerSize',6,'MarkerFaceColor','blue')
hold on
grid(gca,'on')
plot3(C(:,1),C(:,2),C(:,3),'LineStyle','none','Marker', ...
            'o','MarkerSize',6,'MarkerFaceColor','r') 

%plot3(RC(:,1),RC(:,2),RC(:,3),'LineStyle','none','Marker', ...
 %           'v','MarkerSize',6,'MarkerFaceColor','g') 


axis equal
xlabel('uT')
ylabel('uT')
zlabel('uT')
legend('Uncalibrated Samples', 'Calibrated Samples','Location', 'southoutside')
title("Uncalibrated vs Calibrated" + newline + "Magnetometer Measurements")
hold off
