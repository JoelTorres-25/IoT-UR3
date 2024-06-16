function [bit,finalFrame,lines] = BrazoNaranja(videoFrame)
A= videoFrame;
[BW,~] = generadorMascaraNaranja(A);
im6 = imfill(BW,"holes");
j1 = bwareaopen(im6,300);
BW3 = bwmorph(j1,"skel",25);
[H,theta,rho] = hough(BW3);
peaks = houghpeaks(H,1);
lines = houghlines(BW3,theta,rho,peaks);
numLines = length(lines);
bit = 0;
if numLines==1
    xy = [lines(1).point1; lines(1).point2];
    finalFrame= insertShape(A, 'Line', [xy(1,:) xy(2,:)], ...
                                     'LineWidth', 2, 'Color', 'red');
    X1 = lines.point1(1);
    Y1= lines.point1(2);
    X2 = lines.point2(1);
    Y2 = lines.point2(2);
    dy = Y2 - Y1;
    dx = X2 - X1;
    angulo_radianes = atan2(dy, dx);
    angulo_grados = rad2deg(angulo_radianes);
    %r =abs(angulo_radianes);
    g =abs(angulo_grados);
    if (g > -30) && (g < 30)
        bit = 0;
        %disp('Posición A');
    elseif (g > 70) && (g < 120)
        bit = 1;
        %disp('Posición B');
    end    
else
    finalFrame = videoFrame;
end

end