This is repository made for reading a wired XBOX controller input and printing 3 bytes that describe value of buttons and the Left thumbstick.<br/>
***NOTICE***
D-PAD, START, SELECT,and the right thumbstcik values are not included because adding those needs another 3 bytes. 
But they can be added if required<br/>
**FIRST BYTE [Buttons]**
Byte Number | #0 | #1 | #2 | #3 | #4 | #5 | #6 | #7 
--- | --- | --- | --- |--- |--- |--- |--- |--- 
Button | A | B | X | Y | Left Shoulder | Right Shoulder | Right Trigger | Left Trigger 
<br />
The seccond byte is a signed 8_bit intiger that holds Y values. Negative values show Down direction and positive values are Up<br/>
The third byte is a signed 8_bit intiger that holds X values. Negative values show Left direction and positive values are Right<br/>
