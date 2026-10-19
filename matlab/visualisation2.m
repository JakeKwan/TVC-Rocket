% Visualisation script for post flight data.

%% Data
clear;
data = readtable("C:\Users\jakek\Desktop\rocket\py\datalog.csv");

timeS = data{:, "timeUs"} * 1e-6;
accel = data{:, ["accelX", "accelY", "accelZ"]};
gyro = data{:, ["gyroX", "gyroY", "gyroZ"]};
altitude = data{:, "altitude"};
rpy = data{:, ["roll", "pitch", "yaw"]};
xPID = data{:, ["xPIDError", "xPIDOutput"]};
zPID = data{:, ["zPIDError", "zPIDOutput"]};

dt = timeS(2) - timeS(1);

%% Graphs
figure(1);
viewer = poseplot;
title('Pose Plot');

samplerate = 50; % hz
xlimit = 5; % s
maxpoints = samplerate * xlimit;

figure(2);
clf;
ax = subplot(2,2,1);
gAccelX = animatedline('Parent', ax, 'Color', 'r', 'MaximumNumPoints', maxpoints);
gAccelY = animatedline('Parent', ax, 'Color', 'g', 'MaximumNumPoints', maxpoints);
gAccelZ = animatedline('Parent', ax, 'Color', 'b', 'MaximumNumPoints', maxpoints);
xlabel(ax, 'Time');
ylabel(ax, 'Acceleration (g)');
ax.YLimitMethod = 'padded';
title(ax, 'Raw Acceleration (X,Y,Z)');
grid(ax, 'on');
legend(ax, {'X','Y','Z'});

% Gyroscope animated plot
ax2 = subplot(2,2,2);
gGyroX = animatedline('Parent', ax2, 'Color', 'r', 'MaximumNumPoints', maxpoints);
gGyroY = animatedline('Parent', ax2, 'Color', 'g', 'MaximumNumPoints', maxpoints);
gGyroZ = animatedline('Parent', ax2, 'Color', 'b', 'MaximumNumPoints', maxpoints);
xlabel(ax2, 'Time');
ylabel(ax2, 'Gyro (deg/s)');
ax2.YLimitMethod = 'padded';
title(ax2, 'Raw Gyroscope (X,Y,Z)');
grid(ax2, 'on');
legend(ax2, {'X','Y','Z'});

% RPY
ax3 = subplot(2,2,3);
roll = animatedline('Parent', ax3', 'Color', 'r', 'MaximumNumPoints', maxpoints);
pitch = animatedline('Parent', ax3', 'Color', 'g', 'MaximumNumPoints', maxpoints);
yaw = animatedline('Parent', ax3', 'Color', 'b', 'MaximumNumPoints', maxpoints);
xlabel(ax3, 'Time');
ylabel(ax3, 'Angle (deg)');
ax3.YLimitMethod = 'padded';
title(ax3, 'RPY');
grid(ax3, 'on');
legend(ax3, {'Roll','Pitch','Yaw'});

% Altitude
ax4 = subplot(2,2,4);
gAltitude = animatedline('Parent', ax4, 'MaximumNumPoints', maxpoints);
xlabel(ax4, 'Time');
ylabel(ax4, 'Altitude (m)');
ax4.YLimitMethod = 'padded';
title(ax4, 'Altitude');
grid(ax4, 'on');
legend(ax4, {'Altitude'});

% Link x-axes for synchronized zoom/pan
linkaxes([ax, ax2, ax3, ax4], 'x');

% Pose plot
% figure(2);

%% Animation
for ii = 1:length(timeS)
    t = timeS(ii);

    % Update pose
    q = quaternion(eul2quat(rpy(ii,:)));
    viewer.Orientation = q;

    % Update graphs

    addpoints(gAccelX, t, accel(ii,1));
    addpoints(gAccelY, t, accel(ii,2));
    addpoints(gAccelZ, t, accel(ii,3));
    addpoints(gGyroX,  t, gyro(ii,1));
    addpoints(gGyroY,  t, gyro(ii,2));
    addpoints(gGyroZ,  t, gyro(ii,3));
    addpoints(roll, t, rad2deg(rpy(ii,1)));
    addpoints(pitch,t, rad2deg(rpy(ii,2)));
    addpoints(yaw,  t, rad2deg(rpy(ii,3)));
    addpoints(gAltitude, t, altitude(ii));

    ax.XLim = t + [-xlimit 0.1*xlimit];
    ax2.XLim = ax.XLim;

    pause(dt);
end