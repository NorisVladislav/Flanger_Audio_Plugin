close all; clear; clc;

%Flanger-ul este un efect audio de modulație obținut prin amestecarea unui semnal original cu o versiune întârziată a acestuia, 
% unde întârzierea variază periodic

% Încarcă semnalul audio
[x, Fs] = audioread("Caramitru44kScurt.wav");

% Parametrii Flanger
BL = 0.7; % Blend - mix între semnalul original și cel întârziat
FF = 0.7; % Feedforward - cât din semnalul întârziat se adaugă la semnalul de ieșire
FB = 0.7; % Feedback - cât din semnalul întârziat este recirculat în buffer

depth_sec = 0.002; % Intarzierea aplicata semnalului (2 ms)
depth_samples = round(depth_sec * Fs); % Conversia intarzierii in sample-uri - Adâncime în sample-uri
mod_freq = 0.3; % Frecvența de modulație (Hz) între 0.1 și 1 Hz - Cat de repede variaza intarzierea

% Buffer circular pentru delay - Memoreaza esantionele intarziate 
buffer_size = depth_samples; % Mărimea bufferului este egală cu adâncimea maximă
buffer = zeros(buffer_size, 1);
buffer_index = 1; % Pozitia din buffer

% Semnalul procesat
y = zeros(size(x));

% Oscilator pentru întârzierea variabilă
n_samples = length(x); % Memoreaza numarul de esantioane din X
mod_signal = (sin(2 * pi * mod_freq * (1:n_samples) / Fs) + 1) / 2; % Semnal sinusoidal care variaza între 0 și 1, variaza sinusoidal mod_freq pentru a obtine Flanger
mod_signal = smoothdata(mod_signal, 'gaussian', 50); % Rectifica variatiile semnalului de intarziere

for n = 1:n_samples
    % Calculează întârzierea curentă
    current_delay = round(mod_signal(n) * depth_samples); % Current_delay = numarul de esantioane care variaza sinusoidal
    
    % Indexul pentru întârziere (buffer circular)
    delay_index = buffer_index - current_delay;
    if delay_index < 1
        delay_index = delay_index + buffer_size;
    end
    
    % Extrage semnalul întârziat din buffer
    delayed_sample = buffer(delay_index);
    
    % Aplică formula efectului Flanger
    y(n) = BL * x(n) + FF * delayed_sample;
    
    % Actualizează buffer-ul cu feedback
    buffer(buffer_index) = x(n) + FB * delayed_sample;
    
    % Incrementeaza indexul bufferului
    buffer_index = buffer_index + 1;
    if buffer_index > buffer_size
        buffer_index = 1;
    end
end

% Redă semnalul original și cel procesat
sound(x, Fs);
pause(length(x)/Fs + 1);
sound(y, Fs);
