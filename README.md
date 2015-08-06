simple-viwer-recorder
===

Usage:
---
> * 1.start in shell    
        ./simple-viwer-recorder
        

> * 2.run the binary continously. **Note**:You can change the .sh file to run the binary in a different way
        ./test_sensor.sh
    
    
> * 3.you can make the occupancy rate of CPU cores 100% to make the error is easy to  seen. **Note**:if CPU`s core is four, you should start four processes.
        ./CPU & 
    
> * 4.
        Esc:   the simple-viwer-recorder will exit when recording 300 frames, approximately 10 seconds. If you want exit, you can press Esc to exit.  
        C:     if you want to continue play and record, you can press c to make it continue.
        1:     see the depth frame
        2:     see the color frame
        3:     see the mixed frame
