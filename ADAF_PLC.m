% Crear el objeto serial
s = serialport('COM3', 115200); % Sustituir 'COM3' por el puerto correcto en tu sistema

% Configurar propiedades adicionales si es necesario
configureTerminator(s, "LF"); % Configurar el terminador de línea (si es necesario)

% Enviar datos al ESP32
write(s, '1', 'char'); % Enviar '1' para encender el LED
pause(1); % Esperar 1 segundo
write(s, '0', 'char'); % Enviar '0' para apagar el LED

clear s; % Esto cierra y elimina el objeto serial