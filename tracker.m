%% detect - main 
clear
% build: mexOpenCV tracker_mex.cpp -L/usr/lib -lopencv_aruco -I/usr/include/opencv2 -I/usr/include/opencv -I/usr/include
% mexOpenCV tracker_mex.cpp -L~/opencv310/lib/ -lopencv_aruco.3.1.0 -I/usr/include

cam = webcam;

h = imshow( snapshot(cam) );

% while true
    
    im = snapshot(cam);
    
    try
        trakced_im = track(im);
        set(h,'Cdata',tracked_im);
        drawnow;
    catch
%         break;
    end
    
% end% while true

clear cam;