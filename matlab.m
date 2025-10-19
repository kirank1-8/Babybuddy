clear; clc;

% Replace COM port with your ESP32 port
s = serialport("COM5",115200);
flush(s);
disp("Reading data...");

hr=[]; spo2=[]; doppler=[]; vib=[]; mood={};

figure;
while true
    try
        line = readline(s);  % Read one line
        values = split(line, ',');  % Split CSV
        
        % Only process valid lines
        if numel(values) >= 5
            hr(end+1) = str2double(values{1});
            spo2(end+1) = str2double(values{2});
            doppler(end+1) = str2double(values{3});
            vib(end+1) = str2double(values{4});
            mood{end+1} = strtrim(values{5});

            % Plot live data
            subplot(3,1,1); plot(hr,'r'); title('Heart Rate'); ylabel('BPM');
            subplot(3,1,2); plot(doppler,'b'); title('Doppler Motion');
            subplot(3,1,3); plot(vib,'k'); title('Vibration');
            drawnow;
        end
    catch ME
        warning("Error reading line: %s", ME.message);
    end
end
